# Fichero Makefile
#
# Banderas para el compilador (C y C++). Se indican los directorios donde se pueden
# encontrar ficheros para incluir mediante la opción -I
# la opción -g sirve para permitir la depuración
# 
CFLAGS= -c -g -I$(INC) -std=c++11

# Definición del compilador
#
CC = g++

# Directorios
#
SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

# Orden que será ejecutada por defecto
#
all: $(BIN)/main

# Ejecutables
# 
$(BIN)/main: $(OBJ)/main.o $(LIB)/libmetah.a
	$(CC) $^ -o $@ -L$(LIB)/ -lmetah

# Bibliotecas
#
$(LIB)/libmetah.a: $(OBJ)/manejodedatos.o $(OBJ)/utilidades.o $(OBJ)/clasificador-kNN.o $(OBJ)/random_ppio.o $(OBJ)/greedy.o $(OBJ)/busquedaLocal.o  $(OBJ)/anneal.o $(OBJ)/busquedaMulti.o
	ar rvs $@ $^

# Objetos
#
$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/manejodedatos.h $(INC)/clasificador-kNN.h $(INC)/greedy.h $(INC)/random_ppio.h $(INC)/utilidades.h $(INC)/busquedaLocal.h  $(INC)/anneal.h $(INC)/busquedaMulti.h
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/manejodedatos.o: $(SRC)/manejodedatos.cpp $(INC)/manejodedatos.h
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/utilidades.o: $(SRC)/utilidades.cpp $(INC)/manejodedatos.h $(INC)/random_ppio.h $(INC)/utilidades.h
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/clasificador-kNN.o: $(SRC)/clasificador-kNN.cpp $(INC)/manejodedatos.h $(INC)/clasificador-kNN.h
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/random_ppio.o: $(SRC)/random_ppio.cpp $(INC)/random_ppio.h
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/greedy.o: $(SRC)/greedy.cpp $(INC)/manejodedatos.h $(INC)/clasificador-kNN.h
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/busquedaLocal.o: $(SRC)/busquedaLocal.cpp $(INC)/manejodedatos.h $(INC)/clasificador-kNN.h $(INC)/random_ppio.h $(INC)/utilidades.h $(INC)/busquedaLocal.h
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/anneal.o: $(SRC)/anneal.cpp $(INC)/manejodedatos.h $(INC)/clasificador-kNN.h $(INC)/random_ppio.h $(INC)/utilidades.h $(INC)/anneal.h
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/busquedaMulti.o: $(SRC)/busquedaMulti.cpp $(INC)/manejodedatos.h $(INC)/clasificador-kNN.h $(INC)/random_ppio.h $(INC)/utilidades.h $(INC)/busquedaLocal.h $(INC)/busquedaMulti.h
	$(CC) $(CFLAGS) $< -o $@


# Clean
#
clean:
	rm $(OBJ)/*.o $(LIB)/lib*.a

# MrProper
#
mrproper: clean
	rm $(BIN)/*
