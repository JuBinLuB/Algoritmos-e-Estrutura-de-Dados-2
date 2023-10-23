#ifndef BUSCASEQUENCIAL_H_INCLUDED
#define BUSCASEQUENCIAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "funcionario.h"

// Realiza uma busca sequencial por um funcionario na base de dados.
TFunc *buscaSequencial(int chave, FILE * in);

#endif // BUSCASEQUENCIAL_H_INCLUDED
