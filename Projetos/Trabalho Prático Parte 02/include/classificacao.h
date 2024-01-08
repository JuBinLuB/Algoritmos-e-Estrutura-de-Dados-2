#ifndef CLASSIFICACAO_H_INCLUDED
#define CLASSIFICACAO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "livro.h"
#include "usuario.h"

// Executa o algoritmo de geracao de particoes por Selecao com Substituicao para livros.
int selecaoSubstituicaoL(FILE *in, FILE *log, char *nome, int M);

// Executa o algoritmo de geracao de particoes por Selecao com Substituicao para usuarios.
int selecaoSubstituicaoU(FILE *in, FILE *log, char *nome, int M);

// Verifica se ha pelo menos um registro nao congelado.
int existemNaoCongelados(int *congelados, int n);

#endif // CLASSIFICACAO_H_INCLUDED
