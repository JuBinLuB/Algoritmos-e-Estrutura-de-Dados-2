#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "buscaBinaria.h"
#include "funcionario.h"

TFunc *buscaBinaria(int chave, FILE *in, FILE *log, int inicio, int fim) {
    // Registra o tempo de inicio da execucao do codigo.
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Declaracao de variaveis.
    TFunc *f = NULL;
    int codigo = -1;
    int contador = 0;

    fprintf(log, "\tBusca Binaria...\n\n");

    while (inicio <= fim && codigo != chave) {
        int meio = trunc((inicio + fim) / 2);
        // printf("Inicio: %d; Fim: %d; Meio: %d\n", inicio, fim, meio);
        fseek(in, (meio - 1) * tamanhoRegistro(), SEEK_SET);
        f = le(in);
        codigo = f->cod;

        if (f) {
            if (codigo > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
        contador++;
        // Exibe o numero de comparacoes realizados pela busca no arquivo log.
        fprintf(log, "\tComparacoes: %d\n", contador);
    }
    // Registra o tempo de fim da execucao do código.
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calcula o tempo decorrido pelo programa, encontrando a diferenca entre end e start,
    // e, em seguida, divide a diferenca por 1e9 para converter para segundos.
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Registra o tempo de CPU consumido pela aplicacao no arquivo de log.
    fprintf(log, "\n\tThe elapsed time is %f seconds\n", time_spent);

    if (codigo == chave) {
        return f;
    }
    free(f);
    return NULL;
}
