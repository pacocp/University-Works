#include <vector>
#include <string>
#include "manejodedatos.h"
#include "random_ppio.h"
#include "utilidades.h"

void flip( vector<bool> &conjunto, int &pos)
{
	if( conjunto[pos] == 0)
	{
		conjunto[pos] = 1;
	}
	else
	{
		conjunto[pos] = 0;
	}
}

void generarVecinoRandom( string &relation, vector< bool> &vecino)
{
	int num_atributos;
	int num_ejemplos;
	
	checkRelation( relation, num_atributos, num_ejemplos);

	for( int i = 0; i < num_atributos-1; i++)
	{
		if( Rand() >= 0.5)
		{
			flip( vecino, i);
		}
	}
}