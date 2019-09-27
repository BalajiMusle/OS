#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
stack smashing: if undesired data is written on return address in stack frame of a function, then its stack frame is considered to be corrupted. This is called as "stack smashing".
*/
void fun()
{
	char arr[2], *ptr, i, f=2;
	printf("fun : &f = %u\n", &f);
	ptr = arr;
	for(i=0; i<10; i++)
	{
		printf("i = %d\n", i);
		*ptr++ = 'A'+i;
	}
}

int main()
{
	int m=1;
	printf("main : &m = %u\n", &m);
	// heap corruption: writing beyond dynamically allocated memory block
	char *ptr = (char*)malloc(8);
	strcpy(ptr, "sunbeam");
	printf("ptr = %s\n", ptr);
	ptr[8] = 'A';
	free(ptr);
	/*
	printf("main() starts!\n");
	fun();
	printf("main() ends!\n");
	*/
	return 0;
}

