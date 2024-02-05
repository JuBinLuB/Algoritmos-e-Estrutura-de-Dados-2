#ifndef LISTALIVRO_H_INCLUDED
#define LISTALIVRO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "livro.h"

typedef struct {
    TLivro **lista;
    int tam;
} ListaLivros;

// Cria lista de livros.
ListaLivros *criaLivros(int tam, ...);

// Salva lista de livros no arquivo nomeArquivo.
void salvaLivros(char *nomeArquivo, ListaLivros *l);

// Le lista de livros do arquivo nomeArquivo.
ListaLivros *leLivros(char *nomeArquivo);

// Imprime livros.
void imprimeLivros(ListaLivros *l);

// Compara duas listas de livros.
// Retorna 1 se os livros das duas listas forem iguais e 0 caso contrario.
int cmpLivros(ListaLivros *l1, ListaLivros *l2);

// Desaloca lista de livros.
void liberaLivros(ListaLivros *l);

#endif // LISTALIVRO_H_INCLUDED
