############################################################
# Grupo: B1 Alumno:Francisco Carrillo Pérez ; Media de una suma con signo
############################################################
.section .data
	lista:      .int 1, 3, 2, 3, 4, 10, 6, 7, 5, 9 # = 50 / 10 = 5
	longlista:  .int (. - lista) / 4
	resultado:  .int 0
	salida:    .string "media = %i / 0x%x\n"


.section .text
         .global _start
         .extern printf   # busca printf fuera de este fichero

_start:    

	pushl   longlista
	pushl   $lista
	call    media
	addl    $8, %esp
	movl    %eax, resultado

	pushl   resultado
	pushl   resultado
	pushl   $salida
	call    printf # llamada a función printf(&formato,resultado)
	addl    $12, %esp   # deja a la pila intacta es 12 porque hago 3 pushl
        
        # void _exit(int status);
	mov     $1, %eax  # exit: servicio 1 kernel Linux
	mov     $0, %ebx  # status: código a retornar (0=OK)
	int     $0x80     # llamar _exit(0);



media:                     
	pushl   %ebp           # guardar marco de pila
	movl    %esp, %ebp     # nuevo marco de pila
        pushl   12(%ebp)       # longlista
	pushl   8(%ebp)        # lista
	call    suma64signo        # suma en %edx:%eax
	addl    $8, %esp       # restaura pila
        idivl   12(%ebp)       # edx:eax/12(%ebp) en %eax
        popl    %ebp
	ret


suma64signo:                   
	pushl   %ebp           #guardo %ebp
        movl    %esp, %ebp     # nuevo marco de pila
        movl    $0, %edi
        pushl   %esi           # guardar %esi
	movl    8(%ebp), %esi  # lista en %esi
	pushl   %ebx           # guardar %ebx
        pushl   %ecx         #guardar %ecx
	movl    $0, %ebx     # %ebx = 0 
        movl    $0, %ecx     # %edx = 0 
	
.bucle:
	movl   (%esi,%edi,4),%eax                  # lista[esi] en eax
	cltd                   # extiende el signo de %eax %edx:%eax
	addl    %eax, %ebx     # %eax + %ebx se guarda en  %ebx
	adcl    %edx, %ecx     #comparo donde esta el numero de elementos en la pila con %edi
        inc     %edi           # incrementar %edi
        cmp     12(%ebp), %edi
	jne    .bucle          # repetir mientras 12(%ebp) != %edi
	movl    %ebx, %eax     # mover parte baja antes de volver
        mov 	%ecx, %edx
	popl    %esi           # restaurar esi
	popl    %edi           # restaurar edi
	popl    %ebx           # restaurar ebx
	popl    %ebp           # restaurar ebp
	ret


