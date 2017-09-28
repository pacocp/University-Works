
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
	int fp=0,fp_ant=0;
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
	while( !vacio && !fin)
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
		
		// Comprobamos si el mejor éxito anterior es mejor que el mejor éxito hasta el momento o no es la misma caracteristica
		// que antes, en caso contrario acabamos
		cout << "iteracion: " << total << endl;
		if( max >= mejor && fp_ant != fp)
		{
			cout << "Cojo la variable: " << fp << endl;
			seleccion[fp] = 1;
			mejor = max;
			fp_ant = fp;
		}
		else
		{
			//En caso contrario actualizamos una de las conciciones para salir del bucle
			cout << "PARO" << endl;
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

void greedyAleatorio( string &relation, vector< vector< float> > &training, vector< vector< float> > &test, vector< bool> &seleccion, float tolerancia)
{
	float acierto = 0;
	bool fin = false;
	bool vacio = false;
	int fp=0,fp_ant=0;
	float mejor = 0;
	float max = 0;
	int total = 0;
	int num_atributos;
	int num_ejemplos;
	vector< int> LRC;
	float cmejor = -1000000;
	float cpeor = 1000000;
	float umbral;
	int iaux;

	checkRelation( relation, num_atributos, num_ejemplos);

	vector< bool> solucion(num_atributos, 0);
	vector< bool> LC( num_atributos, 0);
	
	if( num_ejemplos % 2 == 0)
	{
		num_ejemplos = num_ejemplos/2;
	}
	else
	{
		num_ejemplos = (num_ejemplos/2)-1;
	}
	
	// Mientras que no acabemos o la lista de atributos esté vacía
	while( !vacio && !fin)
	{
		// Identificamos cual es el mejor y el peor valor
		cout << "Identificando cual es el mejor y peor valor" << endl;
		for( int i = 0; i < num_atributos-1; i++)
		{
			if( LC[i] == 0)
			{
				LC[i] = 1;
				acierto = getExito( relation, training, test, LC);
				
				if( acierto > cmejor)
				{
					cmejor = acierto;
				}
				if( acierto < cpeor)
				{
					cpeor = acierto;
				}
				
				LC[i] = 0;
			}	
		}

		// Calculamos el umbral
		umbral = cmejor - /*tolerancia*/0.1*( cmejor - cpeor);

		LRC.clear();

		// Metemos en LRC las características cuyo éxito superan el umbral
		for( int i = 0; i < num_atributos-1; i++)
		{
			if( LC[i] == 0)
			{
				LC[i] = 1;
				acierto = getExito( relation, training, test, LC);
				
				if( acierto >= umbral)
				{
					cout << "METO LA VARIABLE " << i << endl;
					LRC.push_back(i);
				}
				
				LC[i] = 0;
			}
		}

		// Cogemos una característica de LRC de forma aleatoria
		iaux = Randint(0, LRC.size()-1);
		fp = LRC[iaux];
		solucion[fp] = 1;
		max = getExito( relation, training, test, solucion);
		cout << "iteracion: " << total << endl;
		// Comprobamos si el mejor éxito anterior es mejor que el mejor éxito hasta el momento, en caso contrario acabamos
		if( max >= mejor && fp_ant != fp)
		{
			cout << "Cojo la variable: " << fp << endl;
			seleccion = solucion;
			LC = solucion;
			LRC.clear();
			mejor = max;
			fp_ant = fp;
		}
		else
		{
			cout << "PARO" << endl;
			//En caso contrario actualizamos una de las conciciones para salir del bucle
			fin = true;
		}

		// Comprobamos todos los atributos
		total++;

		if( total == num_atributos-1)
		{
			vacio = true;
		}
	}
}