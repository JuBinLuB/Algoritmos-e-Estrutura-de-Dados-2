#ifndef BUSCABINARIA_H_INCLUDED
#define BUSCABINARIA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "livro.h"

// Realiza uma busca binaria por um funcionario na base de dados.
TLivro *buscaBinaria(int chave, FILE *in, FILE *log, int inicio, int fim);

#endif // BUSCABINARIA_H_INCLUDED
