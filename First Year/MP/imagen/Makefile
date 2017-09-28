BIN = bin
SRC = src
INC = include
OBJ = obj

CXX = g++
CXXFLAGS = -Wall -g  -I$(INC) -c

# ************ Generación de documentación ******************
#documentacion:
#	doxygen doc/doxys/Doxyfile

# ************ Compilación de módulos ************
$(BIN)/all: $(BIN)/ocultar.o $(BIN)/revelar.o $(BIN)/transformar.o $(BIN)/generar.o  $(BIN)/componer.o

$(BIN)/componer.o: $(OBJ)/imagenES.o $(OBJ)/imagen.o $(OBJ)/transformar.o $(OBJ)/componer.o
	$(CXX) -o $(BIN)/componer $(OBJ)/imagenES.o $(OBJ)/imagen.o $(OBJ)/transformacion.o $(OBJ)/componer.o

$(BIN)/transformar.o: $(OBJ)/imagenES.o $(OBJ)/imagen.o $(OBJ)/transformar.o $(OBJ)/transformacion.o
	$(CXX) -o $(BIN)/transformar $(OBJ)/imagenES.o $(OBJ)/imagen.o $(OBJ)/transformacion.o $(OBJ)/transformar.o

$(BIN)/generar.o: $(OBJ)/imagenES.o $(OBJ)/imagen.o $(OBJ)/transformacion.o $(OBJ)/generadores.o $(OBJ)/generar.o
	$(CXX) -o $(BIN)/generar $(OBJ)/imagenES.o $(OBJ)/imagen.o $(OBJ)/transformacion.o $(OBJ)/generadores.o $(OBJ)/generar.o

$(BIN)/ocultar.o : $(OBJ)/imagenES.o $(OBJ)/imagen.o $(OBJ)/procesar.o $(OBJ)/ocultar.o
	$(CXX) -o $(BIN)/ocultar $(OBJ)/imagenES.o $(OBJ)/imagen.o $(OBJ)/procesar.o $(OBJ)/ocultar.o

$(BIN)/revelar.o : $(OBJ)/imagenES.o $(OBJ)/imagen.o $(OBJ)/procesar.o $(OBJ)/revelar.o
	$(CXX) -o $(BIN)/revelar $(OBJ)/imagenES.o $(OBJ)/imagen.o $(OBJ)/procesar.o $(OBJ)/revelar.o

$(OBJ)/imagenES.o : $(SRC)/imagenES.cpp $(INC)/imagenES.h
	$(CXX) $(CXXFLAGS) $(SRC)/imagenES.cpp -o $(OBJ)/imagenES.o

$(OBJ)/imagen.o : $(SRC)/imagen.cpp $(INC)/imagen.h $(INC)/imagenES.h
	$(CXX) $(CXXFLAGS) $(SRC)/imagen.cpp -o $(OBJ)/imagen.o

$(OBJ)/procesar.o : $(SRC)/procesar.cpp $(INC)/procesar.h
	$(CXX) $(CXXFLAGS) $(SRC)/procesar.cpp -o $(OBJ)/procesar.o

$(OBJ)/generadores.o : $(SRC)/generadores.cpp $(INC)/generadores.h
	$(CXX) $(CXXFLAGS) $(SRC)/generadores.cpp -o $(OBJ)/generadores.o

$(OBJ)/generar.o : $(SRC)/generar.cpp $(INC)/generadores.h
	$(CXX) $(CXXFLAGS) $(SRC)/generar.cpp -o $(OBJ)/generar.o

$(OBJ)/ocultar.o : $(SRC)/ocultar.cpp $(INC)/procesar.h
	$(CXX) $(CXXFLAGS) $(SRC)/ocultar.cpp -o $(OBJ)/ocultar.o

$(OBJ)/revelar.o : $(SRC)/revelar.cpp $(INC)/procesar.h
	$(CXX) $(CXXFLAGS) $(SRC)/revelar.cpp -o $(OBJ)/revelar.o

$(OBJ)/transformacion.o : $(SRC)/transformacion.cpp $(INC)/transformacion.h
	$(CXX) $(CXXFLAGS) $(SRC)/transformacion.cpp -o $(OBJ)/transformacion.o

$(OBJ)/transformar.o : $(SRC)/transformar.cpp $(INC)/transformacion.h
	$(CXX) $(CXXFLAGS) $(SRC)/transformar.cpp -o $(OBJ)/transformar.o

$(OBJ)/componer.o : $(SRC)/componer.cpp $(INC)/transformacion.h
	$(CXX) $(CXXFLAGS) $(SRC)/componer.cpp -o $(OBJ)/componer.o

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
