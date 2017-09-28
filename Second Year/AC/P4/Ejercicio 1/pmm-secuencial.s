	.file	"pmm-secuencial.c"
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
	movl	%eax, %ebp
	movq	%rax, %rbx
	movq	%rax, 24(%rsp)
	salq	$3, %rbp
	movl	%eax, %r14d
	movq	%rbp, %rdi
	call	malloc
	movq	%rbp, %rdi
	movq	%rax, %r13
	call	malloc
	movq	%rbp, %rdi
	movq	%rax, %r15
	call	malloc
	testl	%ebx, %ebx
	movq	%rax, %r12
	je	.L3
	movl	%ebx, %eax
	xorl	%ebx, %ebx
	subl	$1, %eax
	movl	%eax, 20(%rsp)
	leaq	8(,%rax,8), %rax
	movq	%rax, 8(%rsp)
	.p2align 4,,10
	.p2align 3
.L5:
	movq	%rbp, %rdi
	call	malloc
	movq	%rbp, %rdi
	movq	%rax, 0(%r13,%rbx)
	movq	%rax, (%rsp)
	call	malloc
	movq	%rbp, %rdi
	movq	%rax, (%r15,%rbx)
	call	malloc
	movq	(%rsp), %rdx
	movq	%rax, (%r12,%rbx)
	testq	%rdx, %rdx
	je	.L27
	addq	$8, %rbx
	cmpq	%rbx, 8(%rsp)
	jne	.L5
	xorl	%r9d, %r9d
.L8:
	movq	0(%r13,%r9,8), %rdi
	movq	(%r15,%r9,8), %rcx
	xorl	%eax, %eax
	movq	(%r12,%r9,8), %rdx
	.p2align 4,,10
	.p2align 3
.L7:
	movsd	.LC2(%rip), %xmm3
	movq	$0, (%rdx,%rax,8)
	movsd	%xmm3, (%rdi,%rax,8)
	movsd	%xmm3, (%rcx,%rax,8)
	addq	$1, %rax
	cmpl	%eax, %r14d
	ja	.L7
	addq	$1, %r9
	cmpl	%r9d, %r14d
	ja	.L8
	call	omp_get_wtime
	movl	20(%rsp), %eax
	movsd	%xmm0, (%rsp)
	xorl	%r11d, %r11d
	leaq	8(,%rax,8), %r10
.L10:
	movq	(%r12,%r11,8), %r9
	movq	0(%r13,%r11,8), %rdi
	xorl	%ecx, %ecx
	.p2align 4,,10
	.p2align 3
.L14:
	movsd	(%r9,%rcx), %xmm1
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L11:
	movq	(%r15,%rax,8), %rdx
	movsd	(%rdx,%rcx), %xmm0
	mulsd	(%rdi,%rax,8), %xmm0
	addq	$1, %rax
	cmpl	%eax, %r14d
	addsd	%xmm0, %xmm1
	ja	.L11
	movsd	%xmm1, (%r9,%rcx)
	addq	$8, %rcx
	cmpq	%rcx, %r10
	jne	.L14
	addq	$1, %r11
	cmpl	%r11d, %r14d
	ja	.L10
	call	omp_get_wtime
	movl	20(%rsp), %ecx
	subsd	(%rsp), %xmm0
	movl	$.LC4, %esi
	movq	(%r12), %rax
	movl	$1, %edi
	movl	%ecx, %ebx
	movq	(%r12,%rbx,8), %rdx
	movsd	(%rax), %xmm1
	leaq	8(,%rbx,8), %rbp
	movl	$3, %eax
	movsd	(%rdx,%rbx,8), %xmm2
	movl	24(%rsp), %edx
	xorl	%ebx, %ebx
	call	__printf_chk
.L15:
	movq	0(%r13,%rbx), %rdi
	call	free
	movq	(%r15,%rbx), %rdi
	call	free
	movq	(%r12,%rbx), %rdi
	addq	$8, %rbx
	call	free
	cmpq	%rbp, %rbx
	jne	.L15
.L16:
	movq	%r13, %rdi
	call	free
	movq	%r15, %rdi
	call	free
	movq	%r12, %rdi
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
	addq	(%r12,%rax), %rax
	movq	(%r12), %rdx
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
