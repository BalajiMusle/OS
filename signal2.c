#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/*
signal() UNIX syscall --> register signal handler
	arg1: signal number (int number or macro)
	arg2: address of the signal handler function --> void ___(int) 
		-- function pointer --> typedef void (*sighandler_t)(int);
	returns: old signal handler (in success).
*/

//step1: implement signal handler
void sigint_handler(int sig)
{
	printf("signal caught : %d\n", sig);
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

