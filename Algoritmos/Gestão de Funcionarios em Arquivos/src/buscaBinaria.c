#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "buscaBinaria.h"
#include "funcionario.h"

TFunc *buscaBinaria(int chave, FILE * in, FILE *log, int inicio, int fim) {
    // Armazena o tempo de execucao do codigo (BEGIN).
    clock_t begin = clock();
    sleep(3);

    // Declaracao de variaveis.
    TFunc *f = NULL;
    double time_spent = 0.0;
    int cod = -1;
    int contador = 0;

    fprintf(log, "\tBusca Binaria...\n\n");

    while (inicio <= fim && cod != chave) {
        int meio = trunc((inicio + fim) / 2);
        // printf("Inicio: %d; Fim: %d; Meio: %d\n", inicio, fim, meio);
        fseek(in, (meio - 1) * tamanhoRegistro(), SEEK_SET);
        f = le(in);
        cod = f->cod;

        if (f) {
            if (cod > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
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

    if (cod == chave) {
        return f;
    }
    free(f);
    return NULL;
}
