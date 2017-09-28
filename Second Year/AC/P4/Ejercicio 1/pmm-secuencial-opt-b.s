	.file	"pmm-secuencial-opt-b.c"
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
	movq	%rax, %r15
	movq	%rax, 8(%rsp)
	salq	$3, %r14
	movl	%eax, 24(%rsp)
	movq	%r14, %rdi
	call	malloc
	movq	%r14, %rdi
	movq	%rax, %rbp
	call	malloc
	movq	%r14, %rdi
	movq	%rax, %r12
	call	malloc
	testl	%r15d, %r15d
	movq	%rax, %rbx
	je	.L3
	movl	%r15d, %eax
	xorl	%r13d, %r13d
	subl	$1, %eax
	movl	%eax, 20(%rsp)
	leaq	8(,%rax,8), %rax
	movq	%rax, (%rsp)
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
	cmpq	%r13, (%rsp)
	jne	.L5
	movl	24(%rsp), %r8d
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
	cmpl	%eax, %r8d
	ja	.L7
	addq	$1, %rdi
	cmpl	%edi, %r8d
	ja	.L8
	movl	%r8d, 24(%rsp)
	leaq	8(%rbx), %r15
	leaq	8(%rbp), %r14
	call	omp_get_wtime
	movsd	%xmm0, (%rsp)
	movl	24(%rsp), %r8d
	xorl	%r13d, %r13d
	movq	%rbp, 24(%rsp)
.L10:
	movq	-8(%r15), %rdi
	xorl	%edx, %edx
	xorl	%ebp, %ebp
	movq	-8(%r14), %r11
	movq	(%r15), %rsi
	movq	(%r14), %r10
	.p2align 4,,10
	.p2align 3
.L14:
	leaq	8(%rdx), %r9
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L11:
	movq	(%r12,%rax,8), %rcx
	movsd	(%rcx,%rdx), %xmm0
	mulsd	(%r11,%rax,8), %xmm0
	addsd	(%rdi,%rdx), %xmm0
	movsd	%xmm0, (%rdi,%rdx)
	movsd	(%rcx,%r9), %xmm0
	mulsd	(%r10,%rax,8), %xmm0
	addq	$1, %rax
	cmpl	%eax, %r8d
	addsd	8(%rsi,%rdx), %xmm0
	movsd	%xmm0, 8(%rsi,%rdx)
	ja	.L11
	addl	$2, %ebp
	addq	$16, %rdx
	cmpl	%ebp, %r8d
	ja	.L14
	addl	$2, %r13d
	addq	$16, %r15
	addq	$16, %r14
	cmpl	%r13d, %r8d
	ja	.L10
	movq	24(%rsp), %rbp
	call	omp_get_wtime
	movl	20(%rsp), %ecx
	subsd	(%rsp), %xmm0
	movl	$.LC4, %esi
	movq	(%rbx), %rax
	movl	$1, %edi
	movl	%ecx, %r13d
	movq	(%rbx,%r13,8), %rdx
	movsd	(%rax), %xmm1
	leaq	8(,%r13,8), %r14
	movl	$3, %eax
	movsd	(%rdx,%r13,8), %xmm2
	movl	8(%rsp), %edx
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
	movsd	%xmm0, (%rsp)
	call	omp_get_wtime
	movabsq	$34359738360, %rax
	subsd	(%rsp), %xmm0
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
