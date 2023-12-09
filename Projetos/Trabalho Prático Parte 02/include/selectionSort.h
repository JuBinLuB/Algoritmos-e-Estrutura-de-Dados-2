#ifndef SELECTIONSORT_H_INCLUDED
#define SELECTIONSORT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Realiza a ordenacao por selecao em um arquivo contendo registros de livros.
void selectionSortL(FILE *arq, FILE* log, int tam);

// Realiza a ordenacao por selecao em um arquivo contendo registros de usuarios.
void selectionSortU(FILE *arq, FILE* log, int tam);

#endif // SELECTION_H_INCLUDED
