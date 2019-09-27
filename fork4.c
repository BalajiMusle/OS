#include <stdio.h>
#include <unistd.h>

int main()
{
	int i, ret;
	printf("program started!!\n");
	ret = fork();
	if(ret == 0)
	{	// child process
		for(i=0; i<10; i++)
		{
			printf("child : %d\n", i);
			sleep(1);
		}
	}
	else
	{	// parent process
		for(i=0; i<10; i++)
		{
			printf("parent : %d\n", i);
			sleep(1);
		}
	}
	printf("program completed!!\n");
	return 0;
}

