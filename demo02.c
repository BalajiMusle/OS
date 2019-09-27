#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	char *filepath = "/home/pi/hello.txt";
	int fd, cnt;
	char buf[32];
	fd = open(filepath, O_RDONLY);
	
	while( (cnt = read(fd, buf, 32)) > 0 )
	{
		write(1, buf, cnt);
	}

	close(fd);
	_exit(0);
}

