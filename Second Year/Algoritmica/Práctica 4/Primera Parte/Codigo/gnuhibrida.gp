f(x) = a0*8**x
fit f(x) "salida.dat" via a0 
set encoding utf8
set terminal png size 1024,768
set title 'Backtracking -Ef.Hibrida'
set output 'divideyvenseras-hibrida.png'
set xlabel 'Tamaño'
set ylabel 'Tiempo'
plot 'salida.dat', f(x) title 'X^8'
