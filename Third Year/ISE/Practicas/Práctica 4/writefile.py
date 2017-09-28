#!/usr/bin/env python
# -*- coding:utf-8 -*-

from sys import argv
import subprocess

parametros = argv
filename = str(argv[1])
f = open(filename,'w')
for i in range(0,1000000,1):

        f.write(str(i))
