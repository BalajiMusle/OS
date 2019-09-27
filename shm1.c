#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct shm
{
	int cnt;
}shm_t;

// create shm_t obj into data sect.
shm_t sm;

int main()
{
	int i, ret, s;
	shm_t *ptr;

	// get pointer to object
	ptr = &sm;
	// init counter to 0
	ptr->cnt = 0;

	ret = fork();
	if(ret == 0)
	{	// child process -- incr 
		for(i=0; i<10; i++)
		{
			ptr->cnt++;
			printf("child : %d\n", ptr->cnt);
			sleep(1);
		}
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
	}

	return 0;
}
