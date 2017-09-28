#include <iostream>
#include <pthread.h>
using namespace std;

const unsigned long m;
const unsigned long n;
double resultado_parcial[n];
double f( double x)
{
	return 4.0/(1+x*x);
}
void * funcion_hebra( void * ih_void)
{
	unsigned long_ih = (unsigned long) ih_void;
	double sumap = 0.0;
    for(unsigned long i= 0; i < m; i++)
    	 sumap += f( (i+0.5)/m);

	resultado_parcial(ih) = sumap;
}

double calcular_integral_concurrente()
{
	for( unsigned i = 0 ; i < n ; i++ ){
		pthread_create( &(id_hebra[i]), NULL, proc, (void *)i );
	}
	

    return sumap/m;
}
int main(int argc,char * argv[])
{
	m = argv[1];
	n = argv[2];
	


}