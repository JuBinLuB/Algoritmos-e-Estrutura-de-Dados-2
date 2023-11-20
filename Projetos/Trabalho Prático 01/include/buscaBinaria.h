#ifndef BUSCABINARIA_H_INCLUDED
#define BUSCABINARIA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "livro.h"
#include "usuario.h"

// Realiza uma busca binaria por um livro na base de dados.
TLivro *buscaBinariaL(int chave, FILE *in, FILE *log, int inicio, int fim);

// Realiza uma busca binaria por um usuario na base de dados.
TUsuario *buscaBinariaU(int chave, FILE *in, FILE *log, int inicio, int fim);

#endif // BUSCABINARIA_H_INCLUDED
