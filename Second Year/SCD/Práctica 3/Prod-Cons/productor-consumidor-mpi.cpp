/************************************************************
	Francisco Carrillo Pérez                                *
	Sistemas Concurrentes y distribuidos.                   *
	Práctica 3                                              *
************************************************************/


#include <iostream>
using namespace std;
#include <cmath>
#include "mpi.h"

#define Productor 0
#define Buffer 1
#define Consumidor 2
#define ITERS 20
#define TAM 10
#define Nbuffer 5
void productor()
{ 
	for( unsigned int i = 0 ; i < ITERS; i++)
	{ 
		cout << "Productor produce valor " << i << endl ;
		MPI_Ssend( &i, 1, MPI_INT, Nbuffer, Productor, MPI_COMM_WORLD );
	}
}
void consumidor()
{ 
	int value, peticion=1; 
	float raiz; 
	MPI_Status status;
	for( unsigned int i = 0 ; i < (ITERS+5) ; i++ )
	{ 
		MPI_Ssend( &peticion, 1, MPI_INT, Nbuffer, Consumidor, MPI_COMM_WORLD );
		MPI_Recv ( &value, 1, MPI_INT, Nbuffer, Buffer, MPI_COMM_WORLD, &status);
		cout << "Consumidor recibe valor "<<value<<" de Buffer "<<endl ;
		raiz = sqrt(value);
	}
}
void buffer()
{ 
	int value[TAM], peticion, pos=0,rama;
	MPI_Status status;
	for( unsigned int i = 0 ; i < ITERS*2*5 ; i++ )
	{ 
		if (pos==0) rama=0;
		// el consumidor no puede consumir
		else if (pos==TAM) rama=1; // el productor no puede producir
		else
			// se puede consumir o producir
			{ 
				MPI_Probe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				if ( status.MPI_SOURCE < Nbuffer ) rama = 0 ; 
				else rama = 1 ;
			}
		switch(rama)
		{ 
			case 0 :
			MPI_Recv(&value[pos],1,MPI_INT,MPI_ANY_SOURCE, Productor,MPI_COMM_WORLD,&status);
			cout<< "Buffer recibe "<< value[pos] << " de Prod." << endl ;
			pos++; break;
			case 1 :
			MPI_Recv( &peticion,1,MPI_INT,MPI_ANY_SOURCE, Consumidor,MPI_COMM_WORLD,&status);
			MPI_Ssend( &value[pos-1],1,MPI_INT,status.MPI_SOURCE,Buffer,MPI_COMM_WORLD);
			cout<< "Buffer envia "<< value[pos-1] << " a Cons." << endl ;
			pos--; break;
		}
	}
}


int main( int argc, char *argv[] )
{ 
	int rank, size ;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank ) ;
	MPI_Comm_size( MPI_COMM_WORLD, &size ) ;
	if ( size != 10 )
	{ 
		if (rank == 0) cout << "El numero de procesos debe ser 10" << endl;
		MPI_Finalize( ); return 0;
	}
	else
	{
		if ( rank <Nbuffer ) productor() ;
		else if ( rank == 5 ) buffer() ;
		else consumidor() ;
		MPI_Finalize( ) ;
		return 0;
	}
	
}
