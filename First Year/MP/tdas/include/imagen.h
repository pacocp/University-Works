/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
/**
  * @file imagen.h
  * @brief Fichero cabecera para insertar la implementación deseada
  *
  * Permite modificar la implementación mediante un número del 1 a 4
  *
  */

#define CUAL_COMPILO 1

#if CUAL_COMPILO==1
  #include "imagen1.h"
#elif CUAL_COMPILO==2
  #include "imagen2.h"
#elif CUAL_COMPILO==3
  #include "imagen3.h"
#else
  #include "imagen4.h"
#endif
/* Fin Fichero: imagen.h */
