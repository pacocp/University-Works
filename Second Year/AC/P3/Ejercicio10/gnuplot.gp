set encoding utf8
set terminal png
set title 'Ejercicio 10'
set output 'ejercicio10.png'
set xlabel 'size'
set ylabel 'execution time (s)'
plot 'datos.dat' using 1:2 title 'Secuencial' with lines , 'datos.dat' using 1:3 title 'Paralelo' with lines




