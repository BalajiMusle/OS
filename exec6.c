#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[])
{
	int ret, err, s, i;
	printf("parent started!\n");
	ret = fork();
	if(ret == 0)
	{	// child process
		char *args[] = { "child2.out", NULL };
		err = execve("./child2.out", args, envp);
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

/*
To pass env vars of parent (or modified env vars) to child explicitly use execle() or execve().
*/


