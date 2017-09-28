#include <iostream>
#include <vector>
#include <string>
#include "manejodedatos.h"
#include "clasificador-kNN.h"
#include "greedy.h"
#include "random_ppio.h"
#include "utilidades.h"
#include <math.h>
#include <genetic.h>
#include "busquedaLocal.h"
#include "hybrid.h"

//*******************************************************************************************************
//																										*
// Algoritmo híbdrido cada 10 generaciones se aplica una búsqueda local a todos los cromosomas          *
//																										*
//*******************************************************************************************************
void AGGAM1( string relation, vector< vector< float> > training, vector< vector< float> > test, vector< bool> &seleccion)
{
	const int TAMPOB = 10;
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
	bool salir = false;
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
	
	//mientras que el número de evaluaciones sea menor a 5000
	while(!salir)
	{
		if(num_evaluaciones > 5000)
		{
			salir = true;
		}
		else
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
			
			//Cada 10 generaciones aplicamos una búsqueda local primer mejor
			if(num_evaluaciones%10 == 0 && num_evaluaciones != 0)
			{
				for(int i=0; i<TAMPOB && !salir; i++)
				{
					if(num_evaluaciones > 5000)
					{
						salir = true;
					}
					else
					{
						primerMejor(relation,training,test,poblacion_hijos[i],num_evaluaciones);
					}
					
				}
				
			}
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
			num_evaluaciones++; //Aumentamos el valor del número de evaluaciones
			//cout << num_evaluaciones << endl;
			}
		
	}

	seleccion = poblacion[indice_elite];
}


//*******************************************************************************************************
//																										*
// Algoritmo híbdrido cada 10 generaciones se aplica una búsqueda local a todos los cromosomas          *
//																										*
//*******************************************************************************************************
void AGGAM2( string relation, vector< vector< float> > training, vector< vector< float> > test, vector< bool> &seleccion)
{
	const int TAMPOB = 10;
	const float TAMBUS = 0.1*TAMPOB;
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
	
	//mientras que el número de evaluaciones sea menor a 5000
	while( num_evaluaciones < 5000)
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
		
		//Cada 10 generaciones aplicamos una búsqueda local primer mejor
		if(num_evaluaciones%10 == 0)
		{
			int ale = Randint(0,9);
			primerMejor(relation,training,test,poblacion_hijos[ale],num_evaluaciones);
			
		}

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

//*******************************************************************************************************
//																										*
// Algoritmo híbdrido cada 10 generaciones se aplica una búsqueda local a los 0.1*TAMPOB mejores cromo  *
// somas                                                                                                *
//																										*
//*******************************************************************************************************
void AGGAM3( string relation, vector< vector< float> > training, vector< vector< float> > test, vector< bool> &seleccion)
{
	const int TAMPOB = 10;
	const float PCRUCE = 0.7;
	const float PMUTAR = 0.01;
	const int TAMBUS = 0.1*TAMPOB;
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
	bool salir = false;
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
	
	//mientras que el número de evaluaciones sea menor a 5000
	while(!salir)
	{
		if(num_evaluaciones > 5000)
		{
			salir = true;
		}
		else
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
			
			//Cada 10 generaciones aplicamos una búsqueda local primer mejor
			if(num_evaluaciones%10 == 0 && num_evaluaciones != 0)
			{
			
			    primerMejor(relation,training,test,poblacion_hijos[0],num_evaluaciones);
				
			}
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
			num_evaluaciones++; //Aumentamos el valor del número de evaluaciones
			//cout << num_evaluaciones << endl;
			}
		
	}

	seleccion = poblacion[indice_elite];
}