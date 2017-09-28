set encoding utf8
set terminal png size 1024,768
set title 'Suma Vectores PC-Local'
set output 'sumavectoresLocal.png'
set xlabel 'Bytes'
set ylabel 'Execution time'
set logscale y 2
plot 'datos_local.dat' using 1:3 title 'Local' with lines , 'datos_global.dat' using 1:3 title 'Global' with lines, 'datos_dynamic.dat' using 1:3 title 'Dynamic' with lines





