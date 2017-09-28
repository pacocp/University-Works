#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <manejodedatos.h>
#include <clasificador-kNN.h>
#include <greedy.h>
#include <random_ppio.h>
#include <utilidades.h>
#include <busquedaLocal.h>
#include <genetic.h>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;
high_resolution_clock::time_point tantes, tdespues;
duration<double> transcurrido;
	
int main()
{
	
	string relation;
	vector< string> atributos(300);
	vector< vector< float> > datos(1000);
	vector< vector< float> > datos_normal(1000);
	vector< vector< float> > test(1000);
	vector< vector< float> > training(1000);
	vector< vector< float> > vecinos;
	vector< float> prediccion;
	float faux;
	float exito;
	int num_atributos;
	int num_ejemplos;

	Set_random(111);
	
	introducirDatos(relation, atributos, datos,1);
	checkRelation( relation, num_atributos, num_ejemplos);
	normalizar( relation, datos, datos_normal);
	dividirDatos( relation, datos, test, training, 0);


	
	vector< bool> car(num_atributos, 1);
    vector< bool> seleccion(num_atributos, 0);
	
	
	// Prueba introducción de datos y normalización
/*
	cout << relation << endl;

	for( int i = 0; i < num_atributos; i++)
	{
		cout << atributos[i] << endl;
	}	

	for( int i = 0; i < num_ejemplos; i++)
	{
		for( int j = 0; j < num_atributos+1; j++)
		{
			cout << datos[i][j] << " " ;
		}
		cout << endl;
	}


	*/
/*
	cout << "\n\n";
	
	for( int i = 0; i < 5; i++)
	{
		for( int j = 0; j < 5; j++)
		{
			cout << datos_normal[i][j] << " " ;
		}
		cout << endl;
	}

*/
	//Prueba dividir datos
/*
	cout << endl << "Test" << endl;
	for( int i = 0; i <= num_ejemplos/2; i++)
	{
		for( int j = 0; j < num_atributos+1; j++)
		{
			cout << test[i][j] << " " ;
		}
		cout << endl;
	}

	
	cout << endl << "Training" << endl;
	for( int i = 0; i < num_ejemplos/2; i++)
	{
		for( int j = 0; j < num_atributos+1; j++)
		{
			cout << training[i][j] << " " ;
		}
		cout << endl;
	}
*/
	// Prueba Distancia Euclidea
/*
	faux = calcularDistanciaEuclidea( relation, test[0], training[5], car);
	cout << faux << endl;

*/

	// Prueba obtener vecinos
/*
	obtenerTresVecinos( relation, training, test[7], vecinos, car);

	for( int i = 0; i < 3; i++)
	{
		for( int j = 0; j < num_atributos+1; j++)
		{
			cout << vecinos[i][j] << " ";
		}
		cout << endl;
	}

	cout << "\n\n" << endl;
	// Prueba votar

	cout << votarClase( relation, vecinos) << endl; 

*/
	// Prueba clasificador
/*
	clasificar( relation, training, test, prediccion, car);
	int acierto = calcularPrecision( relation, test, prediccion);

	//float acierto = getExito( relation, training, test, car);
	
	for( int i = 0; i < (num_ejemplos/2); i++)
	{
		cout << "Prediccion: " << prediccion[i] << " Test: " << test[i][num_atributos] << endl;
	}
	cout << "El porcentaje de aciertos: " << acierto << endl;
*/
	// Prueba Greedy
/*
	greedy( relation, training, test, seleccion);
	exito = getExito( relation, training, test,seleccion);
	
*/

	// Prueba primerMejor
/*
	primerMejor( relation, training, test, seleccion);
	exito = getExito( relation, training, test, seleccion);
*/
/*
	//Prueba simulated annealing
	anneal(relation, training, test, seleccion);
	exito = getExito( relation, training, test, seleccion);
*/

    //Prueba BMB
/*
    BMB(relation,training,test,seleccion);
    exito = getExito( relation, training, test, seleccion);
*/

    //Prueba ILS
/*
    ILS(relation,training,test,seleccion);
    exito = getExito( relation, training, test, seleccion);
*/

    //Prueba GRASP
/*
    float tolerancia = 0.3; //Tolerancia para el GRAPS
    GRASP(relation,training,test,seleccion,tolerancia);
    exito = getExito( relation, training, test, seleccion);
*/
    //Prueba AGG
  
    cout << "\nEjecutando AGG...\n\n";
	tantes = high_resolution_clock::now();
    AGG(relation,training,test,seleccion);
    tdespues = high_resolution_clock::now();
    transcurrido = duration_cast<duration<double>>(tdespues - tantes);
    cout << "TIEMPO" << transcurrido.count() << endl;
    exito = getExito( relation, training, test, seleccion);
  
    //Prueba AGE
    /*
    cout << "\nEjecutando AGE...\n\n";
	tantes = high_resolution_clock::now();
    AGE(relation,training,test,seleccion);
    tdespues = high_resolution_clock::now();
    transcurrido = duration_cast<duration<double>>(tdespues - tantes);
    cout << "TIEMPO" << transcurrido.count() << endl;
    exito = getExito( relation, training, test, seleccion);
    */

	cout << "El exito es: " << exito << endl;
	cout << "Las características seleccionadas son: ";
	for( int i = 0; i < num_atributos-1; i++)
	{
		if( seleccion[i] == 1)
		{
			cout << " 1 ";
		}
		else
		{
			cout << " 0 ";
		}
	}

	cout << endl;

}