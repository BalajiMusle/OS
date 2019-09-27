#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY	0x2405
#define SEM_KEY	0x1506

typedef struct shm
{
	int cnt;
}shm_t;


typedef union semun 
{
	int val;
	struct semid_ds *buf; 
	unsigned short *array;
	struct seminfo *__buf; 
}semun_t;


int main()
{
	int i, ret, s, shmid, semid;
	shm_t *ptr;
	semun_t su;
	struct sembuf ops[1];

	// create semaphore with single counter.
	semid = semget(SEM_KEY, 1, IPC_CREAT | 0600);
	if(semid < 0)
	{
		perror("semget() failed");
		_exit(1);
	}

	// initialize semaphore counter = 1
	su.val = 1;
	ret = semctl(semid, 0, SETVAL, su);
	if(ret < 0)
	{
		perror("semctl() SETVAL failed");
		_exit(1);
	}

	// create shared memory region
	shmid = shmget(SHM_KEY, sizeof(shm_t), IPC_CREAT | 0600);
	if(shmid < 0)
	{
		perror("shmget() failed");
		semctl(semid, 0, IPC_RMID);
		_exit(1);
	}

	// get pointer to object in shm region
	ptr = shmat(shmid, NULL, 0); // nattach=1
	if(ptr == (void*)-1)
	{
		perror("shmat() failed");
		_exit(2);
	}

	// init counter to 0
	ptr->cnt = 0;

	ret = fork(); // nattach=2
	if(ret == 0)
	{	// child process -- incr 
		for(i=0; i<10; i++)
		{
			// P(s);
			ops[0].sem_num = 0;
			ops[0].sem_op = -1;
			ops[0].sem_flg = 0;
			semop(semid, ops, 1);
			
			ptr->cnt++;
			printf("child : %d\n", ptr->cnt);
			
			// V(s);
			ops[0].sem_num = 0;
			ops[0].sem_op = +1;
			ops[0].sem_flg = 0;
			semop(semid, ops, 1);
			
			sleep(1);
		}
		// detach shm rgn
		shmdt(ptr); // nattach=1
		_exit(0);
	}
	else
	{	// parent process -- decr
		for(i=0; i<10; i++)
		{
			// P(s);
			ops[0].sem_num = 0;
			ops[0].sem_op = -1;
			ops[0].sem_flg = 0;
			semop(semid, ops, 1);
			
			ptr->cnt--;
			printf("parent : %d\n", ptr->cnt);

			// V(s);
			ops[0].sem_num = 0;
			ops[0].sem_op = +1;
			ops[0].sem_flg = 0;
			semop(semid, ops, 1);
			
			sleep(1);
		}
		// parent waits for the child
		waitpid(-1, &s, 0);
		// print final count
		printf("final count = %d\n", ptr->cnt);
		// detach shm rgn
		shmdt(ptr); // nattach=0
		// destroy shm -- destroyed immediately because nattach=0
		shmctl(shmid, IPC_RMID, NULL);
		// destroy semaphore object
		semctl(semid, 0, IPC_RMID);
	}

	return 0;
}
