/************************************************************
	Francisco Carrillo Pérez                                *
	Sistemas Concurrentes y distribuidos.                   *
	Práctica 3                                              *
************************************************************/



#include "mpi.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h> 
using namespace std;
#define vFilosofo 0
#define vTenedor 1
#define SENTARSE 'T'
#define LEVANTARSE 'L'

int filosofos_comiendo = 0;

void Filosofo( int id, int nprocesos )
{
	int buf; MPI_Status status;
	int izq = (id+1) % nprocesos ,
		der = (id+nprocesos-1) % nprocesos ;
	while ( true )
		{ 	
			cout<< "Filosofo" << id << " solicita sentarse" << endl;
			MPI_Ssend(&buf,1,MPI_INT,10,SENTARSE,MPI_COMM_WORLD);
			cout << "Filosofo " << id << " se ha sentado" << endl;
			cout << "Filosofo " << id << " solicita tenedor izq. " << izq << endl;
			MPI_Ssend(&buf,1,MPI_INT,izq, vFilosofo, MPI_COMM_WORLD);	
			cout << "Filosofo " << id << " solicita tenedor der. " << der << endl;
			MPI_Ssend(&buf,1,MPI_INT,der, vFilosofo, MPI_COMM_WORLD);	
			cout << "Filosofo " << id << " COMIENDO" << endl ;
			sleep( (rand()%3)+1 ); // comiendo
			// suelta el tenedor izquierdo
			cout << "Filosofo "<<id<< " suelta tenedor izq. " << izq << endl;
			MPI_Recv(&buf,1,MPI_INT,izq,vTenedor,MPI_COMM_WORLD,&status);
			// suelta el tenedor derecho
			cout << "Filosofo " << id << " suelta tenedor der. " << der << endl;
			MPI_Recv(&buf,1,MPI_INT,der,vTenedor,MPI_COMM_WORLD,&status);
			cout<< "Filosofo " << id << " solicita levantarse" << endl;	
			MPI_Ssend(&buf,1,MPI_INT,10,LEVANTARSE,MPI_COMM_WORLD);
			cout << "Filosofo " << id << " se ha levantado" << endl;

			cout << "Filosofo " << id << " PENSANDO" << endl;
			sleep( (rand()%3)+1 ); // pensando
		}

 }
void Tenedor( int id, int nprocesos )
{
		int buf, Filo ;
		MPI_Status status;
		while ( true )
		{ 	// Espera un peticion desde cualquier filosofo vecino ...
			do{
					MPI_Probe(MPI_ANY_SOURCE,vFilosofo, MPI_COMM_WORLD,&status);
					Filo=status.MPI_SOURCE;
				}while(!(id+1==Filo || id-1==Filo || id+1-nprocesos==Filo));
			// Recibe la peticion del filosofo ...
			MPI_Recv(&buf,1,MPI_INT,Filo,vFilosofo,MPI_COMM_WORLD,&status);
			cout << "Ten. " << id << " recibe petic. de " << Filo << endl;
			// Espera a que el filosofo suelte el tenedor...
			MPI_Ssend(&buf,1,MPI_INT,Filo, vTenedor, MPI_COMM_WORLD);
			cout << "Ten. " << id << " recibe liberac. de " << Filo << endl ;
		}

}
void Camarero()
{
	int buf,Filo;
	MPI_Status status;
	while(true)
	{
		
		MPI_Probe(MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD,&status);
		Filo=status.MPI_SOURCE;
		if (status.MPI_TAG==SENTARSE && filosofos_comiendo<4){ //Se puede sentar
			// Recibe la peticion de sentarse del filosofo ...
			cout<<"Camarero recibe petic. sentarse de "<<Filo<<endl;
			MPI_Recv(&buf,1,MPI_INT,Filo,SENTARSE,MPI_COMM_WORLD,&status);
			filosofos_comiendo++; 
			//cout << "**************SENTADOS: " << sentados << "******************"<< endl; 
		} else {
			// Espera a que el filosofo termine de comer...
			cout<<"Camarero recibe petic. levantarse de "<<Filo<<endl;
			MPI_Recv(&buf,1,MPI_INT,MPI_ANY_SOURCE,LEVANTARSE,MPI_COMM_WORLD,&status);
			filosofos_comiendo--;
			//cout << "**************SENTADOS: " << sentados << "******************"<< endl; 
		}
	}

}
 int main( int argc, char** argv )

{ 
		int rank,size;
		srand( time(0) );
		MPI_Init( &argc, &argv );
		MPI_Comm_rank( MPI_COMM_WORLD, &rank );
		MPI_Comm_size( MPI_COMM_WORLD, &size );
		if ( size != 11 )
			{ 
				if (rank == 0) cout << "El numero de procesos debe ser 11" << endl;
				MPI_Finalize( ); return 0;
			}
		if(rank == 10)
			Camarero();
		if ( rank%2 == 0) Filosofo(rank,size-1); // los pares son filosofos
		else Tenedor(rank,size-1);
 			// los impares son tenedores
		MPI_Finalize();
		return 0;

}
