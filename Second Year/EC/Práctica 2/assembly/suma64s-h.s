	.file	"suma64s-h.cc"
	.text
	.globl	_Z8suma64s1Pii
	.type	_Z8suma64s1Pii, @function
_Z8suma64s1Pii:
.LFB1142:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	movl	20(%esp), %edi
	movl	24(%esp), %ebp
	testl	%ebp, %ebp
	je	.L4
	movl	$0, %esi
	movl	$0, %eax
	movl	$0, %edx
.L3:
	movl	(%edi,%esi,4), %ecx
	movl	%ecx, %ebx
	sarl	$31, %ebx
	addl	%ecx, %eax
	adcl	%ebx, %edx
	addl	$1, %esi
	cmpl	%ebp, %esi
	jne	.L3
	jmp	.L2
.L4:
	movl	$0, %eax
	movl	$0, %edx
.L2:
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 12
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 8
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE1142:
	.size	_Z8suma64s1Pii, .-_Z8suma64s1Pii
	.globl	_Z8suma64s2Pii
	.type	_Z8suma64s2Pii, @function
_Z8suma64s2Pii:
.LFB1143:
	.cfi_startproc
	pushl	%edi
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	pushl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	16(%esp), %edx
	movl	20(%esp), %eax
	testl	%eax, %eax
	jle	.L9
	movl	%edx, %esi
	leal	(%edx,%eax,4), %edi
	movl	$0, %eax
	movl	$0, %edx
.L8:
	movl	(%esi), %ecx
	movl	%ecx, %ebx
	sarl	$31, %ebx
	addl	%ecx, %eax
	adcl	%ebx, %edx
	addl	$4, %esi
	cmpl	%edi, %esi
	jne	.L8
	jmp	.L7
.L9:
	movl	$0, %eax
	movl	$0, %edx
.L7:
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 12
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE1143:
	.size	_Z8suma64s2Pii, .-_Z8suma64s2Pii
	.globl	_Z8suma64s3PiS_
	.type	_Z8suma64s3PiS_, @function
_Z8suma64s3PiS_:
.LFB1144:
	.cfi_startproc
	pushl	%edi
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	pushl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	16(%esp), %esi
	movl	20(%esp), %edi
	cmpl	%edi, %esi
	je	.L14
	movl	$0, %eax
	movl	$0, %edx
.L13:
	addl	$4, %esi
	movl	-4(%esi), %ecx
	movl	%ecx, %ebx
	sarl	$31, %ebx
	addl	%ecx, %eax
	adcl	%ebx, %edx
	cmpl	%esi, %edi
	jne	.L13
	jmp	.L12
.L14:
	movl	$0, %eax
	movl	$0, %edx
.L12:
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 12
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE1144:
	.size	_Z8suma64s3PiS_, .-_Z8suma64s3PiS_
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"suma64s1   = "
.LC1:
	.string	"suma64s2   = "
.LC2:
	.string	"suma64s3   = "
.LC3:
	.string	"accumulate = "
	.text
	.globl	main
	.type	main, @function
main:
.LFB1145:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	andl	$-16, %esp
	subl	$16, %esp
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	movl	$9, 4(%esp)
	movl	$v, (%esp)
	call	_Z8suma64s1Pii
	movl	%eax, %esi
	movl	%edx, %edi
	movl	%eax, resultado
	movl	%edx, resultado+4
	movl	$.LC0, 4(%esp)
	movl	$_ZSt4cout, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%esi, 4(%esp)
	movl	%edi, 8(%esp)
	movl	%eax, (%esp)
	call	_ZNSo9_M_insertIxEERSoT_
	movl	%eax, (%esp)
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	movl	$9, 4(%esp)
	movl	$v, (%esp)
	call	_Z8suma64s2Pii
	movl	%eax, %esi
	movl	%edx, %edi
	movl	%eax, resultado
	movl	%edx, resultado+4
	movl	$.LC1, 4(%esp)
	movl	$_ZSt4cout, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%esi, 4(%esp)
	movl	%edi, 8(%esp)
	movl	%eax, (%esp)
	call	_ZNSo9_M_insertIxEERSoT_
	movl	%eax, (%esp)
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	movl	$0, %esi
	movl	$0, %edi
	movl	$v, %ecx
.L18:
	addl	$4, %ecx
	movl	-4(%ecx), %eax
	cltd
	addl	%eax, %esi
	adcl	%edx, %edi
	cmpl	$v+36, %ecx
	jne	.L18
	movl	%esi, resultado
	movl	%edi, resultado+4
	movl	$.LC2, 4(%esp)
	movl	$_ZSt4cout, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%esi, 4(%esp)
	movl	%edi, 8(%esp)
	movl	%eax, (%esp)
	call	_ZNSo9_M_insertIxEERSoT_
	movl	%eax, (%esp)
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	movl	$0, %esi
	movl	$v, %eax
.L20:
	addl	(%eax), %esi
	addl	$4, %eax
	cmpl	$v+36, %eax
	jne	.L20
	movl	%esi, %edi
	sarl	$31, %edi
	movl	%esi, resultado
	movl	%edi, resultado+4
	movl	$.LC3, 4(%esp)
	movl	$_ZSt4cout, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%esi, 4(%esp)
	movl	%edi, 8(%esp)
	movl	%eax, (%esp)
	call	_ZNSo9_M_insertIxEERSoT_
	movl	%eax, (%esp)
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	movl	$0, %eax
	leal	-8(%ebp), %esp
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1145:
	.size	main, .-main
	.type	_GLOBAL__sub_I_v, @function
_GLOBAL__sub_I_v:
.LFB1157:
	.cfi_startproc
	subl	$28, %esp
	.cfi_def_cfa_offset 32
	movl	$_ZStL8__ioinit, (%esp)
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, 8(%esp)
	movl	$_ZStL8__ioinit, 4(%esp)
	movl	$_ZNSt8ios_base4InitD1Ev, (%esp)
	call	__cxa_atexit
	movl	$2147483647, v+32
	addl	$28, %esp
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE1157:
	.size	_GLOBAL__sub_I_v, .-_GLOBAL__sub_I_v
	.section	.init_array,"aw"
	.align 4
	.long	_GLOBAL__sub_I_v
	.globl	resultado
	.bss
	.align 8
	.type	resultado, @object
	.size	resultado, 8
resultado:
	.zero	8
	.globl	v
	.data
	.align 32
	.type	v, @object
	.size	v, 36
v:
	.long	1
	.long	16
	.long	256
	.long	4096
	.long	65536
	.long	1048576
	.long	16777216
	.long	268435456
	.zero	4
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
