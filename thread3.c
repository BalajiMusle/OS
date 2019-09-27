#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// passing param to the thread.
// waiting for given thread.

void* print_table(void *param);

int main()
{
	pthread_t t1, t2, t3;
	printf("main thread started!\n");
	pthread_create(&t1, NULL, print_table, (void*)4);
	pthread_create(&t2, NULL, print_table, (void*)14);
	pthread_create(&t3, NULL, print_table, (void*)24);
	// calling thread will wait for given thread.
	printf("main thread is waiting for other threads!\n");
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	printf("main thread completed!\n");
	return 0;
}

void* print_table(void *param)
{
	int i, num = (int)param;
	for(i=1; i<=10; i++)
	{
		printf("%d * %d = %d\n", num, i, num * i);
		sleep(1);
	}
	return NULL;
}

