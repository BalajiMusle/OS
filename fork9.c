#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define CHILD_CNT 	5

// from one parent create multiple child processes (CHILD_CNT)

int main()
{
	int i, j, ret, pid, s;
	// create multiple child from same parent.
	for(i=1; i<=CHILD_CNT; i++)
	{
		ret = fork();
		if(ret == 0)
		{
			// each child is counting from 0-4 & then exitting
			for(j=0; j<5; j++)
			{
				printf("child%d -> %d\n", i, j);
				sleep(1);
			}
			_exit(i);
		}
	}
	// parent is counting from 0-2
	for(j=0; j<3; j++)
	{
		printf("parent -> %d\n", j);
		sleep(1);
	}

	// parent is waiting for all its child termination
	// and getting their exit values (to avoid zombies).
	for(i=1; i<=CHILD_CNT; i++)
	{
		pid = waitpid(-1, &s, 0);
		printf("child (%d) --> exit status = %d\n", pid, WEXITSTATUS(s));
	}
	return 0;
}


