#ifndef _ANNEAL_H_
#define _ANNEAL_H_

#include <vector>

/*Implementación del cliterio de metrópolis para la aceptación o no de un vecino*/
int metrop (float de, float t);

/*Función que devuelve la solución utilizando el simulated annealing*/
void anneal( string &relation, vector< vector< float> > &training, vector< vector< float> > &test, vector< bool> &seleccion);


#endif