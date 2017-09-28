set encoding utf8
set terminal png size 1024,768
set title 'Comparación'
set output './backtrackempirica.png'
set xlabel 'Tamaño de la matriz'
set ylabel 'Tiempo de ejecución (s)'

plot 'salida.dat' using 1:2 title 'Backtracking' with lines
