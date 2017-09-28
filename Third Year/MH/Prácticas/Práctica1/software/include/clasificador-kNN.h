#ifndef _kNN_H_
#define _kNN_H_
using namespace std;

// Calcula la distancia euclidea  con selección de características entre dos ejemplos
float calcularDistanciaEuclidea( string relation, vector< float> primero, vector< float> segundo, vector< bool> carac);

// Obtiene los tres vecinos más cercanos del ejemplo en función de su distancia euclidea
void obtenerTresVecinos( string relation, vector< vector< float> > training, vector< float> ejemplar, vector< vector< float> > &vecinos, vector< bool> caracteristicas);

// Vota la clase más probable en función de los vecinos
int votarClase( string relation, vector< vector< float> > vecinos);

// Calcula el porcentaje de aciertos de la predicción
float calcularPrecision( string relation, vector< vector< float> > test, vector< float> &prediccion);

// Clasificador knn con k = 3
void clasificar( string relation, vector< vector< float> > training, vector< vector< float> > test, vector< float> &prediccion, vector< bool> carac);

// Obtener el exito de una selección de características
float getExito( string relation, vector< vector< float> > training, vector< vector< float> > test, vector< bool> seleccion);

#endif