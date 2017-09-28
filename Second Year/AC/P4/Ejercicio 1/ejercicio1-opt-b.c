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

	for(i =0; i < 5000 ; i+=4)
	{
		s[i].a = 1;
		s[i].b = 1;
		s[i+1].a = 1;
		s[i+1].b = 1;
		s[i+2].a = 1;
		s[i+2].b = 1;
		s[i+3].a = 1;
		s[i+3].b = 1;
		s[i+4].a = 1;
		s[i+4].b = 1;
	}

	for(ii=0; ii<tama;ii++)
	{
		X1=0;X2=0;
		for(i=0; i <5000;i+=2) 
		{
			//X1
			X1+=(s[i].a << 1) +ii;
			X1+=(s[i+1].a << 1) +ii;
			
			
			//X2
			X2+=(s[i].b << 1) -ii;
			X2+=(s[i+1].b << 1)-ii;
			
		}
		
		R[ii]= (X1 < X2) ? X1 : X2;
	}
	//Medida de tiempo
	t2 = omp_get_wtime();

	total = t2 - t1;


	printf("El valor final de R[%d] es: %d",tama-1,R[tama-1]);
	

	printf("\n\n");
	
	//Imprimir el resultado y el tiempo de ejecución
	printf("Tiempo(seg.):%11.9f\t \n", total);
}
 
