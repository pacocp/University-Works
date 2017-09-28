#!/usr/bin/python

cantidaddeunosyceros = input("Introduceme la cantidad de 1 y 0: \n")
ceros = 0
unos = 0
for digito in cantidaddeunosyceros:
    if digito == "0":
    	ceros = ceros + 1
    else:
    	if digito == "1":
    		unos = unos + 1

print("El número de 0 es: "+str(ceros))

print("El número de 1 es: "+str(unos))