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

void eliminarCiudadesUsadas(vector<Ciudad> &ciudades, int indice1, int indice2, int indice3){

	int contador = 1, i = 0;

	while((i < ciudades.size()) && (contador <= 3)){
		if((ciudades[i].indice == indice1) || (ciudades[i].indice == indice2) || (ciudades[i].indice == indice3)){
			ciudades.erase(ciudades.begin() + i);
			contador++;
		}
		else
			i++;
	}
}

//Método para obtener la ciudad de más al Norte, más al Este y más al Oeste
void obtenerCircuitoParcial(vector<Ciudad> &ciudades, vector<Ciudad> &ciudades_solucion){

	int indice_este = 0, indice_oeste = 0, indice_norte = 0;
	int minimo_x = 10000, maximo_x = 0, maximo_y = 0;

	for(int i = 0; i < ciudades.size(); i++){
		//Calcular ciudad más al oeste
		if(ciudades[i].x < minimo_x){
			minimo_x = ciudades[i].x;
			indice_oeste = i;
		}
		//Calcular ciudad más al norte
		if(ciudades[i].y > maximo_y){
			maximo_y = ciudades[i].y;
			indice_norte = i;
		}
		//Calcular ciudad más al este
		if(ciudades[i].x > maximo_x){
			maximo_x = ciudades[i].x;
			indice_este = i;
		}
	}

	//Añadir ciudades a la solución
	ciudades_solucion.push_back(ciudades[indice_oeste]);
	ciudades_solucion.push_back(ciudades[indice_norte]);
	ciudades_solucion.push_back(ciudades[indice_este]);
	ciudades_solucion.push_back(ciudades[indice_oeste]);
	//Eliminar del vector de ciudades
	eliminarCiudadesUsadas(ciudades, indice_norte+1, indice_oeste+1, indice_este+1);

}

//Método para calcular la distancia total de un vector de ciudades
double calcularDistanciaTotal(vector<Ciudad> ciudades){

	double distancia = 0.0, x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0;

	for(int i = 1; i < ciudades.size(); i++){
		x1 = ciudades[i-1].x;
		y1 = ciudades[i-1].y;
		x2 = ciudades[i].x;
		y2 = ciudades[i].y;

		distancia += sqrt(pow(x1-x2, 2)+pow(y1-y2, 2));
	}

	return distancia;
}

//Método para seleccionar la siguiente ciudad solución
void seleccionarCiudad(vector<Ciudad> &ciudades, vector<Ciudad> &ciudades_solucion){

	Ciudad ciudad_actual;
	vector<Ciudad> v_aux;
	double min_distancia = 99999999999;
	int indice_ciudad = 0, indice_posicion_insertar = 0;
	//vector<Ciudad >::iterator it;

	for(int i = 0; i < ciudades.size(); i++){
		ciudad_actual = ciudades[i];
		for(int j = 1; j < ciudades_solucion.size() - 1; j++){	
			v_aux = ciudades_solucion;
			v_aux.insert(v_aux.begin() + j, ciudad_actual);
			double d = calcularDistanciaTotal(v_aux);
			if(d < min_distancia){
				min_distancia = d;
				indice_ciudad = i;
				indice_posicion_insertar = j;
			}
			v_aux.clear();
		}
	}

	ciudades_solucion.insert(ciudades_solucion.begin() + indice_posicion_insertar, ciudades[indice_ciudad]);
	ciudades.erase(ciudades.begin() + indice_ciudad);
}

//Método para calcular el circuito solución
void calcularRuta(vector<Ciudad> &ciudades, vector<Ciudad> &ciudades_solucion){

	obtenerCircuitoParcial(ciudades, ciudades_solucion);

	while(ciudades.size()){
		seleccionarCiudad(ciudades, ciudades_solucion);
	}
}

int main(int argc, char* argv[]){

	vector<Ciudad> ciudades, ciudades_solucion;
	leerCiudades(ciudades, argv[1]);
	calcularRuta(ciudades, ciudades_solucion);

	for(int i = 0; i < ciudades_solucion.size(); i++)
		cout << ciudades_solucion[i].indice << " " << ciudades_solucion[i].x << " " << ciudades_solucion[i].y << endl;

	//ciudades_solucion.erase(ciudades_solucion.end() - 1);
	cout << endl << calcularDistanciaTotal(ciudades_solucion) << endl;

	return 0;
}
