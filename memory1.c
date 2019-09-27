#include <stdio.h>

int num1 = 10;
int num2 = 20;

int main()
{
	int num3 = 30;
	printf("&main = %p\n", main);
	printf("&num1 = %p\n", &num1);
	printf("&num2 = %p\n", &num2);
	printf("&num3 = %p\n", &num3);
	return 0;
}

