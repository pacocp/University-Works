
//**************************************************************
//Francisco Carrillo Pérez Grupo:B1 Estructura de Computadores *
// size.cc                                                     *
//**************************************************************
#include <array>        // array
#include <chrono>       // clock
#include <iomanip>      // setw
#include <iostream>     // cout

using namespace std::chrono;

const unsigned GAP = 12;
const unsigned REP = 10;
const unsigned STEPS = 16 * 1024 * 1024; // 16M steps

std::array<int, STEPS> bytes; // STEPS x 4 bytes = 16M x 4B = 64MB

int main()
{
	std::cout << "#" 
	          << std::setw(GAP - 1) << "size (B)"
	          << std::setw(GAP    ) << "time (ms)"
	          << std::endl;

	bytes.fill(0);

	for (unsigned size = 1024 / sizeof(int); size <= STEPS; size <<= 1)
	{
		std::array<unsigned, REP> sec;
		unsigned mod = size - 1;

		for (auto &s: sec)
		{
			auto start = high_resolution_clock::now();

			//completar aqui...
			for(unsigned i =0; i < STEPS ; i++)
			{
				bytes[(i << 4)  & mod ] |= 0x1;
			}

			auto stop = high_resolution_clock::now();

			s = duration_cast<milliseconds>(stop - start).count();
		}

		std::cout << std::setw(GAP) << size * sizeof(int)
		          << std::setw(GAP) << std::fixed << std::setprecision(1)
		          << std::setw(GAP) << *std::min(sec.begin(), sec.end())
		          << std::endl;
	}

	return bytes.front() + bytes.back();
}
