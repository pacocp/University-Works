/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
/**
  * @file ocultar.cpp
  * @brief Fichero con el main que hace el programa para ocultar un mensaje en una imágen de tipo PGM o PPM.
  *
  * 
  */

#include <iostream> 
using namespace std;
#include "codificar.h"


int main()
{
	
    	const int MAXBUFFER= 1000000;
        TipoImagen imag;
    	const int MAXNOMBRE= 100;
        char nombre_imagen[MAXNOMBRE];
	char nombre_imagen_salida[MAXNOMBRE];
        const int MAXMSG = MAXBUFFER / 8;
        char cad[MAXMSG];
        const char extension_ppm [] = {'.','p','p','m'};
        const char extension_pgm [] = {'.','p','g','m'};
    	unsigned char buffer[MAXBUFFER];
        int filas, columnas, Tamimagen;
        bool resultado,lectura;
    
  	cout << "Introduzca la imagen de entrada: " << endl;
	cin.getline(nombre_imagen,MAXNOMBRE);
	// Lee el tipo de la imagen
	imag = LeerTipoImagen(nombre_imagen,filas,columnas);
        if(imag == IMG_PGM)
         {
           cout << "Introduzca la imagen de salida: " << endl;
           cin.getline(nombre_imagen_salida,MAXNOMBRE);
           Extension(nombre_imagen_salida,extension_pgm);
           cout << "Introduzca el mensaje: " << endl;
           cin.getline(cad,MAXMSG);
           // Nos mete los bits en el buffer
	   lectura = LeerImagenPGM ( nombre_imagen,  filas,  columnas,  buffer);
           Tamimagen = filas*columnas*3;
           resultado = Ocultar( buffer, cad, Tamimagen);
           resultado = EscribirImagenPGM (nombre_imagen_salida, buffer, filas, columnas);
           if(resultado == true)
		{
			cout << "La frase ha sido ocultada " << endl;
		}
	}
	else
		{
			if(imag == IMG_PPM)
				{
                                         cout << "Introduzca la imagen de salida: " << endl;
                                         cin.getline(nombre_imagen_salida,MAXNOMBRE);
                                         Extension(nombre_imagen_salida,extension_ppm);
                                         cout << "Introduzca el mensaje: " << endl;
                                         cin.getline(cad,MAXMSG);
					 lectura = LeerImagenPPM (nombre_imagen,  filas,  columnas,  buffer);
                                         Tamimagen = filas*columnas*3;
          				 resultado = Ocultar( buffer, cad, Tamimagen);
                                         resultado = EscribirImagenPPM (nombre_imagen_salida, buffer, filas, columnas);
           				 if(resultado == true)
						{
			                            cout << "La frase ha sido ocultada " << endl;
						}
		                 }
                        else
                                {
                                     // en el caso de que la imagen no tenga formato ni PPM ni PGM
			             cout << "La imagen tiene un formato incompatible" << endl;
			
		                }
                 }
}

/* Fin Fichero: ocultar.cpp */

    
     
    

