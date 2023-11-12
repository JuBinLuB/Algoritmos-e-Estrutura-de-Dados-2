#ifndef LIVRO_H_INCLUDED
#define LIVRO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int ISBN;
    char titulo[50];
    char autor[50];
    char dataPublicacao[11];
} TLivro;

// Retorna tamanho do livro em bytes.
int tamanhoRegistro();

// Retorna a quantidade de registros no arquivo.
int tamanhoArquivo(FILE *arq);

// Cria livro.
TLivro *livro(int ISBN, char *titulo, char *autor, char *dataPublicacao);

// Salva livro no arquivo out, na posicao atual do cursor.
void salva(TLivro *func, FILE *out);

// Le um livro do arquivo in na posicao atual do cursor.
// Retorna um ponteiro para livro lido do arquivo.
TLivro *le(FILE *in);

// Imprime livro.
void imprime(TLivro *func);

// Cria base de dados.
void criarBase(FILE *out, int tam);

// Embaralha base de dados.
void shuffle(int *vet, int MAX, int MIN);

// Imprime base de dados.
void imprimirBase(FILE *out);

#endif // LIVRO_H_INCLUDED
