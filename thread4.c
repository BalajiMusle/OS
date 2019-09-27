#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// passing multiple params to the thread
// wait for completion of the thread
// collect result from the thread

// returning result from thread
//	- way1: return value of thread function
//	- way2: pthread_exit(void*)
/*
struct input
{
	int num1;
	int num2;
};

void* addition(void *param);

int main()
{
	struct input in = { 20, 30 };
	void *out;
	int res;
	pthread_t ta;
	printf("main: thread started!\n");
	pthread_create(&ta, NULL, addition, &in);
	printf("main: thread waiting for addition to complete!\n");
	pthread_join(ta, &out);
	res = (int)out;
	printf("main: result = %d\n", res);
	return 0;
}

void* addition(void *param)
{
	struct input *ptr = (struct input*)param;
	int res;
	res = ptr->num1 + ptr->num2;
	sleep(5);
	//return (void*)res;
	pthread_exit((void*)res);
}
*/

struct input
{
	int num1;
	int num2;
};

void* addition(void *param);

int main()
{
	struct input in = { 22, 33 };
	void *out;
	int *res;
	pthread_t ta;
	printf("main: thread started!\n");
	pthread_create(&ta, NULL, addition, &in);
	printf("main: thread waiting for addition to complete!\n");
	pthread_join(ta, &out);
	res = (int*)out;
	printf("main: result = %d\n", *res);
	free(res);
	return 0;
}

void* addition(void *param)
{
	struct input *ptr = (struct input*)param;
	int *res = (int*)malloc(sizeof(int));
	*res = ptr->num1 + ptr->num2;
	sleep(5);
	return res;
	//pthread_exit(res);
}













