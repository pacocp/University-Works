// Compilar con -O2 y -fopenmp
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

struct 
{
	int a;
	int b;
} s[5000];

main()
{
	int ii,i;
	int X1,X2;
	int tama = 1000000;
	int R[tama];
	double t1, t2, total;
	

	//Medida de tiempo
	t1 = omp_get_wtime();

	for(i =0; i < 5000 ; i++)
	{
		s[i].a = 1;
		s[i].b = 1;
	}

	for(ii=0; ii<tama;ii++)
	{
		X1=0;X2=0;
		for(i=0; i <5000;i++) X1+=2*s[i].a+ii;
		for(i=0; i <5000;i++) X2+=2*s[i].b-ii;
		if(X1 < X2) R[ii]=X1; else R[ii]=X2;
	}

	//Medida de tiempo
	t2 = omp_get_wtime();
	total = t2 - t1;

	printf("El valor de R[%u] es: %u ",tama-1,R[tama-1]);
	
	
	printf("\n\n");

	//Imprimir el resultado y el tiempo de ejecución
	printf("Tiempo(seg.):%11.9f\t \n", total);
}
 
