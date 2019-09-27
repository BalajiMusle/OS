#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

/*
sigaction() Linux syscall --> register signal handler
syntax: ret = sigaction(signum, &sa_new, &sa_old);
	arg1: singal number
	arg2: struct sigaction --> in param
		sa_handler member --> function pointer -- void (*)(int);
		*sa_sigaction member --> function pointer -- void (*)(int,siginfo_t*,void*);
		*sa_flags member --> extra info
			0 --> sa_handler contains address of signal handler function
			SA_SIGINFO --> sa_sigaction contains address of signal handler function
		sa_mask member --> signal mask to be used while execution of the handler.
	arg3: struct sigaction --> out param
	returns: 0 on success.
*/

//step1: implement signal handler
void sigint_handler(int sig, siginfo_t *si, void *param)
{
	printf("signal caught : %d\n", sig);
	printf("sender process id : %d\n", si->si_pid);
}

int main()
{
	int i=0, ret;
	struct sigaction sa_in, sa_out;
	//step2: register signal handler
	memset(&sa_out, 0, sizeof(struct sigaction));
	memset(&sa_in, 0, sizeof(struct sigaction));
	sa_in.sa_sigaction = sigint_handler;
	sa_in.sa_flags = SA_SIGINFO;
	ret = sigaction(SIGINT, &sa_in, &sa_out);
	if(ret < 0)
	{
		perror("sigaction() failed");
		_exit(1);
	}

	while(1)
	{
		printf("running : %d\n", ++i);
		sleep(1);
	}
	return 0;
}

