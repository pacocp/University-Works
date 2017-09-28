
#include <iostream>
#include <vector>
#include <string>
#include "manejodedatos.h"
#include "clasificador-kNN.h"
#include "greedy.h"
#include "random_ppio.h"
#include "utilidades.h"
#include <math.h>
#include "anneal.h"

int metrop (float de, float t)
/* Implementacion del criterio de Metropolis. Devuelve 1 si el vecino
   es aceptado y 0 en caso contrario. Acepta automaticamente dicho
   vecino si es mejor que la solucion actual (es decir, si
   de = F(Sactual) - F(Snueva) es negativo). En caso contrario, lo
   acepta o rechaza probabilisticamente en funcion del valor de la
   temperatura, t, y la diferencia de costos, de. */

{
 return de < 0.0 || Rand() < exp(-de/t);
 }

void anneal( string &relation, vector< vector< float> > &training, vector< vector< float> > &test, vector< bool> &seleccion)
{
	int num_atributos;
	int num_ejemplos;

	checkRelation( relation, num_atributos, num_ejemplos);

	vector< bool> sol_act(num_atributos);
	vector< bool> mejor_sol_global(num_atributos);
	vector< bool> sol_nueva(num_atributos);
	float exito_act;
	float exito_nuevo;
	float mejor_exito_global;
	bool fin_externo = false; //Para salir del while externo
	bool fin_interno = false; //Para salir del while interno
	bool acepto_sol_nueva = false; //si no acepto soluciones nuevas para el enfriamiento que tengo, me salgo
	int contador_vecinos;
	int num_sol = 0;
	// Generamos solución actual aleatoria
	generarVecinoRandom( relation, sol_act);
	//Obtenemos el éxito actual
	exito_act = getExito( relation, training, test, sol_act); 
	mejor_exito_global = exito_act; //COjo como mejores exitos y solución los primeros
	mejor_sol_global = sol_act;
	/******* TEMPERATURAS ******************/
	float temperatura_inicial = (0.3*exito_act)/(-log(0.3)) ; //Incializamos la temperatura
	float temperatura_min = 0.001; //Temperatura mínucma
	if(temperatura_inicial < temperatura_min)
	{
		temperatura_min = 0.0001; // Si la temperatura inicial es más pequeña que la mínima reducimos aún más la temperatura mínimica
	}
	
	float beta = (temperatura_inicial - temperatura_min)/((15000/(num_atributos-2)^2)*temperatura_inicial*temperatura_min); //Para el enfriamiento
	float temperatura = temperatura_inicial;
	//***************************************
	while(!fin_externo)
	{
		acepto_sol_nueva = false;
		contador_vecinos = 0;
		while( !fin_interno) // Paramos cuando la solución nueva sea mejor que la actual o se haya generado todo el vecindario de la solución actual 
			//o el criterio de metrópolis acepte una solución peor
		{
			
			sol_nueva = sol_act;
			flip( sol_nueva, contador_vecinos);
			num_sol++; //Aumentamos el número de soluciones
			exito_nuevo = getExito( relation, training, test, sol_nueva);

			//Si el éxito nuevo es mejor que el actual
			if(exito_nuevo > exito_act)
			{
				
				fin_interno = true;
				acepto_sol_nueva = true;
			}
			//Si acepto por el criterio de metrópolis
			else if( metrop(exito_nuevo,temperatura) == 1 )
			{
				
				fin_interno = true;
				acepto_sol_nueva = true;
				temperatura = temperatura/(1+ beta*temperatura);
				
				
			}
			//Si he generado todo el vecindario
			if(contador_vecinos == num_atributos-2 || num_sol == 15000)
			{
				fin_interno = true;
				temperatura = temperatura/(1+ beta*temperatura);
				
				
			}

			contador_vecinos++;
		}
		
		//Si el éxito nuevo es mejor que el global actualizamos el global
		if(exito_nuevo > mejor_exito_global)
		{
			mejor_exito_global = exito_nuevo;
			mejor_sol_global = sol_nueva;
		}
		//Si he aceptado por el criterio de metrópolis o el éxito nuevo es mejor que el actual
		// actualizamos la solución
		if( metrop(exito_nuevo,temperatura) == 1 || exito_nuevo > exito_act)
		{
			sol_act = sol_nueva;
			exito_act = exito_nuevo;
			
		}

		//Si no hemos aceptado una solución nueva o el número de evaluaciones es 15000 acabamos	
		if( acepto_sol_nueva == false || ( num_sol == 15000))
		{
			fin_externo = true;
		}
		fin_interno = false;

	}
	seleccion = mejor_sol_global;
}