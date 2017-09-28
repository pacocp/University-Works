#include<stdio.h>
#include<pthread.h>

const unsigned long m = 100; //Número de muestras
const unsigned long n = 10; //Número de hebras
double resultado_parcial[10]; //Vector de resultados parciales

//Implementa función f
double f(double x){	
	return (4.0/(1+x*x));
}

void* funcionHebra(void* ih_void){ //Función que ejecuta cada hebra
	
	unsigned long ih = (unsigned long) ih_void; //Indice de la hebra
	double sumap = 0.0;
	unsigned long i = ih*n;

	//Calcular suma parcial
	for(i; i < n*ih+(m/n); i++)
		sumap += f((i+0.5)/m);

	//Guardar suma parcial en vector
	resultado_parcial[ih] = sumap;
}

double calcularIntegralConcurrente(){

	double suma = 0.0;
	unsigned long i = 0;
	
	//Crear y lanzar n hebras, cada una ejecuta "funcionHebra"
	pthread_t vt[n];

	for(i; i < n; i++)
		pthread_create(&vt[i],NULL,funcionHebra,(void*)i);

	i = 0;
	//Esperar (join) a que termine cada hebra
	for(i; i < n; i++)
		pthread_join(vt[i],NULL);

	//Sumar todas las sumas parciales en una variable
	i = 0;
	for(i; i < n; i++){
		suma += resultado_parcial[i];
		printf("%f\n",suma);
	}

	//Devolver resultado completo
	return suma/m;
}

int main(){
	
	double d = calcularIntegralConcurrente();

	printf("Resultado: %f\n", d);
}
