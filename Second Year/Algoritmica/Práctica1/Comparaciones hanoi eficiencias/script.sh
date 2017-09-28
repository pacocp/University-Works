#!/bin/csh -vx


g++ -o  hanoio1 hanoi.cpp -O1 -std=gnu++0x
g++ -o  hanoio2 hanoi.cpp -O2 -std=gnu++0x
g++ -o  hanoio3 hanoi.cpp -O3 -std=gnu++0x
g++ -o  hanoios hanoi.cpp -Os -std=gnu++0x



printf "" > ./salidas/hanoio1.dat
printf "" > ./salidas/hanoio2.dat
printf "" > ./salidas/hanoio3.dat
printf "" > ./salidas/hanoios.dat


@ i = 1
while ( $i < 32 )
  ./hanoio1 $i >> ./salidas/hanoio1.dat
  @ i += 1
end

@ i = 1
while ( $i < 32 )
  ./hanoio2 $i >> ./salidas/hanoio2.dat
  @ i += 1
end

@ i = 1
while ( $i < 32 )
  ./hanoio3 $i >> ./salidas/hanoio3.dat
  @ i += 1
end

@ i = 1
while ( $i < 32 )
  ./hanoios $i >> ./salidas/hanoios.dat
  @ i += 1
end
