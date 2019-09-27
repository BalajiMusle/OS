#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int ret, err, s, i;
	printf("parent started!\n");
	ret = fork();
	if(ret == 0)
	{	// child process --> ls -l -a /home
		err = execlp("ls", "ls", "-l", "-a", "/home", NULL);
		if(err < 0)
		{
			perror("exec() failed");
			_exit(1);
		}
	}
	else
	{	// parent process
		// wait for completion of child and collect its exit value.
		waitpid(-1, &s, 0);
		printf("parent: child exit status : %d\n", WEXITSTATUS(s));
	}
	printf("parent completed!\n");
	return 0;
}

