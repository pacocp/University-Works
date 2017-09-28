
#ifndef _BUSQUEDA_MULTI_H_
#define _BUSQUEDA_MULTI_H_

using namespace std;

// Búsqueda multiarranque básica
void BMB( string &relation, vector< vector< float> > &training, vector< vector< float> > &test, vector< bool> &seleccion);

// Búsqueda GRASP
void GRASP( string &relation, vector< vector< float> > &training, vector< vector< float> > &test, vector< bool> &seleccion, float tolerancia);

// Búsqueda ILS
void ILS( string &relation, vector< vector< float> > &training, vector< vector< float> > &test, vector< bool> &seleccion);

#endif
