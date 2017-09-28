//-----------------------------------------------------------------------------
// media-h.cc
//-----------------------------------------------------------------------------

#include <iostream>  // std::cout std::endl
#include <limits>    // std::numeric_limits
#include <numeric>   // std::accumulate

//-----------------------------------------------------------------------------

const int N = 9;
int v[N] = {0x1, 0x10, 0x100, 0x1000, 0x10000, 0x100000, 0x1000000, 0x10000000, std::numeric_limits<int>::max()};
long long int r1 = 0, r2 = 0;

//-----------------------------------------------------------------------------

long long int suma64s(int v[], int n)
{
	long long int t = 0;

	for (int i = 0; i < n; ++i)
		t += v[i];

	return t;
}

//-----------------------------------------------------------------------------

long long int media(int v[], int n)
{
	return suma64s(v, n) / n;
}

//-----------------------------------------------------------------------------


int main(int argc, char* argv[])
{
	r1 = media(v, N);
	std::cout << "media = " << r1 << std::endl;

	r2 = std::accumulate(&v[0], &v[0] + N, 0ll) / N;
	std::cout << "media = " << r2 << std::endl;

	return r1 + r2;
}

//-----------------------------------------------------------------------------


