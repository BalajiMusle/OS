
.globl main
.func main

main:
	# _exit(4);
	mov r7, #1
	mov r0, #4
	swi 0

.endfunc

