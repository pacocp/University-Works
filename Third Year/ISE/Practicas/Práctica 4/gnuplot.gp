set encoding utf8
set terminal gif
set title 'BubbleSort'
set output 'bubblesortbenchmark.gif'
set xlabel 'size of data'
set ylabel 'execution time'
plot 'python-bubble.dat' using 1:2 title 'Python' with lines , 'php-bubble.dat' using 1:2 title 'Php' with lines, 'perl-bubble.dat' using 1:2 title 'Perl' with lines

set title 'Write Test '
set output 'writefile.gif'
set xlabel 'names'
set ylabel 'execution time(s)'
set boxwidth 0.5
set style fill solid
plot 'write.dat' using 1:3:xtic(2) title 'Values' with boxes

set title 'Read Test'
set output 'readfile.gif'
set xlabel 'names'
set ylabel 'execution time(s)'
set boxwidth 0.5
set style fill solid
plot 'read.dat' using 1:3:xtic(2) title '' with boxes




