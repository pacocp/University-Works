#!/bin/bash

#Se asigna al trabajo la cola ac
#PBS -q ac

for ((N=100;N<1000;N=N+100))
        do
        	echo "S"
            $PBS_O_WORKDIR/pmm-secuencial $N 
            echo "--------------------------- \n"
            echo "P"
            $PBS_O_WORKDIR/pmm-OpenMP $N
	done
