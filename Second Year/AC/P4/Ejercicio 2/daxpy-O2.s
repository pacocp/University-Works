	.file	"daxpy.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"Tiempo(seg.):%11.9f\t \n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB2:
	.section	.text.startup,"ax",@progbits
.LHOTB2:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB38:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movl	$16000000, %edi
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	call	malloc
	movl	$16000000, %edi
	movq	%rax, %rbx
	call	malloc
	movq	%rax, %rbp
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2:
	movl	$2, 0(%rbp,%rax)
	movl	$2, (%rbx,%rax)
	addq	$4, %rax
	cmpq	$16000000, %rax
	jne	.L2
	call	omp_get_wtime
	movsd	%xmm0, 8(%rsp)
	xorl	%eax, %eax
	movss	.LC0(%rip), %xmm2
	.p2align 4,,10
	.p2align 3
.L3:
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2ss	0(%rbp,%rax), %xmm0
	cvtsi2ss	(%rbx,%rax), %xmm1
	mulss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	cvttss2si	%xmm0, %edx
	movl	%edx, (%rbx,%rax)
	addq	$4, %rax
	cmpq	$16000000, %rax
	jne	.L3
	call	omp_get_wtime
	subsd	8(%rsp), %xmm0
	movl	$.LC1, %esi
	movl	$1, %edi
	movl	$1, %eax
	call	__printf_chk
	movq	%rbp, %rdi
	call	free
	movq	%rbx, %rdi
	call	free
	addq	$24, %rsp
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE38:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE2:
	.section	.text.startup
.LHOTE2:
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	1315859240
	.ident	"GCC: (Ubuntu 5.3.1-14ubuntu2) 5.3.1 20160413"
	.section	.note.GNU-stack,"",@progbits
