;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 
; FRANCISCO CARRILLO PÉREZ
; INGENIERÍA DEL CONOCIMIENTO
; GRUPO: A2
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                     ;
;                      TEMPLATES                      ;
;                                                     ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Para realizar distintas tareas y que entre en distintas reglas
(deftemplate MostrarPropuesta)
(deftemplate HacerPropuesta)
(deftemplate ValoresPeligrosos)
(deftemplate ValoresSobrevalorados)
(deftemplate ValoresInfravalorados)
(deftemplate ContadorHechos
    (slot Contador))
;Para manejar la empresa
(deftemplate Empresa
        (slot Nombre)
        (slot Valor)
        (slot Variacion)
        (slot Capitalizacion)
        (slot PER)
        (slot RPD)
        (slot Tama)
        (slot PorcdelIBEX)
        (slot EtiquetaPer)
        (slot EtiquetaRPD)
        (slot Sector)
        (slot variacionCincoDias)
        (slot tresDiasBajada)
        (slot cincoDiasBajada)
        (slot VariacionRespectoSectorCincoDias)
        (slot VRRS)
        (slot VariacionMes)
        (slot VariacionTrimestre)
        (slot VariacionSemestre )
        (slot VariacionAnual)
)

;Para manejar los sectores
(deftemplate Sector
        (slot Nombre)
        (slot Variacion)
        (slot Capitalizacion)
        (slot PERmedio)
        (slot RPDmedio)
        (slot PorcdelIBEX)
        (slot variacionCincoDias)
        (slot tresDiasBajada)
        (slot cincoDiasBajada)
        (slot VariacionMes)
        (slot VariacionTrimestre)
        (slot VariacionSemestre)
        (slot VariacionAnual)
)

; Para manejar la cartera del usuario
(deftemplate Cartera
        (slot Nombre)
        (slot Acciones)
        (slot CotizCompra)
)

;Para leer la primera linea del archivo
(deftemplate PrimeraLinea
        (slot Disponible)
        (slot CantidadDisponible)
        (slot CantidadDisponible2)
)
;;;;;;;;;;;;;;;;;;;;;;;;;
;
; TIPOS DE VALORES
;
;;;;;;;;;;;;;;;;;;;;;;;;;

;Para indicar que un valor es inestable
(deftemplate Inestable
        (slot Nombre)
        (slot Valor)
        (slot Sector)
        (slot Explicacion)
)

;Para indicar que un valor es peligroso
(deftemplate Peligroso
        (slot Nombre)
        (slot Valor)
        (slot Sector)
        (slot Explicacion)
)

;Para indicar que un valor esta sobrevalorado
(deftemplate Sobrevalorado
        (slot Nombre)
        (slot Valor)
        (slot Sector)
        (slot Explicacion)
)

;Para indicar que un valor está infravalorado
(deftemplate Infravalorado
        (slot Nombre)
        (slot Valor)
        (slot Sector)
        (slot Explicacion)
)

;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;  NOTICIAS
;
;;;;;;;;;;;;;;;;;;;;;;;;;;

;Para trabajar con la noticia positiva
(deftemplate Noticia
            (slot Empresa)
            (slot Tipo)
            (slot Antig)
            (slot Fecha)
            (slot NoticiaExpl)
            (slot URL)
)
;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;  PROPUESTAS
;
;;;;;;;;;;;;;;;;;;;;;;;;;;

;Para trabajar con las propuestas
(deftemplate Propuesta
        (slot Tipo)
        (slot Nombre)
        (slot Nombre2)
        (slot Valor)
        (slot Sector)
        (slot Explicacion)
        (slot RE)
        (slot Cod)
)

;Para ayudar a trabajar con las propuestas
(deftemplate PropuestaAux
        (slot Tipo)
        (slot Nombre)
        (slot Nombre2)
        (slot Valor)
        (slot Sector)
        (slot Explicacion)
        (slot RE)
        (slot Cod)
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                     ;
;                      Rules                          ;
;                                                     ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; LOGO DE INICIO
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defrule MostrarLogo
    (declare (salience 2000))
    =>
    (printout t crlf "****************************************" crlf)
    (printout t      "*                                      *" crlf)
    (printout t      "*      SISTEMA EXPERTO EN BOLSA        *" crlf)
    (printout t      "*                                      *" crlf)
    (printout t      "****************************************" crlf)
)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; LECTURA DE DATOS
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Apertura del archivo
(defrule openfiles
        (declare (salience 10))
        =>
        (printout t crlf crlf "*****PASO A LEER SUS DATOS*****" crlf)
        (open "Analisis.txt" mianalisis)
        (assert (SeguirLeyendoAnalisis))
        (open "AnalisisSectores.txt" mianalisissector)
        (assert (SeguirLeyendoSector))
        (open "Cartera.txt" micartera)
        (assert (SeguirLeyendoCarteraPrimera))
        (open "Noticias.txt" misnoticias)
        (assert (SeguirLeyendoNoticias))
)

;Leer los valores del fichero analisis
(defrule LeerValoresAnalisisFromFile
        (declare (salience 9))
        ?f <- (SeguirLeyendoAnalisis)
        =>
        (bind ?nombre (read mianalisis))
        (retract ?f)
        (if (neq ?nombre EOF) then
                (bind ?campo2 (read mianalisis))
                (bind ?campo3 (read mianalisis))
                (bind ?campo4 (read mianalisis))
                (bind ?campo5 (read mianalisis))
                (bind ?campo6 (read mianalisis))
                (bind ?campo7 (read mianalisis))
                (bind ?campo8 (read mianalisis))
                (bind ?campo9 (read mianalisis))
                (bind ?campo10 (read mianalisis))
                (bind ?campo11 (read mianalisis))
                (bind ?campo12 (read mianalisis))
                (bind ?campo13 (read mianalisis))
                (bind ?campo14 (read mianalisis))
                (bind ?campo15 (read mianalisis))
                (bind ?campo16 (read mianalisis))
                (bind ?campo17 (read mianalisis))
                (bind ?campo18 (read mianalisis))
                (bind ?campo19 (read mianalisis))
                (bind ?campo20 (read mianalisis))
                (assert (Empresa 
                                (Nombre ?nombre) 
                                (Valor ?campo2)
                                (Variacion ?campo3) 
                                (Capitalizacion ?campo4)
                                (PER ?campo5)
                                (RPD ?campo6) 
                                (Tama ?campo7)
                                (PorcdelIBEX ?campo8)
                                (EtiquetaPer ?campo9)
                                (EtiquetaRPD ?campo10)
                                (Sector ?campo11)
                                (variacionCincoDias ?campo12)
                                (tresDiasBajada ?campo13)
                                (cincoDiasBajada ?campo14)
                                (VariacionRespectoSectorCincoDias ?campo15)
                                (VRRS ?campo16)
                                (VariacionMes ?campo17)
                                (VariacionTrimestre ?campo18)
                                (VariacionSemestre ?campo19)
                                (VariacionAnual ?campo20)))
                (assert (SeguirLeyendoAnalisis))
        )

        
)
;Leer los valores del fichero sector
(defrule LeerValoresSectorFromFile
        (declare (salience 9))
        ?f <- (SeguirLeyendoSector)
        =>
        (bind ?valor (read mianalisissector))
        (retract ?f)
        (if (neq ?valor EOF) then
                (bind ?campo2 (read mianalisissector))
                (bind ?campo3 (read mianalisissector))
                (bind ?campo4 (read mianalisissector))
                (bind ?campo5 (read mianalisissector))
                (bind ?campo6 (read mianalisissector))
                (bind ?campo7 (read mianalisissector))
                (bind ?campo8 (read mianalisissector))
                (bind ?campo9 (read mianalisissector))
                (bind ?campo10 (read mianalisissector))
                (bind ?campo11 (read mianalisissector))
                (bind ?campo12 (read mianalisissector))
                (bind ?campo13 (read mianalisissector))
                (assert (Sector 
                                (Nombre ?valor) 
                                (Variacion ?campo2)
                                (Capitalizacion ?campo3) 
                                (PERmedio ?campo4)
                                (RPDmedio ?campo5)
                                (PorcdelIBEX ?campo6) 
                                (variacionCincoDias ?campo7)
                                (tresDiasBajada ?campo8)
                                (cincoDiasBajada ?campo9)
                                (VariacionMes ?campo10)
                                (VariacionTrimestre ?campo11)
                                (VariacionSemestre ?campo12)
                                (VariacionAnual ?campo13)))
                (assert (SeguirLeyendoSector))
        )
)

;Leer primera linea de valores de la cartera
(defrule LeerValoresCarteraPrimeraLinea
        (declare (salience 9))
        ?f <- (SeguirLeyendoCarteraPrimera)
        =>
        (bind ?nombre (read micartera))
        (retract ?f)
        (if (neq ?nombre EOF) then
                (bind ?campo2 (read micartera))
                (bind ?campo3 (read micartera))
               (assert (PrimeraLinea
                                (Disponible ?nombre) 
                                (CantidadDisponible ?campo2)
                                (CantidadDisponible2 ?campo3)))
                (assert (SeguirLeyendoCartera))
        )
)

;Leer los valores de la cartera
(defrule LeerValoresCarteraFromFile
        (declare (salience 9))
        ?f <- (SeguirLeyendoCartera)
        (PrimeraLinea
                (Disponible ?Disponible)
                (CantidadDisponible ?CantidadDisponible)
                (CantidadDisponible2 ?CantidadDisponible2))
        =>
        (bind ?nombre (read micartera))
        (retract ?f)
        (if (neq ?nombre EOF) then
                (bind ?campo2 (read micartera))
                (bind ?campo3 (read micartera))
                ;(bind ?campo4 (read micartera))
                ;(bind ?campo5 (read micartera))
                ;(bind ?campo6 (read micartera))
                ;(bind ?campo7 (read micartera))
               (assert (Cartera
                                (Nombre ?nombre) 
                                (Acciones ?campo2)
                                (CotizCompra ?campo3)))
                                ;(DiasCompra ?campo4)
                                ;(Rendimiento ?campo5)
                                ;(ValorActual ?campo6) 
                                ;(FechaCompra ?campo7)))
                (assert (SeguirLeyendoCartera))
        )
)

;Leer del fichero de noticias
(defrule LeerValoresNoticiasFromFile
        (declare (salience 9))
        ?f <- (SeguirLeyendoNoticias)
        =>
        (bind ?nombre (read misnoticias))
        (retract ?f)
        (if (neq ?nombre EOF) then
                (bind ?campo2 (read misnoticias))
                (bind ?campo3 (read misnoticias))
                (bind ?campo4 (read misnoticias))
                (bind ?campo5 (read misnoticias))
                (bind ?campo6 (read misnoticias))
               (assert (Noticia
                                (Empresa ?nombre)
                                (Tipo ?campo2)
                                (Antig ?campo3)
                                (Fecha ?campo4) 
                                (NoticiaExpl ?campo5)
                                (URL ?campo6)))
                (assert (SeguirLeyendoNoticias))
        )
)


; Pasar a módulo de detección de valores peligrosos
(defrule PasarModulosValores
    (declare (salience 8))
    =>
    (printout t crlf "*****PASO A ANALIZAR LOS VALORES DEL IBEX35*****" crlf crlf)
    (assert (ValoresPeligrosos))
    (assert (ValoresSobrevalorados))
    (assert (ValoresInfravalorados))
)
;Cierre del archivo
(defrule closefiles
        (declare (salience -12))
        =>
        (close mianalisis)
        (close mianalisissector)
        (close micartera)
        (close misnoticias)
)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; MÓDULO 1 DETECCIÓN VALORES PELIGROSOS
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defrule InestablesPorDefecto
        (declare (salience 7))
        (ValoresPeligrosos)
        (Empresa 
                (Nombre ?nombre) 
                (Valor ?campo2)
                (Sector Construccion))

        =>
        (assert (Inestable 
                (Nombre ?nombre)
                (Valor ?campo2) 
                (Sector Construccion)
                (Explicacion "Es un valor inestable por defecto ya que pertenece al sector de la construccion")))
        

)

(defrule ActualizarInestables
        
        (ValoresPeligrosos)
        (Noticia
                (Empresa ?Nombre)
                (Tipo Mala))
        (Empresa
                (Nombre ?Nombre)
                (Valor ?valor)
                (Sector ?Sector))
        (Cartera
                (CotizCompra ?valor))
        

        =>
        (assert (Inestable 
                (Nombre ?Nombre)
                (Valor ?valor)
                (Sector ?Sector)
                (Explicacion "Este valor es inestable ya que existe una noticia negativa sobre su sector")))
)

(defrule ActualizarPeligrosos3DiasBaj
        
        (ValoresPeligrosos)
        (Inestable
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector))
        (Empresa
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (tresDiasBajada ?tresdiasbajada))
        (Cartera
                (CotizCompra ?Valor))


        =>

        (if (eq  ?tresdiasbajada 1) 
            then
            (assert (Peligroso 
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (Explicacion "Es un valor peligroso ya que era un valor inestable y lleva tres dias bajando")))
        )
)

(defrule ActualizarPeligrososDiferencia
        
        (ValoresPeligrosos)
        (Empresa
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (VariacionRespectoSectorCincoDias ?variacion))
        (Cartera
                (CotizCompra ?Valor))
        

        =>

        (if (eq ?variacion 0.05)
            then
            (assert (Peligroso 
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (Explicacion "Es un valor peligroso ya que la variacion con respecto a su sector es de un cinco porciento"))))
)

; Pasar a módulo de detección de valores sobrevalorados
;(defrule PasarModuloValoresPSobrevalorados
;    (declare (salience 6))
;   =>
;    (retract (ValoresPeligrosos))
;    (assert (ValoresSobrevalorados))
;)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; MÓDULO 2 DETECCIÓN SOBREVALORADOS
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defrule SobrevaloradosGenerales
        (ValoresSobrevalorados)
        (Empresa
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (PER ?ValorPer)
                (RPD ?ValorRPD)
        )
        =>

        (if (and (> ?ValorPer 18)(< ?ValorRPD 2))
           then
        (assert (Sobrevalorado
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (Explicacion "Es un valor sobrevalorado ya que su valor de PER es mayor de 18 y su valor de RPD es menor de 2"))
        )
        )
)

(defrule SobrevaloradoEmpresaPequena
        (ValoresSobrevalorados)
        (Empresa
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (PER ?ValorPer)
                (RPD ?ValorRPD)
                (PorcdelIBEX ?TipoEmpresa)
        )

        =>

        (if (< ?TipoEmpresa 0.02)
        then
        (if (> ?ValorPer 18)
        then
        (assert (Sobrevalorado
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (Explicacion "Es un valor sobrevalorado ya que su valor de PER es mayor de 18 y es una empresa pequena"))
        )       
        )
        [else
        (if (and(>  ?ValorPer 12)(and (<  ?ValorPer 18)(< ?ValorRPD 2)))
        then
        (assert (Sobrevalorado
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (Explicacion "Es un valor sobrevalorado ya que su valor de PER esta entre 12
                y 18 , su valor de RPD es bajo y es una empresa pequena"))
        ) 

        )]
        )
)


(defrule SobrevaloradoEmpresaGrande
        (ValoresSobrevalorados)
        (Empresa
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (PER ?ValorPer)
                (RPD ?ValorRPD)
                (PorcdelIBEX ?TipoEmpresa)
        )

        =>

        (if (> ?TipoEmpresa 0.05)
                then
                (if (and (or (> ?ValorPer 18)(or (> ?ValorPer 12)(< ?ValorPer 18)))(< ?ValorRPD 2))
                then
                (assert (Sobrevalorado
                        (Nombre ?Nombre)
                        (Valor ?Valor)
                        (Sector ?Sector)
                        (Explicacion "Es un valor sobrevalorado ya que su valor de PER es mayor de 18, o entre
                        12 y 18, el valor del RPD es menor de 2 y es una empresa grande"))
                )       
                )
                [else
                (if (and (>  ?ValorRPD 2)(and (<  ?ValorRPD 5)(> ?ValorPer 18)))
                then
                (assert (Sobrevalorado
                        (Nombre ?Nombre)
                        (Valor ?Valor)
                        (Sector ?Sector)
                        (Explicacion "Es un valor sobrevalorado ya que su valor de PER es mayor de 18,
                                valor de RPD esta entre 2 y 5, y es una empresa grande"))
                ) 

                )
                ]
        )
)

; Pasar a módulo de detección de valores infravalorados
;(defrule PasarModuloValoresPSobrevalorados
;    (declare (salience 4))
;    =>
;    (retract (ValoresSobrevalorados))
;    (assert (ValoresInfravalorados))
;)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; MÓDULO 3 DETECCIÓN INFRAVALORADOS
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defrule InfravaloradosGenerales
        
        (ValoresInfravalorados)
        (Empresa
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (PER ?ValorPer)
                (RPD ?ValorRPD)
        )
        =>

        (if (and (< ?ValorPer 12)(> ?ValorRPD 5))
                then
                (assert (Infravalorado
                        (Nombre ?Nombre)
                        (Valor ?Valor)
                        (Sector ?Sector)
                        (Explicacion "Es un valor infravalorado ya que su valor de PER es menor de 12 y su valor de RPD es mayor de 5"))
                )
        )
)

(defrule InfravaloradosCaida
        
        (ValoresInfravalorados)
        (Empresa
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Variacion ?Variacion)
                (Sector ?Sector)
                (VariacionMes ?CaidaMes)
                (VariacionAnual ?CaidaAnual)
                (VariacionTrimestre ?CaidatriMeses)
                (VariacionSemestre ?CaidaSemestre)
                (PER ?ValorPer)
                (RPD ?ValorRPD)
        )
        =>

        (if (and (< ?ValorPer 12)(and (< ?ValorPer 0.05)(or(> ?CaidaAnual 0.3)(or (> ?CaidatriMeses 0.3)(> ?CaidaSemestre 0.3)))))
                then
                (assert (Infravalorado
                        (Nombre ?Nombre)
                        (Valor ?Valor)
                        (Sector ?Sector)
                        (Explicacion "Es un valor infravalorado ya que su valor de PER es menor de 12, ha caido un 30% en los últimos 3 meses,6 meses o 12 meses,
                                y en el último mes ha crecido un poco"))
                )

        )
)

(defrule InfravaloradosEmpresaG
        
        (ValoresInfravalorados)
        (Empresa
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (VariacionMes ?CaidaMes)
                (VariacionAnual ?CaidaAnual)
                (VariacionTrimestre ?CaidatriMeses)
                (VariacionSemestre ?CaidaSemestre)
                (VariacionRespectoSectorCincoDias ?VariacionRespectoSector)
                (PER ?ValorPer)
                (RPD ?ValorRPD)
                (PorcdelIBEX ?TipoEmpresa)
        )

        =>

        (if (> ?TipoEmpresa 0.05)
        then
        (if (and (> ?VariacionRespectoSector 0.05)(and (> ?ValorRPD 5)(and (> ?ValorPer 12)(< ?ValorPer 18))))
                then
                (assert (Infravalorado
                        (Nombre ?Nombre)
                        (Valor ?Valor)
                        (Sector ?Sector)
                        (Explicacion "Es un valor infravalorado ya que se comporta mejor que su sector, es una empresa grande, tiene un RPD 
                                por encima de 5 y un PER entre 12 y 18"))
                )

        )
        )
)

; Pasar a módulo de realización de propuestas
(defrule PasarModuloRealizacionDePropuestas
    (declare (salience -2))
    ?I <- (ValoresInfravalorados)
    ?S <- (ValoresSobrevalorados)
    ?P <- (ValoresPeligrosos)
    =>
    (printout t crlf "*****Pasando al módulo de realización de propuestas*****" crlf)
    (retract ?I)
    (retract ?P)
    (retract ?S)
    (assert (HacerPropuesta))
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; MÓDULO 4.1 REALIZACIÓN DE PROPUESTAS
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defrule ProponerVenderValoresPeligrosos
        (declare (salience -3))
        (HacerPropuesta)
        (Cartera
                (Nombre ?Nombre)
        )
        (Peligroso 
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                ;(Explicacion ?Explicacion)
        )

        (Empresa
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (RPD ?ValorRPD)
                (VariacionMes ?VariacionMes)
                (VariacionRespectoSectorCincoDias ?VariacionRespectoSector)
        )

        
        =>
        
        (if (and (< ?VariacionMes 0)(< ?VariacionRespectoSector -0.03))
                then
                (assert (Propuesta
                        (Tipo Vender)
                        (Nombre ?Nombre)
                        (Nombre2 NADA)
                        (Valor ?Valor)
                        (Sector ?Sector)
                        (Explicacion "La empresa es peligrosa además está entrando en tendencia bajista con respecto a su sector
                                .Según mi estimación existe una probabilidad no despreciable de que puede caer al cabo del año un 20%, 
                                aun que produciera,ValorRPD por dividendos perderíamos un,ValorRPD - 20 %")
                        (RE (- ?ValorRPD 20)))
                        

                )
                

        )
)

(defrule ProponerComprarValoresInfravalorados
         (declare (salience -3))
         (HacerPropuesta)
         (PrimeraLinea
                (CantidadDisponible ?CantidadDisponible)
         )
        (Infravalorado
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                ;(Explicacion ?Explicacion)
        )

        (Empresa
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (PER ?ValorPer)
                (RPD ?ValorRPD)
                (VariacionMes ?VariacionMes)
                (VariacionRespectoSectorCincoDias ?VariacionRespectoSector)
        )
        (Sector
                (Nombre ?Sector)
                (PERmedio ?ValorPerMedio)
        )

        
        =>
        
        (if (and (> ?CantidadDisponible 0)(> ?ValorPer 0))
                then
                (assert (Propuesta
                        (Tipo Comprar)
                        (Nombre ?Nombre)
                        (Nombre2 NADA)
                        (Valor ?Valor)
                        (Sector ?Sector)
                        (Explicacion "Esta empresa está infravalorada y seguramente el PER tienda al 
                            PER medio en 5 años, con lo que  deberiamos revalorizar un  anual a lo que habría que 
                            sumar el ValorRPD% de beneficios por dividendos")
                        (RE (/ (* (- ?ValorPerMedio ?ValorPer) 100)(+ ?ValorRPD (* ?ValorPer 5))))
                        )

                )
                

        )
        (if (and (> ?CantidadDisponible 0)(= ?ValorPer 0)) then
            (assert (Propuesta
                        (Tipo Comprar)
                        (Nombre ?Nombre)
                        (Nombre2 NADA)
                        (Valor ?Valor)
                        (Sector ?Sector)
                        (Explicacion "Esta empresa está infravalorada y seguramente el PER tienda al 
                            PER medio en 5 años, con lo que  deberiamos revalorizar un  anual a lo que habría que 
                            sumar el ValorRPD% de beneficios por dividendos")
                        (RE ?ValorRPD)))

        )

)

(defrule ProponerVenderValoresSobrevalorados
        (declare (salience -3))
        (HacerPropuesta)
        (Cartera
                (Nombre ?Nombre)
        )
        (Sobrevalorado
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                ;(Explicacion ?Explicacion)
        )

        (Empresa
                (Nombre ?Nombre)
                (Valor ?Valor)
                (Sector ?Sector)
                (PER ?ValorPer)
                (RPD ?ValorRPD)
                (VariacionMes ?VariacionMes)
                (VariacionRespectoSectorCincoDias ?VariacionRespectoSector)
        )
        (Sector
                (Nombre ?Sector)
                (PERmedio ?ValorPerMedio)
        )

        
        =>
        (if (> ?ValorPer 0) then
        (if (< (+ ?ValorRPD (/(- ?ValorPer ?ValorPerMedio)(* 5 ?ValorPer)))(+ ?Valor 5)) then
            (assert (Propuesta
                            (Tipo Vender)
                            (Nombre ?Nombre)
                            (Nombre2 NADA)
                            (Valor ?Valor)
                            (Sector ?Sector)
                            (Explicacion "Esta empresa está sobrevalorada, es mejor amortizar lo invertido,ya que seguramente el PER tan alto 
                                    deberá bajar el PERMedio del sector en unos 5 años, con lo que se debería devaluar un (PERMedio­PER)*100/(5*PER) anual, 
                                    así que aunque se pierda el, ValorRPD de beneficios por dividendos saldría rentable")
                            (RE (+ ?ValorRPD (/(- ?ValorPer ?ValorPerMedio)(* 5 ?ValorPer))))

                    ))

        ))

        (if (= ?ValorPer 0) then
            (assert (Propuesta
                            (Tipo Vender)
                            (Nombre ?Nombre)
                            (Nombre2 NADA)
                            (Valor ?Valor)
                            (Sector ?Sector)
                            (Explicacion "Esta empresa está sobrevalorada, es mejor amortizar lo invertido,ya que seguramente el PER tan alto 
                                    deberá bajar el PERMedio del sector en unos 5 años, con lo que se debería devaluar un (PERMedio­PER)*100/(5*PER) anual, 
                                    así que aunque se pierda el, ValorRPD de beneficios por dividendos saldría rentable")
                            (RE ?ValorRPD)

                    ))
        )
        

)

(defrule PropuestaCambiarInversion
        (declare (salience -3))
        ;Para Volver al Módulo
        (HacerPropuesta)

        (Cartera
                (Nombre ?NombreEmpresa2)
                (Acciones ?CantidadDisponible)


        )
        (Empresa
                (Nombre ?NombreEmpresa1)
                (RPD ?ValorRPD1)
                (Valor ?Valor1)
                (Sector ?Sector1)
        )
        (Empresa
                (Nombre ?NombreEmpresa2)
                (RPD ?ValorRPD2)
                (Valor ?Valor2)
                (Sector ?Sector2)
        )

        (not (Sobrevalorado
                (Nombre ?NombreEmpresa1))
        )

        (not (Infravalorado
                (Nombre ?NombreEmpresa2))
        )

        

        =>
    
        (if (> (- ?ValorRPD1 ?ValorRPD2) 0)
            then
            (assert (Propuesta
                            (Tipo Cambiar)
                            (Nombre ?NombreEmpresa2)
                            (Nombre2 ?NombreEmpresa1)
                            (Valor ?Valor2)
                            (Sector ?Sector2)
                            (Explicacion "La empresa 1 debe tener una revalorización acorde con la evolución de la bolsa. Por dividiendos se espera un
                                    RDP% que es más alto que lo que está dando la empresa 2 por eso te propongo cambiar los valores de unas por las
                                    de esta otra. Aunque se pague el 1% del coste del cambio te saldría rentable.")
                            (RE (- ?ValorRPD1 ?ValorRPD2)))

            )
        
        )

)

; Pasar a módulo de realización de propuestas
(defrule PasarModuloMostrarPropuestas
    (declare (salience -4))
    ?H <- (HacerPropuesta)
    =>
    (printout t crlf "**************************" crlf)
    (printout t      "***     PROPUESTAS     ***" crlf)
    (printout t      "**************************" crlf)
    (retract ?H)
    (assert (MostrarPropuesta))
    (assert (ContadorHechos (Contador 1)))
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; MÓDULO 4.2 MOSTRAR PROPUESTAS AL USUARIO
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Variable global para tener un control de cuentas propuestas se muestran
;(defglobal ?*contadorMostrarPropuestas* = 0)

;Muestra las 5 mejores propuestas al usuario basándose en el RE
(defrule Mostrar5MejoresPropuestas
    (declare (salience -4))
    ?M <- (MostrarPropuesta) 
    ?C <- (ContadorHechos (Contador ?Cont))
    ?P1 <- (Propuesta
        (Tipo ?Tipo1)
        (Nombre ?Nombre1)
        (Valor ?Valor1)
        (Sector ?Sector1)
        (Explicacion ?Explicacion1)
        (RE ?RE1)
        (Cod ?cod)
    )
    
    =>
    ;Insertamos propuesta aux
    (assert (PropuestaAux
        (Tipo ?Tipo1)
        (Nombre ?Nombre1)
        (Valor ?Valor1)
        (Sector ?Sector1)
        (Explicacion ?Explicacion1)
        (RE ?RE1)
        (Cod ?Cont)))
    (printout t crlf ?Cont". La propuesta es de tipo "?Tipo1", para la empresa "?Nombre1" que tiene valor 
        "?Valor1" perteneciente al sector "?Sector1" y deberías "?Tipo1" ya que el RE esperado es "?RE1"
        ya que "?Explicacion1 crlf)
    ;(modify ?P1 (Cod ?Cont))
    (retract ?M)
    (assert (ContadorHechos (Contador (+ ?Cont 1))))
    (retract ?C)
    (retract ?P1)
    (if (< ?Cont 5)
        then
        (assert (MostrarPropuesta))
    )
    (assert (MostrarUltimaOpcion))
)

;Mostrar la última opción que es no hacer nada y nos permite pasar a realizar una elección
(defrule UltimaOpcion
    (declare (salience -5))
    ?U <- (MostrarUltimaOpcion)
    ?C <- (ContadorHechos (Contador ?Cont))
    =>
    (printout t crlf "6. No hacer nada y salir" crlf)
    (assert (PropuestaAux
        (Cod 6)))
    (assert  (HacerEleccion))
    (retract ?C)
    (retract ?U)
)
;El usuario introduce por pantalla una decisión
(defrule RealizarUnaEleccion
    (declare (salience -6))
    ?H <- (HacerEleccion)
    =>
    (printout t crlf "Escribe el número de la opción que deseas realizar ")
    (bind ?cod (read))
    (retract ?H)
    (assert (Elegido ?cod))

)

;Comprobación de la elección del usuario
(defrule ComprobarEleccion
    (declare (salience -7))
    ?E <- (Elegido ?cod)
    ?P <- (PropuestaAux
        (Tipo ?Tipo)
        (Nombre ?Nombre1)
        (Nombre2 ?Nombre2)
        (Valor ?Valor)
        (Sector ?Sector)
        (Explicacion ?Explicacion)
        (RE ?RE1)
        (Cod ?cod)
    )

    ?Primera <- (PrimeraLinea
        (Disponible ?Disponible)
        (CantidadDisponible ?CantidadD)
        (CantidadDisponible2 ?CantidadD2)
    )


    =>

    ;(close micartera) ; La cerramos para sobreescribir
    ;(open "Cartera.txt" micartera "w") ;Abrimos la cartera
    ;Si es del tipo comprar
    (if (eq ?Tipo Comprar)
        then
        (printout t "¿Cuánto quieres comprar?" crlf)
        (bind ?cantidad (read))
        (modify ?Primera (CantidadDisponible (- ?CantidadD (* ?cantidad ?Valor)))(CantidadDisponible2 (- ?CantidadD (* ?cantidad ?Valor))))
        (assert (Cartera (Nombre ?Nombre1)(Acciones ?cantidad)(CotizCompra ?Valor)))
        (printout t crlf "*****Compra realizada****" crlf)
        (printout t crlf "*****Volviendo a examinar posibles propuestas*****" crlf)
        ;Hacer que vuelva al módulo 4.1
        (assert (HacerPropuesta))
        (retract ?P) ;ELiminamos la propuesta ya elegida de la base de hechos
        (retract ?E)
    )
    ;Si es del tipo vender
    (if (eq ?Tipo Vender)
        then
        (printout t "¿Cuánto quieres vender?" crlf)
        (bind ?cantidad (read))
        (modify ?Primera (CantidadDisponible (+ ?CantidadD (* ?cantidad ?Valor)))(CantidadDisponible2 (+ ?CantidadD (* ?cantidad ?Valor))))
        (printout micartera  "DISPONIBLE " (+ ?CantidadD (* ?cantidad ?Valor)) " " 
            (+ ?CantidadD2 (* ?cantidad ?Valor)) crlf)
        (assert (RealizarVenta ?cantidad ?Valor ?Nombre1))
        (retract ?P) ;ELiminamos la propuesta ya elegida de la base de hechos
        (retract ?E)
    )
    ;Si es del tipo cambiar
    (if (eq ?Tipo Cambiar)
        then
        (printout t "¿Cuánto quieres cambiar?" crlf)
        (bind ?cantidad (read))
        ;(modify ?Primera (CantidadDisponible (-(* ?cantidad ?Valor)(* ?cantidad ?ValorEmpresa2)))
        ;    (CantidadDisponible2 (-(* ?cantidad ?Valor)(* ?cantidad ?ValorEmpresa2))))
        ;(printout micartera "DISPONIBLE " 
        ;    (+ ?CantidadD (-(* ?cantidad ?Valor)(* ?cantidad ?ValorEmpresa2))) " " 
        ;    (+ ?CantidadD2 (-(* ?cantidad ?Valor)(* ?cantidad ?ValorEmpresa2))) crlf)
        (assert (RealizarCambio ?cantidad ?Valor ?Nombre1 ?Nombre2))
        ;(retract ?P) ;ELiminamos la propuesta ya elegida de la base de hechos
        (retract ?E)
    )
    (if (= ?cod 6)
        then
        (printout t crlf crlf "¡MUCHAS GRACIAS POR HABER CONFIADO EN ESTE SISTEMA EXPERTO EN BOLSA!" crlf)
    )
)

;Realizar una venta de elección por el usuario de las que se le han propuesto
(defrule RealizarVenta
    (declare (salience -8))
    ?R <- (RealizarVenta ?cantidad ?Valor ?Nombre1)
    ?ValorCarteraCambiar <- (Cartera
                (Nombre ?Nombre1)
                (Acciones ?Acciones1)
                (CotizCompra ?CotizCompra1)
    )
    (Empresa
        (Nombre ?Nombre1)
        (Valor ?Valor)
    )

    =>

    (modify ?ValorCarteraCambiar (Acciones (- ?Acciones1 ?cantidad))(CotizCompra ?Valor))
    (retract ?R)
    (printout t crlf "*****Venta realizada*****" crlf)
    (printout t crlf "*****Volviendo a examinar posibles propuestas******" crlf)
    ;Hacer que vuelva al módulo 4.1
    (assert (HacerPropuesta))
    (retract ?R)

)


;Realizar un cambio de elección por el usuario de las que se le han propuesto
(defrule RealizarCambio
    (declare (salience -8))
    ?R <- (RealizarCambio ?cantidad ?Valor ?Nombre1 ?Nombre2)
    ?ValorCarteraCambiar <- (Cartera
                (Nombre ?Nombre1)
                (Acciones ?Acciones1)
                (CotizCompra ?CotizCompra1)
    )
    (Empresa 
        (Nombre ?Nombre2)
        (Valor ?ValorEmpresa2)
    )

    =>

    (modify ?ValorCarteraCambiar (Acciones (- ?Acciones1 ?cantidad)))
    (assert (Cartera (Nombre ?Nombre2)(Acciones ?cantidad))(CotizCompra ?ValorEmpresa2))
    (retract ?R)
    (printout t crlf "*****Cambio realizado*****" crlf)
    (printout t crlf "*****Volviendo a examinar posibles propuestas*****" crlf)
    ;Hacer que vuelva al módulo 4.1
    (assert (HacerPropuesta))

)