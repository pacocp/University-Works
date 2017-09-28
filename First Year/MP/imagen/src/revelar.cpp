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


int main(int argc,   char * argv[])
{
  
      if(argc != 2)
      {
        cout << "Error en el número de argumentos." << endl;
        cout << "Forma de ejecución: " << endl;
        cout << "revelar salida.pgm > resultado.txt" << endl;
      }
      else
      {
        TipoImagen imag;
        int filas, columnas, Tamimagen;
        bool resultado,lectura;
        char cad[1000000/8];
        imag = LeerTipoImagen(argv[1],filas,columnas);
        Imagen img;
        if(imag == IMG_PGM)
           {
             lectura = img.LeerImagen(argv[1]);
             Tamimagen = filas*columnas;
             resultado = Revelar(img.Getvector(), cad, Tamimagen);
             cout << cad << endl;
           }
        else
           {
               cout << "Error en el formato de la imagen, tiene que ser PGM" << endl;
           }
      }
}

