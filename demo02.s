.data

.balign 4
filepath:
	.asciz	"/home/pi/hello.txt"

.balign 4
buf:
	.skip	32

fd:
	.word	0

.equ SYS_EXIT, 1
.equ SYS_OPEN, 5
.equ SYS_CLOSE, 6
.equ SYS_WRITE, 4
.equ SYS_READ, 3
.equ O_RDONLY, 0
.equ STDOUT, 1

.text
.balign 4

.globl main
.func main

main:
	ldr r6, =fd
	
	# fd = open(filepath, O_RDONLY);	
	mov r7, #SYS_OPEN
	ldr r0, =filepath
	mov r1, #O_RDONLY
	swi 0
	str r0, [r6]

	# cnt = read(fd, buf, 32);
	mov r7, #SYS_READ
	ldr r0, [r6]
	ldr r1, =buf
	mov r2, #32
	swi 0
	mov r5, r0

	# write(STDOUT, buf, cnt);
	mov r7, #SYS_WRITE
	mov r0, #STDOUT
	ldr r1, =buf
	mov r2, r5
	swi 0

	# close(fd);
	mov r7, #SYS_CLOSE
	ldr r0, [r6]
	swi 0

	# _exit(?);
	mov r7, #SYS_EXIT
	swi 0

.endfunc






