;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; FRANCISCO CARRILLO PÉREZ 
; TÉCNICAS DE LOS SISTEMAS INTELIGENTES 
; GRUPO: LUNES
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;Ejercicio 2. Una vez comprobado que el dominio descrito es correcto, considerar que la 
;acción de movimiento consume energía, de forma que cada vez que se mueva el 
;jugador, consume una unidad de energía. Tener en cuenta que el jugador partirá 
;inicialmente de una cantidad de energía (configurada en el estado inicial de cada 
;problema) y solo se puede mover si tiene suficiente energía para ello. 
;a. Modificar el dominio del anterior ejercicio para adecuarlo a esta nueva 
;característica. 
;b. Extender el problema definido en el anterior ejercicio y comprobar que el 
;planificador obtiene un plan para estas nuevas restricciones. Determinar 
;mediante experimentación la cantidad de energía mínima a partir de la cual 
;puede resolver el problema planteado. 

(define (domain LosMundosDeBelkan)
	 (:requirements :strips :typing)
	 (:types robot zona objeto personaje)
	 (:functions
		(coste-fuel) ;representa el fuel del robot
	 )
	 ;Declaracion de los predicados del mundo de Belkan
	 (:predicates   
	 		(at ?x - robot ?y - zona)
			(at1 ?x - objeto ?y - zona)
			(at2 ?x - personaje ?y - zona)
			(conectada ?x - zona ?y - zona)
			(cogido ?x - objeto)
			(tiene ?x - objeto ?y - personaje)
			(manovacia)
	 )
	;Acción de movimiento del robot
	(:action mover-robot
		:parameters (?r - robot ?z1 - zona ?z2 - zona)
		:precondition (and (not (at ?r ?z2))(at ?r ?z1)(conectada ?z1 ?z2))
		:effect (and (not (at ?r ?z1))(at ?r ?z2)(increase (coste-fuel) 1))
	)

	;Acción de coger un objeto
	(:action coger-objeto
		:parameters (?r - robot ?obj - objeto ?z - zona)
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
		:precondition (and (not (tiene ?obj ?p))(at ?r ?z)(at2 ?p ?z)(cogido ?obj))
		:effect (and (not (cogido ?obj))(tiene ?obj ?p)(manovacia))
	)
)