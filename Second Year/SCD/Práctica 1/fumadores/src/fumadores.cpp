/************************************************************
	Francisco Carrillo Pérez                                *
	Sistemas Concurrentes y distribuidos.                   *
	Práctica 1                                              *
************************************************************/


#include <iostream>
#include <time.h> // incluye ”time(....)”
#include <unistd.h> // incluye ”usleep(...)”
#include <stdlib.h> // incluye ”rand(...)” y ”srand”
#include <pthread.h>
#include <semaphore.h>
using namespace std;
// funcion que simula la accion de fumar
// como un retardo aleatorio de la hebra
sem_t sem_fum1,sem_fum2,sem_fum3,sem_estanquero;
void fumar()
{ 
	const unsigned miliseg = 100U + (rand() % 1900U) ; // calcular un numero aleatorio de milisegundos (entre 1/10 y 2 segundos)
	usleep( 1000U*miliseg ); // retraso bloqueado durante miliseg milisegundos
}
void * fumador(void * indice)
{
	while(true){
	unsigned long num = (unsigned long) indice;
	if(num == 1)
	{
		sem_wait(&sem_fum1);
		cout << "\nFumador 1 ha cogido el ingrediente";
		sem_post(&sem_estanquero);
		fumar();
		cout << "\nFumador 1 ha acabado de fumar";
		
	}
	else
	{
		if(num == 2)
		{
			sem_wait(&sem_fum2);
			cout << "\nFumador 2 ha cogido el ingrediente";
			sem_post(&sem_estanquero);
			fumar();
			cout << "\nFumador 2 ha acabado de fumar";
			
		}
		else
		{
			sem_wait(&sem_fum3);
			cout << "\nFumador 3 ha cogido el ingrediente";
			sem_post(&sem_estanquero);
			fumar();
			cout << "\nFumador 3 ha acabado de fumar";
		}
	}
}
    
}
void * estanquero(void *)
{
	while(true)
	{
		sem_wait(&sem_estanquero);
    	int ingrediente = rand() % 3; //papel--->0; tabaco ---->1 ; cerillas ---->2
   		 if(ingrediente == 0)
   		 {
   		 	    cout << "\nSe ha producido papel";
    	        sem_post(&sem_fum3);
    			
    	 }
   		 else
   		 {
    		if(ingrediente == 1)
    		{
    			cout << "\nSe ha producido tabaco";
    			sem_post(&sem_fum2);
    			
    			
    		}
    		else
    		{
    			cout << "\nSe han producido cerillas";
    			sem_post(&sem_fum1);
    			
    			
    		}
   		 }
	}



}
int main()
{
	srand( time(NULL) ); // inicializa la semilla aleatoria
	sem_init(&sem_fum1,0,0);
	sem_init(&sem_fum2,0,0);
	sem_init(&sem_fum3,0,0);
	sem_init(&sem_estanquero,0,1);

	pthread_t h_fum1, h_estan,h_fum2,h_fum3;

    unsigned long i = 1;
    unsigned long j = 2;
    unsigned long h = 3;

	pthread_create( &h_fum1, NULL, fumador,(void *)i);
	pthread_create( &h_fum2, NULL, fumador,(void *)j);
	pthread_create( &h_fum3,NULL,fumador,(void *)h);
	pthread_create( &h_estan,NULL, estanquero,NULL);

	pthread_join( h_fum1, NULL);
	pthread_join( h_fum2, NULL);
	pthread_join( h_fum3, NULL);
	pthread_join( h_estan, NULL);




}