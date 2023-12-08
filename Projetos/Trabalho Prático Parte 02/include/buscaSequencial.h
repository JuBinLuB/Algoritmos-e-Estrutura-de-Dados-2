#ifndef BUSCASEQUENCIAL_H_INCLUDED
#define BUSCASEQUENCIAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "livro.h"
#include "usuario.h"

// Realiza uma busca sequencial por um livro na base de dados.
TLivro *buscaSequencialL(int chave, FILE *in, FILE *log);

// Realiza uma busca sequencial por um usuario na base de dados.
TUsuario *buscaSequencialU(int chave, FILE *in, FILE *log);

#endif // BUSCASEQUENCIAL_H_INCLUDED
