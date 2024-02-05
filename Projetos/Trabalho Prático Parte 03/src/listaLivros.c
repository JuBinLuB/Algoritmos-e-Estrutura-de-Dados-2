#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "listaLivros.h"
#include "livro.h"

// Cria lista de livros.
ListaLivros *criaLivros(int tam, ...) {
	va_list ap;
	ListaLivros *l = (ListaLivros *)malloc(sizeof(ListaLivros));
	l->tam = tam;
	l->lista = (TLivro **)malloc(sizeof(TLivro *) * (tam));
	va_start(ap, tam);
	for (int i = 0; i < tam; i++) {
        l->lista[i] = va_arg(ap, TLivro *);
    }
    va_end(ap);
    return l;
}

// Salva lista de livros no arquivo nomeArquivo.
void salvaLivros(char *nomeArquivo, ListaLivros *l) {
	FILE *out = fopen(nomeArquivo, "wb");
	for (int i = 0; i < l->tam; i++) {
		salvaL(l->lista[i], out);
	}
	fclose(out);
}

// Le lista de livros do arquivo nomeArquivo.
ListaLivros *leLivros(char *nomeArquivo) {
	int tam = 0;
	ListaLivros *listaLivros = (ListaLivros *)malloc(sizeof(ListaLivros));
	FILE *in = fopen(nomeArquivo, "rb");
	if (in != NULL) {
		TLivro *livro = NULL;
		while((livro = leL(in)) != NULL) {
			tam += 1;
			free(livro);
		}
		fseek(in, 0, SEEK_SET);
		listaLivros->tam = tam;
		listaLivros->lista = (TLivro **)malloc(sizeof(TLivro *) * (tam));
		tam = 0;
		while((livro = leL(in)) != NULL) {
			listaLivros->lista[tam++] = livro;
		}
		fclose(in);
	} else {
		listaLivros->tam = 0;
		listaLivros->lista = NULL;
	}
	return listaLivros;
}

// Imprime livros.
void imprimeLivros(ListaLivros *lista) {
	for (int i = 0; i < lista->tam; i++) {
		imprimeL(lista->lista[i]);
	}
}

// Compara duas listas de livros.
// Retorna 1 se os livros das duas listas forem iguais e 0 caso contrario.
int cmpLivros(ListaLivros *l1, ListaLivros *l2) {
	if (l1->tam != l2->tam) {
		return 0;
	}
	for (int i = 0; i < l1->tam; i++) {
		if (!cmpLivro(l1->lista[i], l2->lista[i])) {
			return 0;
		}
	}
	return 1;
}

// Desaloca lista de livros.
void liberaLivros(ListaLivros *l) {
	for (int i = 0; i < l->tam; i++) {
		free(l->lista[i]);
	}
	free(l->lista);
	free(l);
}
