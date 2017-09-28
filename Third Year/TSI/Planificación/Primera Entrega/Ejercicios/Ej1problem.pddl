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

(define (problem Problema1)

(:domain LosMundosDeBelkan)

(:OBJECTS Z1 Z2 Z3 Z4 Z5 Z6 Z7 Z8 Z9 Z10 Z11 Z12 Z13 Z14 Z15 Z16 Z17 Z18 Z19 Z20 Z21 Z22 Z23 Z24 
	Z25 - zona ROBOT - robot OSCAR MANZANA ROSA ALGORITMO ORO - objeto PRINCESA PRINCIPE BRUJA
	PROFESOR LEONARDO - personaje)

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
)

(:goal (AND (TIENE ORO PRINCIPE)(TIENE OSCAR LEONARDO)(TIENE MANZANA BRUJA)(TIENE ALGORITMO PROFESOR)(TIENE ROSA PRINCESA)))

)