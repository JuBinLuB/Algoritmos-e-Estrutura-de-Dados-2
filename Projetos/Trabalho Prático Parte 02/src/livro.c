#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>

#include "livro.h"
#include "randomizer.h"

// Retorna tamanho do livro em bytes.
int tamanhoRegistroL() {
    return sizeof(int)          // ISBN
           + sizeof(char) * 50  // titulo
           + sizeof(char) * 50  // autor
           + sizeof(char) * 11  // dataPublicacao
           + sizeof(int);       // emprestado
}

// Retorna a quantidade de registros no arquivo.
int tamanhoArquivoL(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / tamanhoRegistroL());
    return tam;
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
    livro->emprestado = 0;
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

// Cria a base de dados.
void criarBase(FILE *out, int tam) {
    int vet[tam];
    char data[15];
    TLivro *l;

    // Inicializa a semente uma vez no início da funcao.
    srand(time(NULL));

    for (int i = 0; i < tam; i++) {
        vet[i] = i + 1;
    }
    shuffle(vet, tam, (tam * 2) / 100);
    printf("\n\tGerando a base de dados...\n");

    for (int i = 0; i < tam; i++) {
        gerarDataAleatoria(data);
        l = livro(vet[i], "A", "XXXX", data);
        salvaL(l, out);
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

// Cria base de dados ordenada.
void criarBaseOrdenada(FILE *out, int tam) {
    int vet[tam];
    char data[15];
    TLivro *l;

    // Inicializa a semente uma vez no início da funcao.
    srand(time(NULL));

    for (int i = 0; i < tam; i++) {
        vet[i] = i + 1;
    }
    printf("\n\tGerando a base de dados...\n");

    for (int i = 0; i < tam; i++) {
        gerarDataAleatoria(data);
        l = livro(vet[i], "A", "XXXX", data);
        salvaL(l, out);
    }
    free(l);
}

// Imprime a base de dados.
void imprimirBaseL(FILE *out) {
    printf("\n\tImprimindo a base de dados...\n");
    rewind(out);
    TLivro *l;

    while ((l = leL(out)) != NULL) {
        imprimeL(l);
    }
    printf("\n\tFim da base de dados...\n\n");
    free(l);
}

// Libera a memoria alocada para os registros de um vetor de livros em memoria.
void liberarRegistrosL(TLivro **livro, int M) {
    for (int i = 0; i < M; i++) {
        if (livro[i] != NULL) {
            free(livro[i]);
        }
    }
}
