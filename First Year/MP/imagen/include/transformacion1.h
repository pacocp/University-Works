/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
#include "imagen.h"
#ifndef _TRANSFORMACION1_H_
#define _TRANSFORMACION1_H_

class Transformacion
{
   private:
           int TAM;
   	       unsigned char datos[256];
   public:
           Transformacion(){TAM = 256;}
   	       void Set(int i,unsigned char v); //Introduce el elemento v en la posicion i del vector
   	       unsigned char Get(int i) const ; // Devuelve el elemento de la posicion i del vector
   	       bool Escribirtransformacion_txt( const char nombre[]);//Escribe la transformación en un fichero de texto txt
   	       bool Leertransformacion(const char nombre[]);  //Lee una transformación de un fichero de texto 
   	       bool Escribirtransformacion_bin(const char nombre[]);//Escribe la transformación en un fichero de texto binario
           bool AplicarTransformacion(Imagen img); //Aplica una transformación a una imagen
           int Get_TAM(){return TAM;}
           void Set_TAM(int n){TAM = n;}
};
 Transformacion  operator+ (const Transformacion &trans1,const Transformacion &trans2);//sobrecarga del operador +

#endif