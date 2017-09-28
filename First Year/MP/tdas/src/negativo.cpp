/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
/** 

  * @file negativo.cpp
  * @brief Fichero con el main que crea el negativo de una imagen de tipo PGM.
  *
  * 
  */
#include <iostream>
#include "imagenES.h"
#include "transformar.h"
#include "imagen.h"
using namespace std;

int main(int argc, const char * argv[])
{
    if(argc != 3)
    {
      cout << "Error en el número de argumentos" << endl;
    }
    else
    {
	
    bool resultado;
    Imagen img;
    resultado = LeerImagen(argv[1],img);
    if(resultado == true)
	  {
             Negativo(img);
	           resultado = EscribirImagen(argv[2],img);	
             if(resultado == true)
              {
              	cout << "La imagen ha sido creada con éxito" << endl;
              	
              }
              else
              {
                cout << "Error al crear la imagen" << endl;
                
              }
             Destruir (img);
       }
              
           
	else
              {
          	cout << "Ha ocurrido un error en la lectura " << endl;
              }
    }
}
/* Fin Fichero: negativo.cpp */
