/*******************************************************************************************
*                                                                                          *
*     Francisco Carrillo Pérez                                                             *
*                                                                                          * 
*     Metodología de la programación                                                       * 
*                                                                                          *
*******************************************************************************************/
//prompt% componer t neg_y_mitad_txt.trf mitad_txt.trf negativo_bin.trf

#include <iostream>
using namespace std;
#include "transformacion.h"

int main(int argc, const  char * argv[])
{
	if(argc != 5)
	{
		cout << "Fallo en el numero factores dados" << endl;;
	}
	else
	{
	
	   char tipo = *argv[1];
       if(tipo == 'b')
       {
       	   Transformacion resultado, trans1,trans2;
       	   resultado.Set_TAM(256);
       	   if(trans1.Leertransformacion(argv[3]))
       	   {
       	   	 cout << "La primera transformacion se ha leido correctamente" << endl;
       	   }
       	   else
       	    {
       	    	cout << "Error al leer la primera transformacion" << endl;
       	    }
       	   if(trans2.Leertransformacion(argv[4]))
       	    {
       	   	 cout << "La primera transformacion se ha leido correctamente" << endl;
       	   }
       	   else
       	    {
       	    	cout << "Error al leer la primera transformacion" << endl;
       	    }
       	   resultado = trans1 + trans2;
       	   
       	   if(resultado.Escribirtransformacion_bin(argv[2]))
       	   {
       	   	 cout << "Se ha creado correctamente" << endl;
       	   }
       	   else
       	   {
       	   	 cout << "Error al crear la transformacion" << endl;
       	   }
       	   
       }
       if(tipo == 't')
       {
       	   
       	   Transformacion resultado, trans1,trans2;
       	   resultado.Set_TAM(256);
       	   if(trans1.Leertransformacion(argv[3]))
       	   {
       	   	 cout << "La primera transformacion se ha leido correctamente" << endl;
       	   }
       	   else
       	    {
       	    	cout << "Error al leer la primera transformacion" << endl;
       	    }
       	   if(trans2.Leertransformacion(argv[4]))
       	    {
       	   	 cout << "La primera transformacion se ha leido correctamente" << endl;
       	   }
       	   else
       	    {
       	    	cout << "Error al leer la primera transformacion" << endl;
       	    }
       	   
       	   resultado = trans1 + trans2;
       	   if(resultado.Escribirtransformacion_txt(argv[2]))
       	   {
       	   	 cout << "Se ha creado correctamente" << endl;
       	   }
       	   else
       	   {
       	   	 cout << "Error al crear la transformacion" << endl;
       	   }
       }
	}
}
	