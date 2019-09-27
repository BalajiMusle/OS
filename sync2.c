#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// ------------------------------------------------------------------

// circular queue implementation -- data structures
#define MAX	10

typedef struct cirbuf
{
	char buf[MAX];
	int front, rear;
	int cnt;
}cirbuf_t;

void cirbuf_init(cirbuf_t *cb)
{
	cb->cnt = 0;
	cb->front = -1;
	cb->rear = -1;
	memset(cb->buf, 0, sizeof(cb->buf));
}

void cirbuf_push(cirbuf_t *cb, int val)
{
	cb->rear = (cb->rear + 1) % MAX;
	cb->buf[cb->rear] = val;
	cb->cnt++;
}

int cirbuf_pop(cirbuf_t *cb)
{
	cb->front = (cb->front + 1) % MAX;
	cb->cnt--;
	return cb->buf[cb->front];
}

int cirbuf_full(cirbuf_t *cb)
{
	return cb->cnt == MAX;
}

int cirbuf_empty(cirbuf_t *cb)
{
	return cb->cnt == 0;
}

void* writer(void *param);
void* reader(void *param);

cirbuf_t cb;

sem_t fil, emp;
pthread_mutex_t mut;

int main()
{
	pthread_t wt, rt;

	pthread_mutex_init(&mut, NULL);
	sem_init(&fil, 0, 0);
	sem_init(&emp, 0, MAX);
	
	pthread_create(&wt, NULL, writer, NULL);
	pthread_create(&rt, NULL, reader, NULL);
	
	getchar();
	
	sem_destroy(&emp);
	sem_destroy(&fil);
	pthread_mutex_destroy(&mut);
	return 0;
}

void* writer(void *param)
{
	int val;
	//sleep(5);
	while(1)
	{
		// P(emp);
		sem_wait(&emp);
		// lock(mut);
		pthread_mutex_lock(&mut);

		// generate random number and add into cirbuf
		val = rand() % 100;
		cirbuf_push(&cb, val);
		printf("WR : %d\n", val);

		// unlock(mut);
		pthread_mutex_unlock(&mut);
		// V(fil);
		sem_post(&fil);
		
		sleep(1);
	}
}

void* reader(void *param)
{
	int val;
	//sleep(15);
	while(1)
	{
		// P(fil);
		sem_wait(&fil);
		// lock(mut);
		pthread_mutex_lock(&mut);

		// get/pop data from cirbuf and print it
		val = cirbuf_pop(&cb);
		printf("RD : %d\n", val);
	
		// unlock(mut);
		pthread_mutex_unlock(&mut);
		// V(emp);
		sem_post(&emp);
		
		sleep(1);
	}
}




