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
	int X1,X2,X1_1,X2_1,X1_2,X2_2;
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
		X1_1 =0; 
		X1_2 = 0;
		X2_2 =0;
		X2_1 = 0;
		for(i=0; i <5000;i+=2) 
		{
			//X1
			X1+=2*s[i].a+ii;
			X1_2+=2*s[i+1].a+ii;
			
			
			//X2
			X2 +=2*s[i].b-ii;
			X2_2+=2*s[i+1].b-ii;
			
		}
		X1 = X1 + X1_2;
		X2 = X2 + X2_2;
		R[ii]= (X1 < X2) ? X1 : X2;
	}
	//Medida de tiempo
	t2 = omp_get_wtime();
	total = t2 - t1;


	
	printf("El valor de R[%d] es: %d",tama-1,R[tama-1]);
	

	printf("\n\n");
	
	//Imprimir el resultado y el tiempo de ejecución
	printf("Tiempo(seg.):%11.9f\t \n", total);
}
 
