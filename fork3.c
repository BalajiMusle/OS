#include <stdio.h>
#include <unistd.h>

int main()
{
	int i, ret;
	printf("program started!!\n");
	ret = fork();
	if(ret == 0)
	{	// child process
		for(i=0; i<1000; i++)
			printf("child : %d\n", i);
	}
	else
	{	// parent process
		for(i=0; i<1000; i++)
			printf("parent : %d\n", i);
	}
	printf("program completed!!\n");
	return 0;
}

