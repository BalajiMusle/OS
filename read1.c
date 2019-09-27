#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
int fd = open("filepath", flags, mode);
	- arg1: path of file to be opened.
	- arg2: flags/info for opening the file.
		- O_RDONLY, O_WRONLY, O_RDWR
		- O_TRUNC, O_APPEND, O_CREAT
	- arg3: file perms of new file (only if 2nd arg contains O_CREAT)
		- octal number (e.g. 0644 --> 110 100 100 --> rw-(u) r--(g) r--(o))
	- returns: file descriptor i.e. int val to identify the file in the process.
		- this file desc should be passed for all other file system calls like read(), close(), ...
		- if syscall fails, it returns -1.

ret = read(fd, buf, len);
	- read() is a blocking call i.e. until read() is completed current thread is stopped.
	- arg1: file desc of file to be read.
	- arg2: base addr of buffer where data should be read into.
	- arg3: number of bytes to be read.
	- ret: number of bytes successfully read.
		if failed, it returns -1.

close(fd);
	- arg1: file desc of file to be closed.
*/

int main(int argc, char *argv[])
{
	int fd;
	int cnt, ret;
	char buf[512];

	if(argc != 2)
	{
		fprintf(stderr, "syntax: ./%s <file path>.\n", argv[0]);
		exit(1);
	}

	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		perror("open() failed");
		exit(2);
	}

	while( ( cnt = read(fd, buf, sizeof(buf)) ) > 0)
	{
		ret = write(1, buf, cnt);
	}

	close(fd);
	return 0;
}










