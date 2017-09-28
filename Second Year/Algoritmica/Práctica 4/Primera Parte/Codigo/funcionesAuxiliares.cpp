#include<stdlib.h> // rand
#include<time.h> // Time()
#include<iostream>// cin cout

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
	int **matrix;
	matrix = new int*[n-1];
	for (int i =0; i<n;i++)
		matrix[i] = new int[n-1];
	int j = 0;
	int i = 0;
	for (i =1; i <n ; i++){
		for (j = i; j < n; j++){
			int num=1+rand()%(101-1);
			matrix[i][j] = num;
			matrix[j][i] = num;
		}
	}
	for (i =0; i <n ; i++){
		for (j = 0; j < n; j++){
		 	if (i==j) matrix[i][j] = 0;		
		}

	}
	
	return matrix;
}

/********************************************************************
// Este main era para comprobar si la matriz del apartado anterior es 
// simetrica y con la diagonal de 0.
int main(){

	int n = 5;

	int **p;

	p = generarEntrada(n);

	for (int i = 0; i<n; i++){
		for (int j =0; j<n ;j++){
			if(p[i][j] == p[j][i])
				cout << "True";
			else 
				cout<< "False";
			if(i==j && p[i][j]==0)
				cout << "True";
			else 
				cout<< "False";
		}

	}

}
********************************************************************/



/******************************************************
 * @brief Funcion para calcular los valores de una lista
 * @param int valor valor para almacenar el resultado 
 * total de la compatibilidad de la lista de valores 
 * enteros alamacenados en p
 * @param int* p lista de valores de la posible solucion 
 * @param int** matrix matriz simetrica que almacena la 
 * compatiblidad de los asistentes.
 *****************************************************/
void calcularCompatibilidad(int &valor,int n, int p[], int matrix[][]){

	// sumamos la compatibilidad con el contiguo
	// 0 con 1 , 1 con 2, 2 con 3, hasta n-2 con n-1..
	for (int i = 0; i< n-1; i++){
		valor  +=  matrix[p[i]][p[i+1]];
	}
	// sumamos el primero con el último
	// 0 con n-1
	valor += matrix[p[0]][p[n-1]];
}

