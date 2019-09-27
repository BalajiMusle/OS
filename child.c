#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i;
	for(i=0; i<argc; i++)
	{
		printf("child : %s\n", argv[i]);
		sleep(1);
	}
	return 7;
}

