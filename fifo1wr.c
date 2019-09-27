#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// writer process
int main()
{
	int fd;
	char buf[32];
	fd = open("desd_fifo", O_WRONLY);
	if(fd < 0)
	{
		perror("failed to open fifo");
		_exit(1);
	}
	
	printf("writer: enter a string : \n");
	scanf("%s", buf);

	write(fd, buf, strlen(buf)+1);

	close(fd);
	return 0;
}

