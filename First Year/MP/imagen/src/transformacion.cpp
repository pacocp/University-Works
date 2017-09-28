/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/

#include "transformacion.h" // Aquí se define el valor de CUAL_COMPILO

#if CUAL_COMPILO==1
  #include "transformacion1.cpp"
#elif CUAL_COMPILO==2
  #include "transformacion2.cpp"
#endif
 
 
 

