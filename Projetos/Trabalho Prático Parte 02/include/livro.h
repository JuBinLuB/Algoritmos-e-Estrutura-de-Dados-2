#ifndef LIVRO_H_INCLUDED
#define LIVRO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int ISBN;
    char titulo[50];
    char autor[50];
    char dataPublicacao[11];
    int emprestado;
} TLivro;

// Retorna tamanho do livro em bytes.
int tamanhoRegistroL();

// Retorna a quantidade de registros no arquivo.
int tamanhoArquivoL(FILE *arq);

// Cria livro.
TLivro *livro(int ISBN, char *titulo, char *autor, char *dataPublicacao);

// Salva livro no arquivo out, na posicao atual do cursor.
void salvaL(TLivro *livro, FILE *out);

// Le um livro do arquivo in na posicao atual do cursor.
// Retorna um ponteiro para livro lido do arquivo.
TLivro *leL(FILE *in);

// Imprime livro.
void imprimeL(TLivro *livro);

// Cria base de dados.
void criarBase(FILE *out, int tam);

// Embaralha base de dados.
void shuffle(int *vet, int MAX, int MIN);

// Cria base de dados ordenada.
void criarBaseOrdenada(FILE *out, int tam);

// Imprime base de dados.
void imprimirBaseL(FILE *out);

// Libera a memoria alocada para os registros de um vetor de livros em memoria.
void liberarRegistrosL(TLivro **livro, int M);

#endif // LIVRO_H_INCLUDED
