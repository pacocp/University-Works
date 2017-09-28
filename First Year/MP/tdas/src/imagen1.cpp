/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
/** 

  * @file imagen1.cpp
  * @brief Fichero con las definiciones para la Entrada/Salida de imágenes de estructura del tipo 1.
  *
  * Permite la Entrada/Salida de archivos de tipo PGM.
  */
#include "imagenES.h"
#include "imagen.h"
#include <iostream>




void Crear (Imagen& img, int f, int c) // Reserva recursos
     {
        img.filas = f;
        img.columnas = c;
        img.puntero = new unsigned char [f*c];
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
         img.puntero[i*img.filas+j] = v;
     }
unsigned char Get (const Imagen& img, int i, int j)  // Devuelve img(i,j)
     {
        return img.puntero[i*img.filas+j];
     }
void Destruir (Imagen& img) // Libera recursos de m
    {
        delete [] img.puntero;
    }
bool LeerImagen(const char file[], Imagen& img) // Carga imagen file en img 
{
    bool resultado = false;
    TipoImagen Tipo;
    int f_aux, c_aux;
    Tipo = LeerTipoImagen (file,f_aux, c_aux);
    if(Tipo == IMG_PGM)
    {
       Crear(img,f_aux,c_aux);
       resultado = LeerImagenPGM (file,f_aux,c_aux ,img.puntero);
    }
    return resultado;
}
bool EscribirImagen(const char file[], const Imagen& img) //Salva img en file
{
    
    bool resultado;
    TipoImagen Tipo;
    int f_aux, c_aux;
    Tipo = LeerTipoImagen (file, f_aux,c_aux);
    resultado = EscribirImagenPGM (file,img.puntero,img.filas,img.columnas);
    
    
    return resultado;
}
/* Fin Fichero: imagen1.cpp */
