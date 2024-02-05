#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "compartimentoHash.h"

// Imprime compartimento hash.
void imprimeCompartimento(TCompartimento *compartimento) {
	printf("\n\tProx:");
	printf("%d\n", compartimento->prox);
}

// Cria compartimento hash. Lembrar de usar free(compartimentoHash).
TCompartimento *compartimentoHash(int prox) {
	TCompartimento *compartimento = (TCompartimento *)malloc(sizeof(TCompartimento));
	compartimento->prox = prox;
	return compartimento;
}

// Salva compartimento no arquivo out, na posicao atual do cursor.
void salvaCompartimento(TCompartimento *compartimento, FILE *out) {
	fwrite(&compartimento->prox, sizeof(int), 1, out);
}

// Le um compartimento do arquivo in na posicao atual do cursor.
// Retorna um ponteiro para compartimento lido do arquivo.
TCompartimento *leCompartimento(FILE *in) {
	TCompartimento *compartimento = (TCompartimento *) malloc(sizeof(TCompartimento));
	if (0 >= fread(&compartimento->prox, sizeof(int), 1, in)) {
		free(compartimento);
		return NULL;
	}
	return compartimento;
}

// Compara dois compartimentos.
// Retorna 1 se os valores dos atributos de ambos forem iguais e 0 caso contrario.
int cmpCompartimento(TCompartimento *c1, TCompartimento *c2) {
	if (c1 == NULL) {
		return (c2 == NULL);
	}
	if (c1->prox != c2->prox) {
		return 0;
	}
	return 1;
}

// Retorna tamanho do compartimento hash em bytes.
int tamanhoCompartimento() {
	return sizeof(int); // prox
}
