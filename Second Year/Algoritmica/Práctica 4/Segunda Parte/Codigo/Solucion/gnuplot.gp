set encoding utf8
set terminal png size 1024,768
set title 'Comparacion Backtracking vs Branch and Bound'
set output 'comparacion.png'
set xlabel 'Numero ciudades'
set ylabel 'Tiempo ejecucion'
plot './ResultadosBacktrack/resultadosback.dat' using 1:2 title 'Backtrack' with lines, './ResultadosBB/bboundtiempos.dat' using 1:2 title 'Branch and Bound' with lines 





