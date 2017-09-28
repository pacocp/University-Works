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
	
	printf("omp_get_dynamic: %d \n",omp_get_dynamic());
	printf("omp_get_max_threads: %d \n",omp_get_max_threads());
	omp_get_schedule(&kind, &modifier);
	printf("omp_get_schedule: kind %d, modifier %d \n",kind,modifier);
	#pragma omp parallel 
	{

		#pragma omp single
		{
			omp_set_dynamic(1);
			omp_set_num_threads(4);
			omp_set_schedule(2, chunk);
			printf("omp_get_dynamic: %d \n",omp_get_dynamic());
			printf("omp_get_max_threads: %d \n",omp_get_max_threads());
			omp_get_schedule(&kind, &modifier);
			printf("omp_get_schedule: kind %d, modifier %d \n",kind,modifier);
			

		}
		#pragma omp for firstprivate(suma) \
		lastprivate(suma) /*schedule(dynamic,chunk)*/
		for (i=0; i<n; i++)
		{ 
			
		 	suma = suma + a[i];
			printf(" thread %d suma a[%d] suma=%d \n",
			omp_get_thread_num(),i,suma);
		}
		
	}	
	printf("Fuera de 'parallel for' suma=%d\n",suma);
}
