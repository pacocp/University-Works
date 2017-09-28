;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 
; FRANCISCO CARRILLO PÉREZ
; INGENIERÍA DEL CONOCIMIENTO
; GRUPO: A2
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(deffacts misHechos
        (hombre Paco)
        (hombre Pepe)
        (hombre Francisco)
        (hombre Miguel)
        (hombre Alvaro)
        (hombre Victor)
        (hombre Paquillo)
        (hombre Narciso)

        (mujer MMar)
        (mujer Loida)
        (mujer Paqui)
        (mujer Lali)
        (mujer Alejandra)
        
        (casado Paco MMar)
        (casado Francisco Paqui)
        (casado Pepe Lali)

        (hijo-de Pepe Victor)
        (hijo-de Paco Paquillo)
        (hijo-de Francisco Alvaro)
        (hijo-de MMar Paquillo)
        (hijo-de Lali Victor)
        (hijo-de Paqui Alvaro)
        (hijo-de Paco Miguel)
        (hijo-de MMar Miguel)
        (hijo-de Paco Loida)
        (hijo-de MMar Loida)
        (hijo-de Narciso Paco)
        (hijo-de Narciso Pepe)


)

; user input

(defrule pideNombre1
        ; sin antecedente para que se ejecute el primero
        =>
               (printout t "Escriba el nombre de un miembro de la familia: ")
               (assert (informacionSobre (read)))
)

(defrule pideNombre2
        ; sin antecedente para que se ejecute el primero
        =>
               (printout t "Escriba el nombre de un miembro de la familia: ")
               (assert (informacionSobre2 (read)))
)


;-------------------------------------------------------
(defrule es-padre
                (informacionSobre ?N1) 
                (informacionSobre2 ?N2)
                (padre-de ?N1 ?N2)
        =>
                (printout t ?N1 "es padre de " ?N2  crlf))


(defrule es-hijo
                (informacionSobre ?N1) 
                (informacionSobre2 ?N2)
                (hijo-de ?N1 ?N2)
        
                
        =>
                (printout t ?N2 " es hijo de " ?N2 crlf))

(defrule es-tio
                (informacionSobre ?N1)
                (informacionSobre2 ?N2)
                (tio-de ?N1 ?N2)
        =>

                (printout t ?N2 " es tio de " ?N1 crlf))


(defrule es-abuelo
                (informacionSobre ?N1)
                (informacionSobre2 ?N2)
                (abuelo-de ?N1 ?N2)
        =>

                (printout t ?N1 " es abuelo de " ?N2 crlf)
)

(defrule es-hermano
                (informacionSobre ?N1)
                (informacionSobre2 ?N2)
                (hermanos ?N1 ?N2)
        =>

                (printout t ?N1 " es herman@ de " ?N2 crlf)
        )

(defrule es-primo
                (informacionSobre ?N1)
                (informacionSobre2 ?N2)
                (primos ?N1 ?N2)
        =>

                (printout t ?N1 " es prim@ de " ?N2 crlf)

        )

(defrule es-nieto
                (informacionSobre ?N1)
                (informacionSobre2 ?N2)
                (nieto-de ?N1 ?N2)
        =>

                (printout t ?N1 " es nieto de " ?N2 crlf))

(defrule es-cuñado
                (informacionSobre ?N1)
                (informacionSobre2 ?N2)
                (cuñados ?N1 ?N2)
        =>

                (printout t ?N1 " es cuñado de " ?N2 crlf))
(defrule es-suegro
                (informacionSobre ?N1)
                (informacionSobre2 ?N2)
                (suegro-de ?N1 ?N2)
        =>

                (printout t ?N2  " es suegro de " ?N1 crlf))
                
(defrule es-pareja
                (informacionSobre ?N1)
                (informacionSobre2 ?N2)
                (casado ?N1 ?N2 )
        =>
        (printout t ?N1 " está casado con " ?N2 crlf))
;-------------------------------------------------------------------

(defrule deduceHermanos
                (hijo-de ?padre ?hijo)
                (hijo-de ?padre ?hijo2)
                (test (neq ?hijo ?hijo2)) ; Para que no sea yo mi hermano
        =>
                (assert 
                        (hermanos ?hijo ?hijo2)
                        (padre-de ?hijo ?padre)
                        (padre-de ?hijo2 ?padre)
                )
)

(defrule deducePadres
            (hijo-de ?padre ?hijo)

            =>
            (assert
                (padre-de ?padre ?hijo))
    )
(defrule deducecasados
        (casado ?A ?B)
        =>
        (assert (casado ?B ?A)))

(defrule deducirSuegro
                (hijo-de ?A ?B)
                (casado ?B ?C)
        =>
                (assert (suegro-de ?C ?A))
)

(defrule deducirPrimos
                (tio-de ?A ?B)
                (hijo-de ?B ?C)
        ;(test (neq ?A ?C))
        =>
                (assert (primos ?A ?C)
                        (primos ?C ?A))
)

(defrule deducirAbuelos
                (hijo-de ?abuelo ?padre)
                (hijo-de ?padre ?nieto)
        =>
                (assert 
                        (abuelo-de ?abuelo ?nieto)
                        (nieto-de ?nieto ?abuelo))
)

(defrule deducirMatrimonios
                (casado ?padre ?madre)
        =>
                (assert (casado ?madre ?padre))
)

(defrule deducirTiosSolteros
                (hermanos ?A ?B)
                (hijo-de ?A ?C)
        =>
                (assert (tio-de ?C ?B))
)

(defrule deducirTiosCasados
                (casado ?A ?B)
                (tio-de ?C ?A)
        =>
                (assert (tio-de ?C ?B))
)

(defrule deducirCuñados
                (casado ?A ?B)
                (hermanos ?A ?C)
        =>
                (assert(cuñados ?B ?C))
)



