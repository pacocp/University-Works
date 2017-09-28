#!/usr/bin/env python
# -*- coding:utf-8 -*-

import sys
import subprocess
import threading 
def script(i):
    subprocess.call(['python','writefile.py','/run/media/pacocp/Paco-Pen/file'+str(i)+'.txt',str(i)])
    

threads = list()
for i in range(1000,50000,1000):
    t1 = threading.Thread(target=script, args=(i,))
    threads.append(t1)
    t2 = threading.Thread(target=script, args=(i+1000,))
    threads.append(t2)
    t3 = threading.Thread(target=script, args=(i+3000,))
    threads.append(t3)
    if((i+1000)>50000):
        t1.start()
    else:
        if((i+3000)>50000):
            t1.start()
        else:
            t1.start()
            t2.start()
            t3.start()
            
sys.exit(0)