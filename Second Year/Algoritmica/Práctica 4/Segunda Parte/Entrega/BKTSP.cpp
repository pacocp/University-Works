#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include <time.h>
#include <limits>

using namespace std;

double cota_local = 0.0;
double cota_global = numeric_limits<double>::max();
int nodos_explorados = 0;

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

//Método para calcular la distancia entre dos ciudades
double calcularDistancia(Ciudad a, Ciudad b){

	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Funcion para generar una matriz de distancias (FUNCIONA)
vector< vector<double> > generaMatriz(vector <Ciudad> ciudades){

	vector<vector<double> > salida(ciudades.size());
	double distancia = 0.0;

	for ( int i = 0 ; i < ciudades.size() ; i++ )
	   salida[i].resize(ciudades.size());

	for (int i =0; i < ciudades.size() ; i++){
		for(int j =0; j<ciudades.size();j++){
			if(i==j)
				salida[i][j]=0;
			else{
				distancia = calcularDistancia(ciudades[i], ciudades[j]);			
				salida[i][j]= distancia;
			}		
		}
	}
	return salida;
}

void backtracking (int nivel, int ciudad_actual, vector<bool> &visitadas, int solucion[], const vector< vector<double> > &matriz
	, double cota_local, int solucion_final[]) {

	visitadas[ciudad_actual] = true;
	solucion[nivel - 1] = ciudad_actual;
	nodos_explorados++; 

	//Recorremos todas las ciudades
	for (int siguiente_ciudad = 0; siguiente_ciudad < visitadas.size(); siguiente_ciudad++) {
		//Si la ciudad en la que estamos en este momento no ha sido visitada aún
		if (visitadas[siguiente_ciudad] == false) {	
			//Establecemos su cota local
			cota_local = cota_local + matriz[ciudad_actual][siguiente_ciudad];
			//Comprobamos si esta solución va por buen camino
			if (cota_local < cota_global) {	
				//Descendemos un nivel en el árbol			
				backtracking(nivel + 1, siguiente_ciudad, visitadas, solucion, matriz, cota_local, solucion_final);
			}
			//Si estamos en un nodo hoja (solución)
			if (nivel == (visitadas.size() - 1)) {		
				//Cerramos el circuito (primera ciudad con última)
				cota_local += matriz[0][siguiente_ciudad];			
				//Si esta cota obtenida, es mejor que la solución que llevamos hasta el momento la actualizamos		
				if (cota_local < cota_global) {
					cota_global = cota_local;
					for(int i = 0; i < visitadas.size(); i++)
						solucion_final[i] = solucion[i];
				} 
			}
			//En el caso de que no estemos en un nodo hoja, deshacemos los cambios que hemos hecho
			else {
				cota_local = cota_local - matriz[ciudad_actual][siguiente_ciudad];
			}
			
			visitadas[siguiente_ciudad] = false;
		}
	}
}

unsigned int factorial(unsigned int n){

    if (n == 0)
       return 1;

    return n * factorial(n - 1);
}

int main (int argc, char* argv[]) {	
	
	if(argc != 2){
		cerr << "USO: ./" << argv[0] << " archivo_ciudades.tsp" << endl;
		exit(1);
	}
	clock_t t_ini, t_fin;
	double secs;
	vector<Ciudad> ciudades;
	vector< vector<double> > matriz_distancias; 

	leerCiudades(ciudades, argv[1]);
	matriz_distancias = generaMatriz(ciudades);

	vector<bool> visitadas(ciudades.size(), false);
	int solucion[ciudades.size()];
	int solucion_final[ciudades.size()];
	t_ini = clock();
	backtracking (1, ciudades[0].indice-1, visitadas, solucion, matriz_distancias, cota_local, solucion_final);
	t_fin = clock();
	double distancia = 0;
	secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	

	for(int i = 1; i < ciudades.size(); i++){
		distancia += matriz_distancias[solucion_final[i-1]][solucion_final[i]];

	}

	

	distancia += matriz_distancias[0][solucion_final[ciudades.size() - 1]];

	cout << "DISTANCIA: " << distancia << endl;

	int nodos_totales = factorial(ciudades.size());
	cout << "NODOS TOTALES " << nodos_totales << endl;
	cout << "NODOS PODADOS " << nodos_totales - nodos_explorados << endl;
	cout << "NODOS EXPLORADOS " << nodos_explorados << endl;
	cout << "TIEMPO (seg)" << secs << endl;

	return 0;
}
