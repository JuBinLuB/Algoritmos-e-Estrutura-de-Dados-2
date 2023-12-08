#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "livro.h"

typedef struct {
    int ID;
    char nome[50];
    char dataNascimento[11];
    TLivro emprestimo;
} TUsuario;

// Retorna tamanho do usuario em bytes.
int tamanhoRegistroU();

// Retorna a quantidade de registros no arquivo.
int tamanhoArquivoU(FILE *arq);

// Cria usuario.
TUsuario *usuario(int ID, char *nome, char *dataNascimento);

// Salva usuario no arquivo out, na posicao atual do cursor.
void salvaU(TUsuario *usuario, FILE *out);

// Le um usuario do arquivo in na posicao atual do cursor.
// Retorna um ponteiro para usuario lido do arquivo.
TUsuario *leU(FILE *in);

// Imprime usuario.
void imprimeU(TUsuario *usuario);

// Imprime a base de dados.
void imprimirBaseU(FILE *out);

#endif // USUARIO_H_INCLUDED
