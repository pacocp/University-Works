#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include <time.h>
#include <limits>
#include <queue>

using namespace std;

double cota_global = numeric_limits<double>::max();
int nodos_explorados = 0, nodos_expandidos = 0;

struct Ciudad{
	int indice;
	double x;
	double y;
} ciudad;

struct Nodo{
	Ciudad c;
	vector<bool> visitadas;
	vector<Ciudad> solucion_parcial;
	double cota_local;
	int nivel;

	Nodo(){}

	Nodo(Ciudad _c, vector<bool> _visitadas, vector<Ciudad> _solucion_parcial, double _cota, int _nivel){
		c = _c;
		visitadas = _visitadas;
		solucion_parcial = _solucion_parcial;
		cota_local = _cota;
		nivel = _nivel;
	}

	bool operator > (const Nodo &n1)const{
        return (*this).cota_local > n1.cota_local;
    }
    bool operator >= (const Nodo &n1)const{
        return (*this).cota_local >= n1.cota_local;
    }
    bool operator < (const Nodo &n1)const{
        return (*this).cota_local < n1.cota_local;
    }
    bool operator <= (const Nodo &n1)const{
        return (*this).cota_local <= n1.cota_local;
    }
    bool operator == (const Nodo &n1)const{
        return (*this).cota_local == n1.cota_local;
    }
    bool operator != (const Nodo &n1)const{
        return (*this).cota_local != n1.cota_local;
    }
    void operator = (const Nodo &n){
    	(*this).c = n.c;
    	(*this).visitadas = n.visitadas;
		(*this).solucion_parcial = n.solucion_parcial;
		(*this).cota_local = n.cota_local;
		(*this).nivel = n.nivel;
    }

};

//Esta clase está diseñada para que el priority queue ordene según la cota local de cada nodo
class compararNodo{

public:
	bool operator()(Nodo n1, Nodo n2){
		return n1.cota_local > n2.cota_local;
	}
};

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

//Calcula un vector con la distancia mínima desde las ciudades
vector<double> costeMinimo(const vector<vector<double> > &matriz_costes){

	double distancia_minima = numeric_limits<double>::max();
	vector<double> vector_distancias_minimas;

	for(int i = 0; i < matriz_costes.size(); i++){
		for(int j = 0; j < matriz_costes.size(); j++){
			if((matriz_costes[i][j] < distancia_minima) && (i != j))
				distancia_minima = matriz_costes[i][j];
		}
		vector_distancias_minimas.push_back(distancia_minima);
		distancia_minima = numeric_limits<double>::max();
	}

	return vector_distancias_minimas;
}

//Calcular y devolver la cota local
double getCotaLocal(const vector<Ciudad> &solucion_parcial, const vector<double> &vector_distancias_minimas, 
	const vector<vector<double> > &matriz_costes, const vector<bool> visitadas){

	double cota = 0.0;
	bool cerrar_ciclo = true;

	//Añadimos a la cota local la distancia que llevamos hasta el momento
	for(int i = 1; i < solucion_parcial.size(); i++)
		cota += matriz_costes[solucion_parcial[i-1].indice - 1][solucion_parcial[i].indice - 1];

	//Añadimos a la cota local una estimación optimista para terminar de completar el circuito
	for(int i = 0; i < visitadas.size(); i++){
		if(!visitadas[i]){
			cota += vector_distancias_minimas[i];
			cerrar_ciclo = false;
		}
	}

	//Si ya hemos incluido todas las ciudades, cerramos el ciclo del circuito
	if(cerrar_ciclo)
		cota += matriz_costes[solucion_parcial[0].indice - 1][solucion_parcial[solucion_parcial.size()-1].indice - 1];
	
	return cota;
}

vector<Nodo> generarNodosVivos(int nivel, vector<bool> visitadas, vector<Ciudad> solucion_parcial, 
	const vector<Ciudad> &ciudades, const vector<vector<double> > &matriz_costes, const vector<double> &vector_distancias_minimas){

	vector<Nodo> nodos_vivos;

	for(int i = 0; i < visitadas.size(); i++){
		//Comprobamos que el nodo vivo que generamos no esté ya generado
		if(visitadas[i] == false){
			nodos_expandidos++;
			//Incluimos en la información de dicho nodo, la solución parcial que tenía el padre más el propio nodo
			//formando parte de esta solución
			solucion_parcial.push_back(ciudades[i]);
			//También indicamos en la información del nodo, que esta ciudad ya ha sido visitada
			visitadas[i] = true;
			//Calculamos la cota local relacionada con este nodo
			double cota_local = getCotaLocal(solucion_parcial, vector_distancias_minimas, matriz_costes, visitadas);
			Nodo nodo(ciudades[i], visitadas, solucion_parcial, cota_local, nivel + 1);
			//Deshacemos todos los cambios para poder seguir generando hijos del mismo padre y que la información no esté alterada
			solucion_parcial.pop_back();
			visitadas[i] = false;
			nodos_vivos.push_back(nodo);
		}
	}

	return nodos_vivos;
}

//Algoritmo Branch & Bound
vector<Ciudad> BB_TSP(const vector<vector<double> > &matriz_costes, const vector<Ciudad> &ciudades, const vector<double> &vector_distancias_minimas){

	priority_queue<Nodo, vector<Nodo>, compararNodo> cola;
	vector<bool> visitadas(ciudades.size(), false);
	vector<Ciudad> solucion_parcial, solucion_final;
	vector<Nodo> nodos_vivos;
	solucion_parcial.push_back(ciudades[0]);
	int nivel = 0;

	double cota_local = getCotaLocal(solucion_parcial, vector_distancias_minimas, matriz_costes, visitadas);
	visitadas[0] = true;

	//Generamos el nodo inicial (ciudad 0) y lo introducimos en la priority queue
	Nodo nodo_inicial(ciudades[0], visitadas, solucion_parcial, cota_local, nivel);

	cola.push(nodo_inicial);

	//Mientras que haya nodos vivos
	while(!cola.empty()){
		//Obtenemos el primer nodo de la cola con prioridad
		Nodo nodo_actual = cola.top();
		cola.pop();
		//Si es un nodo hoja y su cota local es menor que la global
		if((nodo_actual.nivel == (ciudades.size()-1)) && (nodo_actual.cota_local < cota_global)){
			nodos_explorados++;
			//Actualizamos la cota global así como la solución final
			cota_global = nodo_actual.cota_local;
			solucion_final = nodo_actual.solucion_parcial;
		}
		//Comprobamos si el nodo más prometedor que tenemos, es capaz de alcanzar una solución mejor que la que 
		//tenemos hasta el momento
		if(nodo_actual.cota_local < cota_global){
			nodos_explorados++;
			//Generamos los hijos de este nodo vivo
			nodos_vivos = generarNodosVivos(nodo_actual.nivel, nodo_actual.visitadas, nodo_actual.solucion_parcial, ciudades, matriz_costes, vector_distancias_minimas);
			for(int i = 0; i < nodos_vivos.size(); i++)
				cola.push(nodos_vivos[i]);
		}
		//En el caso de que no haya en la lista de nodos vivos ningún nodo prometedor, devolvemos la solución que habíamos calculado
		//hasta el momento, ya que es la mejor que vamos a encontrar
		else{
			return solucion_final;
		}
	}

	return solucion_final;
}

//Cálculo factorial de un número n
unsigned int factorial(unsigned int n){

    if (n == 0)
       return 1;

    return n * factorial(n - 1);
}

// Funcion principal
int main(int argc, char* argv[]){

	if(argc != 2){
		cerr << "USO: ./" << argv[0] << " fichero_entrada" << endl;
		exit(1);
	}
	clock_t t_ini, t_fin;
	double secs;
	vector<Ciudad> ciudades, solucion_final;
	vector<double> vector_distancias_minimas;

	leerCiudades(ciudades, argv[1]);
	vector<vector<double> > matriz = generaMatriz(ciudades);
	vector_distancias_minimas = costeMinimo(matriz);
	t_ini = clock();
	solucion_final = BB_TSP(matriz, ciudades, vector_distancias_minimas);

	t_fin = clock();
	secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	double distancia = 0.0;
	
	for(int i = 1; i < solucion_final.size(); i++){
		distancia += matriz[solucion_final[i-1].indice - 1][solucion_final[i].indice - 1];

	}
	
	distancia += matriz[solucion_final[0].indice - 1][solucion_final[solucion_final.size() - 1].indice - 1];

	cout << "DISTANCIA: " << distancia << endl;

	int nodos_totales = factorial(solucion_final.size());
	cout << "NODOS TOTALES " << nodos_totales << endl;
	cout << "NODOS PODADOS " << nodos_totales - nodos_explorados << endl;
	cout << "NODOS EXPLORADOS " << nodos_explorados << endl;
	cout << "NODOS EXPANDIDOS " << nodos_expandidos << endl;
	cout << "TIEMPO (seg)" << secs << endl;
	return 0;
}
