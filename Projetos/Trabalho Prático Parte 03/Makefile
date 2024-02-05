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
	 $(OBJ)/listaLivros.o \
	 $(OBJ)/compartimentoHash.o \
	 $(OBJ)/listaCompartimentos.o \
	 $(OBJ)/encadeamentoExterior.o
	ar -rcs $(LIB)/libbiblioteca.a $(OBJ)/*.o

myapps: clean_apps \
	$(BIN)/test_encadeamento_exterior

# Target genérica para compilação dos Tipos Abstratos de Dados.
$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

# Target genérica para compilação do programa.
$(BIN)/%: $(APPS)/%.c $(OBJ)/*.o
	gcc $(FLAGS) $< $(LIBS) -I $(INCLUDE) -o $@

run:
	$(BIN)/test_encadeamento_exterior

clean:
	rm -rf $(BIN)/* $(LIB)/* $(OBJ)/*

clean_apps:
	rm -rf $(BIN)/*
