#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// reader process
int main()
{
	int fd;
	char buf[32];
	fd = open("desd_fifo", O_RDONLY);
	if(fd < 0)
	{
		perror("failed to open fifo");
		_exit(1);
	}
	
	printf("reader: waiting for data...\n");
	read(fd, buf, sizeof(buf));
	printf("reader: data received : %s\n", buf);

	close(fd);
	return 0;
}

