#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "funcionario.h"
#include "buscaSequencial.h"

// Realiza uma busca sequencial por um funcionario na base de dados.
TFunc *buscaSequencial(int chave, FILE *in, FILE *log) {
    // Registra o tempo de inicio da execucao do codigo.
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Declaracao de variaveis.
    TFunc *f = NULL;
    int encontrado = 0;
    int contador = 0;

    rewind(in);
    fprintf(log, "\tBusca Sequencial...\n\n");

    while ((f = le(in)) != NULL) {
        if (f->cod == chave) {
            encontrado = 1;
            break;
        }
        contador++;
        // Exibe o numero de comparacoes realizados pela busca no arquivo log.
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
        return f;
    }
    free(f);
    return NULL;
}
