#include <stdio.h>
#include <string.h>
#include <signal.h>

/*
sigsuspend(&mask);
	- 1. save the current signal mask (old).
	- 2. change signal mask of current process -- as given in arg (new).
	- 3. pause execution of the process until any unmasked signal (new mask) is received.
	- 4. reset the old signal mask (saved in step 1).

sigsuspend() set the mask temporarily i.e. until an unmasked signal is received by the process.
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
	sigset_t newmask;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigterm_handler;
	sigaction(SIGTERM, &sa, NULL);

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigalrm_handler;
	sigaction(SIGALRM, &sa, NULL);
	
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	sigaddset(&newmask, SIGTERM);

	printf("SIGINT & SIGTERM are masked ...\n");
	sigsuspend(&newmask);
	printf("Good Bye!!\n");

	return 0;
}


