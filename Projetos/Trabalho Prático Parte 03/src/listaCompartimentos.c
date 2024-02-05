#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include "listaCompartimentos.h"
#include "compartimentoHash.h"

// Imprime compartimentos.
void imprimeCompartimentos(ListaCompartimentos *lc) {
	for (int i = 0; i < lc->qtd; i++) {
		imprimeCompartimento(lc->lista[i]);
	}
}

// Cria lista de compartimentos. Lembrar de usar liberaCompartimentos(compartimentos).
ListaCompartimentos *criaCompartimentos(int qtd, ...) {
	va_list ap;
	ListaCompartimentos *lc = (ListaCompartimentos *)malloc(sizeof(ListaCompartimentos));
	lc->qtd = qtd;
	lc->lista = (TCompartimento **) malloc(sizeof(TCompartimento *) * (qtd));
	va_start(ap, qtd);
	for (int i = 0; i < qtd; i++) {
        lc->lista[i] = va_arg(ap, TCompartimento *);
    }
    va_end(ap);
    return lc;
}

// Salva lista de compartimentos no arquivo nome_arquivo.
void salvaCompartimentos(char *nome_arquivo, ListaCompartimentos *lc) {
	FILE *out = fopen(nome_arquivo, "wb");
	int i;
	for (i = 0; i < lc->qtd; i++) {
		salvaCompartimento(lc->lista[i], out);
	}
	fclose(out);
}

// Le lista de compartimentos do arquivo nome_arquivo.
ListaCompartimentos * leCompartimentos(char *nome_arquivo) {
	int qtd = 0;
	ListaCompartimentos *lc = (ListaCompartimentos *)malloc(sizeof(ListaCompartimentos));
	FILE *in = fopen(nome_arquivo, "rb");
	if (in != NULL) {
		TCompartimento *compartimento = NULL;
		while((compartimento = leCompartimento(in)) != NULL) {
			qtd += 1;
			free(compartimento);
		}
		fseek(in, 0, SEEK_SET);
		lc->qtd = qtd;
		lc->lista = (TCompartimento **)malloc(sizeof(TCompartimento *) * (qtd));
		qtd = 0;
		while((compartimento = leCompartimento(in)) != NULL) {
			lc->lista[qtd++] = compartimento;
		}
		fclose(in);
	} else {
		lc->qtd = 0;
		lc->lista = NULL;
	}
	return lc;
}

// Compara duas listas de compartimentos.
// Retorna 1 se os compartimentos das duas listas forem iguais e 0 caso contrario.
int cmpCompartimentos(ListaCompartimentos *c1, ListaCompartimentos *c2) {
	if (c1->qtd != c2->qtd) {
		return 0;
	}
	for (int i = 0; i < c1->qtd; i++) {
		if (!cmpCompartimento(c1->lista[i], c2->lista[i])) {
			return 0;
		}
	}
	return 1;
}

// Desaloca lista de compartimentos.
void liberaCompartimentos(ListaCompartimentos *lc) {
	for (int i = 0; i < lc->qtd; i++) {
		free(lc->lista[i]);
	}
	free(lc->lista);
	free(lc);
}

// Adiciona compartimento a lista.
void addCompartimento(ListaCompartimentos *lc, int prox) {
	assert(lc != NULL && "Lista Inválida");
	
	TCompartimento **novo = (TCompartimento **)calloc((lc->qtd + 1), sizeof(TCompartimento *));
	assert(novo != NULL && "Falha na criação");
	
	for(int i = 0; i < lc->qtd; i++){
		novo[i] = lc->lista[i];
		lc->lista[i] = NULL;
	}
	
	novo[lc->qtd] = (TCompartimento *)malloc(sizeof(TCompartimento *));
	novo[lc->qtd]->prox = prox;

	free(lc->lista);
	lc->lista = novo;
	lc->qtd++;
}
