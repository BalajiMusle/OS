#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
/*
int arr[]={10,5,4,8};

void* minimum(void* param);

int main()
{
	int *res,*re;
	pthread_t t1;
	pthread_create(&t1,NULL,minimum,NULL);
	pthread_join(t1,&res);
	re=(int*)res;
	printf("%d\n",*re);
	_exit(0);
}

void* minimum(void* param)
{
	int i,j;
//	int* params=(int*) param;
	for(i=0;i<4;i++)
	{
		for(j=0;j<3;j++)
		{
			int temp;
			if(arr[j]>arr[j+1])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}	
	pthread_exit(arr);
}
*/


void* minimum(void* param);

int main()
{
	int arr[5];
	int *res,*re,i;
	pthread_t t1;
	printf("Enter 5 no::\n");
	for(i=0;i<5;i++)
	{
		scanf("%d",&arr[i]);
	}
	pthread_create(&t1,NULL,minimum,arr);
	pthread_join(t1,&res);
	re=(int*)res;
	printf("smallest no is::%d\n",*re);
	_exit(0);
}

void* minimum(void* param)
{
	int i,j,*arr;
	arr=(int*)param;
//	int* params=(int*) param;
	for(i=0;i<4;i++)
	{
		for(j=0;j<3;j++)
		{
			int temp;
			if(arr[j]>arr[j+1])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}	
	pthread_exit(arr);
}
