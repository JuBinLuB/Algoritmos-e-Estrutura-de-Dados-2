#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int ID;
    char nome[50];
    char cpf[15];
    char dataNascimento[11];
    int emprestimos[5];
} TUsuario;

#endif // USUARIO_H_INCLUDED
