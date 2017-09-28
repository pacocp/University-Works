# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGETS= practica1

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuraci�n
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I.
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I.

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut

# definicion del compilador
#
CC = g++

# orden que sera ejecutada por defecto
#
#default : $(TARGETS)

# regla de ejecucion
#
practica2: practica2.o objetos.o file_ply_stl.o
	$(CC)  $(CXXFLAGS) -o practica2 practica2.o objetos.o file_ply_stl.o  $(LDFLAGS)

objetos.o :  objetos.cc
	$(CC) -o $@ -c $(CXXFLAGS) objetos.cc  $(LDFLAGS)

practica2.o :  practica2.cc
	$(CC) -o $@ -c $(CXXFLAGS) practica2.cc  $(LDFLAGS)

file_ply_stl.o :  file_ply_stl.cc
		$(CC) -o $@ -c $(CXXFLAGS) file_ply_stl.cc  $(LDFLAGS)

#
#
clean:
	rm -f *.o
	rm -f $(TARGETS)

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *
