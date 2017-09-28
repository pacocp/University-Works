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

(define (domain LosMundosDeBelkan)
	 (:requirements :strips :typing)
	 (:types robot zona objeto personaje tipo mochila)
	 (:functions
		(coste-fuel) ;representa el fuel del robot
		(coste-zona ?z - tipo) ;coste de una zona
	 )
	 ;Declaracion de los predicados de los Mundos de Belkan
	 (:predicates   
	 		(at ?x - robot ?y - zona)
			(at1 ?x - objeto ?y - zona)
			(at2 ?x - personaje ?y - zona)
			(conectada ?x - zona ?y - zona)
			(cogido ?x - objeto)
			(tiene ?x - objeto ?y - personaje)
			(manovacia)
			(mochilavacia)
			(contiene ?x - objeto)
			(clase ?x - zona ?y - tipo)
			(permite-avanzar ?x - objeto ?y - tipo)
			(sin-objeto-necesario ?x - tipo)
	 )
	;Acción de movimiento del robot
	(:action mover-robot
		:parameters (?r - robot ?z1 - zona ?z2 - zona ?t - tipo ?obj - objeto)
		:precondition (and (not (at ?r ?z2))(at ?r ?z1)(conectada ?z1 ?z2)(or(cogido ?obj)(contiene ?obj))(or (permite-avanzar ?obj ?t)(sin-objeto-necesario ?t))
			(>=(-(coste-fuel)(coste-zona ?t))0))
		:effect (and (not (at ?r ?z1))(at ?r ?z2)(decrease (coste-fuel)(coste-zona ?t)))
	)
	;Acción de coger un objeto
	(:action coger-objeto
		:parameters (?r - robot ?obj - objeto ?obj1 - objeto ?z - zona)
		:precondition (and (at ?r ?z) (at1 ?obj ?z)(manovacia))
		:effect (and (not (manovacia))(cogido ?obj))

	)
	;Acción de dejar un objeto
	(:action dejar-objeto
		:parameters (?r - robot ?obj - objeto ?z - zona)
		:precondition (and (at ?r ?z)(cogido ?obj))
		:effect (and (not (cogido ?obj))(at1 ?obj ?z)(manovacia))
	)
	;Entregar un objeto a un personaje
	(:action entregar-objeto
		:parameters(?r - robot ?obj - objeto ?z - zona ?p - personaje)
		:precondition (and (not (tiene ?obj ?p))(at ?r ?z)(at1 ?obj ?z)(at2 ?p ?z)(cogido ?obj))
		:effect (and (not (cogido ?obj))(tiene ?obj ?p)(manovacia))
	)
	;Guardar un objeto en la mochila
	(:action meter-mochila
		:parameters(?r - robot ?obj - objeto)
		:precondition(and (cogido ?obj)(mochilavacia))
		:effect(and (not (cogido ?obj))(not (mochilavacia))(manovacia)(contiene ?obj))
	)
	;Sacar un objeto de la mochila
	(:action sacar-mochila
		:parameters(?r - robot ?obj - objeto)
		:precondition(and (contiene ?obj)(manovacia))
		:effect(and (not (contiene ?obj))(not (manovacia))(mochilavacia)(cogido ?obj))
	)
)