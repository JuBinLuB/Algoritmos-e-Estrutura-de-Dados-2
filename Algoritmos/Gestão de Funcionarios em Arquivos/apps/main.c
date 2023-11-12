#include <stdio.h>
#include <stdlib.h>

#include "funcionario.h"
#include "buscaSequencial.h"
#include "buscaBinaria.h"

int main() {
    // Declaracao de ponteiros para arquivo.
    FILE *arq;
    FILE *log;

    // Declaracao de ponteiro para funcionario.
    TFunc *f;

    // Abre o arquivo.
    if ((arq = fopen("funcionario.dat", "w+b")) == NULL || (log = fopen("log.txt", "w+")) == NULL) {
        printf("\tErro ao abrir arquivo\n");
        exit(1);
    } else {
        criarBase(arq, 1000);
        imprimirBase(arq);

        system("pause");
        system("cls");

        printf("\n\tBusca Sequencial...\n");
        f = buscaSequencial(10, arq, log);
        imprime(f);

        system("pause");
        system("cls");

        printf("\tBusca Binaria...\n\n");
        f = buscaBinaria(10, arq, log, 0, tamanhoArquivo(arq) - 1);
        imprime(f);

        system("pause");
        system("cls");
        free(f);
    }
    return 0;
}
