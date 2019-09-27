#include <stdio.h>
#include <unistd.h>

void* func1(void *param);
void* func2(void *param);

int main()
{
	int i;
	func1(NULL);
	func2(NULL);
	for(i=0; i<10; i++)
	{
		printf("main : %d\n", i);
		sleep(1);
	}
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

void* func2(void *param)
{
	int i;
	for(i=0; i<10; i++)
	{
		printf("func2: %d\n", i);
		sleep(1);
	}
	return NULL;
}

