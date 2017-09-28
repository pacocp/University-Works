
#ifndef _GREEDY_H_
#define _GREEDY_H_

using namespace std;

// Algoritmo Greedy para selección de características
void greedy( string &relation, vector< vector< float> > &training, vector< vector< float> > &test, vector< bool> &seleccion);

//Algoritmo Greedy aleatorio para la metaheurística GRAPS
void greedyAleatorio( string &relation, vector< vector< float> > &training, vector< vector< float> > &test, vector< bool> &seleccion, float tolerancia);
#endif
