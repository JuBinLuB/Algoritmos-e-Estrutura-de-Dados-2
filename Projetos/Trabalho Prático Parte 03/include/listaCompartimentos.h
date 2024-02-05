#ifndef LISTACOMPARTIMENTOS_H_INCLUDED
#define LISTACOMPARTIMENTOS_H_INCLUDED

#include "compartimentoHash.h"

typedef struct ListaCompartimentos {
	TCompartimento **lista;
	int qtd;
} ListaCompartimentos;

// Imprime compartimentos.
void imprimeCompartimentos(ListaCompartimentos *lc);

// Cria lista de compartimentos. Lembrar de usar liberaCompartimentos(compartimentos).
ListaCompartimentos *criaCompartimentos(int qtd, ...);

// Salva lista de compartimentos no arquivo nome_arquivo.
void salvaCompartimentos(char *nomeArquivo, ListaCompartimentos *lc);

// Le lista de compartimentos do arquivo nome_arquivo.
ListaCompartimentos *leCompartimentos(char *nomeArquivo);

// Compara duas listas de compartimentos.
// Retorna 1 se os compartimentos das duas listas forem iguais e 0 caso contrario.
int cmpCompartimentos(ListaCompartimentos *c1, ListaCompartimentos *c2);

// Desaloca lista de compartimentos.
void liberaCompartimentos(ListaCompartimentos *lc);

// Adiciona compartimento a lista.
void addCompartimento(ListaCompartimentos *lc, int prox);

#endif // LISTACOMPARTIMENTOS_H_INCLUDED
