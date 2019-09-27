#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* func1(void *param);

int main()
{
	int i, ret;
	pthread_t t1;
	printf("main thread started!\n");
	ret = pthread_create(&t1, NULL, func1, NULL);
	
	printf("press enter to cancel the thread!\n");
	getchar();
	
	printf("main thread cancelling the thread!\n");
	pthread_cancel(t1);

	printf("press enter to exit main thread!\n");
	getchar();
	printf("main thread completed.\n");
	return 0;
}

void* func1(void *param)
{
	int i;
	for(i=0; i<10; i++)
	{
		printf("func1: %d\n", i);
		sleep(1);
	}
	return NULL;
}

