/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
/** 

  * @file imagen3.cpp
  * @brief Fichero con las definiciones para la Entrada/Salida de imágenes de estructura del tipo 3.
  *
  * Permite la Entrada/Salida de archivos de tipo PGM.
  */
#include <iostream>
#include "imagen.h"
#include "imagenES.h"



void Crear (Imagen& img, int f, int c) // Reserva recursos
     {
        img.filas = f;
        img.columnas = c;
        img.puntero = new unsigned char * [f];
	img.puntero[0] = new unsigned char [f*c];

	for (int i=1; i < f; i++)
	{
		img.puntero[i] = img.puntero[i-1]+c;	
	}
        
     }
int Filas (const Imagen& img) // Devuelve el número filas de m
     { 
        return img.filas;
     } 
int Columnas (const Imagen& img) // Devuelve el número columnas de m
     {
        return img.columnas;
     }
     
void Set (Imagen& img, int i, int j, unsigned char v) // Hace img(i,j)=v
     {
         img.puntero[i][j] = v;
     }
unsigned char Get (const Imagen& img, int i, int j)  // Devuelve img(i,j)
     {
        return img.puntero[i][j];
     }
void Destruir (Imagen& img) // Libera recursos de m
    {
        delete img.puntero[0];
	delete [] img.puntero;
    }
bool LeerImagen(const char file[], Imagen& img) // Carga imagen file en img
    {
        unsigned char *buffer;
       
        TipoImagen Tipo;
        int f_aux,c_aux;
	      bool resultado = false;
	      Tipo = LeerTipoImagen (file, f_aux,c_aux);
        Crear(img,f_aux,c_aux);
        buffer = new unsigned char [f_aux*c_aux];
	      resultado = LeerImagenPGM (file, f_aux, c_aux, buffer);
        for (int f = 0; f < f_aux; f++)
               {
                   for (int c = 0; c < c_aux; c++)
                        {       
                            Set (img, f, c, buffer[f*c_aux+c]);      
                         }   
                         
		}
       delete [] buffer;
       return resultado;


    }
bool EscribirImagen(const char file[], const Imagen& img) //Salva img en file
    {
        unsigned char *buffer;
        int f_aux,c_aux;
        f_aux = Filas(img);
        c_aux = Columnas(img);
        buffer = new unsigned char [f_aux*c_aux]; 
        bool resultado = false;
	      for (int f = 0; f < img.filas; f++)
        {   
              for (int c = 0; c < img.columnas; c++)
               {       
                   buffer[f*c_aux+c] = img.puntero[f][c];      
               }   
        }
      
	resultado = EscribirImagenPGM (file, buffer, img.filas, img.columnas);
		
       delete [] buffer;
       return resultado;
    }
/* Fin Fichero: imagen3.cpp */
