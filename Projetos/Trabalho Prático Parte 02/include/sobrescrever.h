#ifndef SOBRESCREVER_H_INCLUDED
#define SOBRESCREVER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Funcao para sobrescrever registros de livros do arquivo original pelo conteudo do novo arquivo.
void sobrescreverArquivoL(FILE *arquivoOriginal, FILE *novoArquivo, int tamanhoRegistro);

// Funcao para sobrescrever registros de usuarios do arquivo original pelo conteudo do novo arquivo.
void sobrescreverArquivoU(FILE *arquivoOriginal, FILE *novoArquivo, int tamanhoRegistro);

#endif // SOBRESCREVER_H_INCLUDED
