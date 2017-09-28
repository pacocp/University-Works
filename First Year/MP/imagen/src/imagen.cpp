/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
#include "imagen.h"
#include "imagenES.h"
#include <cassert>
using namespace std;

Imagen::Imagen(int f, int c)
{   
    puntero = new unsigned char [f*c];
    this -> filas = f;
    this -> columnas = c;
}
bool Imagen::LeerImagen(const char nombre[]) // Carga img desde fichero “nombre”
{
	bool resultado = false;
    TipoImagen Tipo;
    int f_aux, c_aux;
    Tipo = LeerTipoImagen (nombre,f_aux, c_aux);
    this -> ~Imagen();
    this-> filas = f_aux;
    this-> columnas = c_aux;
    this->puntero = new unsigned char [f_aux*c_aux];
    resultado = LeerImagenPGM (nombre,filas,columnas,puntero);
    
    return resultado;
}
bool Imagen::EscribirImagen(const char nombre[]) const// Salva img en nombre
{
	bool resultado;
    resultado = EscribirImagenPGM (nombre,puntero,filas,columnas);
    return resultado;
}
void Imagen::Set (int i, int j, unsigned char v)
{
    assert(i>-1 && j>-1 && i<filas && j<columnas);
    puntero[i*columnas+j] = v;
}
unsigned char Imagen::Get (int i, int j) const
{
    assert(i>-1 && j>-1 && i<filas && j<columnas);
    return puntero[i*columnas+j];
}

Imagen& Imagen::operator= (const Imagen &img)
{
    Imagen aux(img);
    unsigned char *paux = aux.puntero;
    aux.puntero = (this->puntero);
    this->puntero = paux;
    swap(aux.filas,this->filas);
    swap(aux.columnas,this->columnas);
    return *this;
}