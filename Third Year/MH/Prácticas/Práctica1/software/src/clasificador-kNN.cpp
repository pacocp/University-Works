
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "manejodedatos.h"
#include "clasificador-kNN.h"

float calcularDistanciaEuclidea( string relation, vector< float> primero, vector< float> segundo, vector< bool> carac)
{
	float distancia = 0;
	float diferencia;
	float pow1;
	int num_atributos;
	int num_ejemplos;

	checkRelation( relation, num_atributos, num_ejemplos);

	// Calculamos la distancia euclidea de todos los atributos de los dos ejemplares
	for( int i = 0; i < num_atributos; i++)
	{
		if( carac[i] == 1)
		{
			diferencia = primero[i] - segundo[i];
			pow1 = diferencia * diferencia;
			distancia += pow1;
		}
	}

	return sqrt(distancia);
}

void obtenerTresVecinos( string relation, vector< vector< float> > training, vector< float> ejemplar, vector< vector< float> > &vecinos, vector< bool> caracteristicas)
{
	int num_atributos;
	int num_ejemplos;
	vector< int> indices_vecinos(3, -1);
	vector< float> distancia_vecinos(3, 1000000);
	float dist;
	float faux;
	int iaux;
	int nuevo_indice;
	vecinos.clear(); //Limpiamos el vector porque si no da mil fallos

	checkRelation( relation, num_atributos, num_ejemplos);

	num_ejemplos = num_ejemplos/2;

	// Calculamos las distancias euclideas del ejemplar con cada ejemplo del training
	for( int i = 0; i < num_ejemplos; i++)
	{
		dist = calcularDistanciaEuclidea( relation, ejemplar, training[i], caracteristicas);
		nuevo_indice = i;

		// Guardamos las distancias más cercanas al ejemplar a analizar
		for( int j = 0; j < 3; j++)
		{
		    if( dist <= distancia_vecinos[j])
			{
				faux = distancia_vecinos[j];
				iaux = indices_vecinos[j];

				distancia_vecinos[j] = dist;
				indices_vecinos[j] = nuevo_indice;

				dist = faux;
				nuevo_indice = iaux;
			}
		}
	}

	// Guardamos los 3 vecinos más cercanos
	for( int i = 0; i < 3; i++)
	{
		vecinos.push_back(training[indices_vecinos[i]]);

	}
}

int votarClase( string relation, vector< vector< float> > vecinos)
{
	float votos_1 = 0;
	float votos_2 = 0;
	float votos_6 = 0;
	float votos_10 = 0;
	float votos_16 = 0;
	float votos;	
	int num_atributos;
	int num_ejemplos;

	checkRelation( relation, num_atributos, num_ejemplos);
	
	if(relation.compare("arrhythmia") == 0)
	{
		// Contamos las clases de los ejemplares vecinos
		for( int i = 0; i < 3; i++)
			{
				
				if( vecinos[i][num_atributos] == 1)
				{
					
					votos_1++;
				}
			    if(vecinos[i][num_atributos] == 2)
				{
					
					votos_2++;
				}
				if(vecinos[i][num_atributos] == 10)
				{
					
					votos_10++;
				}
				if(vecinos[i][num_atributos] == 16)
				{
					
					votos_16++;
				}
			}

			
			// Decidimos que clase es en función de los votos
			if( votos_1 >= 2)
			{
				return 1;
			}
		    else if( votos_2 >= 2)
			{
				return 2;
			}
		    else if( votos_10 >= 2)
			{
				return 10;
			}
			else if(votos_16 >= 2)
			{
				return 16;
			}
			else if(votos_1 >=1)
			{
				return 1;
			}
			else if(votos_2 >=1)
			{
				return 2;
			}
			else if(votos_10 >=1)
			{
				return 10;
			}
			else if(votos_16 >=1)
			{
				return 16;
			}
	
	
	
	
	}
	else if( relation.compare("ejemplo") == 0)
	{
		// Contamos las clases de los ejemplares vecinos
		for( int i = 0; i < 3; i++)
		{
			if( vecinos[i][num_atributos-1] == 0)
			{
				votos--;
			}
			else
			{
				votos++;
			}
		}

		// Decidimos que clase es en función de los votos
		if( votos >= 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}	
	}
	else if( relation.compare("Movement_Libras") == 0)
	{
		vector < float> votos_movement(15);
		// Contamos las clases de los ejemplares vecinos
		for( int i = 0; i < 3; i++)
			{
				
				if( vecinos[i][num_atributos] == 1)
				{
					
					votos_movement[1]++;
				}
			    if(vecinos[i][num_atributos] == 2)
				{
					
					votos_movement[2]++;
				}
				if(vecinos[i][num_atributos] == 3)
				{
					
					votos_movement[3]++;
				}
				if(vecinos[i][num_atributos] == 4)
				{
					
					votos_movement[4]++;
				}
				if(vecinos[i][num_atributos] == 5)
				{
					
					votos_movement[5]++;
				}
				if(vecinos[i][num_atributos] == 6)
				{
					
					votos_movement[6]++;
				}
				if(vecinos[i][num_atributos] == 7)
				{
					
					votos_movement[7]++;
				}
				if(vecinos[i][num_atributos] == 8)
				{
					
					votos_movement[8]++;
				}
				if(vecinos[i][num_atributos] == 9)
				{
					
					votos_movement[9]++;
				}
				if(vecinos[i][num_atributos] == 10)
				{
					
					votos_movement[10]++;
				}
				if(vecinos[i][num_atributos] == 11)
				{
					
					votos_movement[11]++;
				}
				if(vecinos[i][num_atributos] == 12)
				{
					
					votos_movement[12]++;
				}
				if(vecinos[i][num_atributos] == 13)
				{
					
					votos_movement[13]++;
				}
				if(vecinos[i][num_atributos] == 14)
				{
					
					votos_movement[14]++;
				}
				if(vecinos[i][num_atributos] == 15)
				{
					
					votos_movement[15]++;
				}
			}
			float max = votos_movement[0];
			float pos_max = 0;
			for(int i = 0; i < 15; i++)
			{
				if(max < votos_movement[i+1])
				{
					max = votos_movement[i+1];
					pos_max = i+1;
				}
			}

			if(pos_max == 1)
			{
				return 1;
			}
			else if(pos_max == 2)
			{
					
				return 2;
			}
			else if(pos_max ==3)
			{
					
				return 3;
			}
			else if(pos_max ==4)
			{
					
				return 4;
			}
			else if(pos_max == 5)
			{
				return 5;
			}
			else if(pos_max == 6)
			{
					
				return 6;
			}
			else if(pos_max ==7)
			{
					
				return 7;
			}
			else if(pos_max == 8)
			{
					
				return 8;
			}
			else if(pos_max == 9)
			{
					
				return 9;
			}
			else if(pos_max == 10)
			{
					
				return 10;
			}
			else if(pos_max == 11)
			{
					
				return 11;
			}
			else if(pos_max == 12)
			{
					
				return 12;
			}
			else if(pos_max == 13)
			{
					
				return 13;
			}
			else if(pos_max == 14)
			{
					
				return 14;
			}
			else if(pos_max == 15)
			{
					
				return 15;
			}
	}
	else if( relation.compare("Wisconsin") == 0)
	{
		// Contamos las clases de los ejemplares vecinos
		for( int i = 0; i < 3; i++)
		{
			
			if( vecinos[i][num_atributos] == 0)
			{
				votos--;
			}
			else
			{
				votos++;
			}
		}

		// Decidimos que clase es en función de los votos
		if( votos >= 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}	
	}
		
}
	

/*
* relation -> nombre de los datos que vamos a clasificar
* test -> datos para comprobar el entrenamiento
* prediccion -> datos que predecimos
*/
float calcularPrecision( string relation, vector< vector< float> > test, vector< float> &prediccion)
{
	int num_atributos;
	int num_ejemplos;
	float correctos = 0;
	float porcentaje;

	checkRelation( relation, num_atributos, num_ejemplos);

	if( num_ejemplos % 2 == 0)
	{
		num_ejemplos = (num_ejemplos/2);
	}
	else
	{
		num_ejemplos = (num_ejemplos/2) + 1;
	}

	// Comparamos la predicción con las clases reales
	for( int i = 0; i < num_ejemplos; i++)
	{
		if( test[i][num_atributos] == prediccion[i])
		{
			correctos++;
		}
	}

	// Calculamos el porcentaje de acierto
	porcentaje = (correctos/num_ejemplos) * 100.0;

	return porcentaje;
}
/*
* relation -> Nombre de los datos que vamos a clasificar
* training -> datos de entrenamiento
* test -> datos para comprobar el entrenamiento
* prediccion -> donde vamos a ir guardando la clasificación de los datos
* carac -> características que vamos a utilizar
*/
void clasificar( string relation, vector< vector< float> > training, vector< vector< float> > test, vector< float> &prediccion, vector< bool> carac)
{
	vector< vector< float> > vecinos;
	float resultado;
	int num_atributos;
	int num_ejemplos;

	checkRelation( relation, num_atributos, num_ejemplos);
	
	if( num_ejemplos % 2 == 0)
	{
		num_ejemplos = (num_ejemplos/2);
	}
	else
	{
		num_ejemplos = (num_ejemplos/2) + 1;
	}

	// Predecimos las clases de los ejemplares del conjunto test
	for( int i = 0; i < num_ejemplos; i++)
	{
		obtenerTresVecinos( relation, training, test[i], vecinos, carac);
		resultado = votarClase( relation, vecinos);
		prediccion.push_back(resultado);
	}
}


float getExito( string relation, vector< vector< float> > training, vector< vector< float> > test, vector< bool> seleccion)
{
	vector< float> prediccion;
	float exito = 0;
	bool clasif = false;
	// Clasificamos y devolvemos el porcentaje

	for( int i = 0; i < seleccion.size()-1 && !clasif; i++)
	{
		if( seleccion[i] == 1)
		{
			clasif = true;
		}
	}

	if( clasif)
	{
		clasificar( relation, training, test, prediccion, seleccion);
		
		exito = calcularPrecision( relation, test, prediccion);
	}
	
	return exito;
}
