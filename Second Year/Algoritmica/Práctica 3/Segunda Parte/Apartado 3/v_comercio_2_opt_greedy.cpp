/*
Referencia: 
https://louisville.edu/speed/faculty/sheragu/Research/Intelligent/tsp.PDF
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

struct Ciudad{
	int indice;
	double x; //Coordenadas
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
	
	//Vamos cogiendo cada vez la ciudad más cercana dentro del conjunto de ciudades
	for(int i = 0; i < ciudades.size(); i++){
		ciudad_actual = ciudades[i];
		v_aux = ciudades_solucion;
		v_aux.push_back(ciudad_actual);
		double d = calcularDistanciaTotal(v_aux);
		if(d < min_distancia){
			min_distancia = d;
			indice_ciudad = i;
			
		}
		v_aux.clear();
	
		
	}

	ciudades_solucion.push_back(ciudades[indice_ciudad]);
	ciudades.erase(ciudades.begin() + indice_ciudad);
}

//Algoritmo Greedy para calcular una ruta

void calcularRuta(vector<Ciudad> &ciudades, vector<Ciudad> &ciudades_solucion){

	ciudades_solucion.push_back(ciudades.at(0));
	ciudades.erase(ciudades.begin());
	while(ciudades.size()){

		//Vamos seleccionando las ciudades, dentro de la función también se va eliminando
		seleccionarCiudad(ciudades,ciudades_solucion);
	}

}
// Devuelve en new tour una cadena con las ciudades que corresponden 
// a la posicion i y j intercambiadas

void SwapCiudades(vector<Ciudad> &tour, vector<Ciudad> &new_tour,int i, int k ) 
{
    int size = tour.size();
    

    // 1. Hasta i-1
    for ( int c = 0; c <= i - 1; ++c )
    {
        new_tour[c].x = tour[c].x;
	new_tour[c].y = tour[c].y;
	new_tour[c].indice = tour[c].indice;
    }
     
    // 2. Desde ciudades(i) y a ciudades(k)
    int dec = 0;
    for ( int c = i; c <= k; ++c )
    {
        new_tour[c].x = tour[k-dec].x;
	new_tour[c].y = tour[k-dec].y;
	new_tour[c].indice = tour[k-dec].indice;        
	dec++;
    }
 
    // 3. Desde ciudades (k+1) hasta el final
    for ( int c = k + 1; c < size; ++c )
    {
        new_tour[c].x = tour[c].x;
	new_tour[c].y = tour[c].y;
	new_tour[c].indice = tour[c].indice;
    }
}

//MAIN

int main(int argc, char* argv[]){

	vector<Ciudad> ciudades, ciudades_solucion;
	leerCiudades(ciudades, argv[1]);
	int tam = ciudades.size();	
	// Paso 1++
	calcularRuta(ciudades, ciudades_solucion);
	int z = calcularDistanciaTotal(ciudades_solucion);
	int zp = 0;
	int i = 1;
	int j = 2;
	vector<Ciudad> Sp(tam);
	
	for(int i = 0; i < ciudades_solucion.size(); i++)
		cout << ciudades_solucion[i].indice << " " << ciudades_solucion[i].x << " " << ciudades_solucion[i].y << endl;

	
	
	cout << endl << calcularDistanciaTotal(ciudades_solucion) << endl;
	// Aqui es donde empieza nuestro algoritmo.
	// A la hora de calcular tiempos empezamos aqui 
	// porque la solucion inicial podria ser cualquiera 
	// cojo esta porque ya da una solución coherente 
	// y porque asi aparecia en la descripcion del algoritmo
	while (i <= tam-2 && j <= tam-1)
	{	// Paso2
		SwapCiudades(ciudades_solucion,Sp,i,j);
		
		zp = calcularDistanciaTotal(Sp); 
		
		if(zp >= z && j < tam-1)
		{
			j++;
		}
		else if(zp >= z && j == tam -1){
			i = i+1;
			j = i+1;

		}
		//Paso 3
		else if(zp < z){
			// Copiamos la solucion parcial en el vector de salida (ciudades_solucion)
			for (int l = 0; l <= tam; l++){
				ciudades_solucion[l].x = Sp[l].x;
				ciudades_solucion[l].y = Sp[l].y;
				ciudades_solucion[l].indice = Sp[l].indice;
			}
			z=zp;	
			i=i+1;
			j=i+1;
		}

	
	}
	
	
	for(int i = 0; i < ciudades_solucion.size(); i++)
		cout << ciudades_solucion[i].indice << " " << ciudades_solucion[i].x << " " << ciudades_solucion[i].y << endl;

	

	cout << endl << calcularDistanciaTotal(ciudades_solucion) << endl;

	return 0;
}
