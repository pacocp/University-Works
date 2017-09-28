/************************************************************
  Francisco Carrillo Pérez                                  *
  Estructura de Computadores                                *
  Práctica 3b                                               *
************************************************************/

//------------------------------------------------------------------------------
// popcount.cc
// http://www.dalkescientific.com/writings/diary/archive/2011/11/02/faster_popcount_update.html
//------------------------------------------------------------------------------
#include <x86intrin.h> // __rdtscp
#include <algorithm>  // count generate
#include <chrono>     // now
#include <stdexcept>  // exception runtime_error
#include <iomanip>    // setw
#include <iostream>   // cout endl
#include <iterator>   // ostream_iterator
#include <numeric>    // accumulate iota
#include <random>     // uniform_int_distribution
#include <string>     // string
#include <vector>     // vector

#include "rdtsc.h"    // rdtsc

//------------------------------------------------------------------------------

const unsigned GAP = 12;        // gap between columns
const unsigned SIZE = 1 << 20;  // list size
const unsigned REP = 32;        // how many times we repeat the experiment
const uint64_t m1  = 0x5555555555555555; //binary: 0101...
const uint64_t m2  = 0x3333333333333333; //binary: 00110011..
const uint64_t m4  = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
const uint64_t m8  = 0x00ff00ff00ff00ff; //binary:  8 zeros,  8 ones ...
const uint64_t m16 = 0x0000ffff0000ffff; //binary: 16 zeros, 16 ones ...
const uint64_t m32 = 0x00000000ffffffff; //binary: 32 zeros, 32 ones
const uint64_t h01 = 0x0101010101010101; //the sum of 256 to the power of 0,1,2,3...

unsigned list[SIZE];

//------------------------------------------------------------------------------

unsigned popcount01(unsigned elem)
{
	unsigned count = 0;
        for(unsigned i = 0; i<sizeof(unsigned)*8;i++){
         unsigned mask = 1 << i;
	 count += (elem & mask) != 0;
}
	return count;
}

//------------------------------------------------------------------------------

unsigned popcount02(unsigned elem)
{
	unsigned count = 0;
        do{
		count += elem & 0x1;
 		elem >>= 1;
		
         }while(elem);
	return count;
}

//------------------------------------------------------------------------------

unsigned popcount03(unsigned elem)
{
	unsigned count = 0;
	for(unsigned i = 0; i<sizeof(elem)*8;i++){
		asm("shr $1,%[e] \n"
		    "adc $0,%[c] \n"
			:[c] "+r" (count) //cuando una cosa es de entrada y salida solo se pone en la salida
			:[e] "r" (elem));
	}
	return count;
}

//------------------------------------------------------------------------------

unsigned popcount04(unsigned elem)
{
	unsigned count = 0;
	do{
		asm("shr $1,%1 \n" // %1 es elem, porque es el segundo que aparece
		    "adc $0,%0 \n" //%0 es el count, porque es el primero que aparece
			:"+r" (count),"+r" (elem)); //cuando una cosa es de entrada y salida solo se pone en la salida
			
	}while(elem);
	return count;
}

//------------------------------------------------------------------------------

unsigned popcount05(unsigned elem) // from o'hallaron
{
	unsigned count = 0;
	int i;
	for (i = 0; i < 8; i++) {
	count += elem &  0x0101010101010101;
	elem >>= 1;
	}
	
	count += (count >> 16);
	count += (count >> 8);

	return count & 0xFF ;
}

//------------------------------------------------------------------------------

unsigned popcount06(unsigned elem) // gustavo
{
	unsigned count = 0;
	for(unsigned i = 0; i<sizeof(elem)*8;i++)
	{
		asm("popcnt %0, %1   \n"
			: "+r"   (elem),"=r" (count)
			);

	}
	
	return count;
}

//------------------------------------------------------------------------------

unsigned popcount07(unsigned x) // from wikipedia
{
	 x = (x & m1 ) + ((x >>  1) & m1 ); //put count of each  2 bits into those  2 bits 
    x = (x & m2 ) + ((x >>  2) & m2 ); //put count of each  4 bits into those  4 bits 
    x = (x & m4 ) + ((x >>  4) & m4 ); //put count of each  8 bits into those  8 bits 
    x = (x & m8 ) + ((x >>  8) & m8 ); //put count of each 16 bits into those 16 bits 
    x = (x & m16) + ((x >> 16) & m16); //put count of each 32 bits into those 32 bits 
    x = (x & m32) + ((x >> 32) & m32); //put count of each 64 bits into those 64 bits 
    
	return x;
}

//------------------------------------------------------------------------------

unsigned popcount08(unsigned elem) // by Wegner
{
	unsigned count = 0;
    for (count=0; elem; count++)
        elem &= elem-1;
	return count;
}

//------------------------------------------------------------------------------

unsigned popcount09(unsigned elem) // wikipedia_v2
{
	elem -= (elem >> 1) & m1;             //put count of each 2 bits into those 2 bits
    elem = (elem & m2) + ((elem >> 2) & m2); //put count of each 4 bits into those 4 bits 
    elem = (elem + (elem >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
    elem += elem >>  8;  //put count of each 16 bits into their lowest 8 bits
    elem += elem >> 16;  //put count of each 32 bits into their lowest 8 bits
    elem += elem >> 32;  //put count of each 64 bits into their lowest 8 bits
    
    return elem & 0x7f;
}

//------------------------------------------------------------------------------

unsigned popcount10(unsigned elem)
{
	//versión de página web ---> http://markplusplus.wordpress.com/2005/10/17/pop/
	unsigned count = elem - ((elem >> 1) & 033333333333)
                  - ((elem >> 2) & 011111111111);
   return ((count + (count >> 3)) & 030707070707) % 63;
}

//------------------------------------------------------------------------------

/*unsigned popcount11(unsigned elem)
{
	unsigned count = 0;


	return count;
}
*/
//------------------------------------------------------------------------------

unsigned popcount11(unsigned elem) //wikipedia_v3
{
	elem -= (elem >> 1) & m1;             //put count of each 2 bits into those 2 bits
    elem = (elem & m2) + ((elem >> 2) & m2); //put count of each 4 bits into those 4 bits 
    elem = (elem + (elem >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
    return (elem * h01)>>56;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ... 
	
}

//------------------------------------------------------------------------------

unsigned popcount12(unsigned elem)
{
	return __builtin_popcount(elem);
}

//------------------------------------------------------------------------------

template <class _F> void test (_F & __f, const char *msg)
{
	using namespace std::chrono;
//	using namespace std::chrono_literals; // c++14
//	auto min = 24h;                       // c++14

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
		result = 0;
		auto t1 = high_resolution_clock::now();
		std::for_each(list, list + SIZE, [&](unsigned x){ result += __f(x); });
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
	try
	{
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_int_distribution<unsigned> distribution;
		auto generator = std::bind(distribution, engine);
		std::generate(list, list + SIZE, generator);

		std::cout <<     "                      "
		          << std::setw(GAP) << "popcnt"
		          << std::setw(GAP) << "cycles"
		          << std::setw(GAP) << "time(ns)"
		          << std::setw(GAP) << "total(us)"
		          << std::endl;

		test(popcount01, "popcount01(for_______)");
		test(popcount02, "popcount02(while_____)");
		test(popcount03, "popcount03(inline____)");
		test(popcount04, "popcount04(inline_v2_)");
		test(popcount05, "popcount05(0'hallaron)");
		test(popcount06, "popcount06(gus_______)");
		test(popcount07, "popcount07(wikipedia_)");
		test(popcount08, "popcount08(Wegner____)");
		test(popcount09, "popcount09(lt8_______)");
		test(popcount10, "popcount10(lt8_v2____)");
		test(popcount11, "popcount11(lt8_v3____)");
		//test(popcount12, "popcount12(lt16______)");
		test(popcount12, "popcount12(builtin___)");
	}
	catch(std::exception& e)
	{
		std::cerr << argv[0] << ": " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}

//------------------------------------------------------------------------------
