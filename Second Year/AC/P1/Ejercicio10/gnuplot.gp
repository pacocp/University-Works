set encoding utf8
set terminal png size 1024,768
set title 'Suma Vectores ATCGRID'
set output 'ejercicio10-ATGRID.png'
set xlabel 'Bytes'
set ylabel 'Execution time'
set logscale y 2
plot 'datos_local.dat' using 1:2 title 'Secuencial' with lines , 'datos_local.dat' using 1:3 title 'Parallel-For' with lines, 'datos_local.dat' using 1:4 title 'Parallel-Sections' with lines





