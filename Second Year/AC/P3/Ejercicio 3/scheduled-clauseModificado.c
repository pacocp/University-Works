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
			
			printf("dyn-var: %d \n",omp_get_dynamic());
			printf("nthreads_var: %d \n",omp_get_max_threads());
			printf("thread_limit_var: %d \n",omp_get_thread_limit());
			printf("thread_limit_var: %d \n",omp_get_thread_limit());
			omp_get_schedule(&kind, &modifier);
			printf("get_schedulre: kind %d,modifier %d \n",kind,modifier);

		}
	}	
	printf("Fuera de 'parallel for' suma=%d\n",suma);
	printf("Fuera de la región paralell: \n");
	printf("dyn-var: %d \n",omp_get_dynamic());
	printf("nthreads_var: %d \n",omp_get_max_threads());
	printf("thread_limit_var: %d \n",omp_get_thread_limit());
	printf("thread_limit_var: %d \n",omp_get_thread_limit());
	omp_get_schedule(&kind, &modifier);
	printf("get_schedulre: kind %d,modifier %d \n",kind,modifier);
}
