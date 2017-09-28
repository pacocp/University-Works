;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; FRANCISCO CARRILLO PÉREZ 
; TÉCNICAS DE LOS SISTEMAS INTELIGENTES 
; GRUPO: LUNES
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;Ejercicio 1. Definir un dominio y problema de planificación con las siguientes características:
;a. Representar en el dominio los objetos del mundo (jugador, personajes, tipos
;de objetos y las zonas del mundo).
;b. Representar predicados que permitan describir los estados del mundo,
;mediante la especificación de aspectos como la relación de conexión entre
;zonas, las posiciones de los objetos y cualquier otra relación o propiedad que
;sea necesaria para la correcta definición de las acciones que puede realizar el
;jugador.
;c. Representar las acciones ir (de una zona a otra), coger (un objeto), dejar (un
;objeto) y entregar (un objeto a un personaje).
;d. Plantear un problema de planificación con un estado inicial con 25 zonas
;conectadas arbitrariamente en el que aparezcan situados los 5 personajes en
;distintas zonas y al menos 5 objetos. El objetivo de este problema consistirá en
;conseguir que todos los personajes tengan al menos un objeto. Comprobar
;con Metric‐FF que se obtiene un plan para conseguir esta misión.

(define (domain LosMundosDeBelkan)
	 (:requirements :strips :typing)
	 (:types robot zona objeto personaje)
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
		:effect (and (not (at ?r ?z1))(at ?r ?z2))
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