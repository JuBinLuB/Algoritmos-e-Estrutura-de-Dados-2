#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "selectionSort.h"
#include "livro.h"

// Realiza a ordenacao por selecao em um arquivo contendo registros de livros.
void selectionSort(FILE *arq, FILE *log, int tam) {
    // Registra o tempo de inicio da execucao do codigo.
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Ponteiros para registros de livros.
    TLivro *atual;
    TLivro *menor;
    TLivro *proximo;

    for (int i = 1; i < tam; i++) {
        // Define a posicao do registro atual.
        fseek(arq, (i - 1) * tamanhoRegistro(), SEEK_SET);
        // Le o registro atual.
        atual = le(arq);
        // Assume que o menor registro esta na posicao atual.
        menor = atual;

        int posicaoMenor = i;

        for (int j = i + 1; j <= tam; j++) {
            // Define a posicao do registro a ser comparado.
            fseek(arq, (j - 1) * tamanhoRegistro(), SEEK_SET);
            // Le o registro a ser comparado.
            proximo = le(arq);

            // Verifica se o registro comparado e' menor que o menor registro atual.
            if (proximo->ISBN < menor->ISBN) {
                // Atualiza o registro menor e sua posicao.
                menor = proximo;
                posicaoMenor = j;
            }
        }
        if (menor->ISBN < atual->ISBN) {
            // Troca os registros no arquivo.
            fseek(arq, (posicaoMenor - 1) * tamanhoRegistro(), SEEK_SET);
            // Salva o registro atual na posicao do menor registro.
            salva(atual, arq);
            fseek(arq, (i - 1) * tamanhoRegistro(), SEEK_SET);
            // Salva o menor registro na posicao do registro atual.
            salva(menor, arq);
        }
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
