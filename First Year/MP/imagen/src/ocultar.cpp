/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/

#include <iostream> 
using namespace std;
#include "procesar.h"
#include "imagen.h"
#include "imagenES.h"


int main(int argc,const  char * argv[])
{
	 if(argc != 3) 
   {
      cout << "Error en el número de argumentos" << endl;
      cout << "Forma de ejecución: " << endl;
      cout << "ocultar lenna.pgm salida.pgm < mensaje.txt" << endl;
    }
   else
   {
      TipoImagen imag;
      int filas, columnas, Tamimagen;
      bool resultado,lectura;
      imag = LeerTipoImagen(argv[1],filas,columnas);
      Imagen img;
      char c;
      if(imag == IMG_PGM)
         {
           img.LeerImagen(argv[1]);
           const int MAXMSG = (img.Filas()*img.Columnas()) / 8;
           char cad[MAXMSG];
           unsigned char vec_aux[img.Filas()*img.Columnas()];
           for(int i = 0; i < MAXMSG && cin.get(c);i++)
           {
            cad[i] = c;
           }
	         
           Tamimagen = img.Filas()*img.Columnas();
           for(int i=0; i<img.Filas(); i++){
               for (int j=0; j<img.Columnas(); j++){
                     vec_aux[i*img.Columnas()+j] = img.Get(i,j);
                   }
                  }
           resultado = Ocultar(vec_aux,cad,Tamimagen);
           for(int i=0; i<img.Filas(); i++){
               for (int j=0; j<img.Columnas(); j++){
                   img.Set(i,j, vec_aux[i*img.Columnas()+j]);
                 }
               }
           resultado = img.EscribirImagen(argv[2]);
           
           if(resultado == true)
		         {
			           cout << "La frase ha sido ocultada " << endl;
		         }
           else
           {
                 cout << "La imagen no ha sido ocultada" << endl;
           }
         }
           else
           {
            cout << "El formato de la imagen es el incorrecto, debe ser PGM" << endl;
           }
          
    }
}



    
     
    

