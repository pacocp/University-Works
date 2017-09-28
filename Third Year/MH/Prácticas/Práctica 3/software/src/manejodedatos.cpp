#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <manejodedatos.h>

using namespace std;

void checkRelation( string relation, int &num_atributos, int &num_ejemplos)
{	
	if( relation.compare("ejemplo") == 0)
	{
		num_atributos = 4;
		num_ejemplos = 13;
	}
	else if(relation.compare("arrhythmia") == 0)
	{
		num_atributos = 278;
		num_ejemplos = 386;
	}
	else if(relation.compare("Movement_Libras") == 0)
	{
		num_atributos = 90;
		num_ejemplos = 360;
	}
	else if(relation.compare("Wisconsin")==0)
	{
		num_atributos = 30;
		num_ejemplos = 569;
	}
}

int ejemploSet(  string &relation, vector< string> &atributos, vector< vector< float> > &datos)
{
	// Variables
	int num_atributos;
	int num_ejemplos;
	string saux;
	char caux;
	float faux;
	ifstream f("fichero.txt");

	// Guardamos el nombre de la relación
	f.ignore(256, ' ');
	f >> relation;

	// Comprobamos el número de atributos y ejemplos del set
	checkRelation( relation, num_atributos, num_ejemplos);
	
	// Guardamos los nombres de los atributos
	for( int i = 0; i < num_atributos-1; i++)
	{
		f.ignore(256, ' ');
		f >> saux;
		atributos[i] = saux;
		f.ignore(256, '@');
	}
    
	f.ignore(256, '@');
	f.ignore(256, '\n');

	// Guardamos los valores de los atributos
	for( int i = 0; i < num_ejemplos; i++)
	{
		for( int j = 0; j < num_atributos-1; j++)
		{
	    	f >> faux;
	    	datos[i].push_back(faux);
			f.ignore(256, ' ');
		}
		f >> faux;
    	datos[i].push_back(faux);
		f.ignore(256, '\n');
	}
	f.close();
	return 0;
}

int arrhythmiaSet(  string &relation, vector< string> &atributos, vector< vector< float> > &datos)
{
	// Variables
	int num_atributos;
	int num_ejemplos;
	string saux;
	char caux;
	float faux,faux2;
	ifstream f("arrhythmia.arff");

	// Guardamos el nombre de la relación
	f.ignore(256, ' ');
	f >> relation;

	// Comprobamos el número de atributos y ejemplos del set
	checkRelation( relation, num_atributos, num_ejemplos);
	
	// Guardamos los nombres de los atributos
	for( int i = 0; i < num_atributos-1; i++)
	{
		f.ignore(256, ' ');
		f >> saux;
		atributos[i] = saux;
		f.ignore(256, '@');
	}
    
	f.ignore(256, '@');
	f.ignore(256, '\n');
	datos[0].push_back(54);
	f.ignore(256,' ');
	// Guardamos los valores de los atributos
	for( int i = 0; i < num_ejemplos; i++)
	{
		for( int j = 0; j < num_atributos-1; j++)
		{
	    	f >> faux;
	    	datos[i].push_back(faux);
			f.ignore(256, ' ');
		}

		if(i == 0)
		{
			f >> faux;
    		datos[i].push_back(faux);
    		f.ignore(256, '\n');
		}
		else
		{
			f >> faux;
    		datos[i].push_back(faux);
    		f.ignore(256, ' ');
    		f >> faux;
    		datos[i].push_back(faux);
    		f.ignore(256, '\n');
		}
		
		
	}
	f.close();
	return 0;
}


int movementSet(  string &relation, vector< string> &atributos, vector< vector< float> > &datos)
{
	// Variables
	int num_atributos;
	int num_ejemplos;
	string saux;
	char caux;
	float faux;
	ifstream f("movement_libras.arff");

	// Guardamos el nombre de la relación
	f.ignore(256, ' ');
	f >> relation;

	// Comprobamos el número de atributos y ejemplos del set
	checkRelation( relation, num_atributos, num_ejemplos);
	
	// Guardamos los nombres de los atributos
	for( int i = 0; i < num_atributos-1; i++)
	{
		f.ignore(256, ' ');
		f >> saux;
		atributos[i] = saux;
		f.ignore(256, '@');
	}
    
	f.ignore(256, '@');
	f.ignore(256, '\n');
	datos[0].push_back(0.79691);
	f.ignore(256,' ');
	
	// Guardamos los valores de los atributos
	for( int i = 0; i < num_ejemplos; i++)
	{
		for( int j = 0; j < num_atributos-1; j++)
		{
	    	f >> faux;
	    	datos[i].push_back(faux);
			f.ignore(256, ' ');
		}
		
		if(i == 0)
		{
			f >> faux;
    		datos[i].push_back(faux);
    		f.ignore(256, '\n');
		}
		else
		{
			f >> faux;
    		datos[i].push_back(faux);
    		f.ignore(256, ' ');
    		f >> faux;
    		datos[i].push_back(faux);
    		f.ignore(256, '\n');
		}
		
	}
	f.close();
	return 0;
}

int wdbcSet(  string &relation, vector< string> &atributos, vector< vector< float> > &datos)
{
	// Variables
	int num_atributos;
	int num_ejemplos;
	string saux;
	char caux;
	float faux;
	ifstream f("wdbc.arff");

	// Guardamos el nombre de la relación
	f.ignore(256, ' ');
	f >> relation;

	// Comprobamos el número de atributos y ejemplos del set
	checkRelation( relation, num_atributos, num_ejemplos);
	f.ignore(256,'\n');
	// Guardamos los nombres de los atributos
	for( int i = 0; i < num_atributos; i++)
	{
		f.ignore(256, ' ');
		f >> saux;
		atributos[i] = saux;
		f.ignore(256, '@');
	}
    
	f.ignore(256, '@');
	f.ignore(256, '\n');
	// Guardamos los valores de los atributos
	for( int i = 0; i < num_ejemplos; i++)
	{
		for( int j = 0; j < num_atributos-1; j++)
		{
	    	f >> faux;
	    	datos[i].push_back((float)faux);
			f.ignore(256, ' ');
		}
		if(i == 0)
		{
			f >> faux;
    		datos[i].push_back(faux);
    		f.ignore(256, '\n');
		}
		else
		{
			f >> faux;
    		datos[i].push_back(faux);
    		f.ignore(256, ' ');
    		f >> faux;
    		datos[i].push_back(faux);
    		f.ignore(256, '\n');
		}
		
	}
	f.close();
	for(int i = 0; i < num_ejemplos; i++)
	{
		float clase = datos[i][0];
		datos[i].erase(datos[i].begin());
		datos[i].push_back(clase);
	}
	
	return 0;
}
int introducirDatos( string &relation, vector< string> &atributos, vector< vector< float> > &datos, int opcion)
{
	int ret;
	
	if( opcion == 0)
	{
		ret = arrhythmiaSet( relation, atributos, datos);
	}
	else if( opcion == 1)
	{
		ret = movementSet( relation, atributos, datos);
	}
	else if( opcion == 2)
	{
		ret = wdbcSet( relation, atributos, datos);
	}
	else if( opcion == 3)
	{
		ret = ejemploSet(relation, atributos, datos);
	}

	return ret;
}

void normalizar( string &relation, vector< vector< float> > &datos, vector< vector< float> > &datos_normal)
{
	int num_atributos;
	int num_ejemplos;
	vector< float> max(400);
	vector< float> min(400);
	float faux;
	
    checkRelation( relation, num_atributos, num_ejemplos);
    
	// Obtenemos el mayor y el menos elemento de cada atributo
	for( int i = 0; i < num_atributos; i++)
	{
		max[i] = 0;
		min[i] = 1000000;
		for( int j = 0; j < num_ejemplos; j++)
		{
			
			
			if( datos[j][i] > max[i])
			{
				max[i] = datos[j][i];
			}

			if( datos[j][i] < min[i])
			{
				min[i] = datos[j][i];
			}
			
		}	
	}

	// Aplicamos la fórmula para normalizar todos los valores
	for( int i = 0; i < num_atributos; i++)
	{
		for( int j = 0; j < num_ejemplos; j++)
		{
			faux = (datos[j][i] - min[i])/(max[i] - min[i]);
			datos_normal[i].push_back(faux);
		}
	}
}

void dividirDatos( string &relation, vector< vector< float> > &datos, vector< vector< float> > &primerSet, vector< vector< float> > &segundoSet, int opcion)
{
	int num_atributos;
	int num_ejemplos;
	bool es_test = true;
	int k = 0;
	int l = 0;
	float faux;
	
    checkRelation( relation, num_atributos, num_ejemplos);

	if( opcion == 0) // Dividimos el conjuntos de datos en dos conjuntos justo por la mitad
	{
		for( int i = 0; i < num_ejemplos; i++)
		{
			if( es_test) // Metemos la primera mitad de los datos en un conjunto
			{
				for( int j = 0; j < num_atributos+1; j++)
				{
					primerSet[k].push_back( datos[i][j]);
				}
				k++;
				
				if( i > ((num_ejemplos/2)-(num_ejemplos/4))-1)
				{
					es_test = false;
				}
				else
				{
					if(i > ((num_ejemplos/2)+(num_ejemplos/4))-1)
					{
						es_test = false;
					}
				}
			}
			else // Metemos la segunda mitad de los datos en otro conjunto
			{
				for( int j = 0; j < num_atributos+1; j++)
				{
					segundoSet[l].push_back( datos[i][j]);
				}
				l++;

				if( i > ( num_ejemplos/2)-1)
				{
					es_test = true;
				}
			}
		}
	}
		else if( opcion == 1) // Dividimos los datos introduciendo todos los atributos pares en un conjunto y los impares en otro
	{
		for( int i = 0; i < num_ejemplos; i++)
		{
			if( es_test) // Metemos los elementos pares en un conjunto
			{
				for( int j = 0; j < num_atributos+1; j++)
				{
					primerSet[k].push_back( datos[i][j]);
				}
				k++;
				es_test = false;
			}
			else // Metemos los elementos impares en otro conjunto
			{
				for( int j = 0; j < num_atributos+1; j++)
				{
					segundoSet[l].push_back( datos[i][j]);
				}
				l++;
				es_test = true;
			}
		}
	}
		else if( opcion == 2) // Dividimos los conjuntos dividiendo los elementos intercaladamente de dos en dos
	{
		for( int i = 0; i < num_ejemplos; i = i + 2)
		{
			if( es_test) // Cogemos atributos de dos en dos desde el primero de forma intercalada
			{
				for( int m = i; m < (i+2); m++)
				{
					if( m < num_ejemplos)
					{
						for( int j = 0; j < num_atributos+1; j++)
						{
							primerSet[k].push_back( datos[m][j]);
						}
						k++;
					}
				}
				es_test = false;
			}
			else // Cogemos los atributos de dos en dos desde el tercero de forma intercalada
			{
				for( int m = i; m < (i+2); m++)
				{
					if( m < num_ejemplos)
					{
						for( int j = 0; j < num_atributos+1; j++)
						{
							segundoSet[l].push_back( datos[m][j]);	
						}
						l++;
					}
				}
				es_test = true;
			}
		}
	}
		else if( opcion == 3) // Dividimos los conjuntos dividiendo los atributos intercaladamente de tres en tres
	{
		for( int i = 0; i < num_ejemplos; i = i + 3)
		{
			if( es_test) // Cogemos atributos de tres en tres desde el primero de forma intercalada
			{
				for( int m = i; m < (i+3); m++)
				{
					if( m < num_ejemplos)
					{
						for( int j = 0; j < num_atributos+1; j++)
						{
							primerSet[k].push_back( datos[m][j]);	
						}
						k++;
					}
				}
				es_test = false;	
			}
			else // Cogemos atributos de tres en tres desde el cuarto de forma intercalada
			{
				for( int m = i; m < (i+3); m++)
				{
					if( m < num_ejemplos)
					{
						for( int j = 0; j < num_atributos+1; j++)
						{
							segundoSet[l].push_back( datos[m][j]);	
						}
						l++;
					}
				}
				es_test = true;
			}
		}
	}
	else if( opcion == 4) // Dividimos los conjuntos dividiendo los atributos intercaladamente de cinco en cinco
	{
		for( int i = 0; i < num_ejemplos; i = i + 5)
		{
			if( es_test) // Cogemos atributos de cinco en cinco desde el primero de forma intercalada
			{
				for( int m = i; m < (i+5); m++)
				{
					if( m < num_ejemplos)
					{
						for( int j = 0; j < num_atributos+1; j++)
						{
							primerSet[k].push_back( datos[m][j]);	
						}
						k++;
					}
				}
				es_test = false;
			}
			else // Cogemos atributos de cinco en cinco desde el sexto de forma intercalada
			{
				for( int m = i; m < (i+5); m++)
				{
					if( m < num_ejemplos)
					{
						for( int j = 0; j < num_atributos+1; j++)
						{
							segundoSet[l].push_back( datos[m][j]);	
						}
						l++;
					}
				}
				es_test = true;
			}
		}
	}

	// Igualar los dos conjuntos
	while( (k-l) > 1)
	{
		for( int i = 0; i < num_atributos+1; i++)
		{
			faux = primerSet[k-1][i];
			segundoSet[l].push_back(faux);
		}
		k--;
		l++;
	}
}
