#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

void writex(char *f, int *vector, int n);

void writeb(char *f, int *vector, int n);

void readx(char *f);

void readb(char *f);

#endif // ARQUIVO_H_INCLUDED
