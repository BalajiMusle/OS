#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
	int ret, err, s, fd_out;
	printf("parent started!\n");
	ret = fork();
	if(ret == 0)
	{
		fd_out = open("out.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if(fd_out < 0)
		{
			perror("failed to open/create out.txt");
			_exit(2);
		}
		
		close(1); // close stdout
		dup(fd_out); // duplicate given fd on lowest numbered available file desc i.e. stdout(1).
		close(fd_out); // close fd

		err = execlp("ls", "ls", "-l", "-a", "-i", "/home", NULL);
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


