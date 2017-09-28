#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#endif
int main(int argc, char **argv) {
	int i, n = 16,chunk, a[n],suma=0;
	int modifier;
	omp_sched_t kind;
	if(argc < 2) {
		fprintf(stderr,"\nFalta chunk \n");
		exit(-1);
	}
	chunk = atoi(argv[1]);
	for (i=0; i<n; i++) a[i] = i;
	#pragma omp parallel 
	{
		
		#pragma omp for firstprivate(suma) \
		lastprivate(suma) schedule(dynamic,chunk)
		for (i=0; i<n; i++)
		{ 
			
		 	suma = suma + a[i];
			printf(" thread %d suma a[%d] suma=%d \n",
			omp_get_thread_num(),i,suma);
		}
		#pragma omp single
		{
			
			printf("omp_get_num_threads: %d \n",omp_get_num_threads());
			printf("omp_get_num_procs: %d \n",omp_get_num_procs());
			printf("omp_in_parallel: %d \n",omp_in_parallel());
			

		}
	}	
	printf("Fuera de 'parallel for' suma=%d\n",suma);
	printf("Fuera de la región paralell: \n");
	printf("omp_get_num_threads: %d \n",omp_get_num_threads());
	printf("omp_get_num_procs: %d \n",omp_get_num_procs());
	printf("omo_in_parallel: %d",omp_in_parallel());
}
