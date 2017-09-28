
#include <iostream>
#include <vector>
#include <string>
#include "manejodedatos.h"
#include "clasificador-kNN.h"
#include "greedy.h"
#include "random_ppio.h"
#include "utilidades.h"
#include "busquedaLocal.h"

void primerMejor( string &relation, vector< vector< float> > &training, vector< vector< float> > &test, vector< bool> &seleccion,
	int &evaluaciones)
{
	int num_atributos;
	int num_ejemplos;

	checkRelation( relation, num_atributos, num_ejemplos);

	vector< bool> sol_act(num_atributos);
	vector< bool> sol_nueva(num_atributos);
	float exito_act;
	float exito_nuevo;
	bool fin_externo = false; //Para salir del while externo
	bool fin_interno = false; //Para salir del while interno
	int contador_vecinos;
	int num_sol = 0;
	
	// Generamos solución actual aleatoria
	generarVecinoRandom( relation, sol_act);
	//Obtenemos el éxito actual
	exito_act = getExito( relation, training, test, sol_act); 
	
	while( !fin_externo) // Paramos cuando no se encuentre mejora en todo el entorno o bien se hayan evaluado 15000 soluciones distintas
	{
		contador_vecinos = 0;
		
		while( !fin_interno) // Paramos cuando la solución nueva sea mejor que la actual o se haya generado todo el vecindario de la solución actual 
		{
			sol_nueva = sol_act;
			flip( sol_nueva, contador_vecinos);
			num_sol++; //Aumentamos el número de soluciones
			exito_nuevo = getExito( relation, training, test, sol_nueva);
	
			if( ( exito_nuevo > exito_act) || ( contador_vecinos == num_atributos-2))
			{
				fin_interno = true;
			}

			contador_vecinos++;
		}
		
		if( exito_nuevo > exito_act)
		{
			sol_act = sol_nueva;
			exito_act = exito_nuevo;
		}

		if( ( exito_nuevo <= exito_act) || ( num_sol == 15000))
		{
			fin_externo = true;
		}
		evaluaciones++;
	}

	seleccion = sol_act;
}
