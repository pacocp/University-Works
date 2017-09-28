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
#include "generadores.h"
#include "string.h"
#include <cstdlib>


int main(int argc, const char* argv[])
{
    
    if(argc != 5 && argc != 4)
	{
		cout << "Fallo en el número de argumentos. Las funciones disponibles son: " << endl;
        cout << "Negativo,Desplazar,Umbralizar y Brillo" << endl;
        cout << "Forma de ejecución del negativo: generar b negativo_bin.trf negativo" << endl;
        cout << "Forma de ejecución del desplazar: generar t desplazar2_txt.trf desplazar 2" << endl;
        cout << "Forma de ejecución del umbralizar: generar t mitad_txt.trf umbralilzar 127" << endl;
        cout << "Forma de ejecución del brillo: generar t brillo10_txt.trf brillo 10 " << endl;
	}
	else
	{
        char tipo = *argv[1];
        if(tipo == 'b' || tipo == 't')
        {
           
        	if(strcmp(argv[3],"negativo") == 0)
       	    {
        		
        		if(Negativo(argv[2],tipo))
                {
                    cout << "Se ha creado la transformacion" << endl;
                }
                else
                {
                    cout << "Error al crear la transformacion" << endl;
                }
        		
        	}
        	if(strcmp(argv[3],"desplazar") == 0)
        	{
        		
        		int a;
        		a = atoi(argv[4]);
        		if(Desplazar(argv[2],tipo,a))
                {
                    cout << "Se ha creado la transformacion" << endl;
                }
                else
                {
                    cout << "Error al crear la transformacion" << endl;
                }
        		
        	}
        	if(strcmp(argv[3],"umbralizar") == 0)
        	{
        		
        		int a;
        		a = atoi(argv[4]);
        		if(Umbralizar(argv[2],tipo,a))
                {
                    cout << "Se ha creado la transformacion" << endl;
                }
                else
                {
                    cout << "Error al crear la transformacion" << endl;
                }
        		
        	}
        	if(strcmp(argv[3],"brillo")==0)
        	{
        		
        		int a;
        		a = atoi(argv[4]);
        		if(Brillo(argv[2],tipo,a))
                {
                    cout << "Se ha creado la transformacion" << endl;
                }
                else
                {
                    cout << "Error al crear la transformacion" << endl;
                }
        		
        	}
        }
            
    }
        
        	
        

	
}