;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 
; FRANCISCO CARRILLO PÉREZ
; INGENIERÍA DEL CONOCIMIENTO
; GRUPO: A2
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Template
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(deftemplate TTT
        (slot nombreslot1)
        (slot nombreslot2)
        (multislot nombreslot3)
)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Va pidiendo las caracterísiticas para al final hacer un assert
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defrule pideCarac
        ; sin antecedente para que se ejecute el primero
        =>
               (printout t "Escriba un atributo: ")
               (bind ?campo1 (read))
               (printout t "Escriba un atributo: ")
               (bind ?campo2 (read))
               (printout t "Escriba un atributo: ")
               (bind ?campo3 (readline))
               (assert (TTT
                        (nombreslot1 ?campo1)
                        (nombreslot2 ?campo2)
                        (nombreslot3 ?campo3))
               )

)

