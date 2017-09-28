#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

const int tam_vec = 10; 
int buffer[tam_vec];	//variable compartida por el productor y consumidor
int primera_libre=0;	//Utilizamos LIFO por lo tanto llevamos la posición primera que está libre
unsigned long  num_elem_vec;
const int num_items=50;	
sem_t sem_prod, sem_cons, sem_mutex,sem_imp; 

int producir_dato(){	
	static int contador = 1 ;
	return contador ++ ;
}

void consumir_dato( int dato ){
	cout << "\ndato recibido: " << dato << endl;
}


void * productor( void * ){ 
	for( unsigned i = 0 ; i < num_items ; i++ ){ 
		int dato = producir_dato() ;

		sem_wait( &sem_prod);	//semaforo para el productor
		buffer[primera_libre]=dato;	//Inserción del dato en el buffer

		sem_wait(&sem_mutex); //sección crítica
		primera_libre++;		//aumento en el índice del buffer
		if(dato % 5 == 0)
		{

			sem_post(&sem_imp);

			sem_wait(&sem_prod);
		}
		sem_post(&sem_mutex); //sección crítica
		cout << "\nDato producido: " << dato << endl;
		sem_post( &sem_cons);	//señal para el consumidor
	}
	
}


void * consumidor( void * ){
	for( unsigned i = 0 ; i < num_items ; i++ ){ 
		int dato ;

		sem_wait( &sem_cons);	//semaforo para el consumidor
		dato=buffer[primera_libre-1];	//"quitamos" el dato del buffer"

		sem_wait( &sem_mutex); //sección crítica
		primera_libre--;		//Decrementamos el índice del buffer
		sem_post( &sem_mutex); //sección crítica

		consumir_dato( dato ) ;
		sem_post( &sem_prod);	//señal para el productor
	}
	
}

void * impresora(void * ){
	while(true){
         sem_wait( &sem_imp); // semaforo para la impresora

         

         cout << "IMPRESORA: " << " " << primera_libre << endl;

         sem_post(&sem_prod);


	}
}

int main(){
	pthread_t h_prod, h_cons,h_imp;
	
	//inicializamos el semaforo al tamaño del vector para que pueda insertar tantos datos como pueda en el buffer
	sem_init( &sem_prod, 0, tam_vec); 
	sem_init( &sem_cons, 0, 0);
	sem_init( &sem_mutex, 0, 1);
	sem_init( &sem_imp, 0, 0);

	pthread_create( &h_prod, NULL, productor, NULL);
	pthread_create( &h_cons, NULL, consumidor, NULL);
	pthread_create( &h_imp, NULL, impresora, NULL);

	pthread_join( h_prod, NULL);
	pthread_join( h_cons, NULL);
	
	cout << endl << "FIN DEL PROGRAMA" << endl;
	sem_destroy( &sem_cons);
	sem_destroy( &sem_prod);
	
}
