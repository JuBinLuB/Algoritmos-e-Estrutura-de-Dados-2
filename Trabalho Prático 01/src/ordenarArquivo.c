#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ordenarArquivo.h"
#include "funcionario.h"

void ordenarArquivo(FILE *arq, int tam) {
    TFunc *atual;
    TFunc *menor;
    TFunc *proximo;

    for (int i = 1; i < tam; i++) {
        fseek(arq, (i - 1) * tamanhoRegistro(), SEEK_SET);
        atual = le(arq);
        fseek(arq, i * tamanhoRegistro(), SEEK_SET);
        menor = le(arq);

        int posicaoMenor = i + 1;

        for (int j = i + 2; j <= tam; j++) {
            proximo = le(arq);
            if (proximo->cod < menor->cod) {
                menor = proximo;
                posicaoMenor = j;
            }
        }
        if (menor->cod < atual->cod) {
            fseek(arq, (posicaoMenor - 1) * tamanhoRegistro(), SEEK_SET);
            salva(atual, arq);
            fseek(arq, (i - 1) * tamanhoRegistro(), SEEK_SET);
            salva(menor, arq);
        }
    }
    fflush(arq);
}
