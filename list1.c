#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

/*
DIR *dp = opendir("dirpath");
	arg1: path of dir
	return: on success returns dir pointer.
		on failure, returns NULL.

struct dirent *de = readdir(dp);
	arg1: dir pointer
	returns: one dentry pointer.
		- if end of dir is reached, returns NULL.

struct dirent:
	d_ino
	d_name

closedir(dp);
	arg1: dir pointer
*/

int main(int argc, char *argv[])
{
	DIR *dp;
	struct dirent *de;
	if(argc != 2)
	{
		fprintf(stderr, "syntax: %s <dir path>\n", argv[0]);
		exit(1);
	}
	
	dp = opendir(argv[1]);
	if(dp == NULL)
	{
		perror("dir open failed");
		exit(2);
	}

	while( (de = readdir(dp)) != NULL )
	{
		printf("%lu\t%s\n", de->d_ino, de->d_name);
	}

	closedir(dp);
	return 0;
}
