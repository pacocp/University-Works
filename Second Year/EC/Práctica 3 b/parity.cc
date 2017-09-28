/************************************************************
  Francisco Carrillo Pérez                                  *
  Estructura de Computadores                                *
  Práctica 3b                                               *
************************************************************/

//------------------------------------------------------------------------------
// parity.cc
//------------------------------------------------------------------------------

#include <x86intrin.h> // __rdtscp

#include <algorithm>   // count generate
#include <chrono>      // now
#include <cstdint>     // uint32_t uint64_t
#include <functional>  // bind
#include <iomanip>     // setw
#include <iostream>    // cout endl
#include <iterator>    // ostream_iterator
#include <numeric>     // accumulate iota
#include <random>      // uniform_int_distribution
#include <stdexcept>   // exception runtime_error
#include <string>      // string

//------------------------------------------------------------------------------

const unsigned GAP = 12;	// gap between columns
const unsigned SIZE = 1 << 20;  // list size
const unsigned REP = 32;	// how many times we repeat every algorithm

unsigned list[SIZE];

//------------------------------------------------------------------------------

unsigned parity01(unsigned elem) // return true if parity of elem is even
{
	unsigned even = 1;
	for (unsigned i = 0; i < 8 * sizeof(decltype(elem)); ++i)
	{
		unsigned mask = 0x1 << i;
		even ^= (elem & mask) != 0;
	}
	return even;
}

//------------------------------------------------------------------------------

unsigned parity02(unsigned elem)
{
	unsigned even = 1;
	do {
		even ^= elem & 0x1;
	} while (elem >>= 1);
	return even;
}

//------------------------------------------------------------------------------

unsigned parity03(unsigned elem)
{
	unsigned even = 1;
	do
	{
		even -= elem;
		elem >>= 1;
	}while(elem);
	return even & 0x1;
}

//------------------------------------------------------------------------------

unsigned parity04(unsigned elem)
{
	unsigned even = 1;
	
		asm(".bucle:       \n"
		    "xor  %0,%1  \n"
			"shr %0 	\n" //si no se pone cuanto se sobreentiende de que solo es una unidad
			"jne .bucle       \n"
			: "+r" (elem) , "+r" (even)::"cc");
	return even & 0x1;
}

//------------------------------------------------------------------------------

unsigned parity05(unsigned elem)
{
	unsigned even = 1;
	int j;
	for(j = 16; j>=1;j/=2)
	{
		
		elem^=(elem>>j);
		
	}
	even ^= elem & 0x1;
	
	return even;
}

//------------------------------------------------------------------------------

unsigned parity06(unsigned elem)
{
	unsigned even = 1;
	int j = 16;
	do
	{
		elem^=(elem>>j);
		j = j/2;
	}while(j>=1);
	
	even ^= elem & 0x1;

	
	return even;
}

//------------------------------------------------------------------------------

unsigned parity07(unsigned elem)
{
	unsigned even = 1;
	asm(" mov %0, %%edx   \n"
		" shr $0x10, %%edx  \n"
		" xor %%edx, %0   \n"
		" mov %0, %%edx  \n"	
		" shr $0x8, %%edx    \n"
		" xor %0, %%edx   \n"
		" setpe %%dl    \n"
		" movzbl %%dl, %1    \n"

		: "+r" (elem) , "+r" (even)
		:
		: "edx"
		);
	return even;
}

//------------------------------------------------------------------------------

/*unsigned parity08(unsigned elem)
{
	unsigned even = 1;

	return even;
}

//------------------------------------------------------------------------------

unsigned parity09(unsigned elem)
{
	unsigned even = 1;
	return even;
}

//------------------------------------------------------------------------------

unsigned parity10(unsigned x)
{
	unsigned even = 1;
	return even;
}
*/
//------------------------------------------------------------------------------

unsigned parity08(unsigned elem)
{
	return (__builtin_popcount(elem) & 1) == 0;
}

//------------------------------------------------------------------------------

template <class _F> void test(_F & __f, const char *msg)
{
	using namespace std::chrono;
	
	uint64_t cycles = std::numeric_limits<uint64_t>::max(), overhead = cycles;
	unsigned p;
	for (unsigned i = 0; i < REP; ++i)
	{
		uint64_t t1 = __rdtscp(&p);
		uint64_t t2 = __rdtscp(&p);
		if (t1 < t2 && t2 - t1 < overhead)
			overhead = t2 - t1;
	}

	for (unsigned i = 0; i < REP; ++i)
	{
		uint64_t t1 = __rdtscp(&p);
		__f(list[SIZE - 1]);
		uint64_t t2 = __rdtscp(&p);
		if (t1 < t2 && t2 - t1 < cycles)
			cycles = t2 - t1;
	}
	cycles -= overhead;

	unsigned result;
	auto min = duration<high_resolution_clock::rep, std::nano>::max(), o2 = min;

	for (unsigned i = 0; i < REP; ++i)
	{
		auto t1 = high_resolution_clock::now();
		auto t2 = high_resolution_clock::now();
		if (t1 < t2 && t2 - t1 < o2)
			o2 = t2 - t1;
	}

	for (unsigned i = 0; i < REP; ++i)
	{
		auto t1 = high_resolution_clock::now();
		result = std::count_if(list, list + SIZE, __f);
		auto t2 = high_resolution_clock::now();
		if (t2 - t1 < min)
			min = t2 - t1;
	}

	std::cout << msg
		  << std::setw(GAP) << result
		  << std::setw(GAP) << cycles
		  << std::setw(GAP) << std::fixed << std::setprecision(2)
		  << duration_cast<nanoseconds>(min - o2).count() / static_cast<float>(SIZE)
		  << std::setw(GAP) << duration_cast<microseconds>(min).count()
		  << std::endl;
}

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_int_distribution<unsigned> distribution;
	auto generator = std::bind(distribution, engine);
	std::generate(list, list + SIZE, generator);

	std::cout <<   "		  "
		  << std::setw(GAP) << "even"
		  << std::setw(GAP) << "cycles"
		  << std::setw(GAP) << "time(ns)"
		  << std::setw(GAP) << "total(us)"
		  << std::endl;

	test(parity01, "parity01(for_____)");
	test(parity02, "parity02(while___)");
	test(parity03, "parity03(while_v2)");
	test(parity04, "parity04(asm_____)");
	test(parity05, "parity05(tree____)");
	test(parity06, "parity06(tree_v2_)");
	test(parity07, "parity07(asm_v2__)");
	//test(parity08, "parity08(lt8_____)");
	//test(parity09, "parity09(lt16____)");
	//test(parity10, "parity10(HD______)");
	test(parity08, "parity08(builtin_)");
}

//------------------------------------------------------------------------------
