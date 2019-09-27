#include <stdio.h>
#include <string.h>
#include <signal.h>

/*
ret = sigprocmask(how, &sigmask, &oldsigmask);
	arg1: how = SIG_SETMASK
	arg2: sigmask = sig mask to be set
	arg3: oldsigmask = out param (old signal mask)
	returns: 0 on success.

sigprocmask() set signal mask of process permanently (i.e. until changed again explicitly).
*/

void sigint_handler(int sig)
{
	printf("SIGINT handled...\n");
}

void sigterm_handler(int sig)
{
	printf("SIGTERM handled...\n");
}

void sigalrm_handler(int sig)
{
	printf("SIGALRM handled...\n");
}

int main()
{
	int i=0;
	struct sigaction sa;
	sigset_t newmask, oldmask;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigterm_handler;
	sigaction(SIGTERM, &sa, NULL);

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigalrm_handler;
	sigaction(SIGALRM, &sa, NULL);
	
	sigemptyset(&oldmask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	sigaddset(&newmask, SIGTERM);

	sigprocmask(SIG_SETMASK, &newmask, &oldmask);
	printf("SIGINT & SIGTERM are masked ...\n");
	
	getchar();

	printf("Old mask is reset (no signals masked ...\n");
	sigprocmask(SIG_SETMASK, &oldmask, NULL);

	getchar();

	printf("Good Bye!!\n");

	return 0;
}


