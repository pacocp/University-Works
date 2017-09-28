/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
/** 
  * @file imagen2.cpp
  * @brief Fichero con las definiciones para la Entrada/Salida de imágenes de estructura del tipo 2.
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
        img.puntero = new unsigned char *[f];
        for(int i = 0; i < f ; i++)
        {
        	img.puntero[i] = new unsigned char [c];
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
        for (int i = 0; i < img.filas; i++)
         {
             delete [] img.puntero[i];     
         }
        delete [] img.puntero;
    }
bool LeerImagen(const char file[], Imagen& img) // Carga imagen file en img
{
    unsigned char *buffer;
    bool resultado = false;
    int f_aux,c_aux;
    TipoImagen Tipo;
    Tipo = LeerTipoImagen(file,f_aux,c_aux);
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
    bool resultado = false;
    int f_aux ,c_aux; 
    f_aux = Filas(img);
    c_aux = Columnas(img);
    buffer = new unsigned char [f_aux*c_aux];
    for (int f = 0; f < f_aux; f++)
    {   
        for (int c = 0; c < c_aux; c++)
        {       
            buffer[f*c_aux+c] = img.puntero[f][c];      
        }   
    }

       
    resultado = EscribirImagenPGM (file,buffer, img.filas, img.columnas);
    

    
    return resultado;
}
/* Fin Fichero: imagen2.cpp */
