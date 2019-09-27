#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY	0x2405

typedef struct shm
{
	int cnt;
}shm_t;

int main()
{
	int i, ret, s, shmid;
	shm_t *ptr;

	// create shared memory region
	shmid = shmget(SHM_KEY, sizeof(shm_t), IPC_CREAT | 0600);
	if(shmid < 0)
	{
		perror("shmget() failed");
		_exit(1);
	}

	// get pointer to object in shm region
	ptr = shmat(shmid, NULL, 0); // nattach=1
	if(ptr == (void*)-1)
	{
		perror("shmat() failed");
		_exit(2);
	}

	// mark shm for destroy (nattach=1)
	shmctl(shmid, IPC_RMID, NULL);
	
	// init counter to 0
	ptr->cnt = 0;

	ret = fork(); // nattach=2
	if(ret == 0)
	{	// child process -- incr 
		for(i=0; i<10; i++)
		{
			ptr->cnt++;
			printf("child : %d\n", ptr->cnt);
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
			ptr->cnt--;
			printf("parent : %d\n", ptr->cnt);
			sleep(1);
		}
		// parent waits for the child
		waitpid(-1, &s, 0);
		// print final count
		printf("final count = %d\n", ptr->cnt);
		// detach shm rgn
		shmdt(ptr); // nattach=0 ---> destroy shm
	}

	return 0;
}
