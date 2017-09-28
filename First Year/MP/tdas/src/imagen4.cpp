/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
/** 

  * @file imagen4.cpp
  * @brief Fichero con las definiciones para la Entrada/Salida de imágenes de estructura del tipo 4.
  *
  * Permite la Entrada/Salida de archivos de tipo PGM.
  */
#include <iostream>
#include "imagenES.h"
#include "imagen.h"


using namespace std;

void Crear (Imagen& img, int f, int c)
{
	int contador = 0;
	img.filas = 0;
	
	while (contador < f)
	{
	
		Celda *aux = new Celda ;
		(*aux).p = new unsigned char [c];
		(*aux).sig = img.filas;
		img.filas = aux;
	
		contador++;
	}
	
	img.columnas = c;
  
}

int Filas (const Imagen& img)
{	
	Celda * contador = img.filas;
	int filas = 0;
	
	while(contador != 0)
	{	
		filas++;
		contador = (*contador).sig;
	}
	
	return filas;
}

int Columnas (const Imagen& img)
{						
	return img.columnas;
}

void Set (Imagen& img, int i, int j, unsigned char v)
{ 
	Celda *contador = img.filas;
	int filas=0;
	
	while (filas != i)
	{
		filas++;
		contador = (*contador).sig;	
	}
	
	contador -> p[j] = v;
}

unsigned char Get (const Imagen& img, int i, int j)
{	
	Celda *contador = img.filas;
	int filas = 0;
	
	while (filas != i)
	{	
		filas++;
		contador = (*contador).sig;
	
	}
	
	return contador -> p[j];
}

void Destruir (Imagen& img)
{							
	while (img.filas != 0)
	{	
		Celda *aux = img.filas;
		img.filas = img.filas -> sig;
		delete[] (*aux).p;
		delete aux;	
	}
}

bool  LeerImagen (const char file[], Imagen& img)
{ 
	int filas,columnas;							
	unsigned char *buffer;
    bool resultado;
	TipoImagen Tipo;
	Tipo = LeerTipoImagen (file,filas,columnas);
	Crear(img,filas,columnas);
	buffer = new unsigned char [filas*columnas];
    resultado = LeerImagenPGM (file, filas, columnas, buffer);
	for (int f = 0; f < filas; f++)
	{
		for (int c = 0; c < columnas; c++)
		{		
			Set (img, f, c, buffer[f*columnas+c]);	
	    }	
		
	}
    delete [] buffer;
    return resultado;
}

bool EscribirImagen (const char file[], const Imagen& img)
{
	int fila;
	unsigned char * buffer;
    bool resultado;
    fila = Filas(img);
	buffer = new unsigned char [fila*Columnas(img)];
	
	
	for (int f = 0; f < fila; f++)
	{	
		for (int c = 0; c <Columnas(img); c++)
		{		
			buffer[f*Columnas(img)+c] = Get (img, f, c);			
		}	
	}

	
	
    resultado =  EscribirImagenPGM (file, buffer, fila, Columnas(img));
		
	
	
    delete [] buffer;
    return resultado;	
}


/* Fin Fichero: imagen4.cpp */
