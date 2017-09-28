	.file	"ejercicio1-opt-a-Ensambla.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.section	.text.startup,"ax",@progbits
.LHOTB0:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB38:
	.cfi_startproc
	movl	$s, %eax
	.p2align 4,,10
	.p2align 3
.L2:
	movl	$1, (%rax)
	movl	$1, 4(%rax)
	addq	$32, %rax
	movl	$1, -24(%rax)
	movl	$1, -20(%rax)
	movl	$1, -16(%rax)
	movl	$1, -12(%rax)
	movl	$1, -8(%rax)
	movl	$1, -4(%rax)
	movl	$1, (%rax)
	movl	$1, 4(%rax)
	cmpq	$s+40000, %rax
	jne	.L2
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE38:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE0:
	.section	.text.startup
.LHOTE0:
	.comm	s,40000,32
	.ident	"GCC: (Ubuntu 5.3.1-14ubuntu2) 5.3.1 20160413"
	.section	.note.GNU-stack,"",@progbits
