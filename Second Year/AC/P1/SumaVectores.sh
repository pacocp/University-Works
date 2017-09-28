#!/bin/bash
#Se asigna al trabajo la cola ac
#PBS -q ac
 
#Se ejecuta SumaVectorC, que está en el directorio en el que se ha ejecutado qsub,
#para N potencia de 2 desde 2^16 a 2^26
for ((N=16384;N<67108865;N=N*2))
do
    $PBS_O_WORKDIR/sumavectores-Parallel $N 
done
