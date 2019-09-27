#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// counting max number of child processes
// that can be created using fork()

int main()
{
	int cnt=0, ret, s;
	printf("parent started!\n");
	// create multiple child processes
	// until fork() fails.
	while(1)
	{
		ret = fork();
		if(ret == -1)
			break;
		if(ret == 0)
		{	// child process
			sleep(10);
			_exit(0);
		}
		else
		{	// parent process
			cnt++;
		}
	}
	// print max child count
	printf("child count = %d\n", cnt);
	
	// collect exit values of all child
	// processes to avoid zombies.
	while(waitpid(-1, &s, 0) > 0)
		;

	printf("parent terminated!\n");
	return 0;
}


