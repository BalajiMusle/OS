#include <stdio.h>

int main()
{
	int i, num, den, res;
	for(i=1; i<=3; i++)
	{
		scanf("%d%d", &num, &den);
		if(den == 0)
		{
			fprintf(stderr, "num=%d, den=%d, denominator cannot be zero.\n", num, den);
		}
		else
		{
			res = num / den;
			printf("num=%d, den=%d, res=%d.\n", num, den, res);
		}
	}
	return 0;
}

