#!/usr/bin/python
import time
 
def hanoi(N, inc='1', temp='2', fin='3'):
 
    if N > 0: 
        hanoi(N-1, inc, fin, temp)
        hanoi(N-1, temp, inc, fin) 

    
    

archi=open('salidahanoiPython.dat','w')
for i in range (1,32):
    start = time.time()    
    hanoi(i)
    end = time.time()
    t = end - start
    archi.write(str(i)+" "+str(t)+"\n" )	
archi.close()
