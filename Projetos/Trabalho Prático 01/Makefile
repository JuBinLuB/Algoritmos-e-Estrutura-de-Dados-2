APPS = ./apps
BIN = ./bin
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SRC = ./src

FLAGS = -o3 -Wall
LIBS = -l biblioteca -L $(LIB)

all: lib myapps

lib: $(OBJ)/livro.o \
	 $(OBJ)/buscaSequencial.o \
	 $(OBJ)/buscaBinaria.o \
	 $(OBJ)/insertionSort.o \
	 $(OBJ)/interface.o \
	 $(OBJ)/randomizer.o
	ar -rcs $(LIB)/libbiblioteca.a $(OBJ)/*.o

myapps: clean_apps \
	$(BIN)/main

# Target genérica para compilação dos Tipos Abstratos de Dados.
$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

# Target genérica para compilação do programa.
$(BIN)/%: $(APPS)/%.c $(OBJ)/*.o
	gcc $(FLAGS) $< $(LIBS) -I $(INCLUDE) -o $@

run:
	$(BIN)/main

clean:
	rm -rf $(BIN)/* $(LIB)/* $(OBJ)/*

clean_apps:
	rm -rf $(BIN)/*
