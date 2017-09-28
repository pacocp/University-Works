set encoding utf8
set terminal png size 1024,768
set title 'Heap Comparado'
set output 'Heap Comparado.png'
set xlabel 'Bytes'
set ylabel 'Execution time'
plot 'salidaheap-jose.dat' using 1:2 title 'Heap PC Jose' with lines, 'salidaheap-borja.dat' using 1:2 title 'Heap PC Borja' with lines 





