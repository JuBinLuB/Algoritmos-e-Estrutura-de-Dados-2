#ifndef CLASSIFICACAO_H_INCLUDED
#define CLASSIFICACAO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "livro.h"

// Executa o algoritmo de geracao de particoes por Selecao com Substituicao.
int selecaoSubstituicao(FILE *arq, FILE *log, int M);

// Verifica se ha pelo menos um registro nao congelado.
int existemNaoCongelados(int *congelados, int n);

// Libera a memoria alocada para os registros em memoria.
void liberarRegistros(TLivro **livro, int M);

#endif // CLASSIFICACAO_H_INCLUDED
