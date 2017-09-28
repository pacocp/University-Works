/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
/**
  * @file imagen3.h
  * @brief Fichero para la cabecera de las funciones con la estructura de tipo imágen 3.
  *
  *
  */
#ifndef __IMAGEN3_H__
#define __IMAGEN3_H__

/**
  * @brief Estructura para definir una imágen del tipo imágen 3.
  *
  */
struct Imagen
         {
           int filas;
           int columnas;
           unsigned char **puntero;
           
          };
 
/**
  * @brief Funcion para reservar recursos para almacenar una imágen del tipo imágen 3.
  *
  * @param img Nombre de la imágen del tipo imágen 3, donde se guardan los datos.
  * @param f Parámetro de las filas de la imágen img.
  * @param c Parámetro de las columnas de la imágen img.
  *
  */
void Crear (Imagen& img, int f, int c); 
/**
  * @brief Funcion que nos dice el número de filas que tiene la imágen img.
  *
  * @param img Nombre de la imágen del tipo imágen 3, de la cuál queremos saber el número de filas que tiene.
  * @return Devuelve el número de filas que tiene la imágen img.
  *
  */
int Filas (const Imagen& img); 
/**
  * @brief Funcion que nos dice el número de columnas que tiene la imágen img.
  *
  * @param img Nombre de la imágen del tipo imágen 3, de la que queremos saber el número de columnas que tiene.
  * @return Devuelve el número de columnas que tiene la imágen img.
  *
  */
int Columnas (const Imagen& img); 
/**
  * @brief Funcion que cambia el valor del char de la posición (i,j) por el valor de "v" de la imágen del tipo 3, img. 
  *
  * @param img Nombre de la imágen del tipo imágen 3.
  * @param i Parámetro que nos dice la posición del char en las filas de la imágen img.
  * @param j Parámetro que nos dice la posición del char en las columnas de la imágen img.
  * @param v Valor del nuevo char que queremos poner en la posición (i, j).
  *
  */
void Set (Imagen& img, int i, int j, unsigned char v); 
/**
  * @brief Funcion que nos dice el valor del char que está en la posición (i,j) en la imágen del tipo 3, img.
  *
  * @param img Nombre de la imágen del tipo imágen 3.
  * @param i Parámetro que nos dice la posición del char en las filas de la imágen, img.
  * @param j Parámetro que nos dice la posición del char en las columnas de la imágen, img.
  * @return Devuelve el char que está en la posición (i,j).
  *
  */
unsigned char Get (const Imagen& img, int i, int j); 
/**
  * @brief Funcion que borra la memoria dinámica dónde se creo la imágen del tipo imágen tipo 3, img.
  *
  * @param img Nombre de la imágen del tipo imágen 3, que está en memoria dinámica.
  */
void Destruir (Imagen& img); 
/**
  * @brief Funcion que pasa los datos de la imágen file a la estructura de imágen tipo 3, img.
  *
  * @param file Nombre de la imágen del tipo PGM.
  * @param img Nombre de la imágen del tipo imágen 3.
  *
  */
bool LeerImagen(const char file[], Imagen& img); 
/**
  * @brief Funcion que crea una imágen en formato PGM, file, con los datos de la imágen del tipo 3, img.
  *
  * @param file Nombre de la imágen del tipo PGM.
  * @param img Nombre de la imágen del tipo imágen 3.
  *
  */
bool EscribirImagen(const char file[], const Imagen& img); 
#endif
/** Fin del archivo imagen3.h **/
