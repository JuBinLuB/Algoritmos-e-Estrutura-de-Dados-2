#ifndef LIVRO_H_INCLUDED
#define LIVRO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int ISBN;
    char titulo[11];
    char autor[11];
    char data[11];
} Livro;

void realizarEmprestimo();

#endif // LIVRO_H_INCLUDED
