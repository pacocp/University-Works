(define (domain zeno-travel)


(:requirements
  :typing
  :fluents
  :derived-predicates
  :negative-preconditions
  :universal-preconditions
  :disjuntive-preconditions
  :conditional-effects
  :htn-expansion

  ; Requisitos adicionales para el manejo del tiempo
  :durative-actions
  :metatags
 )

(:types aircraft person city - object)
(:constants slow fast - object)
(:predicates (at ?x - (either person aircraft) ?c - city)
             (in ?p - person ?a - aircraft)
             (different ?x ?y) (igual ?x ?y)
             )
(:functions (fuel ?a - aircraft)
            (distance ?c1 - city ?c2 - city)
            (slow-speed ?a - aircraft)
            (fast-speed ?a - aircraft)
            (slow-burn ?a - aircraft)
            (fast-burn ?a - aircraft)
            (capacity ?a - aircraft)
            (refuel-rate ?a - aircraft)
            (fuel-limit)
            (total-fuel-used)
            (boarding-time)
            (debarking-time)
            (unpasajero)
            (maxpasajeros ?a - aircraft)
            (pasajeros ?a - aircraft)
            (destino ?p - person ?c - city)
            )

(:derived
  (igual ?x ?x) ())

(:derived 
  (different ?x ?y) (not (igual ?x ?y)))


(:task transport-person
  :parameters (?p - person ?c - city)
  
  (:method Case1 ; si la persona esta en la ciudad no se hace nada
   :precondition (at ?p ?c)
   :tasks ()
   )
   
   
   (:method Case2 ;si no esta en la ciudad destino, pero avion y persona estan en la misma ciudad
    :precondition (and (at ?p - person ?c1 - city)
                       (at ?a - aircraft ?c1 - city))
             
    :tasks ( 
            (board)
            (mover-avion ?a ?c1 ?c)
            (debark)))


   (:method Case3 ;si no esta en la ciudad destino, y avion y persona no estan en la misma ciudad
    :precondition (and (at ?p - person ?c1 - city)
                       (at ?a - aircraft ?c2 - city) (different ?c1 - city ?c2 - city))
             
    :tasks ( 
            (fly ?a ?c2 ?c1)
            (board)
            (mover-avion ?a ?c1 ?c)
            (debark)))
  )

(:task mover-avion
 :parameters (?a - aircraft ?c1 - city ?c2 -city)
 (:method fuel-suficiente-rapido 
  :precondition (and (> (fuel ?a) (* (distance ?c1 ?c2) (fast-burn ?a))) (> (fuel-limit) (total-fuel-used)))
  :tasks (
          (zoom ?a ?c1 ?c2)
         )
   )

 (:method fuel-no-suficiente-rapido 
  :precondition (and (not (> (fuel ?a) (* (distance ?c1 ?c2) (fast-burn ?a)))) (> (fuel-limit) (total-fuel-used)) )
  :tasks (
          (refuel ?a ?c1)
          (zoom ?a ?c1 ?c2)
         )
   )
 (:method fuel-suficiente-lento 
  :precondition (and (> (fuel ?a) (* (distance ?c1 ?c2) (slow-burn ?a))) (> (fuel-limit) (total-fuel-used)))
  :tasks (
          (fly ?a ?c1 ?c2)
         )
   )

 (:method fuel-no-suficiente-lento 
  :precondition (and (not (> (fuel ?a) (* (distance ?c1 ?c2) (slow-burn ?a)))) (> (fuel-limit) (total-fuel-used)) )
  :tasks (
          (refuel ?a ?c1)
          (fly ?a ?c1 ?c2)
         )
   )
  )
 
(:import "Primitivas-Zenotravel4.pddl") 


)
