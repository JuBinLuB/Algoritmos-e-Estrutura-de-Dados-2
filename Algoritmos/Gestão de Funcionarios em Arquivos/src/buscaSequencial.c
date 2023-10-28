#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "funcionario.h"
#include "buscaSequencial.h"

// Realiza uma busca sequencial por um funcionario na base de dados.
TFunc *buscaSequencial(int chave, FILE * in, FILE *log) {
    // Armazena o tempo de execucao do codigo (BEGIN).
    clock_t begin = clock();
    sleep(3);

    // Declaracao de variaveis.
    TFunc *f = NULL;
    double time_spent = 0.0;
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
    // Armazena o tempo de execucao do codigo (END).
    clock_t end = clock();

    // Calcula o tempo decorrido encontrando a diferenca (end - begin) e
    // dividindo a diferenca por CLOCKS_PER_SEC para converter em segundos.
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    // Exibe o tempo de CPU consumido pela aplicacao no arquivo log.
    fprintf(log, "\n\tThe elapsed time is %f seconds\n", time_spent);

    if (encontrado) {
        return f;
    }
    free(f);
    return NULL;
}
