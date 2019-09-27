#include <unistd.h>
#include <stdio.h>

int main()
{
	int ret, fd[2];
	char buf[32];
	// create a pipe
	// fd[0] -- read file desc of pipe
	// fd[1] -- write file desc of pipe
	ret = pipe(fd);
	if(ret < 0)
	{
		perror("pipe() failed");
		_exit(1);
	}
	// write in the pipe -- fd[1]
	write(fd[1], "HELLO", 6);
	// read from the pipe -- fd[0]
	read(fd[0], buf, sizeof(buf));
	printf("Read From Pipe: %s\n", buf);
	// close both file descs of pipe
	close(fd[1]);
	close(fd[0]);
	return 0;
}

