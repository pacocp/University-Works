/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
/**
  * @file imagen4.h
  * @brief Fichero para la cabecera de las funciones con la estructura de tipo imágen 4.
  *
  *
  */
#ifndef __IMAGEN4_H__
#define __IMAGEN4_H__

/**
  * @brief Estructura para definir una serie de celdas enlazadas, desde las que salen los vectores con los datos de cada fila de la imágen, todo en memoria dinámica.
  *
  */

struct Celda
{
	unsigned char *p;  ///< Puntero a un vector con los datos las filas de la imágen.
	Celda *sig;      ///< Puntero a la siguiente celda de esta misma estructura.
};

/**
  * @brief Estructura para definir una imágen del tipo imágen 4.
  *
  */

struct Imagen
{
	int columnas;     ///< Parámetro de las columnas de la imágen del tipo 4.
	Celda *filas;  ///< Puntero a una serie de celdas enlazadas, desde las que salen los vectores con los datos de cada fila de la imágen.
};

/**
  * @brief Funcion para reservar recursos para almacenar una imágen del tipo imágen 4.
  *
  * @param img Nombre de la imágen del tipo imágen 4, donde se guardan los datos.
  * @param f Parámetro de las filas de la imágen Img.
  * @param c Parámetro de las columnas de la imágen img.
  *
  */

void Crear (Imagen& img, int f, int c);

/**
  * @brief Funcion que nos dice el número de filas que tiene la imágen img.
  *
  * @param img Nombre de la imágen del tipo imágen 4, de la cuál queremos saber el número de filas que tiene.
  * @return Devuelve el número de filas que tiene la imágen img.
  *
  */

int Filas (const Imagen& img);

/**
  * @brief Funcion que nos dice el número de columnas que tiene la imágen img.
  *
  * @param img Nombre de la imágen del tipo imágen 4, de la que queremos saber el número de columnas que tiene.
  * @return Devuelve el número de columnas que tiene la imágen img.
  *
  */

int Columnas (const Imagen& img);

/**
  * @brief Funcion que cambia el valor del char de la posición (i,j) por el valor de "v" de la imágen del tipo 4, img. 
  *
  * @param img Nombre de la imágen del tipo imágen 4.
  * @param i Parámetro que nos dice la posición del char en las filas de la imágen img.
  * @param j Parámetro que nos dice la posición del char en las columnas de la imágen img.
  * @param v Valor del nuevo char que queremos poner en la posición (i, j).
  *
  */

void Set (Imagen& img, int i, int j, unsigned char v);

/**
  * @brief Funcion que nos dice el valor del char que está en la posición (i,j) en la imágen del tipo 4, img.
  *
  * @param img Nombre de la imágen del tipo imágen 4.
  * @param i Parámetro que nos dice la posición del char en las filas de la imágen, img.
  * @param j Parámetro que nos dice la posición del char en las columnas de la imágen, img.
  * @return Devuelve el char que está en la posición (i,j).
  *
  */

unsigned char Get (const Imagen& img, int i, int j);

/**
  * @brief Funcion que borra la memoria dinámica dónde se creo la imágen del tipo imágen tipo 4, img.
  *
  * @param img Nombre de la imágen del tipo imágen 4, que está en memoria dinámica.
  */

void Destruir (Imagen& img); 

/**
  * @brief Funcion que pasa los datos de la imágen file a la estructura de imágen tipo 4, img.
  *
  * @param file Nombre de la imágen del tipo PGM.
  * @param img Nombre de la imágen del tipo imágen 4.
  *
  */

bool LeerImagen (const char file[], Imagen& img);

/**
  * @brief Funcion que crea una imágen en formato PGM, file, con los datos de la imágen del tipo 4, img.
  *
  * @param file Nombre de la imágen del tipo PGM a crear.
  * @param img Nombre de la imágen del tipo imágen 4.
  *
  */

bool EscribirImagen (const char file[], const Imagen& img); 

#endif

/** Fin del archivo imagen4.h **/
