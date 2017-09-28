/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
#include <iostream>
using namespace std;
#include "imagen.h"
#ifndef _TRANSFORMACION2_H_
#define _TRANSFORMACION2_H_
class Transformacion
{
   private:
              int TAM;
   	        unsigned char * datos;
   public: 
   	        Transformacion(){datos = new unsigned char [256];TAM = 256;} //Constructor
   	        ~Transformacion(){delete [] datos;} //Destructor 
   	        Transformacion& operator= (const Transformacion &trans) //Sobrecarga del operador =
   	        {

    			   for (int i=0; i<TAM;i++)
    			   {
      				  Set(i,trans.Get(i));
   				   }
   				   return *this;
   	        }
            void Set(int i,unsigned char v); //Introduce el elemento v en la posicion i del vector
   	        unsigned char Get(int i)const ;// Devuelve el elemento de la posicion i del vector   	
   	        bool Escribirtransformacion_txt( const char nombre[]);//Escribe la transformación en un fichero de texto txt
   	        bool Leertransformacion(const char nombre[]);  //Lee una transformación de un fichero de texto 
   	        bool Escribirtransformacion_bin( const char nombre[]);//Escribe la transformación en un fichero de texto binario
   	        bool AplicarTransformacion(Imagen img); //Aplica una transformación a una imagen  
            int Get_TAM(){return TAM;}
            void Set_TAM(int n){TAM = n;}
           
};	
 Transformacion  operator+ (const Transformacion &trans1,const Transformacion &trans2); //sobrecarga del operador +
 
#endif