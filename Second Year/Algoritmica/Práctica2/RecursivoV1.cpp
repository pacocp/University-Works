#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std::chrono;
high_resolution_clock::time_point tantes, tdespues;
duration<double> transcurrido;

using namespace std;


class matrix{

	public:
		vector< vector<int> > datos;

		matrix(int filas, int columnas){

			datos.resize(filas);
			for(int i = 0; i < filas; i++)
				datos[i].resize(columnas);

		}

		/*
	     *
	     * @brief Función para sobrecargar el operados == para dos vectores
	     * @param vectores : matriz en que cada fila corresponde a un vector
	     *	 				 ordenado
	     * @return resultAux : vector ordenado a partir
	     */
	    matrix& operator=(const matrix v2){

	    	this->datos.resize(v2.datos.size());
	    	this->datos.at(0).resize(v2.datos.at(0).size());

	        for (int i = 0; i < v2.datos.size(); i++)
	            for (int j = 0; j < v2.datos.at(i).size();j++)
	                this->datos[i][j] = v2.datos[i][j];

	        return *this;
	    }

};

//typedef vector< vector<int> > matrix; // tipo de dato matrix
/*
 * @brief Funcion para imprimir un vector< vector<int> >
 * @param matrix v : matriz de tipo vector< vector<int> >
 */
void print(matrix v)
{
	for(int i = 0; i < v.datos.size(); i++)
	{

		for (int j =0; j < v.datos.at(0).size(); j++)
		{
			cout << v.datos[i][j] << " ";
		}
		cout << endl;
	}

}

/*
 * @brief Función combinar dos vector< vector<int> > en otro ya ordenado
 * por filas
 *
 * @param matrix v1
 * @param matrix v2
 * @return vector<int>
 */
matrix merge(const matrix v1, const matrix v2){

	int f1 = 0,f2 = 0,c1 = 0,c2 = 0, fr=0, cr=0, tama_columnas = 0;

	matrix v_resultado(1, v1.datos.at(0).size() + v2.datos.at(0).size());

	//Meter números ordenados en el vector ordenado
	while(c1 < v1.datos.at(0).size() && c2 < v2.datos.at(0).size()){
		if(v1.datos.at(f1).at(c1) < v2.datos.at(f2).at(c2)){
			v_resultado.datos[fr][cr] = v1.datos.at(f1).at(c1);
			c1++;
		}
		else{
			v_resultado.datos[fr][cr] = v2.datos.at(f2).at(c2);
			c2++;
		}
		cr++;
	}

	//Terminar de introducir elementos
	for(c1; c1 < v1.datos.at(0).size(); c1++, cr++)
		v_resultado.datos[fr][cr] = v1.datos.at(0).at(c1);

	for(c2; c2 < v2.datos.at(0).size(); c2++, cr++)
		v_resultado.datos[fr][cr] = v2.datos.at(0).at(c2);

	return v_resultado;
}


/*
 *
 * @brief Funcion Recursiva que calculara  un vector ordenado
 * @param vectores : matriz en que cada fila corresponde a un vector
 *	 				 ordenado
 * @return resultAux : vector ordenado a partir
 */
matrix mergeKvectors(matrix &vectores){

	//Caso base
    if (vectores.datos.size() <= 1)
        return vectores;

    int middle = 0;

    //Calcular mitad de filas de la matriz
   	if(vectores.datos.size()%2 == 0)
   		middle = vectores.datos.size()/2;
   	else
   		middle = (vectores.datos.size()/2) +1;

   	//Dividir la matriz principal
    matrix up (middle ,vectores.datos.at(0).size());
	matrix down (vectores.datos.size() - middle,vectores.datos.at(0).size());

	//Rellenar submatrices
    for (int i = 0; i < middle; i++)
		for (int j = 0; j < vectores.datos.at(i).size(); j++)
			up.datos[i][j] = vectores.datos[i][j];

    for (int i = middle; i < vectores.datos.size(); i++)
		for (int j = 0; j < vectores.datos.at(i).size(); j++)
			down.datos[i - middle][j] = vectores.datos[i][j];

	//Llamada recursiva para seguir subdividiendo matrices hasta el caso base
    up = mergeKvectors(up);
    down = mergeKvectors(down);

    //Llamada a merge para combinar el resultado
    matrix resultAux(1,1);
    resultAux = merge(up, down);

	return resultAux;
}
/*
 *
 * @brief Funcion Principal:
 *
 */
int main(int argc, char const *argv[]){

	if (argc != 4){
		cerr << "Formato " << argv[0] << "<ruta_del_archivo_de_entrada>  <num_elem>  <num_vect>" << endl;
		return -1;
    }

	int tam_vectores = atoi(argv[2]); //Tamaño vectores
	int num_vectores = atoi(argv[3]); //Número vectores

	int num = 0;
	string ruta=argv[1];
	ifstream archivo(ruta.c_str());
	// cargamos todos los vectores en una matriz de tipo vector<vector>
	matrix vectorAux(num_vectores,tam_vectores);
	matrix vectorT (num_vectores, tam_vectores);
	vector< vector<int> >  vectorRes;

	for(int i = 0; i < num_vectores; i++){
		for (int j = 0 ; j < tam_vectores; j++){
			archivo >> num;
			vectorT.datos[i][j] = num;
		}
	}
	tantes = high_resolution_clock::now();

	vectorAux = mergeKvectors(vectorT);
	tdespues = high_resolution_clock::now();
	transcurrido = duration_cast<duration<double>>(tdespues - tantes);
	cout <<  tam_vectores << " "<< transcurrido.count() << endl;

	return 0;
}
