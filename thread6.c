#include <stdio.h>
#define _GNU_SOURCE
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <sys/syscall.h>

int gettid()
{
	long ret = syscall(SYS_gettid);
	return ret;
}

void* func1(void *param);

void sigterm_handler(int sig)
{
	// this handler is executed by the thread to which signal was sent
	printf("signal SIGTERM handled : %d\n", sig);
	printf("sigterm_handler --> PID : %d\n", getpid());
	printf("sigterm_handler --> TID : %d\n", gettid());
	// terminate the thread to which signal was sent	
	pthread_exit(NULL);
}

int main()
{
	int i, ret;
	pthread_t t1;
	struct sigaction sa;
	
	printf("main --> PID : %d\n", getpid());
	printf("main --> TID : %d\n", gettid());

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigterm_handler;
	ret = sigaction(SIGTERM, &sa, NULL); 

	printf("main thread started!\n");
	ret = pthread_create(&t1, NULL, func1, NULL);
	
	printf("press enter to send signal to the thread!\n");
	getchar();
	
	printf("main thread sending signal to the thread!\n");
	pthread_kill(t1, SIGTERM);

	printf("press enter to exit main thread!\n");
	getchar();
	printf("main thread completed.\n");
	return 0;
}

void* func1(void *param)
{
	int i;
	printf("func1 --> PID : %d\n", getpid());
	printf("func1 --> TID : %d\n", gettid());
	for(i=0; i<100; i++)
	{
		printf("func1: %d\n", i);
		sleep(1);
	}
	return NULL;
}

