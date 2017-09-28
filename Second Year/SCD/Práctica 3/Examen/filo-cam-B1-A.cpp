#include "mpi.h"
#include <iostream>
#include <time.h>
#include <cmath>
#include <stdlib.h>
#include <unistd.h> 
#define SENTARSE 0	// Etiqueta de los mensajes para sentarse a la mesa
#define LEVANTARSE 1	// Etiqueta de los mensajes para levantarse de la mesa
#define Id_Camarero 10	// Identificador del proceso camarero


using namespace std;

void Filosofo(int id, int nprocesos){
	int izq=(id+1)%nprocesos;int der=(id-1+nprocesos)%nprocesos,rellenar;
	MPI_Status status;
	while(1){
		cout<<"Filosofo "<<id<< " PENSANDO"<<endl<<flush;
		sleep((rand()%4)+1 );//pensando

		cout<<"Filosofo "<<id<< " pide permiso para sentarse" <<endl<<flush;
		MPI_Ssend( &rellenar, 1, MPI_INT, Id_Camarero, SENTARSE, MPI_COMM_WORLD );

		//Solicita tenedor izquierdo
		cout<<"Filosofo "<<id<< " solicita tenedor izq ..."<<izq <<endl<<flush;
		MPI_Ssend( &rellenar, 1, MPI_INT, izq, izq, MPI_COMM_WORLD );

		//Solicita tenedor derecho
		cout<<"Filosofo "<<id<< " solicita tenedor der ..."<<der <<endl<<flush;
		MPI_Ssend( &rellenar, 1, MPI_INT, der, der, MPI_COMM_WORLD );

		cout<<"Filosofo "<<id<< " COMIENDO"<<endl<<flush;
		sleep((rand() % 2)+1); //comiendo

		//suelta el tenedor izquierdo
		cout<<"Filosofo "<<id<< " suelta tenedor izq ..."<<izq <<endl<<flush;
		MPI_Ssend( &rellenar, 1, MPI_INT, izq,izq, MPI_COMM_WORLD );

		//suelta el tenedor derecho
		cout<<"Filosofo "<<id<< " suelta tenedor der ..."<<der <<endl<<flush;
		MPI_Ssend( &rellenar, 1, MPI_INT, der, der, MPI_COMM_WORLD );

		cout<<"Filosofo "<<id<< " pide permiso para levantarse" <<endl<<flush;
		MPI_Ssend( &rellenar, 1, MPI_INT, Id_Camarero, LEVANTARSE, MPI_COMM_WORLD );

	
	}
}
void Tenedor(int id, int nprocesos){
	int buf; MPI_Status status; int Filo;
	while(1){
		// Espera un peticion desde cualquier filosofo vecino ...

		// Recibe la peticion del filosofo ...
		MPI_Recv(&buf,1, MPI_INT, MPI_ANY_SOURCE, id, MPI_COMM_WORLD,&status );
		Filo=status.MPI_SOURCE;
		
		cout<<"Ten. "<<id<<" recibe petic. de "<<Filo<<endl<<flush;
		
		// Espera a que el filosofo suelte el
		MPI_Recv(&buf,1, MPI_INT, Filo, id, MPI_COMM_WORLD,&status );
		cout<<"Ten. "<<id<<" recibe liberac. de "<<Filo<<endl<<flush;
		
		
	}
}

void Camarero(){
	int sentados=0;
	MPI_Status status;
	int peticion,filo;
	while(1){

		if(sentados==4)
		    MPI_Probe(MPI_ANY_SOURCE,LEVANTARSE, MPI_COMM_WORLD,&status);
		else
		    MPI_Probe(MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD,&status);

		if (status.MPI_TAG==SENTARSE)
                   {
		    MPI_Recv(&peticion,1, MPI_INT, status.MPI_SOURCE, SENTARSE, MPI_COMM_WORLD,&status );
		    sentados++;
		    filo=status.MPI_SOURCE;
		    cout<<"El camarero sienta al filosofo "<<filo<<". En la mesa hay sentados "<<sentados<< " filosofos"<< endl;
  		   }
		else
  		   {		
		    MPI_Recv(&peticion,1, MPI_INT, status.MPI_SOURCE/*status.MPI_TAG*/, LEVANTARSE, MPI_COMM_WORLD,&status );
 		    sentados--;
		    filo=status.MPI_SOURCE;
		    cout<<"El camarero levanta al filosofo "<<filo<<". En la mesa hay sentados "<<sentados<< " filosofos"<< endl;
 	 	   }
	        }
}

int main(int argc,char** argv ){
	int rank,size;
	srand(time(0));
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	if( size!=11){
	if (rank == 0) 
		cout<<"El numero de procesos debe ser 11"<<endl<<flush;
	MPI_Finalize( ); 
	return 0;
	}
	if(rank==10)
		Camarero();
	else if ((rank%2) == 0) 
		Filosofo(rank,size-1); // Los pares son Filosofos
	else Tenedor(rank,size-1);// Los impares son Tenedores
	MPI_Finalize();
	return 0;
}
