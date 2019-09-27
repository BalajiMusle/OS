#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

// common handler for two different signals.

//step1: implement signal handler
void sig_handler(int sig)
{
	//printf("signal caught : %d\n", sig);
	switch(sig)
	{
	case SIGINT:
		printf("SIGINT caught...\n");
		break;
	case SIGTERM:
		printf("SIGTERM caught...\n");
		break;
	}
}

int main()
{
	int i=0, ret;
	struct sigaction sa_in, sa_out;
	//step2: register signal handler -- SIGINT
	memset(&sa_out, 0, sizeof(struct sigaction));
	memset(&sa_in, 0, sizeof(struct sigaction));
	sa_in.sa_handler = sig_handler;
	ret = sigaction(SIGINT, &sa_in, &sa_out);
	if(ret < 0)
	{
		perror("sigaction() failed");
		_exit(1);
	}

	//step2: register signal handler -- SIGTERM
	memset(&sa_out, 0, sizeof(struct sigaction));
	ret = sigaction(SIGTERM, &sa_in, &sa_out);
	if(ret < 0)
	{
		perror("sigaction() failed");
		_exit(1);
	}

	while(1)
	{
		printf("parent : %d\n", ++i);
		sleep(1);
	}
	return 0;
}

