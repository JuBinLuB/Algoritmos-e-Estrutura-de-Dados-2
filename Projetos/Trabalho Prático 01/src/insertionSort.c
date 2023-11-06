#include <stdio.h>
#include <stdlib.h>

#include "insertionSort.h"
#include "funcionario.h"

// Realiza a ordenacao por insercao em um arquivo contendo registros de funcionarios.
void insertionSort(FILE *arq, int tam) {
    // Ponteiros para funcionarios.
    TFunc *atual;
    TFunc *proximo;
    int i = 0;

    // Faz o insertion sort.
    for (int j = 2; j <= tam; j++) {
        // Posiciona o arquivo no registro "j".
        fseek(arq, (j - 1) * tamanhoRegistro(), SEEK_SET);
        proximo = le(arq);

        i = j - 1;
        
        // Posiciona o cursor no registro "i".
        fseek(arq, (i - 1) * tamanhoRegistro(), SEEK_SET);
        atual = le(arq);
        
        while ((i > 0) && (atual->cod > proximo->cod)) {
            // Posiciona o cursor no registro "i + 1".
            fseek(arq, i * tamanhoRegistro(), SEEK_SET);
            salva(atual, arq);
            
            i = i - 1;
            
            // Le registro "i".
            fseek(arq, (i - 1) * tamanhoRegistro(), SEEK_SET);
            atual = le(arq);
        }
        // Posiciona cursor no registro "i + 1".
        fseek(arq, i * tamanhoRegistro(), SEEK_SET);
        // Salva registro "j" na posicao "i".
        salva(proximo, arq);
    }
    // Descarrega o buffer para ter certeza que dados foram gravados.
    fflush(arq);
}
