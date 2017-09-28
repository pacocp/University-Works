/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
#include <iostream>
#include "transformacion.h"
#include "imagen.h"
#include <fstream>
#include <string>
#include <cassert> 
using namespace std;

 unsigned char Transformacion::Get(int i) const
 {
 	
 	return datos[i];
 }
 void Transformacion::Set(int i,unsigned char v)
 {
 	
 	datos[i] = v; 
 }

 bool Transformacion::Escribirtransformacion_txt( const char nombre[])
 {

     std::ofstream f (nombre,std::ios::out);
     if(f)
     {
        string cad_mag = "MP-TRF-T";
        f << cad_mag << " ";
        f << TAM << endl;
        int v_aux[TAM];
        for(int i = 0;i < TAM;i++)
        {
            v_aux[i] = datos[i];
        }
        for(int i=0;i<TAM;i++)
        {
        	f << v_aux[i] << endl;
        }
        f.close();
        return true;
     }
     else
     {
     	return false;
     }
 }
 bool Transformacion::Leertransformacion(const char nombre[])
 {
    std::ifstream f(nombre,std::ios::in);
    char cad_mag[9];

    if(f)
    {
    	char txt[] = "MP-TRF-T";
    	char bin[] = "MP-TRF-B";
    	bool resultado_txt = true, resultado_bin = true;
        f.read(cad_mag,9);
        cad_mag[9] = 0;
        f >> TAM;
        assert(TAM <257);
        f.get();
        for(int i=0;i<8 && resultado_txt!=false;i++)
        {
           if(cad_mag[i] != txt[i])
           {
           	   resultado_txt = false;
           }
        }
         for(int i=0;i<8 && resultado_bin!=false;i++)
        {
           if(cad_mag[i] != bin[i])
           {
           	   resultado_bin = false;
           }

        }
        if(resultado_txt == true)
    	{
       		
       		for(int i =0; i <TAM;i++)
            {
                int n;
                f >> n;
                datos[i] = n;
                
            }
       		
       		return true;
    	}
    	else
    	{
    		if(resultado_bin == true)
            {
    		f.close();
    		std::ifstream f(nombre,std::ios::in| std::ios::binary);
            f.ignore(20,'\n');
    		if(f)
    		{   
                int v_aux[TAM];
                f.read((char*)v_aux,sizeof(int)*TAM);
                for(int i=0; i<TAM;i++)
                  {
                          Set(i,v_aux[i]);
                  } 
    		f.close();
    			return true;
    		}
    		else{
    		return false;
    		}
            }
            else
            {
                return false;
            }
    	}
    }
    else
    {
    	return false;
    }
	


 }
 bool Transformacion::Escribirtransformacion_bin(const char nombre[])
 {
 	std::ofstream f(nombre,std::ios::out | std::ios::binary);
 	if(f)
 	{
 		string cad_mag = "MP-TRF-B";
 		f << cad_mag << " ";
        f << TAM << endl;
        int v_aux[TAM];
        for(int i=0; i< TAM;i++)
        {
            v_aux[i] = Get(i);
        }
        f.write(reinterpret_cast<char*>(v_aux),sizeof(int)*TAM);
        f.close();
        return true;
 	}
 	else
 	{
 		return false;
 	}
 }
 bool Transformacion::AplicarTransformacion(Imagen img)
 {
    for(int i =0; i<img.Filas();i++)
    {
        for(int j=0; j<img.Columnas();j++)
        {
            img.Set(i,j,datos[img.Get(i,j)]);
        }
    }
    return true;
 }
  Transformacion  operator+ (const Transformacion &trans1,const Transformacion &trans2)
 {
   Transformacion t_aux;
   
  
   for (int i=0; i < 256; i++)
   {
    t_aux.Set(i,trans2.Get(trans1.Get(i)));
   }
   return t_aux;
 }
  
 
