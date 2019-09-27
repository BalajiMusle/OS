#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

//step1: implement signal handler
void sigint_handler(int sig)
{
	int i;
	for(i=0; i<5; i++)
	{
		printf("signal SIGINT caught : %d\n", sig);
		sleep(1);
	}
}

void sigterm_handler(int sig)
{
	int i;
	for(i=0; i<5; i++)
	{
		printf("signal SIGTERM caught : %d\n", sig);
		sleep(1);
	}
}


int main()
{
	int i=0, ret;
	struct sigaction sa_in;
	//step2: register signal handler
	memset(&sa_in, 0, sizeof(struct sigaction));
	sa_in.sa_handler = sigint_handler;
	sigfillset(&sa_in.sa_mask);
		// --> masks all signals while executing signal handler of this signal SIGINT
	sigaction(SIGINT, &sa_in, NULL);

	memset(&sa_in, 0, sizeof(struct sigaction));
	sa_in.sa_handler = sigterm_handler;
	sigaction(SIGTERM, &sa_in, NULL);
	
	while(1)
	{
		printf("running : %d\n", ++i);
		sleep(1);
	}
	return 0;
}

