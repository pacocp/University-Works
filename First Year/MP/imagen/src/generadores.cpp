/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
#include <iostream>
using namespace std;
#include "transformacion.h"
#include <cstring>

//Las funciones devuelven una transformación

bool Negativo(const char nombre[],char &c) //Devuelve una transformación que crea el negativo de una imagen
{
   Transformacion t_aux;
   t_aux.Set_TAM(256);
   
   for(int i=0;i<256;i++)
   {
   	 t_aux.Set(i,(255-i));
   	 
   }
   if(c == 'b')
   {

    if(t_aux.Escribirtransformacion_bin(nombre))
    {
      return true;
    }
    else
    {
      return false;
    }
   }
   else
   {
      if(c== 't')
      {
        if(t_aux.Escribirtransformacion_txt(nombre))
         {
              return true;
         }
        else
        {
              return false;
        }
      }
   }
   

 
   
}

bool Desplazar(const char nombre[],char &c,int  n) //Devuelve una transformación que desplaza n bits los bits de pixel de una imagen
{
	Transformacion t_aux;
   t_aux.Set_TAM(256);
   for(int i=0;i<256;i++)
   {
   	 t_aux.Set(i,i<<n);
   	 
   }
   if(c == 'b')
   {

    if(t_aux.Escribirtransformacion_bin(nombre))
    {
      return true;
    }
    else
    {
      return false;
    }
   }
   else
   {
      if(c== 't')
      {
        if(t_aux.Escribirtransformacion_txt(nombre))
         {
              return true;
         }
        else
        {
              return false;
        }
      }
   }
  
}

bool Umbralizar(const char nombre[],char &c,int v) //Devuelve una transformación que umbraliza una imagen
{
	Transformacion t_aux;
  t_aux.Set_TAM(256);
	for(int i=0; i<256;i++)
	{
		if(i<=v)
		{
           t_aux.Set(i,0);
		}
		else
		{
			t_aux.Set(i,255);
		}
	}
  if(c == 'b')
   {

    if(t_aux.Escribirtransformacion_bin(nombre))
    {
      return true;
    }
    else
    {
      return false;
    }
   }
   else
   {
      if(c== 't')
      {
        if(t_aux.Escribirtransformacion_txt(nombre))
         {
              return true;
         }
        else
        {
              return false;
        }
      }
   }
}

bool Brillo(const char nombre[],char &c,int d) //Devuelve una transformación que ajusta el brillo de una imagen
{
    Transformacion t_aux;
    t_aux.Set_TAM(256);
    for(int i = 0; i<256;i++)
    {
    	if(i+d<0)
    	{
    		t_aux.Set(i,0);
    	}
    	else
    	{
    		if(i+d>255)
    		{
    			t_aux.Set(i,255);
    		}
    		else
    		{
    			t_aux.Set(i,i+d);
    		}
    	}
    }
    if(c == 'b')
   {

    if(t_aux.Escribirtransformacion_bin(nombre))
    {
      return true;
    }
    else
    {
      return false;
    }
   }
   else
   {
      if(c== 't')
      {
        if(t_aux.Escribirtransformacion_txt(nombre))
         {
              return true;
         }
        else
        {
              return false;
        }
      }
   }
}
bool Comparar(const char cad1[],const  char cad2[])
{
  bool iguales = true;
  int tam1=0,tam2=0;
  for(int i=0; cad1[i]!= 0;i++)
  {
    tam1++;
  }
  for(int i=0; cad2[i]!= 0;i++)
  {
    tam2++;
  }
  for(int i=0;i < tam1 && iguales == true;i++)
  {
     if(cad1[i] != cad2[i])
     {
        iguales =  false;
     }
     
  }
  return iguales;

}
