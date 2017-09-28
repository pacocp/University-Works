/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
#include <iostream>
using namespace std;
#include "transformacion.h"
#include "imagen.h"
int main(int argc, char*argv[])
{
	if(argc !=4)
	{
		cout << "Error en el número de argumentos" << endl;
		cout << "Ejemplo de forma de ejecución: " << endl;
		cout << "transformar lenna.pgm carboncillo_txt.trf lenna_carbon.pgm" << endl;
	}
	else
	{
		Imagen img;
		Transformacion trans;
		if(img.LeerImagen(argv[1]))
		{
			if(trans.Leertransformacion(argv[2]))
			{
				
				for(int i =0; i<img.Filas();i++)
   					 {
       					 for(int j=0; j<img.Columnas();j++)
       							 {
       							 	
           							 img.Set(i,j,trans.Get(img.Get(i,j)));
         						}	
  					  }
				
					if(img.EscribirImagen(argv[3]))
					{
						cout << "Imagen con transformacion creada" << endl;
					}
					else
					{
						cout << "Error al crear la imagen" << endl;
					}

				
			}
			else
			{
				cout << "Error al leer la transformacion" << endl;
			}
			
		}
		else
		{
			cout << "Error al leer la imagen" << endl;
		}
		
		
		
	}
}
