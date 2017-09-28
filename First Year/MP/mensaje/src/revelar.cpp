/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
/**
  * @file revelar.cpp
  * @brief Fichero con el main para el programa para revelar el mesaje incrustado en una imagen de tipo PGM o PPM.
  *
  * 
  */

#include <iostream> 

using namespace std;
#include "codificar.h"

int main()
{
	TipoImagen imag;
    	const int MAXBUFFER= 1000000;
        const int MAXMSG = MAXBUFFER / 8;
    	const int MAXNOMBRE= 100;
    	char nombre_imagen[MAXNOMBRE];
        char cad[MAXMSG];
    	unsigned char buffer[MAXBUFFER];
        int filas, columnas, Tamimagen;
        bool resultado, lectura, fallo;
    
  	cout << "Introduzca la imagen de entrada: " << endl;
	cin.getline(nombre_imagen,MAXNOMBRE); // Lee el tipo de imagen que tenemos
	imag = LeerTipoImagen(nombre_imagen,filas,columnas);
        Tamimagen = filas*columnas*3;
        if(imag == IMG_PGM)
         {
           // Introduce los bits de esa imagen en buffer
           lectura  = LeerImagenPGM ( nombre_imagen,  filas,  columnas,  buffer);
           // Revela la imagen
           resultado = Revelar(buffer,cad, Tamimagen, MAXMSG);
           
           if(resultado == true)
                   {
			cout << "La frase oculta es :  " << endl;
                        cout << cad << endl;
                   }
           else
               {
                 cout << "Error" << endl;
               }
                            
                               
                           
		
           
          }
	 if(imag == IMG_PPM)
		{
			 lectura = LeerImagenPPM ( nombre_imagen,  filas,  columnas,  buffer);
                         Tamimagen = filas*columnas*3;
                         resultado = Revelar(buffer, cad,Tamimagen,MAXMSG);
           		 if(resultado == true)
			     {
			        cout << cad << endl ;
                                                      
			     }
                         else
                             {
                                cout << "Error" << endl;
	                     }
				
		}
        
	if (lectura == false)
	{
		cout << "Se produjo un error en la imagen de entrada" << endl;
		
	}

}
/* Fin de revelar.cpp */
