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
int calcularCompatibilidad(int n, int p[], int **matriz){

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
int calcularSolucionParcial(int n, int solucion_parcial[], vector<bool> comensales_sentados, int **matriz, int nivel){
	
	int max = 0;
	int comensal = 0, pos = 0, num_elementos = 0, elemento_ultimo;
	comensales_sentados[0] = true;

	for(int i = 0; i < n; i++)
		if(solucion_parcial[i] != -1)
			num_elementos++;

	//elemento_ultimo = num_elementos;

	while(num_elementos < n ){
		for (int i = 0; i < n; ++i){
			if(comensales_sentados[i] == false){
				if(matriz[solucion_parcial[num_elementos]][i] > max){
					max = matriz[solucion_parcial[num_elementos]][i];
					pos = i;

				}
			}
		}
		solucion_parcial[num_elementos] = pos;
		comensales_sentados[pos] = true;
		max = 0;
		num_elementos++;
	}

	if(nivel == 1)
		return calcularCompatibilidad(n, solucion_parcial, matriz);
	else
		return (calcularCompatibilidad(n, solucion_parcial, matriz)+matriz[0][n-1]); //Cota optimista

}

void backtracking(int n, int nivel, int comensal, int &suma, vector<bool> &comensales_sentados, int **matriz, int solucion[], int &cota_global){

	comensales_sentados[comensal] = true;

	solucion[nivel - 1] = comensal;
	
	int cota_local = calcularSolucionParcial(n, solucion, comensales_sentados, matriz, nivel+1);

	for(int siguiente_comensal = 0; siguiente_comensal < n; siguiente_comensal++){
		if(comensales_sentados[siguiente_comensal] == false){
			//suma = calcularCompatibilidad(solucion.size(), solucion, matriz);
			suma = suma + matriz[comensal][siguiente_comensal];
			if(cota_local > cota_global) //Si vamos por buen camino, descendemos
				backtracking(n, nivel + 1, siguiente_comensal, suma, comensales_sentados, matriz, solucion, cota_global);
			if(nivel == (n - 1) ){ //Si estamos en el nodo hoja, calculamos la nueva cota
				//suma = calcularCompatibilidad(solucion.size(), solucion, matriz);
				suma = suma + matriz[siguiente_comensal][0];
				cota_local = calcularSolucionParcial(n, solucion, comensales_sentados, matriz, nivel+1);
				if(cota_local > cota_global){
					cota_global = cota_local;
				}
			}
			else{
				suma = suma - matriz[comensal][siguiente_comensal];
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
	int suma = 0;
	cout << "c" ;
	vector<bool> comensales_sentados(n, false);
	cout << "c" ;
	int solucion[n];
	cout << "c" ;
	//int **matriz = generarEntrada(n);
	cout << "c" ;
	for(int i = 0; i < n; i++)
		solucion[i] = -1;
	cout << "a" ;
	solucion[0] = 0;
	cout << "a" ;
	int cota_global = calcularSolucionParcial(n, solucion, comensales_sentados, matriz, 1);
	solucion[0] = -1;
	cout << "b" ;
	cout << "Cota global = " << cota_global << endl;

	//backtracking(n, 1, 0, suma, comensales_sentados, matriz, solucion, cota_global);

	cout << "Matriz inicial: " << endl;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n ;j++){
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}

	//cout << "Solución: " << solucion.size() << endl;

	for(int i = 0; i < n; i++)
		cout << solucion[i] << " " ;

	cout << endl << "Suma = " << suma << endl;

	return 0;
}