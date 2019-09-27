#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char *ptr;
	unsigned int size = 1 * 1024 * 1024 * 1024;
	unsigned int i, pagesize = sysconf(_SC_PAGESIZE);
	printf("page size = %d\n", pagesize);
	ptr = (char*) malloc(size);
	printf("base addr : %p\n", ptr);
	getchar();
	for(i=0; i<size; i+=pagesize)
		ptr[i] = 'A';
	getchar();
	return 0;
}

