;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; FRANCISCO CARRILLO PÉREZ 
; TÉCNICAS DE LOS SISTEMAS INTELIGENTES 
; GRUPO: LUNES
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Ejercicio 4. Considerar ahora que cuando el jugador entrega objetos a un personaje 
;consigue puntos, según la siguiente tabla: 
;a. Modificar el dominio para poder registrar los puntos acumulados por el 
;agente, mediante una función, cada vez que entrega un objeto a un personaje 
;(una función PDDL puede tener dos argumentos). 
;b. Extender el problema del anterior ejercicio para que, por un lado, se pueda 
;representar la tabla anterior y, además, partiendo de 0 puntos el jugador 
;pueda alcanzar al menos una cantidad arbitraria de puntos (indicándolo en el 
;objetivo), sin especificar a qué personajes hay que entregar objetos. Por 
;ejemplo, plantear un problema en el que con solo objetos de tipo oscar y
;manzana el jugador pueda alcanzar 50 puntos (asumiendo que solo están los 5 
;personajes). 

(define (domain LosMundosDeBelkan)
	 (:requirements :strips :typing)
	 (:types robot zona objeto personaje tipo mochila)
	 (:functions
		(coste-fuel) ;representa el fuel del robot
		(coste-zona ?z - tipo) ;coste de una zona
		(suma-puntos ?x - objeto ?y - personaje) ;Suma puntos de los personajes
		(puntos)
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
		:effect (and (not (cogido ?obj))(tiene ?obj ?p)(manovacia)(increase (puntos) (suma-puntos ?obj ?p)))
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