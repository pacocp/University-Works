;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; FRANCISCO CARRILLO PÉREZ 
; TÉCNICAS DE LOS SISTEMAS INTELIGENTES 
; GRUPO: LUNES
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Ejercicio 3. Considerar ahora que (1) hay distintos tipos de zonas dependiendo del tipo de 
;superficie que contengan, en concreto: Bosque, Agua, Precipicio, Arena y Piedra, y (2) 
;hay dos nuevos tipos de objetos: Zapatilla y Bikini. Además, considerar también que el 
;jugador, aparte de poder tener cogido un objeto, está dotado de una mochila donde 
;puede guardar otro objeto (solo uno). Realizar lo siguiente: 
;a. Modificar el dominio del ejercicio anterior para que el jugador pueda 
;desplazarse por el entorno considerando las siguientes restricciones: 
;i. Puede moverse a una zona de bosque sólo si tiene una zapatilla 
;(cogida o en la mochila). (Puede definirse un predicado que permita 
;determinar de qué tipo es un determinado objeto). 
;ii. Puede moverse a una zona de agua si tiene un bikini (cogido o en la 
;mochila). 
;iii. No puede moverse a un precipicio. 
;iv. En una zona pedregosa consume el doble de energía que en cualquier 
;otra. 
;b. Modificar el domino para que pueda cargar y descargar objetos en/de la 
;mochila. Tener en cuenta que solo puede tener cogido un objeto a la vez y uno 
;en la mochila. 
;c. Extender el problema del anterior ejercicio para poder representar un 
;escenario que contenga zonas de los distintos tipos descritos y también 
;objetos de tipo zapatilla y bikini para que el jugador pueda moverse por todas 
;las zonas. Representar al menos que hay una zapatilla en una zona de agua, o 
;un bikini en una zona de bosque. 

(define (problem Problema3)

(:domain LosMundosDeBelkan)

(:OBJECTS Z1 Z2 Z3 Z4 Z5 Z6 Z7 Z8 Z9 Z10 Z11 Z12 Z13 Z14 Z15 Z16 Z17 Z18 Z19 Z20 Z21 Z22 Z23 Z24 
	Z25 - zona ROBOT - robot OSCAR MANZANA ROSA ALGORITMO ORO ZAPATILLA BIKINI - objeto PRINCESA PRINCIPE 
	BRUJA PROFESOR LEONARDO - personaje MOCHILA - mochila BOSQUE AGUA PRECIPICIO ARENA PIEDRA - tipo)

(:INIT  (CONECTADA Z1 Z2)
		(CONECTADA Z2 Z1)
		(CONECTADA Z1 Z6)
		(CONECTADA Z6 Z1)
		(CONECTADA Z2 Z3)
		(CONECTADA Z3 Z2)
		(CONECTADA Z2 Z7)
		(CONECTADA Z7 Z2)
		(CONECTADA Z3 Z4)
		(CONECTADA Z4 Z3)
		(CONECTADA Z3 Z8)
		(CONECTADA Z8 Z3)
		(CONECTADA Z4 Z5)
		(CONECTADA Z5 Z4)
		(CONECTADA Z4 Z9)
		(CONECTADA Z9 Z4)
		(CONECTADA Z5 Z10)
		(CONECTADA Z10 Z5)
		(CONECTADA Z6 Z7)
		(CONECTADA Z7 Z6)
		(CONECTADA Z6 Z11)
		(CONECTADA Z11 Z6)
		(CONECTADA Z7 Z8)
		(CONECTADA Z8 Z7)
		(CONECTADA Z7 Z12)
		(CONECTADA Z12 Z7)
		(CONECTADA Z8 Z9)
		(CONECTADA Z9 Z8)
		(CONECTADA Z8 Z13)
		(CONECTADA Z13 Z8)
		(CONECTADA Z9 Z10)
		(CONECTADA Z10 Z9)
		(CONECTADA Z9 Z14)
		(CONECTADA Z14 Z9)
		(CONECTADA Z10 Z15)
		(CONECTADA Z15 Z10)
		(CONECTADA Z11 Z12)
		(CONECTADA Z12 Z11)
		(CONECTADA Z11 Z16)
		(CONECTADA Z16 Z11)
		(CONECTADA Z12 Z13)
		(CONECTADA Z13 Z12)
		(CONECTADA Z12 Z17)
		(CONECTADA Z17 Z12)
		(CONECTADA Z13 Z14)
		(CONECTADA Z14 Z13)
		(CONECTADA Z13 Z18)
		(CONECTADA Z18 Z13)
		(CONECTADA Z14 Z15)
		(CONECTADA Z15 Z14)
		(CONECTADA Z14 Z19)
		(CONECTADA Z19 Z14)
		(CONECTADA Z15 Z20)
		(CONECTADA Z20 Z15)
		(CONECTADA Z16 Z17)
		(CONECTADA Z17 Z16)
		(CONECTADA Z16 Z21)
		(CONECTADA Z21 Z16)
		(CONECTADA Z17 Z18)
		(CONECTADA Z18 Z17)
		(CONECTADA Z17 Z22)
		(CONECTADA Z22 Z17)
		(CONECTADA Z18 Z19)
		(CONECTADA Z19 Z18)
		(CONECTADA Z19 Z20)
		(CONECTADA Z20 Z19)
		(CONECTADA Z20 Z25)
		(CONECTADA Z25 Z20)
		(CONECTADA Z21 Z22)
		(CONECTADA Z22 Z21)
		(CONECTADA Z22 Z23)
		(CONECTADA Z23 Z22)
		(CONECTADA Z24 Z25)
		(CONECTADA Z25 Z24)
		(AT1 ORO Z2)
		(AT2 PRINCIPE Z4)
		(AT2 LEONARDO Z6)
		(AT2 BRUJA Z7)
		(AT1 OSCAR Z10)
		(AT1 MANZANA Z11)
		(AT2 PRINCESA Z13)
		(AT1 ROSA Z14)
		(AT2 PROFESOR Z21)
		(AT1 ALGORITMO Z25)
		(AT ROBOT Z12)
		(MANOVACIA)
		(MOCHILAVACIA)
		(CLASE Z1 PRECIPICIO)
		(CLASE Z2 PIEDRA)
		(CLASE Z3 PIEDRA)
		(CLASE Z4 PIEDRA)
		(CLASE Z5 PIEDRA)
		(CLASE Z6 PIEDRA)
		(CLASE Z7 BOSQUE)
		(CLASE Z8 BOSQUE)
		(CLASE Z9 BOSQUE)
		(CLASE Z10 AGUA)
		(CLASE Z11 AGUA)
		(CLASE Z12 AGUA)
		(CLASE Z13 AGUA)
		(CLASE Z14 AGUA)
		(CLASE Z15 AGUA)
		(CLASE Z16 ARENA)
		(CLASE Z17 ARENA)
		(CLASE Z18 ARENA)
		(CLASE Z19 ARENA)
		(CLASE Z20 ARENA)
		(CLASE Z21 BOSQUE)
		(CLASE Z22 BOSQUE)
		(CLASE Z23 PRECIPICIO)
		(CLASE Z24 BOSQUE)
		(CLASE Z25 BOSQUE)
		(PERMITE-AVANZAR BIKINI AGUA)
		(PERMITE-AVANZAR ZAPATILLA BOSQUE)
		(SIN-OBJETO-NECESARIO PIEDRA)
		(SIN-OBJETO-NECESARIO ARENA)
		(AT1 BIKINI Z12)
		(AT1 ZAPATILLA Z21)
		(= (coste-zona PRECIPICIO) 10000)
		(= (coste-zona AGUA) 1)
		(= (coste-zona BOSQUE) 2)
		(= (coste-zona ARENA) 1)
		(= (coste-zona PIEDRA) 3)
		(= (coste-fuel) 100)

)

(:goal (AND (TIENE ORO PRINCIPE)(TIENE OSCAR LEONARDO)(TIENE MANZANA BRUJA)(TIENE ALGORITMO PROFESOR)(TIENE ROSA PRINCESA)))

(:metric minimize (coste-fuel))

)