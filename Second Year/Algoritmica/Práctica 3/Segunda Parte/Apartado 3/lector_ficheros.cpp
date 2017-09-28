#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

struct Ciudad{
	int indice;
	double x;
	double y;
} ciudad;

//Método para leer las ciudades desde un fichero
void leerCiudades(vector<Ciudad> &ciudades, const char fichero[]){

	ifstream f(fichero);
	double valor_leido = 0.0;
	int num_ciudades = 0;

	if(f){
		f.ignore(11);
		f >> num_ciudades;
		
		for(int i = 0; i < num_ciudades; i++){
			f >> valor_leido;
			ciudad.indice = valor_leido;
			f >> valor_leido;
			ciudad.x = valor_leido;
			f >> valor_leido;
			ciudad.y = valor_leido;

			ciudades.push_back(ciudad);
		}
	}

	f.close();
}

int main(int argc, char* argv[]){

	vector<Ciudad> ciudades;
	leerCiudades(ciudades, argv[1]);

	for(int i = 0; i < ciudades.size(); i++)
		cout << ciudades[i].indice << " " << ciudades[i].x << " " << ciudades[i].y << endl;

	return 0;
}