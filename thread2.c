#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int c=0;

void* func1(void *param);
void* func2(void *param);
void test(void);

int main()
{
	int i, ret;
	pthread_t t1, t2;
	
	ret = pthread_create(&t1, NULL, func1, NULL);
	ret = pthread_create(&t2, NULL, func2, NULL);

	for(i=0; i<10; i++)
	{
		test();
		printf("main : %d\n", i);
		sleep(1);
	}

	printf("c = %d\n", c);
	return 0;
}

void test(void)
{
	static int b = 0;
	int a = 0;
	a++;
	b++;
	c++;
}

void* func1(void *param)
{
	int i;
	for(i=0; i<10; i++)
	{
		test();
		printf("func1: %d\n", i);
		sleep(1);
	}
	return NULL;
}

void* func2(void *param)
{
	int i;
	for(i=0; i<10; i++)
	{
		test();
		printf("func2: %d\n", i);
		sleep(1);
	}
	return NULL;
}

