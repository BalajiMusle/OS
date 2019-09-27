#define _GNU_SOURCE
// _GNU_SOURCE --> macro to enable/access to kernel specific feature.

#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

int main()
{
	// c library function:
	//	uninitialize c library/runtime and then exit the application using syscall _exit()
	//exit(1);

	// system call:
	//	exit the application.
	//_exit(2);

	// syscall() -- system call that can call any syscall whose number & args are known.
	//	arg1: syscall number
	//	arg*: args to that syscall 
	//syscall(1, 3); // --> call _exit() syscall with value 3
	//syscall(SYS_exit, 3); // --> call _exit() syscall with value 3

	// inline x86 assembly
	asm("mov $1, %eax");
	asm("mov $4, %ebx");
	asm("int $0x80");
	return 0;
}

// echo $? used to see the exit value of last terminated program.
// 
