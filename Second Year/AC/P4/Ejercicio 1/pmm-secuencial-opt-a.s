	.file	"pmm-secuencial-opt-a.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Falta tama\303\261o de matriz y vector"
	.align 8
.LC1:
	.string	"Error en la reserva de espacio para los vectores"
	.align 8
.LC4:
	.string	"Tiempo(seg.):%11.9f\t / Tama\303\261o:%u\t/ V2[0]=%8.6f V2[%d]=%8.6f\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB5:
	.section	.text.startup,"ax",@progbits
.LHOTB5:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB38:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	cmpl	$1, %edi
	jle	.L26
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	movl	%eax, %r14d
	movq	%rax, %r13
	movq	%rax, 16(%rsp)
	salq	$3, %r14
	movl	%eax, %r15d
	movq	%r14, %rdi
	call	malloc
	movq	%r14, %rdi
	movq	%rax, %rbp
	call	malloc
	movq	%r14, %rdi
	movq	%rax, %r12
	call	malloc
	testl	%r13d, %r13d
	movq	%rax, %rbx
	je	.L3
	movl	%r13d, %eax
	movl	%r15d, 28(%rsp)
	xorl	%r13d, %r13d
	subl	$1, %eax
	movl	%eax, 24(%rsp)
	leaq	8(,%rax,8), %rax
	movq	%rax, 8(%rsp)
	.p2align 4,,10
	.p2align 3
.L5:
	movq	%r14, %rdi
	call	malloc
	movq	%r14, %rdi
	movq	%rax, 0(%rbp,%r13)
	movq	%rax, %r15
	call	malloc
	movq	%r14, %rdi
	movq	%rax, (%r12,%r13)
	call	malloc
	testq	%r15, %r15
	movq	%rax, (%rbx,%r13)
	je	.L27
	addq	$8, %r13
	cmpq	%r13, 8(%rsp)
	jne	.L5
	movl	28(%rsp), %r15d
	xorl	%edi, %edi
.L8:
	movq	0(%rbp,%rdi,8), %rsi
	movq	(%r12,%rdi,8), %rcx
	xorl	%eax, %eax
	movq	(%rbx,%rdi,8), %rdx
	.p2align 4,,10
	.p2align 3
.L7:
	movsd	.LC2(%rip), %xmm3
	movq	$0, (%rdx,%rax,8)
	movsd	%xmm3, (%rsi,%rax,8)
	movsd	%xmm3, (%rcx,%rax,8)
	addq	$1, %rax
	cmpl	%eax, %r15d
	ja	.L7
	addq	$1, %rdi
	cmpl	%edi, %r15d
	ja	.L8
	call	omp_get_wtime
	movl	24(%rsp), %eax
	movsd	%xmm0, 8(%rsp)
	leaq	8(%rbx), %r14
	leaq	8(%rbp), %r13
	xorl	%r8d, %r8d
	leaq	8(,%rax,8), %r11
.L10:
	movq	-8(%r14), %rsi
	movq	-8(%r13), %r10
	xorl	%edx, %edx
	movq	(%r14), %rcx
	movq	0(%r13), %r9
	.p2align 4,,10
	.p2align 3
.L14:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L11:
	movq	(%r12,%rax,8), %rdi
	movsd	(%r10,%rax,8), %xmm1
	movsd	(%rdi,%rdx), %xmm0
	mulsd	%xmm0, %xmm1
	mulsd	(%r9,%rax,8), %xmm0
	addq	$1, %rax
	cmpl	%eax, %r15d
	addsd	(%rsi,%rdx), %xmm1
	movsd	%xmm1, (%rsi,%rdx)
	addsd	(%rcx,%rdx), %xmm0
	movsd	%xmm0, (%rcx,%rdx)
	ja	.L11
	addq	$8, %rdx
	cmpq	%r11, %rdx
	jne	.L14
	addl	$2, %r8d
	addq	$16, %r14
	addq	$16, %r13
	cmpl	%r8d, %r15d
	ja	.L10
	call	omp_get_wtime
	movl	24(%rsp), %ecx
	subsd	8(%rsp), %xmm0
	movl	$.LC4, %esi
	movq	(%rbx), %rax
	movl	$1, %edi
	movl	%ecx, %r13d
	movq	(%rbx,%r13,8), %rdx
	movsd	(%rax), %xmm1
	leaq	8(,%r13,8), %r14
	movl	$3, %eax
	movsd	(%rdx,%r13,8), %xmm2
	movl	16(%rsp), %edx
	xorl	%r13d, %r13d
	call	__printf_chk
.L15:
	movq	0(%rbp,%r13), %rdi
	call	free
	movq	(%r12,%r13), %rdi
	call	free
	movq	(%rbx,%r13), %rdi
	addq	$8, %r13
	call	free
	cmpq	%r13, %r14
	jne	.L15
.L16:
	movq	%rbp, %rdi
	call	free
	movq	%r12, %rdi
	call	free
	movq	%rbx, %rdi
	call	free
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L26:
	.cfi_restore_state
	movl	$.LC0, %edi
	call	puts
	orl	$-1, %edi
	call	exit
.L3:
	call	omp_get_wtime
	movsd	%xmm0, 8(%rsp)
	call	omp_get_wtime
	movabsq	$34359738360, %rax
	subsd	8(%rsp), %xmm0
	orl	$-1, %ecx
	addq	(%rbx,%rax), %rax
	movq	(%rbx), %rdx
	movl	$.LC4, %esi
	movl	$1, %edi
	movsd	(%rdx), %xmm1
	xorl	%edx, %edx
	movsd	(%rax), %xmm2
	movl	$3, %eax
	call	__printf_chk
	jmp	.L16
.L27:
	movl	$.LC1, %edi
	call	puts
	movl	$-2, %edi
	call	exit
	.cfi_endproc
.LFE38:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE5:
	.section	.text.startup
.LHOTE5:
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	0
	.long	1073741824
	.ident	"GCC: (Ubuntu 5.3.1-14ubuntu2) 5.3.1 20160413"
	.section	.note.GNU-stack,"",@progbits
