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
	int i, c, ret, s;
	int semid;
	semun_t su;
	struct sembuf ops[1];

	// create a semaphore with single counter.
	semid = semget(SEM_KEY, 2, IPC_CREAT | 0600);
	if(semid < 0)
	{
		perror("semget() failed");
		_exit(1);
	}

	// init sema counter = 0
	su.val = 0;
	ret = semctl(semid, 0, SETVAL, su);
	su.val = 1;
	ret = semctl(semid, 1, SETVAL, su);

	ret = fork();
	if(ret == 0)
	{
		for(c=0; c<5; c++)
		{
			char *str = "SUNBEAM\n";
			// P(m)
			ops[0].sem_num = 1;
			ops[0].sem_op = -1;
			ops[0].sem_flg = 0;
			ret = semop(semid, ops, 1);

			for(i=0; str[i]!='\0'; i++)
			{
				putchar(str[i]);
				fflush(stdout);
				sleep(1);
			}
			// V(m,s)
			ops[0].sem_num = 1;
			ops[0].sem_op = +1;
			ops[0].sem_flg = 0;
			ops[1].sem_num = 0;
			ops[1].sem_op = +1;
			ops[1].sem_flg = 0;
			ret = semop(semid, ops, 2);
		}
		_exit(0);
	}
	else
	{
		for(c=0; c<5; c++)
		{
			char *str = "INFOTECH\n";
			// P(m,s);
			ops[0].sem_num = 1;
			ops[0].sem_op = -1;
			ops[0].sem_flg = 0;
			ops[1].sem_num = 0;
			ops[1].sem_op = -1;
			ops[1].sem_flg = 0;
			ret = semop(semid, ops, 2);

			for(i=0; str[i]!='\0'; i++)
			{
				putchar(str[i]);
				fflush(stdout);
				sleep(1);
			}
			
			// V(m)
			ops[0].sem_num = 1;
			ops[0].sem_op = +1;
			ops[0].sem_flg = 0;
			ret = semop(semid, ops, 1);
		}
		waitpid(-1, &s, 0);

		// destroy semaphore
		semctl(semid, 0, IPC_RMID);
	}
	return 0;
}

