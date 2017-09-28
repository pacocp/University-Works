#ifndef _GENETIC_H_
#define _GENETIC_H_

void generarPoblacionRandom( string relation, vector< vector< bool> > &poblacion, const int TAMPOB);
void evaluarPoblacion( string relation, vector< vector< float> > training, vector< vector< float> > test, vector< vector< bool> > poblacion, vector< float> &eval_poblacion, vector< bool> &evaluados, const int TAMPOB, int &num_evaluaciones);
int seleccionTorneoBinario( vector< vector< bool> > poblacion, vector< float> eval_poblacion, const int TAMPOB);
void cruceDosPuntos( string relation, vector< bool> padre, vector< bool> madre, vector< bool> &uno, vector< bool> &dos);
void elitismo(vector< vector< bool> > &poblacion,vector< float> &eval_poblacion,vector< vector< bool> > poblacion_hijos,vector< float> eval_poblacion_hijos,
	int indice_elite,float valor_elite,const int TAMPOB);
void AGG( string relation, vector< vector< float> > training, vector< vector< float> > test, vector< bool> &seleccion);
void AGE( string relation, vector< vector< float> > training, vector< vector< float> > test, vector< bool> &seleccion);



#endif