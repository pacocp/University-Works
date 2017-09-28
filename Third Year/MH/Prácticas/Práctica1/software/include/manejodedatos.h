
#ifndef _MANEJODATOS_H_
#define _MANEJODATOS_H_

using namespace std;

// Comprueba la relación de trabajo para conocer el número de atributos y de ejemplares
void checkRelation( string relation, int &num_atributos, int &num_ejemplos);

// Introduce el conjunto de ejemplo
int ejemploSet(  string &relation, vector< string> &atributos, vector< vector< float> > &datos);

//Introduce el conjunto de arritmias 
int arrhythmiaSet(  string &relation, vector< string> &atributos, vector< vector< float> > &datos);

//Introduce el conjunto de movemet libras
int movementSet(  string &relation, vector< string> &atributos, vector< vector< float> > &datos);

//Introduce el conjutno de wdbc
int wdbcSet(  string &relation, vector< string> &atributos, vector< vector< float> > &datos);

// Menú para decidir que conjunto de datos introducir en el programa
int introducirDatos( string &relation, vector< string> &atributos, vector< vector< float> > &datos, int opcion);

// Normaliza los datos para evitar desequilibrios al analizarlos
void normalizar( string &relation, vector< vector< float> > &datos, vector< vector< float> > &datos_normal);

// Divide los datos en dos conjuntos iguales
void dividirDatos( string &relation, vector< vector< float> > &datos, vector< vector< float> > &primerSet, vector< vector< float> > &segundoSet, int opcion);

#endif
