	.file	"daxpy.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC3:
	.string	"Tiempo(seg.):%11.9f\t \n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB4:
	.section	.text.startup,"ax",@progbits
.LHOTB4:
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
	andl	$15, %eax
	shrq	$2, %rax
	negq	%rax
	andl	$3, %eax
	je	.L14
	cmpl	$1, %eax
	movl	$2, 0(%rbp)
	movl	$2, (%rbx)
	je	.L15
	cmpl	$3, %eax
	movl	$2, 4(%rbp)
	movl	$2, 4(%rbx)
	jne	.L16
	movl	$2, 8(%rbp)
	movl	$2, 8(%rbx)
	movl	$3999997, %r9d
	movl	$3, %r8d
.L3:
	movl	$4000000, %r10d
	movl	%eax, %ecx
	movl	$3999996, %r11d
	subl	%eax, %r10d
	movl	$999999, %esi
.L2:
	salq	$2, %rcx
	movdqa	.LC0(%rip), %xmm0
	leaq	0(%rbp,%rcx), %rdi
	xorl	%eax, %eax
	addq	%rbx, %rcx
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L4:
	addl	$1, %edx
	movaps	%xmm0, (%rdi,%rax)
	movups	%xmm0, (%rcx,%rax)
	addq	$16, %rax
	cmpl	%esi, %edx
	jb	.L4
	movl	%r9d, %edx
	leal	(%r11,%r8), %eax
	subl	%r11d, %edx
	cmpl	%r11d, %r10d
	je	.L6
	movslq	%eax, %rcx
	cmpl	$1, %edx
	movl	$2, 0(%rbp,%rcx,4)
	movl	$2, (%rbx,%rcx,4)
	leal	1(%rax), %ecx
	je	.L6
	movslq	%ecx, %rcx
	addl	$2, %eax
	cmpl	$2, %edx
	movl	$2, 0(%rbp,%rcx,4)
	movl	$2, (%rbx,%rcx,4)
	je	.L6
	cltq
	movl	$2, 0(%rbp,%rax,4)
	movl	$2, (%rbx,%rax,4)
.L6:
	call	omp_get_wtime
	movq	%rbx, %rax
	movsd	%xmm0, 8(%rsp)
	andl	$15, %eax
	shrq	$2, %rax
	negq	%rax
	andl	$3, %eax
	je	.L17
	pxor	%xmm1, %xmm1
	movss	.LC1(%rip), %xmm0
	cmpl	$1, %eax
	cvtsi2ss	0(%rbp), %xmm1
	movaps	%xmm1, %xmm2
	pxor	%xmm1, %xmm1
	mulss	%xmm0, %xmm2
	cvtsi2ss	(%rbx), %xmm1
	addss	%xmm2, %xmm1
	cvttss2si	%xmm1, %edx
	movl	%edx, (%rbx)
	je	.L18
	pxor	%xmm1, %xmm1
	cmpl	$3, %eax
	cvtsi2ss	4(%rbp), %xmm1
	movaps	%xmm1, %xmm2
	pxor	%xmm1, %xmm1
	mulss	%xmm0, %xmm2
	cvtsi2ss	4(%rbx), %xmm1
	addss	%xmm2, %xmm1
	cvttss2si	%xmm1, %edx
	movl	%edx, 4(%rbx)
	jne	.L19
	pxor	%xmm1, %xmm1
	movl	$3999997, %r9d
	movl	$3, %r8d
	cvtsi2ss	8(%rbp), %xmm1
	mulss	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2ss	8(%rbx), %xmm0
	addss	%xmm1, %xmm0
	cvttss2si	%xmm0, %edx
	movl	%edx, 8(%rbx)
.L9:
	movl	$4000000, %r10d
	movl	%eax, %ecx
	movl	$3999996, %r11d
	subl	%eax, %r10d
	movl	$999999, %esi
.L8:
	salq	$2, %rcx
	movaps	.LC2(%rip), %xmm2
	leaq	0(%rbp,%rcx), %rdi
	xorl	%eax, %eax
	addq	%rbx, %rcx
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L10:
	movdqu	(%rdi,%rax), %xmm0
	cvtdq2ps	(%rcx,%rax), %xmm1
	addl	$1, %edx
	cvtdq2ps	%xmm0, %xmm0
	mulps	%xmm2, %xmm0
	addps	%xmm1, %xmm0
	cvttps2dq	%xmm0, %xmm0
	movaps	%xmm0, (%rcx,%rax)
	addq	$16, %rax
	cmpl	%esi, %edx
	jb	.L10
	subl	%r11d, %r9d
	cmpl	%r11d, %r10d
	leal	(%r11,%r8), %eax
	je	.L12
	pxor	%xmm1, %xmm1
	movslq	%eax, %rdx
	addl	$1, %eax
	leaq	(%rbx,%rdx,4), %rcx
	movss	.LC1(%rip), %xmm0
	subl	$1, %r9d
	cvtsi2ss	0(%rbp,%rdx,4), %xmm1
	movaps	%xmm1, %xmm2
	pxor	%xmm1, %xmm1
	mulss	%xmm0, %xmm2
	cvtsi2ss	(%rcx), %xmm1
	addss	%xmm2, %xmm1
	cvttss2si	%xmm1, %edx
	movl	%edx, (%rcx)
	je	.L12
	pxor	%xmm1, %xmm1
	cltq
	leaq	(%rbx,%rax,4), %rdx
	cvtsi2ss	0(%rbp,%rax,4), %xmm1
	mulss	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2ss	(%rdx), %xmm0
	addss	%xmm1, %xmm0
	cvttss2si	%xmm0, %eax
	movl	%eax, (%rdx)
.L12:
	call	omp_get_wtime
	subsd	8(%rsp), %xmm0
	movl	$.LC3, %esi
	movl	$1, %edi
	movl	$1, %eax
	call	__printf_chk
	movq	%rbp, %rdi
	call	free
	movq	%rbx, %rdi
	call	free
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L14:
	.cfi_restore_state
	movl	$4000000, %r11d
	movl	$1000000, %esi
	movl	$4000000, %r10d
	xorl	%ecx, %ecx
	movl	$4000000, %r9d
	xorl	%r8d, %r8d
	jmp	.L2
.L17:
	movl	$4000000, %r11d
	movl	$1000000, %esi
	movl	$4000000, %r10d
	xorl	%ecx, %ecx
	xorl	%r8d, %r8d
	movl	$4000000, %r9d
	jmp	.L8
.L19:
	movl	$3999998, %r9d
	movl	$2, %r8d
	jmp	.L9
.L15:
	movl	$3999999, %r9d
	movl	$1, %r8d
	jmp	.L3
.L16:
	movl	$3999998, %r9d
	movl	$2, %r8d
	jmp	.L3
.L18:
	movl	$3999999, %r9d
	movl	$1, %r8d
	jmp	.L9
	.cfi_endproc
.LFE38:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE4:
	.section	.text.startup
.LHOTE4:
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	2
	.long	2
	.long	2
	.long	2
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC1:
	.long	1315859240
	.section	.rodata.cst16
	.align 16
.LC2:
	.long	1315859240
	.long	1315859240
	.long	1315859240
	.long	1315859240
	.ident	"GCC: (Ubuntu 5.3.1-14ubuntu2) 5.3.1 20160413"
	.section	.note.GNU-stack,"",@progbits
