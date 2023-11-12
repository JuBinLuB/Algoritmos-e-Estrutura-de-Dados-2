#ifndef BUSCASEQUENCIAL_H_INCLUDED
#define BUSCASEQUENCIAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "livro.h"

// Realiza uma busca sequencial por um livro na base de dados.
TLivro *buscaSequencial(int chave, FILE *in, FILE *log);

#endif // BUSCASEQUENCIAL_H_INCLUDED
