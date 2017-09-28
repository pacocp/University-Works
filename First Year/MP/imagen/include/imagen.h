/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
#include <iostream>
using namespace std;
#ifndef _IMAGEN_H_
#define _IMAGEN_H_
class Imagen { 
private:
      int filas,columnas;
      unsigned char *puntero;
public:
     Imagen(){puntero=0; filas=columnas=0;} //Constructor 
     Imagen(int f,int c); //Constructor con elementos
     ~Imagen(){delete [] puntero;} //Destructor
     Imagen& operator= (const Imagen& img);
     int Filas () const {return filas;} // Devuelve el número de filas de m

     int Columnas () const {return columnas;}// Devuelve el número de columnas de m

     void Set (int i, int j, unsigned char v); // Hace img(i,j)=v

     unsigned char Get (int i, int j) const; // Devuelve img(i,j)

     bool LeerImagen(const char nombre[]); // Carga img desde fichero “nombre”

     bool EscribirImagen(const char nombre[]) const; // Salva img en nombre
     
     unsigned char* Getvector() {return puntero;} //Devuelve el vector de la imagen 

};
#endif