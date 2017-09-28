// Compilar con -O2 y -fopenmp
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){
	int i, j,k;
	double t1, t2, total;

	//Leer argumento de entrada (no de componentes del vector)
	if (argc<2){
		printf("Falta tamaño de matriz y vector\n");
		exit(-1);
	}

	unsigned int N = atoi(argv[1]); // Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)

	double **M1, **M2, **M3;
	M1 = (double**) malloc(N*sizeof(double *));
	M2 = (double**) malloc(N*sizeof(double *));
	M3 = (double**) malloc(N*sizeof(double *));
	

	for (i=0; i<N; i++){
		M1[i] = (double*) malloc(N*sizeof(double));
		M2[i] = (double*) malloc(N*sizeof(double));
		M3[i] = (double*) malloc(N*sizeof(double));
		if ( M1[i]==NULL ){
			printf("Error en la reserva de espacio para los vectores\n");
			exit(-2);
		}
	}
	//A partir de aqui se pueden acceder las componentes de la matriz como M[i][j]

	//Inicializar matriz y vectores

	for(i = 0; i< N; i++)
	{
		for(j = 0; j < N; j++ )
		{
			M1[i][j] = 2;
			M2[i][j] = 2;
			M3[i][j] = 0;
		}
	}


	//Medida de tiempo
	t1 = omp_get_wtime();

	//Calcular producto de matriz por vector v2 = M · v1
	
	for (i=0; i<N; i++){
        for (j=0; j<N; j++) {
            for (k=0; k<N; k++) {
                M3[i][j] += M1[i][k] * M2[k][j];
            }
        }
	}


	//Medida de tiempo
	t2 = omp_get_wtime();
	total = t2 - t1;

	//Imprimir el resultado y el tiempo de ejecución
	printf("Tiempo(seg.):%11.9f\t / Tamaño:%u\t/ V2[0]=%8.6f V2[%d]=%8.6f\n", total,N,M3[0][0],N-1,M3[N-1][N-1]);

	
	for (i=0; i<N; i++){
		free(M1[i]);
		free(M2[i]);
		free(M3[i]);
	}
	free(M1);
	free(M2);
	free(M3);

	return 0;
}

