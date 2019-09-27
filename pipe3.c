#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int pid1, pid2, err, s, ret, fd[2];
	printf("parent started...\n");
	// create pipe
	ret = pipe(fd);
	if(ret < 0)
	{
		perror("pipe() failed");
		_exit(3);
	}
	
	// execute child1 -- who
	pid1 = fork();
	if(pid1 == 0)
	{	// child1 process -- writer process
		// close read end of pipe
		close(fd[0]);

		// dup pipe write end on stdout & close pipe write end
		dup2(fd[1], 1);
		close(fd[1]);

		err = execlp("who", "who", NULL);
		if(err < 0)
		{
			perror("exec() failed");
			_exit(1);
		}
	}

	// execute child2 -- wc
	pid2 = fork();
	if(pid2 == 0)
	{	// child2 process -- reader process
		// close write end of pipe
		close(fd[1]);
	
		// dup pipe read end on stdin & close pipe read end
		dup2(fd[0], 0);
		close(fd[0]);

		err = execlp("wc", "wc", NULL);
		if(err < 0)
		{
			perror("exec() failed");
			_exit(2);
		}
	}

	// parent -- close both ends of pipe
	close(fd[1]);
	close(fd[0]);

	// parent -- waiting for both child processes
	waitpid(pid1, &s, 0);
	waitpid(pid2, &s, 0);
	printf("parent completed...\n");
	return 0;
}

