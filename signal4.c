#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

//step1: implement signal handler --> SIGINT
void sigint_handler(int sig)
{
	printf("signal caught : %d\n", sig);
}

//step1: implement signal handler --> SIGCHLD
void sigchld_handler(int sig)
{
	int s;
	waitpid(-1, &s, 0);
	printf("parent: child exit status = %d\n", WEXITSTATUS(s));
}

int main()
{
	int i=0, ret;
	struct sigaction sa_in, sa_out;
	//step2: register signal handler -- SIGINT
	memset(&sa_out, 0, sizeof(struct sigaction));
	memset(&sa_in, 0, sizeof(struct sigaction));
	sa_in.sa_handler = sigint_handler;
	ret = sigaction(SIGINT, &sa_in, &sa_out);
	if(ret < 0)
	{
		perror("sigaction() failed");
		_exit(1);
	}

	//step2: register signal handler -- SIGCHLD
	memset(&sa_out, 0, sizeof(struct sigaction));
	memset(&sa_in, 0, sizeof(struct sigaction));
	sa_in.sa_handler = sigchld_handler;
	ret = sigaction(SIGCHLD, &sa_in, &sa_out);
	if(ret < 0)
	{
		perror("sigaction() failed");
		_exit(1);
	}

	ret = fork();
	if(ret == 0)
	{	// child process
		for(i=0; i<10; i++)
		{
			printf("child : %d\n", i);
			sleep(1);
		}
		_exit(4);
	}
	else
	{	// parent process
		while(1)
		{
			printf("parent : %d\n", ++i);
			sleep(1);
		}
	}
	return 0;
}

