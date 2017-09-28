(deffacts HechoPrimero
          (FichaPaciente 
                (Nombre Pedro)
                (Casado SI)
                (Direccion H))
)

(deffacts HechoSegundo
          (FichaPaciente 
                (Nombre Juan)
                (Casado NO)
                (Direccion SI))
)

(deffacts DiagnosticoPrimero
        (DatosExploracion
                (Nombre Pedro)
                (Sintomas Perro picor Verde vesiculas Azul))
)

(deffacts DiagnosticoSegundo
        (DatosExploracion
                (Nombre Juan)
                (Sintomas Loco picor Verde vesiculas Morado))
)