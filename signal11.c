#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void sigint_handler(int sig)
{
	printf("signal caught : %d\n", sig);
}

int main()
{
	int i=0, ret;
	struct sigaction sa_in, sa_out;
	char str[64];

	memset(&sa_in, 0, sizeof(struct sigaction));
	sa_in.sa_handler = sigint_handler;
	ret = sigaction(SIGINT, &sa_in, NULL);
	if(ret < 0)
	{
		perror("sigaction() failed");
		_exit(1);
	}

	printf("enter a string.\n");
	ret = read(1, str, sizeof(str));
	printf("read() returned : %d\n", ret);
	if(ret < 0)
	{
		perror("read() failed");
		switch(errno)
		{
		case EBADF:
			printf("invalid file desc in read() -- arg1\n");
			break;
		case EFAULT:
			printf("invalid buffer addr in read() -- arg2\n");
			break;
		case EINTR:
			printf("process blocked in read() is woken up by signal.\n");
			break;
		}
	}
	else
	{
		str[ret] = '\0';
		printf("you entered : %s\n", str);
	}
	return 0;
}

