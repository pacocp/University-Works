#!/bin/bash

echo "9a"

for ((N=1000;N<100000;N=N+1000))
        do
            time ./Ejercicio9/pmv-openMP-a $N > ejercicio11-9a.txt
	done
echo "9b"
for ((N=1000;N<100000;N=N+1000))
        do
            time ./Ejercicio9/pmv-openMP-b $N > ejercicio11-9b.txt
	done
echo "10"

for ((N=1000;N<100000;N= N + 1000))
        do
            time ./Ejercicio10/pmv-openMP-reduction $N > ejercicio11-10.txt
	done