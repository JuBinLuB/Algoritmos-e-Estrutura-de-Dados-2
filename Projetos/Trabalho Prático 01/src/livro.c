#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>

#include "livro.h"
#include "randomizer.h"

// Retorna tamanho do livro em bytes.
int tamanhoRegistro() {
    return sizeof(int)          // ISBN
           + sizeof(char) * 50  // titulo
           + sizeof(char) * 50  // autor
           + sizeof(char) * 11; // dataPublicacao
}

// Cria livro.
TLivro *livro(int ISBN, char *titulo, char *autor, char *dataPublicacao) {
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
    return livro;
}

// Salva livro no arquivo out, na posicao atual do cursor.
void salva(TLivro *livro, FILE *out) {
    fwrite(&livro->ISBN, sizeof(int), 1, out);
    // livro->titulo ao inves de &livro->titulo, pois string ja e' um ponteiro.
    fwrite(livro->titulo, sizeof(char), sizeof(livro->titulo), out);
    fwrite(livro->autor, sizeof(char), sizeof(livro->autor), out);
    fwrite(livro->dataPublicacao, sizeof(char), sizeof(livro->dataPublicacao), out);
}

// Le um livro do arquivo in na posicao atual do cursor.
// Retorna um ponteiro para livro lido do arquivo.
TLivro *le(FILE *in) {
    TLivro *livro = (TLivro *)malloc(sizeof(TLivro));
    if (0 >= fread(&livro->ISBN, sizeof(int), 1, in)) {
        free(livro);
        return NULL;
    }
    fread(livro->titulo, sizeof(char), sizeof(livro->titulo), in);
    fread(livro->autor, sizeof(char), sizeof(livro->autor), in);
    fread(livro->dataPublicacao, sizeof(char), sizeof(livro->dataPublicacao), in);
    return livro;
}

// Imprime livro.
void imprime(TLivro *livro) {
    printf("\n\t**********************************************");
    printf("\n\tISBN: ");
    printf("%d", livro->ISBN);
    printf("\n\tTitulo: ");
    printf("%s", livro->titulo);
    printf("\n\tAutor: ");
    printf("%s", livro->autor);
    printf("\n\tData de Publicacao: ");
    printf("%s", livro->dataPublicacao);
    printf("\n\t**********************************************\n");
}

// Retorna a quantidade de registros no arquivo.
int tamanhoArquivo(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / tamanhoRegistro());
    return tam;
}

// Cria a base de dados.
void criarBase(FILE *out, int tam) {
    int vet[tam];
    char data[15];
    TLivro *l;

    // Inicializa a semente uma vez no in�cio da funcao.
    srand(time(NULL));

    for (int i = 0; i < tam; i++) {
        vet[i] = i + 1;
    }
    shuffle(vet, tam, (tam * 2) / 100);
    printf("\n\tGerando a base de dados...\n");

    for (int i = 0; i < tam; i++) {
        gerarDataAleatoria(data);
        l = livro(vet[i], "A", "XXXX", data);
        salva(l, out);
    }
    free(l);
}

// Embaralha base de dados.
void shuffle(int *vet, int MAX, int MIN) {
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

// Imprime a base de dados.
void imprimirBase(FILE *out) {
    printf("\n\tImprimindo a base de dados...\n");
    rewind(out);
    TLivro *l;

    while ((l = le(out)) != NULL) {
        imprime(l);
    }
    printf("\n\tFim da base de dados...\n\n");
    free(l);
}
