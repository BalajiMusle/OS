#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
wait(&s) UNIX syscall:
	- pause execution of parent process until (one of its) child is terminated.
	- collect exit value of the child from its pcb (into out param).
	- release the pcb of the child process.
	- returns: pid of child process whose exit value is collected.
		- -1 if no child present.

waitpid(pid,&s,flags) Linux syscall:
	- arg1: pid of child process (whose exit value is to be collected).
		- -1 : get exit value of any one child
	- arg2: out param -- collect the exit value.
	- arg3: extra info
		- 0 : no extra info.
		- WNOHANG : do not wait if child is not yet terminated, simply return with error code.
	- returns: pid of child process whose exit value is collected.
		- -1 on failure.

waitpid(-1, &s, 0);	same as wait(&s);
*/

int main()
{
	int i, ret, s;
	printf("program started!!\n");
	ret = fork();
	if(ret == 0)
	{	// child process
		for(i=0; i<10; i++)
		{
			printf("child : %d\n", i);
			sleep(1);
		}
		_exit(5);
	}
	else
	{	// parent process
		for(i=0; i<20; i++)
		{
			printf("parent : %d\n", i);
			sleep(1);
			if(i == 10)
			{
				wait(&s);
				printf("child exit status : %d\n", WEXITSTATUS(s));
			}
		}
	}
	printf("program completed!!\n");
	return 0;
}

// ps -t pts/0 -o pid,ppid,state,cmd

