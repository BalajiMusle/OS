#include <unistd.h>

// stdin - 0	: standard input (terminal)
// stdout - 1	: standard output (terminal)
// stderr - 2	: standard error (terminal)

// _exit() syscall:
//	arg1: exit code

// write() syscall:
//	arg1: file descriptor
//	arg2: base address of variable
//	arg3: number of bytes to write
//	returns: number of bytes successfully written.

int main()
{
	write(1, "hello desd\n", 11);
	_exit(0);
	return 0;
}

