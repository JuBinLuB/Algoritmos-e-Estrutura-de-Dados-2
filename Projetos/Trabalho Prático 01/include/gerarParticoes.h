#ifndef GERARPARTICOES_H_INCLUDED
#define GERARPARTICOES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Executa o algoritmo de geracao de particoes por Selecao com Substituicao.
int selecaoSubstituicao(FILE *arq, int M);

// Verifica se ha pelo menos um registro nao congelado.
int existemNaoCongelados(int *congelados, int n);

#endif // GERARPARTICOES_H_INCLUDED
