#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int i;
	for(i=0; envp[i]!=NULL; i++)
		printf("child2 : %s\n", envp[i]);
	return 0;
}

/*
- Environment Variables -- Important information about the system.

- New Env variables can be created or existing variables can be modified on shell using export command.
	export VAR1=VALUE1

- All environment variables can be printed using "env" command.
	env

- Environment variables can be accessed in a C program via 3rd arg of main() i.e. envp[].

- Environment variables of parent are inherited to the child process.

- New environment variables can be given to a new program using env command:
	env VAR2=VALUE2 VAR3=VALUE3 ./child2.out
*/



