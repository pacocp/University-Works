/* 
	Programa que resuelve el problema de los filósofos con camarero
	Alumno: José Manuel Rejón Santiago 
	Curso: 2º 
	Grupo: B3 
*/ 

#include "mpi.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

#define SOLICITAR 'S'
#define LIBERAR 'L'
#define SENTARSE 'T'
#define LEVANTARSE 'V'
int filosofos_comiendo = 0;


//Método para los filósofos
void Filosofo(int id, int n_procesos){
	int izq = (id+1) % n_procesos;
	int der = (id+n_procesos-1) % n_procesos;
	int value = 1;
	MPI_Status status;

	while(true){

		//Pedir permiso para sentarse
		cout << "Filosofo " << id <<  " pide sentarse en la mesa " << endl;
		MPI_Ssend(&value, 1, MPI_INT, 10, SENTARSE, MPI_COMM_WORLD);
		cout << "Filosofo " << id <<  " se sienta en la mesa " << endl;

		//Solicita tenedor izquierdo
		cout << "Filosofo " << id <<  " solicita tenedor izquierdo " << izq << endl;
		MPI_Ssend(&value, 1, MPI_INT, izq, SOLICITAR, MPI_COMM_WORLD);
		//Solicita tenedor derecho
		cout << "Filosofo " << id <<  " solicita tenedor derecho " << der << endl;
		MPI_Ssend(&value, 1, MPI_INT, der, SOLICITAR, MPI_COMM_WORLD);

		cout << "Filosofo " << id << " COMIENDO" << endl;
		sleep((rand()%3)+1); //Tiempo que está comiendo el filósofo
		//Suelta el tenedor izquierdo
		cout << "Filosofo " << id <<  " suelta tenedor izquierdo " << izq << endl;
		MPI_Ssend(&value, 1, MPI_INT, izq, LIBERAR, MPI_COMM_WORLD);
		//Suelta el tenedor derecho
		cout << "Filosofo " << id <<  " suelta tenedor derecho " << der << endl;
		MPI_Ssend(&value, 1, MPI_INT, der, LIBERAR, MPI_COMM_WORLD);
		//Levantarse
		cout << "Filosofo " << id <<  " se levanta de la mesa " << endl;
		MPI_Ssend(&value, 1, MPI_INT, 10, LEVANTARSE, MPI_COMM_WORLD);

		cout << "Filosofo " << id << " PENSANDO" << endl;
		sleep((rand()%3)+1); //Tiempo que está pensando el filósofo

	}
}

//Método para los tenedores
void Tenedor(int id, int n_procesos){
	int buf, Filo;
	MPI_Status status;

	while(true){
		//Espera una petición desde cualquier filósofo vecino
		MPI_Recv(&buf, 1, MPI_INT, MPI_ANY_SOURCE, SOLICITAR, MPI_COMM_WORLD, &status);
		//Recibe la petición del filósofo
		Filo = status.MPI_SOURCE;
		cout << "Tenedor " << id << " recibe petición de " << Filo << endl;
		//Espera a que el filósofo suelte el tenedor
		MPI_Recv(&buf, 1, MPI_INT, MPI_ANY_SOURCE, LIBERAR, MPI_COMM_WORLD, &status);
		cout << "Tenedor " << id << " recibe liberación de " << Filo << endl;
	}
}

//Método para el camarero
void Camarero(){
	int buf;
	MPI_Status status;

	while(true){
		if(filosofos_comiendo < 4){
			MPI_Recv(&buf, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			if(status.MPI_TAG == SENTARSE)
				filosofos_comiendo++;
			else
				filosofos_comiendo--;
		}
		else{
			MPI_Recv(&buf, 1, MPI_INT, MPI_ANY_SOURCE, LEVANTARSE, MPI_COMM_WORLD, &status);
			filosofos_comiendo--;
		}
	}
}

int main(int argc, char** argv){

	int rank, size;
	srand(time(0));
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(size != 11){
		if(rank == 0)
			cout << "El número de procesos debe ser 11" << endl;
		MPI_Finalize();
		return 0;
	}
	if(rank == 10)
		Camarero();
	else if(rank%2 == 0)
		Filosofo(rank, size-1); //Los pares son filosofos
	else
		Tenedor(rank, size-1); //Los impares son tenedores

	MPI_Finalize();
	return 0;
}