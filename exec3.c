#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int ret, err, s, i;
	printf("parent started!\n");
	ret = fork();
	if(ret == 0)
	{	// child process
		err = execlp("child.out", "child.out", "one", "two", "three", "four", "five", NULL);
		if(err < 0)
		{
			perror("exec() failed");
			_exit(1);
		}
	}
	else
	{	// parent process
		for(i=0; i<3; i++)
		{
			printf("parent : %d\n", i);
			sleep(1);
		}
		// wait for completion of child
		// and collect its exit value.
		waitpid(-1, &s, 0);
		printf("parent: child exit status : %d\n", WEXITSTATUS(s));
	}
	printf("parent completed!\n");
	return 0;
}

