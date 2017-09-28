; Datos de personas

(deftemplate Persona 
            (field Nombre)
            (field ColorOjos)
            (field ColorPelo)
)

(defrule ParejaComplicada
	(Persona
		(Nombre ?N1)
		(ColorOjos ?Ojos1 & azul|verde)
		(ColorPelo ?Pelo1 & ~negro))
	(Persona
		(Nombre ?N2 & ~?N1)
		(ColorOjos ?Ojos2 & ~?Ojos1)
		(ColorPelo ?Pelo2 & rojo | ?Pelo1))
	=>
		(printout t ?N1 " tiene los ojos " ?Ojos1
		" y el pelo " ?Pelo1 crlf
		?N2 " tiene los ojos " ?Ojos2
		" y el pelo " ?Pelo2 crlf))



