#include <stdio.h>
#include <unistd.h>

int main()
{
	int ret;
	printf("program started!!\n");
	ret = fork();
	if(ret == 0)
	{	// child process
		printf("child: fork() returned : %d\n", ret);
		printf("child: child pid = %d\n", getpid());
		printf("child: child's parent pid = %d\n", getppid());
	}
	else
	{	// parent process
		printf("parent: fork() returned : %d\n", ret);
		printf("parent: parent pid = %d\n", getpid());
		printf("parent: parent's parent pid = %d\n", getppid());
	}
	printf("program completed!!\n");
	return 0;
}

