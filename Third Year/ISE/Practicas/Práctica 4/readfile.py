#!/usr/bin/env python
# -*- coding:utf-8 -*-

from sys import argv

parametros = argv
filename = str(argv[1])

with open(filename) as f:
    data = f.read()
