set encoding utf8
set terminal png size 1024,768
set title 'Heapsort'
set output './Gráficas/heapsort.png'
set xlabel 'Bytes'
set ylabel 'Execution time'
plot './salidas-nlogn/salidaheap.dat' using 1:2 title 'heapsort' with lines 





