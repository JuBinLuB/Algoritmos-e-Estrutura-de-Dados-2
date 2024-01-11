#ifndef INTERCALACAO_H_INCLUDED
#define INTERCALACAO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Executa o algoritmo de Intercalacao Otima de particoes para livros.
void intercalacaoL(FILE *out, FILE *log, char *nome, int totalParticoes, int F);

// Executa o algoritmo de Intercalacao Otima de particoes para usuarios.
void intercalacaoU(FILE *out, FILE *log, char *nome, int totalParticoes, int F);

// Funcao para sobrescrever registros de livros do arquivo original pelo conteudo do novo arquivo.
void sobrescreverArquivoL(FILE *arquivoOriginal, FILE *novoArquivo, int tamanhoRegistro);

// Funcao para sobrescrever registros de usuarios do arquivo original pelo conteudo do novo arquivo.
void sobrescreverArquivoU(FILE *arquivoOriginal, FILE *novoArquivo, int tamanhoRegistro);

#endif // INTERCALACAO_H_INCLUDED
