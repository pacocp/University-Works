#!/bin/bash

#Se ejecuta SumaVectorC, que está en el directorio en el que se ha ejecutado qsub,
#para N potencia de 2 desde 2^16 a 2^26
for ((N=65536;N<67108865;N=N*2))
        do
            ./sumavectoresGlobales-Mod  $N 
	done
