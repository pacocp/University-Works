# printf32.s

.section .data
	resultado: .int 0xFF223344
	formato:   .string "i:%i / u:%u / 0x%x\n"

.section .text

	.extern printf

_start: .globl _start

	pushl resultado
	pushl resultado
	pushl resultado
	pushl $formato
	call printf
	add $16, %esp

	mov $1, %eax
	mov $0, %ebx
	int $0x80

