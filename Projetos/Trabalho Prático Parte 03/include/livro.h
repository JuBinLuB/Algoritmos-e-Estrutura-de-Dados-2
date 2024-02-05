#ifndef LIVRO_H_INCLUDED
#define LIVRO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define LIBERADO 0
#define OCUPADO 1

typedef struct {
    int ISBN;
    char titulo[50];
    char autor[50];
    char dataPublicacao[11];
    int emprestado;
    int prox;
    int flag;
} TLivro;

// Cria livro.
TLivro *livro(int ISBN, char *titulo, char *autor, char *dataPublicacao, int prox, int flag);

// Salva livro no arquivo out, na posicao atual do cursor.
void salvaL(TLivro *livro, FILE *out);

// Le um livro do arquivo in na posicao atual do cursor.
// Retorna um ponteiro para livro lido do arquivo.
TLivro *leL(FILE *in);

// Imprime livro.
void imprimeL(TLivro *livro);

// Compara dois Livros.
// Retorna 1 se os valores dos atributos de ambos forem iguais e 0 caso contrario.
int cmpLivro(TLivro *l1, TLivro *l2);

// Retorna tamanho do livro em bytes.
int tamanhoRegistroL();

#endif // LIVRO_H_INCLUDED
