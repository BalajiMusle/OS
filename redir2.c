#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
	int ret, err, s, fd;
	printf("parent started!\n");
	ret = fork();
	if(ret == 0)
	{
		// input redirection
		fd = open("in.txt", O_RDONLY);
		if(fd < 0)
		{
			perror("failed to open in.txt");
			_exit(2);
		}
		close(0); // close stdin
		dup(fd); // duplicate fd on stdin
		close(fd); // close file desc

		// output redirection
		fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fd < 0)
		{
			perror("failed to open out.txt");
			_exit(2);
		}
		close(1); // close stdout
		dup(fd); // duplicate fd on stdout
		close(fd); // close file desc

		// error redirection
		fd = open("err.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fd < 0)
		{
			perror("failed to open err.txt");
			_exit(2);
		}
		dup2(fd, 2); // close stderr & duplicate fd on stderr
		close(fd); // close file desc

		err = execl("./divide.out", "divide.out", NULL);
		if(err < 0)
		{
			perror("exec() failed");
			_exit(1);
		}
	}
	waitpid(-1, &s, 0);
	printf("child exit status : %d\n", WEXITSTATUS(s));
	printf("parent completed!\n");
	return 0;
}


