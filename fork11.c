#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void work(char *name, int max)
{
	int i;
	for(i=0; i<max; i++)
	{
		printf("%s : %d\n", name, i);
		sleep(1);
	}
}

int main()
{
	int ret, s;
	ret = fork();
	if(ret == 0)
	{	// child1 process
		ret = fork();
		if(ret == 0)
		{	// child2 process
			ret = fork();
			if(ret == 0)
			{	// child3 process
				work("child3", 5);
				_exit(3);
			}
			else
			{	// child2
				work("child2", 5);
				waitpid(-1, &s, 0);
				printf("child2: child3 exit status = %d\n", WEXITSTATUS(s));
				_exit(2);
			}
		}
		else
		{	// child1
			work("child1", 5);
			waitpid(-1, &s, 0);
			printf("child1: child2 exit status = %d\n", WEXITSTATUS(s));
			_exit(1);
		}
	}
	else
	{	// parent process
		work("parent", 5);
		waitpid(-1, &s, 0);
		printf("parent: child1 exit status = %d\n", WEXITSTATUS(s));
	}
	return 0;
}









