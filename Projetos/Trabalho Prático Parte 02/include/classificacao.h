#ifndef CLASSIFICACAO_H_INCLUDED
#define CLASSIFICACAO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "livro.h"
#include "usuario.h"

// Executa o algoritmo de geracao de particoes por Selecao com Substituicao para livros.
int selecaoSubstituicaoL(FILE *arq, FILE *log, int M);

// Executa o algoritmo de geracao de particoes por Selecao com Substituicao para usuarios.
int selecaoSubstituicaoU(FILE *arq, FILE *log, int M);

// Verifica se ha pelo menos um registro nao congelado.
int existemNaoCongelados(int *congelados, int n);

// Libera a memoria alocada para os registros de livros em memoria.
void liberarRegistrosL(TLivro **livro, int M);

// Libera a memoria alocada para os registros de usuarios em memoria.
void liberarRegistrosU(TUsuario **usuario, int M);

#endif // CLASSIFICACAO_H_INCLUDED
