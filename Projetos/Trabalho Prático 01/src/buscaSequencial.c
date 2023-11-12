#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "buscaSequencial.h"
#include "livro.h"

// Realiza uma busca sequencial por um livro na base de dados.
TLivro *buscaSequencial(int chave, FILE *in, FILE *log) {
    // Registra o tempo de inicio da execucao do codigo.
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Declaracao de variaveis.
    TLivro *livro = NULL;
    int encontrado = 0;
    int contador = 0;

    rewind(in);
    fprintf(log, "\n\tBusca Sequencial...\n\n");

    while ((livro = le(in)) != NULL) {
        if (livro->ISBN == chave) {
            encontrado = 1;
            break;
        }
        contador++;
        // Registra o numero de comparacoes realizadas pela busca no arquivo de log.
        fprintf(log, "\tComparacoes: %d\n", contador);
    }
    // Registra o tempo de fim da execucao do codigo.
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calcula o tempo decorrido pelo programa, encontrando a diferenca entre end e start,
    // e, em seguida, divide a diferenca por 1e9 para converter para segundos.
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Registra o tempo de CPU consumido pela aplicacao no arquivo de log.
    fprintf(log, "\n\tThe elapsed time is %f seconds\n", time_spent);

    if (encontrado) {
        return livro;
    }
    free(livro);
    return NULL;
}
