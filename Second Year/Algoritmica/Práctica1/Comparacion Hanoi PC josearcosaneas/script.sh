#!/bin/csh -vx


g++ -o ./otros/hanoi ./otros/hanoi.cpp -std=gnu++0x



printf "" > ./salidas-otros/salidahanoi.dat


@ i = 1
while ( $i < 32 )
  ./otros/hanoi $i >> ./salidas-otros/salidahanoi.dat
  @ i += 1
end




