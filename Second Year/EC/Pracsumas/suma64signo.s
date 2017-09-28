################################
# Grupo: B1 Alumno:Francisco Carrillo Pérez ; Suma con precisión con signo
################################
.section .data

	lista:      .int 0x80000000, 0x80000000
	longlista:  .int (. - lista) / 4
	resultado:  .quad 0
	salida:    .string "suma = %lli / 0x%llx\n"



.section    .text
              .global _start
              .extern printf   # busca printf fuera de este fichero
_start:     

	pushl   longlista
	pushl   $lista
	call    suma64signo
	addl    $8, %esp
	movl    %eax, resultado
	movl    %edx, resultado + 4

	pushl   resultado + 4
	pushl   resultado
	pushl   resultado + 4
	pushl   resultado
	pushl   $salida
	call    printf       # llamada a función printf(&formato,resultado)
	addl     $20, %esp  # deja a la pila intacta es 20 porque hago 4 pushl

        # void _exit(int status);
	mov     $1, %eax    # exit: servicio 1 kernel Linux
	mov     $0, %ebx    # status: código a retornar (0=OK)
	int     $0x80       # llamar _exit(0);



suma64signo:                   
	pushl   %ebp           # guardar marco de pila
        movl    %esp, %ebp     # nuevo marco de pila
        movl    $0, %edi       # pongo a 0 %edi, lo voy a utilizar como indice
        pushl   %esi           # guardar esi
	movl    8(%ebp), %esi  # comienzo de la lista en esi
	pushl   %ebx           # guardar %ebx
        pushl   %ecx           # guardar %ecx
	movl    $0, %ebx     # %ebx = 0 
        movl    $0, %ecx     # %edx = 0 
	                   
.bucle:
	movl   (%esi,%edi,4),%eax                  # lista[esi] en eax
	cltd                   # extiende el signo de eax edx:eax
	addl    %eax, %ebx     # %eax + %ebx se guarda en  %ebx
	adcl    %edx, %ecx     
        inc     %edi           #incremento el indice
        cmp     12(%ebp), %edi #comparo donde esta el numero de elementos en la pila con %edi
	jne    .bucle         # repetir mientras 12(%ebp) != %edi
	movl    %ebx, %eax     # resultado en %eax
        movl 	%ecx, %edx
	popl    %esi           # restaurar esi
	popl    %edi           # restaurar edi
	popl    %ebx           # restaurar ebx
	popl    %ebp           # restaurar ebp
	ret


