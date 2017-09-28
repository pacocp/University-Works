/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
/** 

  * @file codificar.cpp
  * @brief Fichero con las definiciones para la Entrada/Salida de imágenes.
  *
  * Permite la Entrada/Salida de archivos de tipo PGM o PPM.
  */


#include <iostream>
using namespace std;
#include "codificar.h"


bool Ocultar( unsigned char buffer[] , const char cad[],int Tamimagen)
{
  
   int pixel = 0, tam = 0;
   for (int i = 0; cad[i] != '\0'; i++)
	{
		tam++;
	}
	if (Tamimagen < tam) //El tamaño del mensaje es mayor que el de la imágen y no entrara en ella.
	{
		return false;
	}
         // si entra
        else
        {
        for( int pos = 0; cad[pos] != '\0'; pos++)
        {
      
             for( int pos2 = 7; pos2 >=0; --pos2)
                 { 
                    if((cad[pos]&(1<<pos2)) !=0)
                     {
                       buffer[pixel] = buffer[pixel] | 1;
              
                     }
                    else
                       {
                         buffer[pixel] = buffer[pixel] & ~1;
               
                       }
                     pixel++ ;
                 }
       
        }
      
    // meter el \0 que falta
    for(int  pos3 = 7; pos3 >=0; --pos3)
        { 
           
               buffer[pixel] = buffer[pixel] &  ~1;
           
         }
    return true;
         }
}
       

       
//_______________________________________________________________________

bool Revelar( unsigned char buffer[],  char cad[], int Tamimagen, const int Tamcadena)
{
  int pos = 0;
  bool salir = false;
  int  b = 0;
  cad[0] = '\0';
  
  

   for (int  i = 0; salir != true && i < Tamimagen && pos <= Tamcadena; i++)
    {
      for( int j = 7; j >=0; --j)
         {
            
                    cad[pos] = cad[pos] << 1;
               
                    if((buffer[b] & (1<<0))==0)
                    {
                        cad[pos] = cad[pos] & ~1;
                     }
                    else
                    {
                        cad[pos] = cad[pos] | 1;
                     }
            
                 b++;
           }
         
         
       
       if(cad[pos] == '\0')
          {
             salir = true;
          }
       pos++ ;
        
     }
      return salir;
 
}

//_________________________________________________________________________

void Extension (char c1[], const char c2[]) // Añade la extensión a la imagen
{
   int i, j = 0;
   for( i = 0; c1 [i] != '\0' ; i++)
         ;
        
   while( c2[j] != '\0' )
             {
                c1[i] = c2[j] ;
                i++;
                j++;
             }
   c1[i] = '\0' ;
}
 
/* Fin Fichero: codificar.cpp */                   
            
       




















