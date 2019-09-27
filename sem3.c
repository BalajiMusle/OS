#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>

// ------------------------------------------------------------------

// circular queue implementation -- data structures
#define MAX	10

typedef struct cirbuf
{
	char buf[MAX];
	int front, rear;
	int cnt;
}cirbuf_t;

void cirbuf_init(cirbuf_t *cb)
{
	cb->cnt = 0;
	cb->front = -1;
	cb->rear = -1;
	memset(cb->buf, 0, sizeof(cb->buf));
}

void cirbuf_push(cirbuf_t *cb, int val)
{
	cb->rear = (cb->rear + 1) % MAX;
	cb->buf[cb->rear] = val;
	cb->cnt++;
}

int cirbuf_pop(cirbuf_t *cb)
{
	cb->front = (cb->front + 1) % MAX;
	cb->cnt--;
	return cb->buf[cb->front];
}

int cirbuf_full(cirbuf_t *cb)
{
	return cb->cnt == MAX;
}

int cirbuf_empty(cirbuf_t *cb)
{
	return cb->cnt == 0;
}

// ------------------------------------------------------------------

#define SHM_KEY	0x1234

// struct cirbuf_t --> shared memory

int shmid;
cirbuf_t *ptr;
// ------------------------------------------------------------------

#define SEM_KEY	0x5678

typedef union semun 
{
	int val;
	struct semid_ds *buf; 
	unsigned short *array;
	struct seminfo *__buf; 
}semun_t;

int semid;
#define FIL_IDX		0
#define MUT_IDX		1
#define EMP_IDX		2

// ------------------------------------------------------------------

void sigint_handler(int sig)
{
	// destroy shared memory
	shmdt(ptr);
	shmctl(shmid, IPC_RMID, NULL);
	// destroy semaphore
	semctl(semid, 0, IPC_RMID);
	_exit(0);
}

void sigchld_handler(int sig)
{
	int s;
	// parent wait for child & avoid zombie
	waitpid(-1, &s, 0);
}

// ------------------------------------------------------------------

int main()
{
	int ret, val;
	semun_t su;
	unsigned short init_vals[] = {0, 1, MAX}; // filled=0, mutex=1, empty=MAX
	struct sembuf ops[2];
	struct sigaction sa;
	// register signal handlers -- SIGINT, SIGCHLD
	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigint_handler;
	ret = sigaction(SIGINT, &sa, NULL);

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigchld_handler;
	ret = sigaction(SIGCHLD, &sa, NULL);
	
	// create semaphore with 3 counters (filled, mutex, empty)
	semid = semget(SEM_KEY, 3, IPC_CREAT | 0600);
	if(semid < 0)
	{
		perror("semget() failed");
		_exit(1);
	}

	// initialize semaphore counters: filled=0, mutex=1, empty=MAX
	su.array = init_vals;
	ret = semctl(semid, 0, SETALL, su);
	
	// create shared memory -- cirbuf_t in shared memory region
	shmid = shmget(SHM_KEY, sizeof(cirbuf_t), IPC_CREAT | 0600);
	if(shmid < 0)
	{
		perror("shmget() failed");
		semctl(semid, 0, IPC_RMID);
		_exit(2);
	}

	// get pointer to shared memory (attach) 
	ptr = (cirbuf_t*) shmat(shmid, NULL, 0);
	if(ptr == (void*)-1)
	{
		perror("shmat() failed");
		semctl(semid, 0, IPC_RMID);
		_exit(3);
	}

	ret = fork();
	if(ret == 0)
	{	// child process -- producer
		//sleep(5);
		while(1)
		{
			// P(empty), P(mutex)
			ops[0].sem_num = EMP_IDX;	
			ops[0].sem_op = -1;	
			ops[0].sem_flg = 0;	
			ops[1].sem_num = MUT_IDX;	
			ops[1].sem_op = -1;	
			ops[1].sem_flg = 0;	
			ret = semop(semid, ops, 2);
			
			// generate random number and add into cirbuf
			val = rand() % 100;
			cirbuf_push(ptr, val);
			printf("WR : %d\n", val);
			sleep(1);
			
			// V(mutex), V(filled)
			ops[0].sem_num = MUT_IDX;	
			ops[0].sem_op = +1;	
			ops[0].sem_flg = 0;	
			ops[1].sem_num = FIL_IDX;	
			ops[1].sem_op = +1;	
			ops[1].sem_flg = 0;	
			ret = semop(semid, ops, 2);
		}

		shmdt(ptr);
		_exit(0);
	}
	else
	{	// parent process -- consumer
		//sleep(15);
		while(1)
		{
			// P(filled), P(mutex)
			ops[0].sem_num = FIL_IDX;	
			ops[0].sem_op = -1;	
			ops[0].sem_flg = 0;	
			ops[1].sem_num = MUT_IDX;	
			ops[1].sem_op = -1;	
			ops[1].sem_flg = 0;	
			ret = semop(semid, ops, 2);
			
			// get/pop data from cirbuf and print it
			val = cirbuf_pop(ptr);
			printf("RD : %d\n", val);
			sleep(1);
			
			// V(mutex), V(empty)
			ops[0].sem_num = MUT_IDX;	
			ops[0].sem_op = +1;	
			ops[0].sem_flg = 0;	
			ops[1].sem_num = EMP_IDX;	
			ops[1].sem_op = +1;	
			ops[1].sem_flg = 0;	
			ret = semop(semid, ops, 2);
		}

	}

	return 0;
}

