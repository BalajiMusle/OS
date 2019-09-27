#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	char cmd[512];
	char *ptr;
	char *args[32];
	int i, ret, err, s;

	while(1)
	{
		// input a command from user.
		printf("cmd> ");
		gets(cmd);
		// split command into array of cmd line args
		i=0;
		ptr = strtok(cmd, " ");
		args[i++] = ptr;
		do {
			ptr = strtok(NULL, " ");
			args[i++] = ptr;
		} while(ptr != NULL);

		// check if command is internal and execute it.
		if(strcmp(args[0], "cd") == 0)
			chdir(args[1]);
		else if(strcmp(args[0], "exit") == 0)
			_exit(0);
		else
		{
			// execute external command
			ret = fork();
			if(ret == 0)
			{
				err = execvp(args[0], args);
				if(err < 0)
				{
					perror("bad command");
					_exit(1);
				}
			}
			else
				waitpid(-1, &s, 0);
		}
	}
	return 0;
}


