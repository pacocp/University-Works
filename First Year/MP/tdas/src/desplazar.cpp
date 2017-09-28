/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/


/**
  * @file desplazar.cpp
  * @brief Fichero con el main que hace el programa para pasar desplazar un número de bits en cada byte de una imágen de tipo PGM.
  *
  * 
  */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "imagenES.h"
#include "transformar.h"
#include "imagen.h"
using namespace std;

int main(int argc, const  char * argv[])
{
    if(argc != 4)
    {
      cout << "Error en el número de argumentos" << endl;
    }
    else
    {

    bool resultado;
    Imagen img;
    int filas,columnas,a;
    TipoImagen Tipo;
    Tipo = LeerTipoImagen(argv[2],filas,columnas);
    Crear(img, filas, columnas);
    resultado = LeerImagen(argv[2],img);
    	
    if(resultado == true)
	  {
	  	    
             a = atoi(argv[1]);
             Desplazar(img,a);
	     resultado = EscribirImagen(argv[3],img);
	     
             if(resultado == true)
              {
              	cout << "La imagen ha sido creada con éxito" << endl;
              
              }
              else
              {
                cout << "Error al crear la imagen" << endl;
                
              }
    }
              
           
	else
        {
          	cout << "Ha ocurrido un error en la lectura " << endl;
                
         }
   Destruir (img);
    }
}
/* Fin Fichero: desplazar.cpp */
