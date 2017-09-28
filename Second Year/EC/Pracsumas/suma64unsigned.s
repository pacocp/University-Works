################################
# Grupo: B1 Alumno:Francisco Carrillo Pérez ; Suma con precisión sin signo
################################
.section .data
	lista:      .int 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff  
	longlista:  .int (. - lista) / 4
	resultado:  .quad 0
	salida:    .string "suma = %llu / 0x%llx\n"


.section    .text
	.extern printf   # busca printf fuera de este fichero
        .global _start

_start:     

	pushl   longlista          #así lo tengo en la pila y no tengo que usar más registros
	pushl   $lista
	call    suma64unsigned
	addl    $8, %esp
	movl    %eax, resultado
	movl    %edx, resultado + 4

	pushl   resultado + 4
	pushl   resultado
	pushl   resultado + 4
	pushl   resultado
	pushl   $salida
	call    printf      # llamada a función printf(&formato, resultado)
	addl     $20, %esp   # deja a la pila intacta es 20 porque hago 4 pushl
       # void _exit(int status);
	mov     $1, %eax    # exit: servicio 1 kernel Linux
	mov     $0, %ebx    # status: código a retornar (0=OK)
	int     $0x80       # llamar _exit(0);


suma64unsigned:                   
	pushl   %ebp           # guardar marco de pila
	movl    %esp, %ebp     # nuevo marco de pila
        movl    $0, %edi       #pongo %edi a 0
	movl    8(%ebp), %esi  # comienzo lista en esi
	movl    12(%ebp), %ecx # número de elementos en ecx
	push    %ebx           # guardar ebx
	movl    $0, %ebx     # ebx = 0 
	movl    $0, %edx     # edx = 0 
	
.bucle:
	movl   (%esi,%edi,4),%eax        # guardo lista[esi] en eax
	addl    %eax, %ebx     # %eax + %ebx se guarda en  %ebx
	adcl    $0, %edx       
        inc     %edi
        cmp     %ecx, %edi
	jne    .bucle          # repetir %ecx != %edi
	movl    %ebx, %eax     # resultado en %eax
	popl    %ebx           # restaura ebx
	popl    %ebp           # recuperar marco de pila
	retl


