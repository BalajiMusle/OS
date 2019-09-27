#include <stdio.h>
#include <unistd.h>
#include <signal.h>

//step1: implement signal handler
void sigint_handler(int sig)
{
	printf("signal caught : %d\n", sig);
	printf("current process : %d\n", getpid());
}

int main()
{
	int i=0;
	//step2: register signal handler
	signal(SIGINT, sigint_handler);

	while(1)
	{
		printf("running : %d\n", ++i);
		sleep(1);
	}
	return 0;
}

