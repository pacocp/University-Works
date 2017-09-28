#include <stdlib.h> // rand
#include <time.h> // Time()
#include <iostream>// cin cout
#include <vector>

using namespace std;

int nivel_anterior = 1;

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
			if (i==j) 
				matriz[i][j] = 0;
			else{
				int num = 1 + ( rand() % (100) );
				matriz[i][j] = num;
				matriz[j][i] = num;
			}
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
int calcularSolucionParcial(int n, vector<int> solucion_parcial, vector<bool> comensales_sentados, int **matriz, int nivel){
	
	int max = 0;
	int comensal = 0, pos = 0;
	comensales_sentados[0] = true;

	while(solucion_parcial.size() < n ){
		for (int i = 0; i < n; ++i){
			if(comensales_sentados[i] == false){
				if(matriz[solucion_parcial.back()][i] > max){
					max = matriz[solucion_parcial.back()][i];
					pos = i;

				}
			}
		}
		solucion_parcial.push_back(pos);
		comensales_sentados[pos] = true;
		max = 0;
	}

	if(nivel == 1)
		return calcularCompatibilidad(n, solucion_parcial, matriz);
	else
		return (calcularCompatibilidad(n, solucion_parcial, matriz)+matriz[0][n-1]); //Cota optimista

}

/*void backtracking(int n, int nivel, int comensal, int &suma, vector<bool> &comensales_sentados, int **matriz, vector<int> &solucion, int &cota_global){

	comensales_sentados[comensal] = true;

	if(solucion.size() == n){

		for(int i = 0; i < n; i++){
			if(solucion[i] == comensal){
				solucion[i] = solucion[nivel - 1];
				solucion[nivel - 1] = comensal;
			}
		}
	}		
	else
		solucion.push_back(comensal);

	/*cout << "............" << endl;
	for(int i = 0; i < solucion.size(); i++)
		cout << solucion[i] << " " ;
	cout << endl;
	for(int i = 0; i < comensales_sentados.size(); i++)
		if(comensales_sentados[i] == true)
			cout << "t ";
		else
			cout << "f ";
	cout << endl << "............" << endl;
	
	int cota_local = calcularSolucionParcial(n, solucion, comensales_sentados, matriz, nivel+1);

	for(int siguiente_comensal = 0; siguiente_comensal < n; siguiente_comensal++){
		if(comensales_sentados[siguiente_comensal] == false){
			//suma = calcularCompatibilidad(solucion.size(), solucion, matriz);
			if(cota_local > cota_global){ //Si vamos por buen camino, descendemos
				//cout << "Llamada a back con nivel " << nivel+1 << " y sig comensal " << siguiente_comensal << endl;
				nivel_anterior = nivel;
				backtracking(n, nivel + 1, siguiente_comensal, suma, comensales_sentados, matriz, solucion, cota_global);
			}
			if(nivel == (n - 1) ){ //Si estamos en el nodo hoja, calculamos la nueva cota
				//suma = calcularCompatibilidad(solucion.size(), solucion, matriz);
				//suma = suma + matriz[siguiente_comensal][0];
				cota_local = calcularSolucionParcial(n, solucion, comensales_sentados, matriz, nivel+1);
				if(cota_local > cota_global){
					cota_global = cota_local;
				}
			}
			//if(nivel_anterior != nivel)
			comensales_sentados[siguiente_comensal] = false;
		}
	}

	suma = cota_global;
}*/


void backtracking (int n_comensales, int nivel, int comensal, int &cota_local, int &cota_global, int solucion[], vector<bool> &comensales_sentados, int **matriz) {
	comensales_sentados[comensal] = true;
	solucion[nivel - 1] = comensal;

	for (int siguiente_comensal = 0; siguiente_comensal < n_comensales; siguiente_comensal++) {
		if (comensales_sentados[siguiente_comensal] == false) {			
			cota_local = cota_local + matriz[comensal][siguiente_comensal];
			if (cota_local > cota_global) {				
				backtracking(n_comensales, nivel + 1, siguiente_comensal, cota_local, cota_global, solucion, comensales_sentados, matriz);
			}
			if (nivel == (n_comensales - 1)) {							
				cota_local = cota_local + matriz[siguiente_comensal][0];
				if (cota_local > cota_global) {
					cota_global = cota_local;
				} 
			} 
			else {
				cota_local = cota_local - matriz[comensal][siguiente_comensal];
			}
			comensales_sentados[siguiente_comensal] = false;
		}
	}
}

int main(int argc, char const *argv[]){

	if(argc < 2){
		cerr << "Número de argumentos inválido. Pruebe con ./programa <número_comensales>" << endl;
		exit(1);
	}

	int n = atoi(argv[1]);
	int cota_local = 0, cota_global = 0;
	vector<bool> comensales_sentados(n, false);
	int solucion[n];
	int **matriz = generarEntrada(n);

	//solucion.push_back(0);
	//int cota_global = calcularSolucionParcial(n, solucion, comensales_sentados, matriz, 1);
	//solucion.clear();
	//cout << "Cota global = " << cota_global << endl;

	//backtracking(n, 1, 0, suma, comensales_sentados, matriz, solucion, cota_global);
	backtracking(n, 1, 0, cota_local, cota_global, solucion, comensales_sentados, matriz);

	cout << "Matriz inicial: " << endl;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n ;j++){
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	for(int i = 0; i < n; i++)
		cout << solucion[i] << " " ;

	cout << endl << "Cota local = " << cota_local << endl;
	cout << endl << "Cota global = " << cota_global << endl;

	return 0;
}