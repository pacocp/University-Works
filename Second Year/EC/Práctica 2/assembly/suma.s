# suma.s: Sumar los elementos de una lista
#         llamando a función, pasando argumentos mediante registros
#         retorna: código retorno 0, comprobar suma en %eax mediante gdb/ddd

# SECCIÓN DE DATOS (.data, variables globales inicializadas)
.section .data
lista:
	.int 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 # ejemplos binario 0b / hex 0x
longlista:
	.int (.-lista)/4 # .= contador posiciones. Aritmética de etiquetas.
resultado:
	.int -1 # 4B a FF para notar cuándo se modifica 
formato:
	.string "suma = %d / 0x%x\n"

# SECCIÓN DE CÓDIGO (.text, instrucciones máquina)
.section .text
	.global _start # PROGRAMA PRINCIPAL - se puede abreviar de esta forma
	.extern printf # busca printf fuera de este fichero

_start:

	mov $lista, %edi   # dirección del array lista
	mov longlista, %ecx # número de elementos a sumar
	call suma           # llamar suma(&lista, longlista);

	mov %eax,resultado  # salvar resultado

	push resultado      # apila resultado
	push resultado      # apila resultado
	push $formato       # apila formato
	call printf         # llamada a función printf(&formato, resultado)
	add $12, %esp       # dejar pila intacta

	# void _exit(int status);
	mov $1, %eax # exit: servicio 1 kernel Linux
	mov $0, %ebx # status: código a retornar (0=OK)
	int $0x80    # llamar _exit(0);

# SUBRUTINA: suma(int* lista, int longlista);
#            entrada: 1) %ebx = dirección inicio array
#                     2) %ecx = número de elementos a sumar
#            salida:     %eax = resultado de la suma

suma:
	push %esi    # preservar %esi (se usa aquí como índice)
	mov $0, %eax # poner a 0 acumulador
	mov $0, %edx # poner a 0 índice
        mov $0, %esi
bucle:
	add (%edi,%esi,4), %eax # acumular i-ésimo elemento
        mov %eax, %ebx
        sar $0x1f, %ebx
        adc %ebx, %edx          #Suma de dos registros con Carry
	inc %esi                # incrementar índice
	cmp %ecx, %esi          # comparar con longitud
	jne bucle               # si no iguales, seguir acumulando
        pop %esi
	
	ret

