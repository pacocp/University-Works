// Compilar con -O2 y -fopenmp
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

main()
{
	const float a = 1000000000;
	int tama = 4000000;
	int *X,*Y;
	Y = (int*) malloc(tama*sizeof(int));
    X = (int*) malloc(tama*sizeof(int));
	int i;
	double t1, t2, total;

	for(i=0; i< tama; i++)
	{
		X[i] = 2;
		Y[i] = 2;
	}
	t1 = omp_get_wtime();

	for(int i=0; i < tama; i++)
	{
		Y[i] = a*X[i]+Y[i];
	}

	//Medida de tiempo
	t2 = omp_get_wtime();

	total = t2 - t1;
	//Imprimir el resultado y el tiempo de ejecución
	printf("Tiempo(seg.):%11.9f\t \n", total);
	free(X);
	free(Y);

}