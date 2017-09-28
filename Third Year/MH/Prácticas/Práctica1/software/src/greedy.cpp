
#include <vector>
#include <string>
#include <iostream>
#include "manejodedatos.h"
#include "clasificador-kNN.h"
#include "random_ppio.h"

/* 
* relation -> nombre de los datos, se utiliza para cargar los valores
* trainig -> datos de entrenamiento
* test -> datos para probar nuestro clasificador 
* seleccion -> características más óptimas que hemos encontrado
*/
void greedy( string &relation, vector< vector< float> > &training, vector< vector< float> > &test, vector< bool> &seleccion)
{
	float acierto = 0;
	bool fin = false;
	bool vacio = false;
	int fp;
	float mejor = 0;
	float max = 0;
	int total = 0;
	int num_atributos;
	int num_ejemplos;

	checkRelation( relation, num_atributos, num_ejemplos); //Vemos con que datos estamos tratando

	if( num_ejemplos % 2 == 0)
	{
		num_ejemplos = num_ejemplos/2;
	}
	else
	{
		num_ejemplos = (num_ejemplos/2)-1;
	}
	
	// Mientras que no acabemos o la lista de atributos esté vacía
	while( !vacio || !fin)
	{
		// Por cada atributo, probamos uno a uno cual produce el mayor éxito
		for( int i = 0; i < num_atributos-1; i++)
		{
			if( seleccion[i] == 0)
			{
				seleccion[i] = 1;
				acierto = getExito( relation, training, test, seleccion);
				if( max < acierto)
				{
					//Actualizamos el exito al máximo que hemos encontrado 
					fp = i;
					max = acierto;
				}
				seleccion[i] = 0;
			}
		}

		// Comprobamos si el mejor éxito anterior es mejor que el mejor éxito hasta el momento, en caso contrario acabamos
		if( max >= mejor)
		{
			seleccion[fp] = 1;
			mejor = max;
		}
		else
		{
			//En caso contrario actualizamos una de las conciciones para salir del bucle
			fin = true;
		}

		// Comprobamos todos los atributos
		total++;

		if( total == num_atributos-1)
		{
			//Si ya hemos recorrido todos los atributos, salimos
			vacio = true;
		}
	}
}


