#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "buscaSequencial.h"
#include "funcionario.h"

// Realiza uma busca sequencial por um funcionario na base de dados.
TFunc *buscaSequencial(int chave, FILE * in, FILE *log) {
    // Armazena o tempo de execução do código.
    double time_spent = 0.0;
    clock_t begin = clock();
    sleep(3);

    TFunc *f = NULL;
    int encontrado = 0;
    int contador = 0;

    rewind(in);

    while ((f = le(in)) != NULL) {
        if (f->cod == chave) {
            encontrado = 1;
            break;
        } else {
            contador++;
            fprintf(log, "\tComparacoes: %d\n", contador);
        }
    }
    clock_t end = clock();

    // Calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos.
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    // Salvando o tempo de CPU consumido pela aplicacao em um arquivo.
    fprintf(log, "\n\tThe elapsed time is %f seconds\n", time_spent);

    if (encontrado) {
        return f;
    }
    free(f);
    return NULL;
}

/*
// Realiza uma busca sequencial por um funcionario na base de dados.
TFunc *buscaSequencial(char *nome, FILE *in) {
    TFunc *f;
    int encontrado = 0;
    int contador = 0;

    rewind(out);

    while ((f = le(in)) != NULL) {
        if (strcmp(nome, f->nome) == 0) {
            encontrado = 1;
            break;
        } else {
            contador++;
        }
        printf("\tComparacoes: %d\n", contador);
    }

    if (encontrado) {
        return f;
    }
    free(f);
    return NULL;
}
*/
