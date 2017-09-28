#ifndef _UTILIDADES_H_
#define _UTILIDADES_H_

using namespace std;

// Genera un vecino dado un conjunto y la posición que queremos cambiar
void flip( vector<bool> &conjunto, int &pos);

// Genera una solución aleatoria en un vector booleano
void generarVecinoRandom( string &relation, vector< bool> &vecino);

#endif