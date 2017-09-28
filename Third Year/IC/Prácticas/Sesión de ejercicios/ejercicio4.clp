;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 
; FRANCISCO CARRILLO PÉREZ
; INGENIERÍA DEL CONOCIMIENTO
; GRUPO: A2
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(deftemplate NumeroHechos
        (field Tipo)
        (field cantidad-de-hechos)
)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(deffacts tipos-hechos

 (Hecho hecho1 hola)
 (Hecho hecho1 adios)
 (Hecho hecho1 muybuenas)
 (Hecho hecho2 hola)
 (Hecho hecho2 adios)
 (Hecho hecho2 muybuenas)
 (NumeroHechos 
        (Tipo hecho1)
        (cantidad-de-hechos 0))
 (NumeroHechos 
        (Tipo hecho2)
        (cantidad-de-hechos 0))
 (ContarHechos hecho1)
 (ContarHechos hecho2)
 )
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Para que no se produzca un bucle infinito vamos creando tareas
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defrule TareaContarHechos
        (ContarHechos ?tipo)
        (Hecho ?tipo ?otrascosas)
       
        =>
        (assert (Tarea ?tipo))
        
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Contamos los hechos modificando los ya existentes
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defrule ContarHechos
        
        ?tarea <- (Tarea ?tipo)
        ?numerohechos <- (NumeroHechos 
                                (Tipo ?tipo) 
                                (cantidad-de-hechos ?cantidad-de-hechos))
        
         =>
        
        (modify ?numerohechos (cantidad-de-hechos  (+ ?cantidad-de-hechos 1)))
        (retract ?tarea)
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;