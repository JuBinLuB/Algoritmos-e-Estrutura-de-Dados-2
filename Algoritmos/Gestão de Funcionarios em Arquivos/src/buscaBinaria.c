#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "buscaBinaria.h"

TFunc *buscaBinaria(int chave, FILE * in, FILE *log, int inicio, int fim) {
    // Armazena o tempo de execução do código.
    double time_spent = 0.0;
    clock_t begin = clock();
    sleep(3);

    TFunc *f = NULL;
    int cod = -1;
    int contador = 0;

    while (inicio <= fim && cod != chave) {
        int meio = trunc((inicio + fim) / 2);
        // printf("Inicio: %d; Fim: %d; Meio: %d\n", inicio, fim, meio);
        fseek(in, (meio - 1) * tamanho_registro(), SEEK_SET);
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
        fprintf(log, "\tComparacoes: %d\n", contador);
    }
    clock_t end = clock();

    // Calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos.
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    // Exibindo o tempo de CPU consumido pela aplicacao.
    fprintf(log, "\n\tThe elapsed time is %f seconds\n", time_spent);

    if (cod == chave) {
        return f;
    }
    free(f);
    return NULL;
}
