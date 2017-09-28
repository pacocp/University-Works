f(x) = a0*x*log(x) 
fit f(x) "salidainsercion.dat" via a0 
set encoding utf8
terminal png size 1024,768
set title 'AlgoritmoInsercion-Ef.Hibrida'
set output 'algoritmoInsercion-hibrida.png'
set xlabel 'Bytes'
set ylabel 'Execution time'
plot 'salidainsercion.dat', f(x) title 'AlgoritmoInsercion - Hibrida'
