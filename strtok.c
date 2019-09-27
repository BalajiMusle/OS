#include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "this,is,an,example,string";
	/*
	char *ptr;
	ptr = strtok(str, ",");
	printf("TOKEN : %s\n", ptr);	
	do
	{
		ptr = strtok(NULL, ",");
		printf("TOKEN : %s\n", ptr);
	}while(ptr != NULL);
	*/

	char* ptr;
	char* arr[12];
	int i=0;
	ptr = strtok(str, ",");
	arr[i++] = ptr;
	do
	{
		ptr = strtok(NULL, ",");
		arr[i++] = ptr;
	}while(ptr != NULL);
	
	for(i=0; arr[i]!=NULL; i++)
		printf("TOKEN %d -> %s\n", i, arr[i]);
	
	return 0;
}


