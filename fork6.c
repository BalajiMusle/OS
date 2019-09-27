#include <stdio.h>
#include <unistd.h>

/*
Zombie Process:
	- If child process is terminated before parent process and parent is not reading its exit status, then child process become zombie.
	- In this state, process is terminated i.e. all its resources are released and its exit value is written into its PCB. The PCB is not yet released.
*/

int main()
{
	int i, ret;
	printf("program started!!\n");
	ret = fork();
	if(ret == 0)
	{	// child process
		for(i=0; i<10; i++)
		{
			printf("child : %d\n", i);
			sleep(1);
		}
	}
	else
	{	// parent process
		for(i=0; i<20; i++)
		{
			printf("parent : %d\n", i);
			sleep(1);
		}
	}
	printf("program completed!!\n");
	return 0;
}

// ps -t pts/0 -o pid,ppid,state,cmd

