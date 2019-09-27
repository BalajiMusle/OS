#include <stdio.h>
#include <unistd.h>

/*
Orphan Process:
	- If parent of a process is terminated, that child process is referred as "Orphan Process".
	- The ownership of such process is taken by "init" process (pid=1).

init Process:
	- It is first process created during system booting.
	- It has pid = 1.
	- In modern kernel, this process is named as "systemd".
*/ 

int main()
{
	int i, ret;
	printf("program started!!\n");
	ret = fork();
	if(ret == 0)
	{	// child process
		for(i=0; i<20; i++)
		{
			printf("child : %d\n", i);
			sleep(1);
		}
	}
	else
	{	// parent process
		for(i=0; i<10; i++)
		{
			printf("parent : %d\n", i);
			sleep(1);
		}
	}
	printf("program completed!!\n");
	return 0;
}

// ps -t pts/0 -o pid,ppid,cmd

