	.file	"sandbox.c"
	.section	.rodata
.LC0:
	.string	"Hello World"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$16, %esp
	movl	$.LC0, -8(%ebp)
	jmp	.L2
.L3:
	movl	-8(%ebp), %ecx
#APP
# 11 "./sandbox.c" 1
	movl $0X4, %eax
movl $0X1, %ebx
movl $0X1, %edx
int $0X80
# 0 "" 2
#NO_APP
	addl	$1, -8(%ebp)
.L2:
	movl	-8(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L3
	nop
	addl	$16, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.5.1 20100924 (Red Hat 4.5.1-4)"
	.section	.note.GNU-stack,"",@progbits
