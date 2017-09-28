#!/bin/bash

for ((N=100;N<1000;N=N+100))
        do
        	echo "S"
            ./pmm-secuencial $N 
            echo "--------------------------- \n"
            echo "P"
            ./pmm-OpenMP $N
	done

