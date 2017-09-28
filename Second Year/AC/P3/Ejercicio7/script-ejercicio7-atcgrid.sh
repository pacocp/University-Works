#!/bin/bash
#PBS -q ac


echo "----Static"

echo "defecto"
export OMP_SCHEDULE="static" 
. $PBS_O_WORKDIR/pmtv-OPENMP 15360 12

echo "chunk 1"
export OMP_SCHEDULE="static,1" 
. $PBS_O_WORKDIR/pmtv-OPENMP 15360 12

echo "chunk 64"
export OMP_SCHEDULE="static,64" 
 $PBS_O_WORKDIR/pmtv-OPENMP 15360 12

echo "----Dynamic"

echo "defecto"
export OMP_SCHEDULE="dynamic" 
 $PBS_O_WORKDIR/pmtv-OPENMP 15360 12

echo "chunk 1"
export OMP_SCHEDULE="dynamic,1" 
 $PBS_O_WORKDIR/pmtv-OPENMP 15360 12

echo "chunk 64"
export OMP_SCHEDULE="dynamic,64" 
 $PBS_O_WORKDIR/pmtv-OPENMP 15360 12

echo "----Guided"

echo "defecto"
export OMP_SCHEDULE="guided" 
 $PBS_O_WORKDIR/pmtv-OPENMP 15360 12

echo "chunk 1"
export OMP_SCHEDULE="guided,1" 
 $PBS_O_WORKDIR/pmtv-OPENMP 15360 12

echo "chunk 64"
export OMP_SCHEDULE="guided,64" 
 $PBS_O_WORKDIR/pmtv-OPENMP 15360 12

