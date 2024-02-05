#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "livro.h"

// Cria livro.
TLivro *livro(int ISBN, char *titulo, char *autor, char *dataPublicacao, int prox, int flag) {
    TLivro *livro = (TLivro *)malloc(sizeof(TLivro));
    // Inicializa espaco de memoria com ZEROS.
    if (livro) {
        memset(livro, 0, sizeof(TLivro));
    }
    // Copia valores para os campos de livro.
    livro->ISBN = ISBN;
    strcpy(livro->titulo, titulo);
    strcpy(livro->autor, autor);
    strcpy(livro->dataPublicacao, dataPublicacao);
    livro->emprestado = 0;
    livro->prox = prox;
    livro->flag = flag;
    return livro;
}

// Salva livro no arquivo out, na posicao atual do cursor.
void salvaL(TLivro *livro, FILE *out) {
    fwrite(&livro->ISBN, sizeof(int), 1, out);
    // livro->titulo ao inves de &livro->titulo, pois string ja e' um ponteiro.
    fwrite(livro->titulo, sizeof(char), sizeof(livro->titulo), out);
    fwrite(livro->autor, sizeof(char), sizeof(livro->autor), out);
    fwrite(livro->dataPublicacao, sizeof(char), sizeof(livro->dataPublicacao), out);
    fwrite(&livro->emprestado, sizeof(int), 1, out);
    fwrite(&livro->prox, sizeof(int), 1, out);
    fwrite(&livro->flag, sizeof(int), 1, out);
}

// Le um livro do arquivo in na posicao atual do cursor.
// Retorna um ponteiro para livro lido do arquivo.
TLivro *leL(FILE *in) {
    TLivro *livro = (TLivro *)malloc(sizeof(TLivro));
    if (0 >= fread(&livro->ISBN, sizeof(int), 1, in)) {
        free(livro);
        return NULL;
    }
    fread(livro->titulo, sizeof(char), sizeof(livro->titulo), in);
    fread(livro->autor, sizeof(char), sizeof(livro->autor), in);
    fread(livro->dataPublicacao, sizeof(char), sizeof(livro->dataPublicacao), in);
    fread(&livro->emprestado, sizeof(int), 1, in);
    fread(&livro->prox, sizeof(int), 1, in);
    fread(&livro->flag, sizeof(int), 1, in);
    return livro;
}

// Imprime livro.
void imprimeL(TLivro *livro) {
    printf("\n\t**********************************************");
    printf("\n\tISBN: ");
    printf("%d", livro->ISBN);
    printf("\n\tTitulo: ");
    printf("%s", livro->titulo);
    printf("\n\tAutor: ");
    printf("%s", livro->autor);
    printf("\n\tData de Publicacao: ");
    printf("%s", livro->dataPublicacao);
    printf("\n\tSituacao: ");
    if (livro->emprestado) {
        printf("Emprestado");
    } else {
        printf("Disponivel");
    }
    printf("\n\t**********************************************\n");
}

// Compara dois Livros.
// Retorna 1 se os valores dos atributos de ambos forem iguais e 0 caso contrario.
int cmpLivro(TLivro *l1, TLivro *l2) {
	if (l1 == NULL) {
		return (l2 == NULL);
	}
	if (l1->ISBN != l2->ISBN) {
		return 0;
	}
	if (strcmp(l1->titulo, l2->titulo) != 0) {
		return 0;
	}
	if (strcmp(l1->autor, l2->autor) != 0) {
		return 0;
	}
	if (strcmp(l1->dataPublicacao, l2->dataPublicacao) != 0) {
		return 0;
	}
	if (l1->emprestado != l2->emprestado) {
		return 0;
	}
	if (l1->prox != l2->prox) {
		return 0;
	}
	if (l1->flag != l2->flag) {
		return 0;
	}
	return 1;
}

// Retorna tamanho do livro em bytes.
int tamanhoRegistroL() {
    return sizeof(int)          // ISBN
           + sizeof(char) * 50  // titulo
           + sizeof(char) * 50  // autor
           + sizeof(char) * 11  // dataPublicacao
           + sizeof(int)        // emprestado
           + sizeof(int)        // prox
           + sizeof(int);       // flag
}
