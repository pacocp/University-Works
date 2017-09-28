/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
/** 

  * @file transformar.cpp
  * @brief Fichero con las definiciones para las funciones Negativo y Desplazar.
  *
  * Permite  pasar a negativo o desplazar un número de bits los bytes de los archivos de tipo PGM.
  */

#include <iostream>
#include "transformar.h"


void Negativo(Imagen& img)
{
  
   for(int i = 0; i< Filas(img) ; i++)
      {
         for(int j = 0; j < Columnas(img) ; j++)
            {
              Set(img,i,j, 255 - Get(img,i,j));
            }
       }
}
//----------------------------------------------------------

void Desplazar(Imagen& img, int  n)
{
        unsigned char aux;
	
	for (int i = 0; i < Filas(img); i++)
	{	
		for (int j = 0; j < Columnas(img); j++)
		{			
		        aux = Get (img, i, j) << n;
			Set (img, i, j, aux);		
		}	
	}
  
}
/* Fin Fichero: transformar.cpp */
