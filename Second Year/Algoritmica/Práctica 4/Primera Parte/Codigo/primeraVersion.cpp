#include <stdlib.h> // rand
#include <time.h> // Time()
#include <iostream>// cin cout
#include <vector>

using namespace std;

/************************************************************
Algoritmo de bactraking - Parte 1
La cena de gala.
************************************************************/
/**
 *
 * Función que genera una entrada para nuestro problema
 * la posicion i,j es igual a la j,i y representa la compatibilidad
 * entre los asistentes i y j.
 */
int **generarEntrada(int n){

	srand(time(NULL)); // inicializa srand
	int **matriz;
	matriz = new int*[n-1];

	for (int i = 0; i < n; i++)
		matriz[i] = new int[n-1];

	for (int i = 0; i < n ;i++){
		for (int j = i; j < n; j++){
			int num = 1 + ( rand() % (100) );
			matriz[i][j] = num;
			matriz[j][i] = num;
		}
	}
	for (int i = 0; i < n ; i++){
		for (int j = 0; j < n; j++){
		 	if (i==j) matriz[i][j] = 0;		
		}

	}
	
	return matriz;
}

/******************************************************
 * @brief Funcion para calcular los valores de una lista
 * @param int valor valor para almacenar el resultado 
 * total de la compatibilidad de la lista de valores 
 * enteros alamacenados en p
 * @param int* p lista de valores de la posible solucion 
 * @param int** matriz matriz simetrica que almacena la 
 * compatiblidad de los asistentes.
 *****************************************************/
int calcularCompatibilidad(int n, vector<int> p, int **matriz){

	int valor = 0;
	// sumamos la compatibilidad con el contiguo
	// 0 con 1 , 1 con 2, 2 con 3, hasta n-2 con n-1..
	for (int i = 0; i< n-1; i++){
		valor  +=  matriz[p[i]][p[i+1]];
	}
	// sumamos el primero con el último
	// 0 con n-1
	valor += matriz[p[0]][p[n-1]];

	return valor;
}

//Función fuerza bruta para calcular un valor greedy
void calcularSolucionParcial(int n, vector<int> &solucion, vector<int> &comensales_disponibles, int **matriz){

	vector<int> posiciones;

	//Añadimos todos los comensales
	for(int i = 0; i < n; i++){
		posiciones.push_back(i);
	}

	//Borramos aquellos que ya están en la solución parcial
	for(int i = 0; i < solucion.size(); i++){
		posiciones.erase(posiciones.begin() + solucion[i]);
	}

	comensales_disponibles = posiciones;
	
	int max = 0;
	int comensal = 0, pos = 0;

	//Mientras haya comensales que colocar
	while(posiciones.size()){

		for(int j = 0; j < posiciones.size(); j++){
			//Comprobamos el último comensal que se ha sentado con todos los posibles candidatos que nos quedan
			if(matriz[solucion[solucion.size()-1]][posiciones[j]] > max){
				max = matriz[solucion[solucion.size()-1]][posiciones[j]];
				comensal = posiciones[j];
				pos = j;
			}
		}

		solucion.push_back(posiciones[pos]); //Añadimos el nuevo comensal a la solución
		posiciones.erase(posiciones.begin() + pos); //Eliminamos el comensal que se ha sentado de los posibles candidatos
		max = 0;
	}

}

//Encontramos el nodo que nos da más valor inicial
int encontrarNodoInicial(int n, int **matriz){

	int maximo = 0, pos_i = 0;

	for (int i = 0; i < n; i++){
		for (int j = i + 1; j < n ;j++){
			if(matriz[i][j] > maximo){
				maximo = matriz[i][j];
				pos_i = i;
			}
		}
	}

	return pos_i;
}

vector<int> backtracking(int n, vector<int> &solucion_parcial, vector<int> &comensales_disponibles, int **matriz, int cota){

	cout << "a" << endl;
	vector<int> solucion_aux = solucion_parcial;
	calcularSolucionParcial(n, solucion_aux, comensales_disponibles, matriz);
	int cota_local = calcularCompatibilidad(n, solucion_aux, matriz);

	cout << "Cota global " << cota << " cota local " << cota_local << endl;
	if(comensales_disponibles.size() == 1){
		solucion_parcial.push_back(comensales_disponibles[0]);
		cota = calcularCompatibilidad(solucion_parcial);
		cout << "Caso base mi amol" << endl;
		return solucion_parcial;
	}

	if(cota_local < cota){ //Podemos
		cout << "Ehtamoh podando" << endl;
		comensales_disponibles.push_back(solucion_parcial.back());
		solucion_parcial.erase(solucion_parcial.end()-1);
		solucion_parcial.push_back(comensales_disponibles[0]);
	}
	else{ //No podemos, si falange
		cout << "No podamoh, recortate un poco el albusto" << endl;
		solucion_parcial.push_back(comensales_disponibles[0]);
		comensales_disponibles.erase(comensales_disponibles.begin());
	}

	backtracking(n, solucion_parcial, comensales_disponibles, matriz, cota);
}


// Este main era para comprobar si la matriz del apartado anterior es 
// simetrica y con la diagonal de 0.
int main(int argc, char *argv[]){

	if(argc < 2){
		cerr << "Número de argumentos inválido. Pruebe con ./programa <número_comensales>" << endl;
		exit(1);
	}

	int n = atoi(argv[1]);
	int **matriz, resultado = 0, nodo = 0, cota_global;
	vector<int> solucion;
	vector<int> comensales_disponibles;

	matriz = generarEntrada(n);
	nodo = encontrarNodoInicial(n, matriz);
	cout << "nodo encontrado" << endl;
	//solucion_parcial = solucion;
	solucion.push_back(nodo);
	calcularSolucionParcial(n, solucion, comensales_disponibles, matriz);
	cout << "solucion parcial" << endl;
	cota_global = calcularCompatibilidad(n, solucion, matriz);
	cout << "cota calculada" << endl;
	solucion.clear(); //Borramos
	
	solucion.push_back(nodo);
	solucion = backtracking(n, solucion, comensales_disponibles, matriz, cota_global);

	cout << "Matriz inicial: " << endl;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n ;j++){
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}

	cout << "Solución: " << endl;

	for(int i = 0; i < solucion.size(); i++)
		cout << solucion[i] << " " ;
	cout << endl;

	resultado = calcularCompatibilidad(n, solucion, matriz);
	
	cout << resultado << endl;


}




