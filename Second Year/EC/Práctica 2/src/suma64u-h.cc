//-----------------------------------------------------------------------------
// suma64u-h.cc
//-----------------------------------------------------------------------------

#include <iostream>  // std::cout std::endl
#include <limits>    // std::numeric_limits
#include <numeric>   // std::accumulate

//-----------------------------------------------------------------------------

const int N = 9;
unsigned int v[N] = {0x1, 0x10, 0x100, 0x1000, 0x10000, 0x100000, 0x1000000, 0x10000000, std::numeric_limits<unsigned int>::max()};
unsigned long long int resultado = 0; //Con el long long nos aseguramos de que tenga 64 bits

//-----------------------------------------------------------------------------

unsigned long long int suma64u1(unsigned int v[], int n)
{
	unsigned long long int t = 0;

	while (n--)
		t += *v++;

	return t;
}

//-----------------------------------------------------------------------------

unsigned long long int suma64u2(unsigned int v[], int n)
{
	unsigned long long int t = 0;

	for (int i = 0; i < n; ++i)
		t += v[i];

	return t;
}

//-----------------------------------------------------------------------------

unsigned long long int suma64u3(unsigned int* primero, unsigned int* ultimo)
{
	unsigned long long int t = 0;

	while (primero != ultimo)
		t += *primero++;

	return t;
}
 
//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	resultado = suma64u1(v, N);
	std::cout << "suma64u1   = " << resultado << std::endl;

	resultado = suma64u2(v, N);
	std::cout << "suma64u2   = " << resultado << std::endl;

	resultado = suma64u3(v, v + N);
	std::cout << "suma64u3   = " << resultado << std::endl;

	resultado = std::accumulate(&v[0], &v[0] + N, 0u);
	std::cout << "accumulate = " << resultado << std::endl;

	return 0;
}

//-----------------------------------------------------------------------------

