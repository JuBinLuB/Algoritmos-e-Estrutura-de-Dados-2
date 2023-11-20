#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "insertionSort.h"
#include "livro.h"
#include "usuario.h"

// Realiza a ordenacao por insercao em um arquivo contendo registros de livros.
void insertionSortL(FILE *arq, FILE *log, int tam) {
    // Registra o tempo de inicio da execucao do codigo.
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Ponteiros para livros.
    TLivro *atual;
    TLivro *proximo;
    int i = 0;
    int contador = 0;

    fprintf(log, "\n\tInsertion Sort Livros...\n\n");

    // Faz o insertion sort.
    for (int j = 2; j <= tam; j++) {
        // Posiciona o arquivo no registro "j".
        fseek(arq, (j - 1) * tamanhoRegistroL(), SEEK_SET);
        proximo = leL(arq);

        i = j - 1;

        // Posiciona o cursor no registro "i".
        fseek(arq, (i - 1) * tamanhoRegistroL(), SEEK_SET);
        atual = leL(arq);
        
        while ((i > 0) && (atual->ISBN > proximo->ISBN)) {
            // Posiciona o cursor no registro "i + 1".
            fseek(arq, i * tamanhoRegistroL(), SEEK_SET);
            salvaL(atual, arq);

            i = i - 1;

            // Le registro "i".
            fseek(arq, (i - 1) * tamanhoRegistroL(), SEEK_SET);
            atual = leL(arq);

            contador++;
            // Registra o numero de trocas realizadas pelo algoritmo no arquivo de log.
            fprintf(log, "\tComparacoes: %d\n", contador);
        }
        // Posiciona cursor no registro "i + 1".
        fseek(arq, i * tamanhoRegistroL(), SEEK_SET);
        // Salva registro "j" na posicao "i".
        salvaL(proximo, arq);

    }
    // Registra o tempo de fim da execucao do ISBNigo.
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calcula o tempo decorrido pelo programa, encontrando a diferenca entre end e start,
    // e, em seguida, divide a diferenca por 1e9 para converter para segundos.
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Registra o tempo de CPU consumido pela aplicacao no arquivo de log.
    fprintf(log, "\n\tThe elapsed time is %f seconds\n", time_spent);

    // Descarrega o buffer para ter certeza que dados foram gravados.
    fflush(arq);
}

// Realiza a ordenacao por insercao em um arquivo contendo registros de usuarios.
void insertionSortU(FILE *arq, FILE *log, int tam) {
    // Registra o tempo de inicio da execucao do codigo.
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Ponteiros para livros.
    TUsuario *atual;
    TUsuario *proximo;
    int i = 0;
    int contador = 0;

    fprintf(log, "\n\tInsertion Sort Usuarios...\n\n");

    // Faz o insertion sort.
    for (int j = 2; j <= tam; j++) {
        // Posiciona o arquivo no registro "j".
        fseek(arq, (j - 1) * tamanhoRegistroU(), SEEK_SET);
        proximo = leU(arq);

        i = j - 1;

        // Posiciona o cursor no registro "i".
        fseek(arq, (i - 1) * tamanhoRegistroU(), SEEK_SET);
        atual = leU(arq);
        
        while ((i > 0) && (atual->ID > proximo->ID)) {
            // Posiciona o cursor no registro "i + 1".
            fseek(arq, i * tamanhoRegistroU(), SEEK_SET);
            salvaU(atual, arq);

            i = i - 1;

            // Le registro "i".
            fseek(arq, (i - 1) * tamanhoRegistroU(), SEEK_SET);
            atual = leU(arq);

            contador++;
            // Registra o numero de trocas realizadas pelo algoritmo no arquivo de log.
            fprintf(log, "\tComparacoes: %d\n", contador);
        }
        // Posiciona cursor no registro "i + 1".
        fseek(arq, i * tamanhoRegistroU(), SEEK_SET);
        // Salva registro "j" na posicao "i".
        salvaU(proximo, arq);

    }
    // Registra o tempo de fim da execucao do ISBNigo.
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calcula o tempo decorrido pelo programa, encontrando a diferenca entre end e start,
    // e, em seguida, divide a diferenca por 1e9 para converter para segundos.
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Registra o tempo de CPU consumido pela aplicacao no arquivo de log.
    fprintf(log, "\n\tThe elapsed time is %f seconds\n", time_spent);

    // Descarrega o buffer para ter certeza que dados foram gravados.
    fflush(arq);
}
