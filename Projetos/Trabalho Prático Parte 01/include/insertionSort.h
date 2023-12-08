#ifndef INSERTIONSORT_H_INCLUDED
#define INSERTIONSORT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Realiza a ordenacao por insercao em um arquivo contendo registros de livros.
void insertionSortL(FILE *arq, FILE *log, int tam);

// Realiza a ordenacao por insercao em um arquivo contendo registros de usuarios.
void insertionSortU(FILE *arq, FILE *log, int tam);

#endif // INSERTIONSORT_H_INCLUDED
