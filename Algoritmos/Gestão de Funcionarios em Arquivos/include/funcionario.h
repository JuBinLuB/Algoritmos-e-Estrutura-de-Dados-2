#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct Funcionario {
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
} TFunc;

// Retorna tamanho do funcionario em bytes.
int tamanhoRegistro();

// Retorna a quantidade de registros no arquivo.
int tamanhoArquivo(FILE *arq);

// Cria funcionario.
TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario);

// Salva funcionario no arquivo out, na posicao atual do cursor.
void salva(TFunc *func, FILE *out);

// Le um funcionario do arquivo in na posicao atual do cursor.
// Retorna um ponteiro para funcionario lido do arquivo.
TFunc *le(FILE *in);

// Imprime funcionario.
void imprime(TFunc *func);

// Cria base de dados.
void criarBase(FILE *out, int tam);

// Embaralha base de dados.
void shuffle(int *vet, int MAX, int MIN);

// Imprime base de dados.
void imprimirBase(FILE *out);

#endif // FUNCIONARIO_H_INCLUDED
