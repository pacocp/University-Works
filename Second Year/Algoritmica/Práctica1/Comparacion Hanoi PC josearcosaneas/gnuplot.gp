
set encoding utf8
set terminal png size 1024,768
set title 'Hanoi Comparado'
set output 'Hanoi Comparado.png'
set xlabel 'Bytes'
set ylabel 'Execution time'
plot 'salidahanoi_josearcosaneas.dat' using 1:2 title 'Hanoi PC JoseArcosAneas' with lines, 'salidahanoi.dat' using 1:2 title 'Hanoi PC Borja' with lines 

