#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define SEM_KEY	0x2809

typedef union semun 
{
	int val;
	struct semid_ds *buf; 
	unsigned short *array;
	struct seminfo *__buf; 
}semun_t;

int main()
{
	int i, ret, s;
	int semid;
	semun_t su;
	struct sembuf ops[1];

	// create a semaphore with single counter.
	semid = semget(SEM_KEY, 1, IPC_CREAT | 0600);
	if(semid < 0)
	{
		perror("semget() failed");
		_exit(1);
	}
	
	// init sema counter = 0
	su.val = 0;
	ret = semctl(semid, 0, SETVAL, su);

	ret = fork();
	if(ret == 0)
	{
		char *str = "SUNBEAM\n";
		for(i=0; str[i]!='\0'; i++)
		{
			putchar(str[i]);
			fflush(stdout);
			sleep(1);
		}
		// V(s)
		ops[0].sem_num = 0;
		ops[0].sem_op = +1;
		ops[0].sem_flg = 0;
		ret = semop(semid, ops, 1);
		
		_exit(0);
	}
	else
	{
		char *str = "INFOTECH\n";
		// P(s);
		ops[0].sem_num = 0;
		ops[0].sem_op = -1;
		ops[0].sem_flg = 0;
		ret = semop(semid, ops, 1);

		for(i=0; str[i]!='\0'; i++)
		{
			putchar(str[i]);
			fflush(stdout);
			sleep(1);
		}

		waitpid(-1, &s, 0);

		// destroy semaphore
		semctl(semid, 0, IPC_RMID);
	}
	return 0;
}

