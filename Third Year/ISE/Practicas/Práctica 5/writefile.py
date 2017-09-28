#!/usr/bin/env python
# -*- coding:utf-8 -*-

from sys import argv
import subprocess

parametros = argv
filename = str(argv[1])
iterations = str(argv[2])
f = open(filename,'w')
for i in range(0,int(iterations),1):

        f.write(str(i))
