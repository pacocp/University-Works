/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
/**
  * @file codificar.h
  * @brief Fichero para la cabecera para las funciones Ocultar y Revelar.
  *
  *
  */

#ifndef _CODIFICAR__H_
#define _CODIFICAR__H_
#include "imagenES.h"

/**
  * @brief Funcion que oculta un mensaje en una imágen en formato PGM o PPM.
  *
  * @param buffer Parámetro de la imagen a la que deseamos insertar el mensaje oculto.
  * @param Tamimagen Parámetro de entrada que específica el tamaño de la imagen en la que insertaremos el mensaje oculto.
  * @param cad Parámetro de entrada con el mensaje que deseeamos ocultar.
  * @return Devuelve true si el mensaje se ha podido ocultar.
  * @return Devuelve false si el mensaje no se ha podido ocultar.
  *
  */
bool Ocultar( unsigned char buffer[] , const char cad[], int Tamimagen);

/**
  * @brief Funcion que revela o extrae un mensaje codificado en una imagen en formato PGM o PPM.
  *
  * @param buffer Parámetro de la imágen de la que deseamos revelar o extraer un mensaje oculto.
  * @param Tamimagen Parámetro de entrada con el tamaño de la imágen de la que queremos revelar o extraer un mesaje oculto.
  * @param Mensaje Parámetro de salida con el mensaje que hemos revelado o extraído.
  * @return Devuelve true si el mensaje se ha podido revelar o extraer.
  * @return Devuelve false si el mensaje no ha podido revelar o extraer.
  *
  */
bool Revelar( unsigned char buffer[],  char cad[], int Tamimagen,const  int Tamcadena);

/**
  * @brief Funcion que añade al final de una cadena otra cadena, en este caso usada para añadir el nombre de los formatos PGM o PPM.
  *
  * @param c1 Parámetro de la primera cadena.
  * @param c2 Parámetro de la segunda cadena que se le añade a la primera.
  *
  */
void Extension (char c1[], const char c2[]);

#endif

/** Fin del archivo codificar.h **/
