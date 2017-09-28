#include <iostream>
#include <vector>
#include <string>
#include "manejodedatos.h"
#include "clasificador-kNN.h"
#include "greedy.h"
#include "random_ppio.h"
#include "utilidades.h"
#include <math.h>
#include "genetic.h"


//********************************************************************************
//  relation -> nombre del archivo
// población -> población actual que tenemos
// TAMPOB -> constante que indica el tamaño de la población
//********************************************************************************
void generarPoblacionRandom( string relation, vector< vector< bool> > &poblacion, const int TAMPOB)
{
	int num_atributos;
	int num_ejemplos;
	int iaux;
	
	checkRelation( relation, num_atributos, num_ejemplos);

	vector< bool> individuo( num_atributos, 0);

	for( int i = 0; i < TAMPOB; i++)
	{
		for( int j = 0; j < num_atributos-1; j++)
		{
			iaux = Randint(0, num_atributos-1);
			
			flip( individuo, iaux);
		}
		
		poblacion[i] = individuo;
   
		for( int j = 0; j < num_atributos-1; j++)
		{
			individuo[j] = 0;
		}
	}
}


//********************************************************************************
//  relation -> nombre del archivo
// training -> división de los datos para aprender
// test -> división de los datos para evaluar
// población -> población actual que tenemos
// TAMPOB -> constante que indica el tamaño
// eval_problacion -> el éxito de cada elemento de la población
// evaluados -> los elementos que han sido evaluados
// TAMPOB -> Tamaño de la población 
// num_evaluaciones -> número de evaluaciones que llevamos realizadas 
//********************************************************************************
void evaluarPoblacion( string relation, vector< vector< float> > training, vector< vector< float> > test, vector< vector< bool> > poblacion, 
	vector< float> &eval_poblacion, vector< bool> &evaluados, const int TAMPOB, int &num_evaluaciones)
{
	int num_atributos;
	int num_ejemplos;

	checkRelation( relation, num_atributos, num_ejemplos);

	float exito;

	// Todo individuo de la población no evaluado se evalua
	for( int i = 0; i < TAMPOB; i++)
	{
		//Si el elemento no ha sido evaluado
		if( !evaluados[i])
		{
			exito = getExito( relation, training, test, poblacion[i]);
			eval_poblacion[i] = exito;
			flip( evaluados, i);
			num_evaluaciones++;
		}
	}
}

//**************************************************************************************
// poblacion -> población actual que tenemos
// eval_poblacion -> exito de cada indivudio de la población
// TAMPOB -> tamaño de la población
//**************************************************************************************
int seleccionTorneoBinario( vector< vector< bool> > poblacion, vector< float> eval_poblacion, const int TAMPOB)
{
	int iaux;
	int ganador;

	iaux = Randint( 0, TAMPOB-1);
	ganador = Randint( 0, TAMPOB-1);

	// Comprobamos que individuo tiene mayor éxito
	if( eval_poblacion[iaux] > eval_poblacion[ganador])
	{
		ganador = iaux;
	}

	return ganador;	
}


//***************************************************************************
// relation -> datos de la base de datos
// padre -> cromosoma padre
// madre -> cromosoma madre
// uno -> primer hijo
// dos -> segundo hijo
//****************************************************************************
void cruceDosPuntos( string relation, vector< bool> padre, vector< bool> madre, vector< bool> &uno, vector< bool> &dos)
{
	int num_atributos;
	int num_ejemplos;
	int primer;
	int segundo;
	
	checkRelation( relation, num_atributos, num_ejemplos);
	
	primer = Randint( 0, num_atributos-2);
	segundo = Randint( primer+1, num_atributos-2);

	for( int i = 0; i < num_atributos-1; i++)
	{
		if( ( i > primer) && ( i < segundo))
		{
			uno[i] = padre[i];
			dos[i] = madre[i];
		}
		else
		{
			uno[i] = madre[i];
			dos[i] = padre[i];
		}
	}
}

//*********************************************************************************************************
// población -> población anterior
// eval_poblacion -> evaluación de las poblaciones
// poblacion_hijos -> población de los hijos
// eval_poblacion_hijos -> evaluaciones de la población de los hijos
// indice_elite -> índice del individuo  con mayor valor
// valor_elite -> valor del individuo mejor
// TAMPOB -> tamaño de la población
//**********************************************************************************************************
void elitismo(vector< vector< bool> > &poblacion,vector< float> &eval_poblacion,vector< vector< bool> > poblacion_hijos,vector< float> eval_poblacion_hijos,
	int indice_elite,float valor_elite,const int TAMPOB)
{
	poblacion_hijos[TAMPOB-1] = poblacion[indice_elite];

	eval_poblacion_hijos[TAMPOB-1] = valor_elite;
}
//*******************************************************************************************************
//																										*
// Esquema generacional con elitismo, es decir, el mejor de la anterior población se mete por el peor  *
// de la población actual.																				*
//																										*
//*******************************************************************************************************
void AGG( string relation, vector< vector< float> > training, vector< vector< float> > test, vector< bool> &seleccion)
{
	const int TAMPOB = 50;
	const float PCRUCE = 0.7;
	const float PMUTAR = 0.01;
	int num_atributos;
	int num_ejemplos;

	checkRelation( relation, num_atributos, num_ejemplos);
	
	vector< vector< bool> > poblacion( TAMPOB);
	vector< float> eval_poblacion( TAMPOB);
	vector< vector< bool> > poblacion_padres( TAMPOB);
	vector< float> eval_poblacion_padres( TAMPOB);
	vector< vector< bool> > poblacion_intermedia( TAMPOB);
	vector< float> eval_poblacion_intermedia( TAMPOB);
	vector< vector< bool> > poblacion_hijos( TAMPOB);
	vector< float> eval_poblacion_hijos( TAMPOB);
	int num_evaluaciones = 0;
	vector< bool> evaluados( TAMPOB, 0);
	int iaux;
	int iaux2;
	int num_cruces;
	vector< bool> primer( num_atributos);
	vector< bool> segundo( num_atributos);
	int num_mut;
	float valor_elite = -1;
	int indice_elite = -1;

	// Generamos una población inicial aleatoria
	generarPoblacionRandom( relation, poblacion, TAMPOB);
	evaluarPoblacion( relation, training, test, poblacion, eval_poblacion, evaluados, TAMPOB, num_evaluaciones);

	//Buscamos cuál es el valor élite
	for( int i = 0; i < TAMPOB; i++)
	{
		if( eval_poblacion[i] > valor_elite)
		{
			indice_elite = i;
			valor_elite = eval_poblacion[i];
		}
	}
	
	//mientras que el número de evaluaciones sea menor a 15000
	while( num_evaluaciones < 15000)
	{
		// Seleccion
	
		for( int i = 0; i < TAMPOB; i++)
		{
			iaux = seleccionTorneoBinario( poblacion, eval_poblacion, TAMPOB);
			poblacion_padres[i] = poblacion[iaux];
			eval_poblacion_padres[i] = eval_poblacion[iaux];
		}

		// Cruce

    	num_cruces = PCRUCE * (TAMPOB/2);;
		
		for( int i = 0; i < TAMPOB; i++)
		{
			if( i < num_cruces)
			{
				iaux = 2*i;
				cruceDosPuntos( relation, poblacion_padres[iaux], poblacion_padres[iaux+1], primer, segundo);
				poblacion_intermedia[iaux] = primer;
				poblacion_intermedia[iaux+1] = segundo;
				evaluados[iaux] = 0;
				evaluados[iaux+1] = 0;
				eval_poblacion_intermedia[iaux] = -1;
				eval_poblacion_intermedia[iaux+1] = -1;
			}
			else
			{
				poblacion_intermedia[i] = poblacion_padres[i];
				eval_poblacion_intermedia[i] = eval_poblacion_padres[i];
			}
		}

		// Mutación

		num_mut = PMUTAR * TAMPOB * (num_atributos-1);

		poblacion_hijos = poblacion_intermedia;
		eval_poblacion_hijos = eval_poblacion_intermedia;
		
		for( int i = 0; i < num_mut; i++)
		{
			iaux = Randint( 0, TAMPOB-1);
			iaux2 = Randint( 0, num_atributos-2);

			flip( poblacion_hijos[iaux], iaux2);
			evaluados[iaux] = 0;
		}
		
		// Reemplazamiento
		
		evaluarPoblacion( relation, training, test, poblacion_hijos, eval_poblacion_hijos, evaluados, TAMPOB, num_evaluaciones);
		
		
		//ELITISMO

		elitismo(poblacion,eval_poblacion,poblacion_hijos,eval_poblacion_hijos,indice_elite,valor_elite,TAMPOB);
		
		
		
		indice_elite = -1;
		valor_elite = -1;
		for( int i = 0; i < TAMPOB; i++)
		{
			if( eval_poblacion_hijos[i] > valor_elite)
			{
				indice_elite = i;
				valor_elite = eval_poblacion_hijos[i];
			}
		}

		poblacion.clear();
		eval_poblacion.clear();
		poblacion = poblacion_hijos;
		eval_poblacion = eval_poblacion_hijos;

		//cout << num_evaluaciones << endl;
	}

	seleccion = poblacion[indice_elite];
}

void AGE( string relation, vector< vector< float> > training, vector< vector< float> > test, vector< bool> &seleccion)
{
	const int TAMPOB = 50;
	const float PCRUCE = 1;
	const float PMUTAR = 0.01;
	int num_atributos;
	int num_ejemplos;

	checkRelation( relation, num_atributos, num_ejemplos);
	
	vector< vector< bool> > poblacion( TAMPOB);
	vector< float> eval_poblacion( TAMPOB);
	vector< vector< bool> > poblacion_padres( TAMPOB);
	vector< float> eval_poblacion_padres( TAMPOB);
	vector< vector< bool> > poblacion_intermedia( TAMPOB);
	vector< float> eval_poblacion_intermedia( TAMPOB);
	vector< vector< bool> > poblacion_hijos( TAMPOB);
	vector< float> eval_poblacion_hijos( TAMPOB);
	int num_evaluaciones = 0;
	vector< bool> evaluados( TAMPOB, 0);
	int iaux;
	int iaux2;
	int num_cruces;
	vector< bool> primer( num_atributos);
	vector< bool> segundo( num_atributos);
	int num_mut;
	int valor_elite = -1;
	int indice_elite = -1;
	float exito;
	float peor1;
	float peor2;

	// Generamos una población inicial aleatoria
	generarPoblacionRandom( relation, poblacion, TAMPOB);
	evaluarPoblacion( relation, training, test, poblacion, eval_poblacion, evaluados, TAMPOB, num_evaluaciones);
	
	while( num_evaluaciones < 15000)
	{
		// Seleccion
	
		for( int i = 0; i < 2; i++)
		{
			iaux = seleccionTorneoBinario( poblacion, eval_poblacion, TAMPOB);
			poblacion_padres[i] = poblacion[iaux];
			eval_poblacion_padres[i] = eval_poblacion[iaux];
		}

		// Cruce
		
		cruceDosPuntos( relation, poblacion_padres[0], poblacion_padres[1], primer, segundo);
		poblacion_intermedia[0] = primer;
		poblacion_intermedia[1] = segundo;
		eval_poblacion_intermedia[0] = -1;
		eval_poblacion_intermedia[1] = -1;

		// Mutación

		num_mut = PMUTAR * 2 * (num_atributos-1);

		poblacion_hijos = poblacion_intermedia;
		eval_poblacion_hijos = eval_poblacion_intermedia;
		
		for( int i = 0; i < num_mut; i++)
		{
			iaux = Randint( 0, 1);
			iaux2 = Randint( 0, num_atributos-2);

			flip( poblacion_hijos[iaux], iaux2);
		}
		
		// Reemplazamiento
		/*
		for( int i = 0; i < 2; i++)
		{
			exito = getExito( relation, training, test, poblacion_hijos[i]);
			eval_poblacion_hijos[i] = exito;
			num_evaluaciones++;
		}
		*/
		evaluarPoblacion( relation, training, test, poblacion_hijos, eval_poblacion_hijos, evaluados, TAMPOB, num_evaluaciones);
		
		// Elitismo
		iaux = 0;
		iaux2 = 1;
		peor1 = eval_poblacion[iaux];
		peor2 = eval_poblacion[iaux2];
		for( int i = 0; i < TAMPOB; i++)
		{
			if( eval_poblacion[i] < peor1)
			{
				iaux = i;
				peor1 = eval_poblacion[i];

				if( peor1 < peor2)
				{
					peor1 = peor2;
					iaux = iaux2;
					peor2 = eval_poblacion[i];
					iaux2 = i;
				}
			}
		}

		poblacion[iaux] = poblacion_hijos[0];
		eval_poblacion[iaux] = eval_poblacion_hijos[0];
		poblacion[iaux2] = poblacion_hijos[1];
		eval_poblacion[iaux2] = eval_poblacion_hijos[1];
		
		//cout << num_evaluaciones << endl;
	}

	for( int i = 0; i < TAMPOB; i++)
	{
		if( eval_poblacion[i] > valor_elite)
		{
			indice_elite = i;
			valor_elite = eval_poblacion[i];
		}
	}

	seleccion = poblacion[indice_elite];
}


