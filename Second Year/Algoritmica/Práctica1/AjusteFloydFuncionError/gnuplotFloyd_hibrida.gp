f(x) = a0*x**3 
fit f(x) "salidafloyd.dat" via a0 
set encoding utf8
set terminal png size 1024,768
set title 'AlgoritmoFloyd-Ef.Hibrida'
set output 'algoritmoFloyd-hibrida.png'
set xlabel 'Bytes'
set ylabel 'Execution time'
plot 'salidafloyd.dat', f(x) title 'AlgoritmoFloyd - Hibrida'
