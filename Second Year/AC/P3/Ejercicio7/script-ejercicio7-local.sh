#!/bin/bash

echo "----Static"

echo "defecto"
export OMP_SCHEDULE="static" 
./pmtv-OPENMP 15360 4

echo "chunk 1"
export OMP_SCHEDULE="static,1" 
./pmtv-OPENMP 15360 4

echo "chunk 64"
export OMP_SCHEDULE="static,64" 
./pmtv-OPENMP 15360 4

echo "----Dynamic"

echo "defecto"
export OMP_SCHEDULE="dynamic" 
./pmtv-OPENMP 15360 4

echo "chunk 1"
export OMP_SCHEDULE="dynamic,1" 
./pmtv-OPENMP 15360 4

echo "chunk 64"
export OMP_SCHEDULE="dynamic,64" 
./pmtv-OPENMP 15360 4

echo "----Guided"

echo "defecto"
export OMP_SCHEDULE="guided" 
./pmtv-OPENMP 15360 4

echo "chunk 1"
export OMP_SCHEDULE="guided,1" 
./pmtv-OPENMP 15360 4

echo "chunk 64"
export OMP_SCHEDULE="guided,64" 
./pmtv-OPENMP 15360 4

