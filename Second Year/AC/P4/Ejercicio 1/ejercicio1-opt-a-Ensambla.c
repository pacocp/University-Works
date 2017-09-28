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

}