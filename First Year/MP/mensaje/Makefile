AR= ar
CXX = g++
CXXFLAGS= -Wall -g -I$(INC)
INC= include
BIN= bin
OBJ= obj
SRC= src
LIB= lib


#all: $(BIN)/ocultar $(BIN)/revelar

#documentacion:
	#doxygen doc/doxys/Doxyfile

$(BIN)/revelar : $(OBJ)/revelar.o $(OBJ)/imagenES.o $(OBJ)/codificar.o
	$(CXX) -o $(BIN)/revelar $(OBJ)/revelar.o $(OBJ)/imagenES.o $(OBJ)/codificar.o
	
$(BIN)/ocultar : $(OBJ)/ocultar.o $(OBJ)/imagenES.o $(OBJ)/codificar.o
	$(CXX) -o $(BIN)/ocultar $(OBJ)/ocultar.o $(OBJ)/imagenES.o $(OBJ)/codificar.o

$(OBJ)/revelar.o : $(SRC)/revelar.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/revelar.cpp -o $(OBJ)/revelar.o

$(OBJ)/ocultar.o : $(SRC)/ocultar.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/ocultar.cpp -o $(OBJ)/ocultar.o

$(OBJ)/imagenES.o : $(SRC)/imagenES.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/imagenES.cpp -o $(OBJ)/imagenES.o

$(OBJ)/codificar.o : $(SRC)/codificar.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/codificar.cpp -o $(OBJ)/codificar.o

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(BIN)/* $(LIB)/* $(SRC)/*~ $(INC)/*~ ./*~
