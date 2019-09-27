#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *ptr;
	unsigned int size = 1 * 1024 * 1024 * 1024;
	ptr = (char*) malloc(size);
	printf("base addr : %p\n", ptr);
	getchar();
	return 0;
}

