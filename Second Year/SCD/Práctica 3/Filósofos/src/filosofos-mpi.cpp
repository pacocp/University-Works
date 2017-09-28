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

void Filosofo( int id, int nprocesos )
{
	int buf; MPI_Status status;
	int izq = (id+1) % nprocesos ,
		der = (id+nprocesos-1) % nprocesos ;
	while ( true )
		{ 	
			if(id!=0) //hacemos que el primero empiece por el otro tenedor
			{
				// solicita tenedor izquierdo
				cout << "Filosofo " << id << " solicita tenedor izq. " << izq << endl;
				MPI_Ssend(&buf,1,MPI_INT,izq, vFilosofo, MPI_COMM_WORLD);
				// solicita tenedor derecho
				cout << "Filosofo " << id << " coge tenedor der. " << der << endl;
				MPI_Ssend(&buf,1,MPI_INT,der, vFilosofo, MPI_COMM_WORLD);
			}
			else
			{
				// solicita tenedor derecho
				cout << "Filosofo " << id << " coge tenedor der. " << der << endl;
				MPI_Ssend(&buf,1,MPI_INT,der, vFilosofo, MPI_COMM_WORLD);

				// solicita tenedor izquierdo
				cout << "Filosofo " << id << " solicita tenedor izq. " << izq << endl;
				MPI_Ssend(&buf,1,MPI_INT,izq, vFilosofo, MPI_COMM_WORLD);
			}
			// ...
			cout << "Filosofo " << id << " COMIENDO" << endl ;
			sleep( (rand()%3)+1 ); // comiendo
			if(id!=0) //también los suelta en orden contrario
			{
				// suelta el tenedor izquierdo
				cout << "Filosofo "<<id<< " suelta tenedor izq. " << izq << endl;
				MPI_Recv(&buf,1,MPI_INT,izq,vTenedor,MPI_COMM_WORLD,&status);
				// suelta el tenedor derecho
				cout << "Filosofo " << id << " suelta tenedor der. " << der << endl;
				MPI_Recv(&buf,1,MPI_INT,der,vTenedor,MPI_COMM_WORLD,&status);
			}
			else
			{
				// suelta el tenedor derecho
				cout << "Filosofo " << id << " suelta tenedor der. " << der << endl;
				MPI_Recv(&buf,1,MPI_INT,der,vTenedor,MPI_COMM_WORLD,&status);
				// suelta el tenedor izquierdo
				cout << "Filosofo "<<id<< " suelta tenedor izq. " << izq << endl;
				MPI_Recv(&buf,1,MPI_INT,izq,vTenedor,MPI_COMM_WORLD,&status);
			}
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
 

int main( int argc, char** argv )
{ 
		int rank,size;
		srand( time(0) );
		MPI_Init( &argc, &argv );
		MPI_Comm_rank( MPI_COMM_WORLD, &rank );
		MPI_Comm_size( MPI_COMM_WORLD, &size );
		if ( size != 10 )
			{ 
				if (rank == 0) cout << "El numero de procesos debe ser 10" << endl;
				MPI_Finalize( ); return 0;
			}
		if ( rank%2 == 0) Filosofo(rank,size); // los pares son filosofos
		else Tenedor(rank,size);
 			// los impares son tenedores
		MPI_Finalize();
		return 0;

}
