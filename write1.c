#include <stdio.h>
#include <unistd.h>

int main()
{
	int ret;
	ret = printf("Hello 1.\n"); // 9
	printf("printf() returned : %d\n", ret);
	ret = fprintf(stdout, "Hello 2.\n"); // 9
	printf("fprintf() returned : %d\n", ret);
	ret = write(1, "Hello 3.\n", 9); // 9   
		/* 
		x86 arch:
			mov %ebx, 1
			mov %ecx, str
			mov %edx, 9
			int 0x80
			mov ret, %eax
		*/
		/*
		ARM arch:
			ldr r0, #1
			ldr r1, =str
			ldr r2, #9
			swi 0
			str r0, [ret]
		*/
	printf("write() returned : %d\n", ret);
	return 0;
}

