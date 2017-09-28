
#include <iostream>
#include <vector>
#include <string>
#include "manejodedatos.h"
#include "clasificador-kNN.h"
#include "greedy.h"
#include "random_ppio.h"
#include "utilidades.h"
#include "busquedaLocal.h"
#include "busquedaMulti.h"

void BMB( string &relation, vector< vector< float> > &training, vector< vector< float> > &test, vector< bool> &seleccion)
{
	int num_atributos;
	int num_ejemplos;

	checkRelation( relation, num_atributos, num_ejemplos);

	vector< bool> sol_act(num_atributos);
	vector< bool> sol_nueva(num_atributos);
	vector< bool> sol_mejor(num_atributos);
	float exito_act;
	float exito_nuevo;
	float exito_mejor;

	// Generamos la primera solución inicial aleatoria
	generarVecinoRandom( relation, sol_act);
	exito_act = getExito( relation, training, test, sol_act);
	sol_mejor = sol_act;
	exito_mejor = exito_act;

	// Hacemos 24 arrancanques nuevos mas para BL
	for( int i = 0; i < 25; i++)
	{
		cout << "ESTOY HACIENDO LA BL NUMERO" << i << endl;
		// Hacemos una BL
		sol_nueva = sol_act;
		primerMejor( relation, training, test, sol_nueva);
		exito_nuevo = getExito( relation, training, test, sol_nueva);

		// Si es mejor solución se sustituye
		if( exito_nuevo > exito_mejor)
		{
			exito_mejor = exito_nuevo;
			sol_mejor = sol_nueva;
		}

		// Generamos una nueva solución de arranque
		generarVecinoRandom( relation, sol_act);
		exito_act = getExito( relation, training, test, sol_act);
	}

	seleccion = sol_mejor;
}

void GRASP( string &relation, vector< vector< float> > &training, vector< vector< float> > &test, vector< bool> &seleccion, float tolerancia)
{
	int num_atributos;
	int num_ejemplos;

	checkRelation( relation, num_atributos, num_ejemplos);
 
	vector< bool> sol_nueva(num_atributos);
	vector< bool> sol_mejor(num_atributos);
	float exito_nuevo;
	float exito_mejor;

	// Hacemos 25 arrancanques nuevos para BL usando un greedy aleatorio
	for( int i = 0; i < 15; i++)
	{
		// Generamos una solución nueva
		greedyAleatorio(relation, training, test, sol_nueva, tolerancia);
		
		// Hacemos una BL sobre la nueva solución
		primerMejor( relation, training, test, sol_nueva);
		exito_nuevo = getExito( relation, training, test, sol_nueva);

		// Si es mejor solución se sustituye
		if( exito_nuevo > exito_mejor)
		{
			exito_mejor = exito_nuevo;
			sol_mejor = sol_nueva;
		}
	}

	seleccion = sol_mejor;
}


void ILS( string &relation, vector< vector< float> > &training, vector< vector< float> > &test, vector< bool> &seleccion)
{
	int num_atributos;
	int num_ejemplos;

	checkRelation( relation, num_atributos, num_ejemplos);
	
	vector< bool> sol_act(num_atributos);
	vector< bool> sol_mejor(num_atributos);
	vector< bool> sol_mutar(num_atributos);
	float exito_act;
	float exito_mejor;
	float exito_mutar;
	int iaux;

	// Generamos la primera solución inicial aleatoria
	generarVecinoRandom( relation, sol_act);
	exito_act = getExito( relation, training, test, sol_act);
	sol_mejor = sol_act;
	exito_mejor = exito_act;

	// Hacemos una BL
	sol_mutar = sol_act;
	primerMejor( relation, training, test, sol_mutar);
	
	// Hacemos 24 arrancanques nuevos mas para BL con mutación
	for( int i = 0; i < 25; i++)
	{
		// Realizamos una mutación de la mejor solución
		for( int j = 0; j < (0.1*(num_atributos-1)); j++)
		{
			iaux = Randint(0, num_atributos-2);
			flip( sol_mutar, iaux);
		}

		// Hacemos una BL a la solución mutada
		primerMejor( relation, training, test, sol_mutar);
		exito_mutar = getExito( relation, training, test, sol_mutar);
		
		// Si es mejor solución se sustituye
		if( exito_mutar > exito_mejor)
		{
			exito_mejor = exito_mutar;
			sol_mejor = sol_mutar;
		}
		
		sol_mutar = sol_mejor;
	}

	seleccion = sol_mejor;
}
