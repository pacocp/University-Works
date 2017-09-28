#include <iostream>
using namespace std;
#include <cmath>
#include "mpi.h"
#include <stdlib.h>
#include <unistd.h> 
#include <time.h>
#define ITERS 20
#define Productor 1
#define Consumidor 0
#define Buffer 2
//#define TAM 10
#define Nbuffer 6
void productor()
{ 
	for( unsigned int i = 0 ; i < ITERS; i++)
	{ 
		cout << "Productor produce valor " << rand()%10 << endl ;
		MPI_Ssend( &i, 1, MPI_INT, Nbuffer, Productor, MPI_COMM_WORLD );
	}
}
void consumidor()
{ 
	int value, peticion=1; 
	float raiz; 
	MPI_Status status;
	while(true){
		MPI_Ssend( &peticion, 1, MPI_INT, Nbuffer, Consumidor, MPI_COMM_WORLD );
		MPI_Recv ( &value, 1, MPI_INT, Nbuffer, Buffer, MPI_COMM_WORLD, &status);
		cout << "Consumidor recibe valor "<<value<<" de Buffer "<<endl ;
		raiz = sqrt(value);
	}
	
}
void buffer()
{ 
	int num,peticion, pos=0,rama;
	MPI_Status status;
	for( unsigned int i = 0 ; i < ITERS*4 ; i++ )
	{ 
		
		MPI_Probe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		//if ( status.MPI_SOURCE <=5 && status.MPI_SOURCE >=2 ) rama = 0 ; 
		//else rama = 1 ;
			
		//switch(rama)
		//{ 
			//case 0 :
		if(status.MPI_TAG == Productor)
		{
			MPI_Recv(&num,1,MPI_INT,MPI_ANY_SOURCE, Productor,MPI_COMM_WORLD,&status);
			cout<< "Buffer recibe "<< num << " de Prod." << endl ;
		}
			
			//break;
		else
		{
			if(num == 3 || num == 7)
			{
				MPI_Recv( &peticion,1,MPI_INT,0, Consumidor,MPI_COMM_WORLD,&status);
				MPI_Ssend( &num,1,MPI_INT,status.MPI_SOURCE,Buffer,MPI_COMM_WORLD);
				cout<< "Buffer envia "<< num << " a Cons.1" << endl ;
			}
			else
			{
				if(num == 2 || num == 5)
				{
					MPI_Recv( &peticion,1,MPI_INT,1, Consumidor,MPI_COMM_WORLD,&status);
					MPI_Ssend( &num,1,MPI_INT,status.MPI_SOURCE,Buffer,MPI_COMM_WORLD);
					cout<< "Buffer envia "<< num << " a Cons.2" << endl ;
				}
				else
				{
					if(num <10 && num >= 0)
					{
						MPI_Recv( &peticion,1,MPI_INT,MPI_ANY_SOURCE, Consumidor,MPI_COMM_WORLD,&status);
						MPI_Ssend( &num,1,MPI_INT,status.MPI_SOURCE,Buffer,MPI_COMM_WORLD);
						cout<< "Buffer envia "<< num << " a Cons" << status.MPI_SOURCE<< endl ;
					}
					
				}
			}
		}
			//case 1 :
			
			//break;
			
			
			
			//}
	}
}


int main( int argc, char *argv[] )
{ 
	int rank, size ;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank ) ;
	MPI_Comm_size( MPI_COMM_WORLD, &size ) ;
	if ( size != 7 )
	{ 
		if (rank == 0) cout << "El numero de procesos debe ser 7" << endl;
		MPI_Finalize( ); return 0;
	}
	else
	{
		if ( rank == 0 || rank == 1  ) consumidor() ;
		else if ( rank== 2 || rank==3 || rank == 4 || rank == 5 ) productor() ;
		else buffer() ;
		MPI_Finalize( ) ;
		return 0;
	}
	
}
