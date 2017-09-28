BIN = bin
SRC = src
INC = include
OBJ = obj
AR= ar
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c

all: $(BIN)/negativo $(BIN)/desplazar
# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Compilación de módulos ************
$(BIN)/negativo : $(OBJ)/negativo.o $(OBJ)/imagenES.o $(OBJ)/transformar.o $(OBJ)/imagen.o
	$(CXX) -o $(BIN)/negativo $(OBJ)/negativo.o $(OBJ)/imagenES.o $(OBJ)/imagen.o $(OBJ)/transformar.o

$(BIN)/desplazar : $(OBJ)/desplazar.o $(OBJ)/imagenES.o $(OBJ)/transformar.o $(OBJ)/imagen.o
	$(CXX) -o $(BIN)/desplazar $(OBJ)/desplazar.o $(OBJ)/imagenES.o $(OBJ)/imagen.o $(OBJ)/transformar.o

$(OBJ)/imagenES.o : $(SRC)/imagenES.cpp $(INC)/imagenES.h
	$(CXX) $(CPPFLAGS) $(SRC)/imagenES.cpp -o $(OBJ)/imagenES.o

$(OBJ)/imagen.o : $(SRC)/imagen.cpp $(INC)/imagen.h
	$(CXX) $(CPPFLAGS) $(SRC)/imagen.cpp -o $(OBJ)/imagen.o

$(OBJ)/transformar.o : $(SRC)/transformar.cpp $(INC)/transformar.h $(INC)/imagen.h
	$(CXX) $(CPPFLAGS) $(SRC)/transformar.cpp -o $(OBJ)/transformar.o

$(OBJ)/negativo.o : $(SRC)/negativo.cpp $(INC)/imagen.h  $(INC)/imagenES.h $(INC)/transformar.h
	$(CXX) $(CPPFLAGS) $(SRC)/negativo.cpp -o $(OBJ)/negativo.o

$(OBJ)/desplazar.o : $(SRC)/desplazar.cpp $(INC)/imagen.h  $(INC)/imagenES.h $(INC)/transformar.h
	$(CXX) $(CPPFLAGS) $(SRC)/desplazar.cpp -o $(OBJ)/desplazar.o



# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
