
.data
##char *str = "hello desd\n";
.balign 4
str:	.asciz "hello desd\n"

## char buf[512];
#.balign 4
#buf:	.skip	512

.text
.arm

.balign 4

.globl main
.func main

.equ SYS_EXIT, 1
.equ SYS_WRITE, 4
.equ STDOUT, 1

main:
	# write(1, "hello desd\n", 11);
	mov r7, #SYS_WRITE
	mov r0, #STDOUT
	ldr r1, =str 
	mov r2, #11
	swi 0

	# _exit(0);
	mov r7, #SYS_EXIT
	mov r0, #0
	swi 0

.endfunc

