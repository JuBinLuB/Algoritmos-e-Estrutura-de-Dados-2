#include <stdio.h>
#include <stdlib.h>

#include "selectionSort.h"
#include "funcionario.h"

// Realiza a ordenacao por selecao em um arquivo contendo registros de funcionarios.
void selectionSort(FILE *arq, int tam) {
    // Ponteiros para registros de funcionarios.
    TFunc *atual;
    TFunc *menor;
    TFunc *proximo;

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
            if (proximo->cod < menor->cod) {
                // Atualiza o registro menor e sua posicao.
                menor = proximo;
                posicaoMenor = j;
            }
        }
        if (menor->cod < atual->cod) {
            // Troca os registros no arquivo.
            fseek(arq, (posicaoMenor - 1) * tamanhoRegistro(), SEEK_SET);
            // Salva o registro atual na posicao do menor registro.
            salva(atual, arq);
            fseek(arq, (i - 1) * tamanhoRegistro(), SEEK_SET);
            // Salva o menor registro na posicao do registro atual.
            salva(menor, arq);
        }
    }
    // Descarrega o buffer para ter certeza que dados foram gravados.
    fflush(arq);
}
