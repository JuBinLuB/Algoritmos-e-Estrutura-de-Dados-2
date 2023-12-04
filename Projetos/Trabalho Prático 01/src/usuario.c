#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "livro.h"
#include "usuario.h"

// Retorna tamanho do usuario em bytes.
int tamanhoRegistroU() {
    return sizeof(int)          // ID
           + sizeof(char) * 50  // nome
           + sizeof(char) * 11  // dataNascimento
           + sizeof(TLivro);    // emprestimo 
}

// Retorna a quantidade de registros no arquivo.
int tamanhoArquivoU(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / tamanhoRegistroU());
    return tam;
}

// Cria usuario.
TUsuario *usuario(int ID, char *nome, char *dataNascimento) {
    TUsuario *usuario = (TUsuario *)malloc(sizeof(TUsuario));
    // Inicializa espaco de memoria com ZEROS.
    if (usuario) {
        memset(usuario, 0, sizeof(TUsuario));
    }
    // Copia valores para os campos de usuario.
    usuario->ID = ID;
    strcpy(usuario->nome, nome);
    strcpy(usuario->dataNascimento, dataNascimento);
    return usuario;
}

// Salva usuario no arquivo out, na posicao atual do cursor.
void salvaU(TUsuario *usuario, FILE *out) {
    fwrite(&usuario->ID, sizeof(int), 1, out);
    // usuario->nome ao inves de &usuario->nome, pois string ja e' um ponteiro.
    fwrite(usuario->nome, sizeof(char), sizeof(usuario->nome), out);
    fwrite(usuario->dataNascimento, sizeof(char), sizeof(usuario->dataNascimento), out);
    fwrite(&usuario->emprestimo, sizeof(TLivro), 1, out);
}

// Le um usuario do arquivo in na posicao atual do cursor.
// Retorna um ponteiro para usuario lido do arquivo.
TUsuario *leU(FILE *in) {
    TUsuario *usuario = (TUsuario *)malloc(sizeof(TUsuario));
    if (0 >= fread(&usuario->ID, sizeof(int), 1, in)) {
        free(usuario);
        return NULL;
    }
    fread(usuario->nome, sizeof(char), sizeof(usuario->nome), in);
    fread(usuario->dataNascimento, sizeof(char), sizeof(usuario->dataNascimento), in);
    fread(&usuario->emprestimo, sizeof(TLivro), 1, in);
    return usuario;
}

// Imprime usuario.
void imprimeU(TUsuario *usuario) {
    printf("\n\t**********************************************");
    printf("\n\tID: ");
    printf("%d", usuario->ID);
    printf("\n\tNome: ");
    printf("%s", usuario->nome);
    printf("\n\tData de Nascimento: ");
    printf("%s", usuario->dataNascimento);

    // Secao de Emprestimo.
    printf("\n\n\t---------- Dados do Emprestimo ----------");
    printf("\n\tISBN: %d", usuario->emprestimo.ISBN);
    printf("\n\tTitulo: %s", usuario->emprestimo.titulo);
    printf("\n\tAutor: %s", usuario->emprestimo.autor);
    printf("\n\tData de Publicacao: %s", usuario->emprestimo.dataPublicacao);
    printf("\n\t-------------------------------------------");
    printf("\n\t**********************************************\n");
}

// Imprime a base de dados.
void imprimirBaseU(FILE *out) {
    printf("\n\tImprimindo a base de dados...\n");
    rewind(out);
    TUsuario *u;

    while ((u = leU(out)) != NULL) {
        imprimeU(u);
    }
    printf("\n\tFim da base de dados...\n\n");
    free(u);
}
