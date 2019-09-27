#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int ret, fd[2], s;
	char buf1[32], buf2[32];
	// create a pipe
	// fd[0] -- read file desc of pipe
	// fd[1] -- write file desc of pipe
	ret = pipe(fd);
	if(ret < 0)
	{
		perror("pipe() failed");
		_exit(1);
	}

	ret = fork();
	if(ret == 0)
	{	// child process -- writer process
		// close read end of pipe
		close(fd[0]);
		// write in the pipe -- fd[1]
		printf("child: enter string : ");
		scanf("%s", buf1);
		write(fd[1], buf1, strlen(buf1)+1);
		// close write end of pipe
		close(fd[1]);
		_exit(0);
	}
	else
	{	// parent process -- reader process
		// close write end of pipe
		close(fd[1]);
		// read from the pipe -- fd[0]
		printf("parent: waiting for child data...\n");
		read(fd[0], buf2, sizeof(buf2));
		printf("parent: read from pipe: %s\n", buf2);
		// close read end of pipe
		close(fd[0]);	
		// get exit status of child process
		waitpid(-1, &s, 0);
	}
	return 0;
}

