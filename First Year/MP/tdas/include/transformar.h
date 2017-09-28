/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
/**
  * @file transformar.h
  * @brief Fichero cabecera para la transformación o tratamiento de imágenes.
  *	
  *
  * Permite pasar una imágen a negativo o desplazar un número de bits en cada byte de la imágen.
  *
  */
#ifndef __TRANSFORMAR_H__
#define __TRANSFORMAR_H__

#include "imagen.h"
/**
  * @brief Pasa una imagen PGM a negativo.
  *
  * @param img Nombre de la imágen que va a ser tratada.
  *
  */
void Negativo(Imagen& img); 
/**
  * @brief Desplaza un número de bits en cada byte de la imágen.
  *
  * @param img Nombre de la imágen que va a ser tratada.
  * @param n indica cuántos bits se van a desplazar en cada byte de la imágen.
  *
  */
void Desplazar(Imagen& img, int n); 
#endif
/** Fin del archivo transformar.h **/
