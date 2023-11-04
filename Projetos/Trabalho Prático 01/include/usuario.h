#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[11];
    char cpf[11];
    char data_nascimento[11];
    int emprestimos[5];
} Usuario;

#endif // USUARIO_H_INCLUDED
