#include <stdio.h>
#include <pthread.h>

void* inc_thread(void *param);
void* dec_thread(void *param);

int cnt = 0;
pthread_mutex_t m;

int main()
{
	pthread_t it, dt;
	
	pthread_mutex_init(&m, NULL);

	pthread_create(&it, NULL, inc_thread, NULL);
	pthread_create(&dt, NULL, dec_thread, NULL);
	
	pthread_join(it, NULL);
	pthread_join(dt, NULL);
	
	printf("main : %d\n", cnt);

	pthread_mutex_destroy(&m);
	return 0;
}

void* inc_thread(void *param)
{
	int i;
	for(i=0; i<10; i++)
	{
		pthread_mutex_lock(&m);
		cnt++;
		printf("inc : %d\n", cnt);
		pthread_mutex_unlock(&m);
		sleep(1);
	}
	return NULL;
}

void* dec_thread(void *param)
{
	int i;
	for(i=0; i<10; i++)
	{
		pthread_mutex_lock(&m);
		cnt--;
		printf("dec : %d\n", cnt);
		pthread_mutex_unlock(&m);
		sleep(1);
	}
	return NULL;
}

