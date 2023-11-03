#include <stdio.h>
#include <stdlib.h>

#include "funcionario.h"
#include "buscaSequencial.h"
#include "buscaBinaria.h"
#include "ordenarArquivo.h"
#include "interface.h"

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
        // Cria uma base de dados contendo 1000 funcionarios.
        criarBase(arq, 1000);
        imprimirBase(arq);

        system("pause");
        system("cls");

        // Teste da busca sequencial.
        printf("\n\tBusca Sequencial...\n");
        f = buscaSequencial(780, arq, log);
        if (f) {
            imprime(f);
        } else {
            printf("\n\tFuncionario nao encontrado!\n");
        }

        // Ordena o arquivo de registros em ordem crescente de código.
        ordenarArquivo(arq, tamanhoArquivo(arq));
        
        // Teste da busca binaria.
        printf("\n\tBusca Binaria...\n");
        f = buscaBinaria(780, arq, log, 0, tamanhoArquivo(arq) - 1);
        if (f) {
            imprime(f);
        } else {
            printf("\n\tFuncionario nao encontrado.\n");
        }
        free(f);
    }
    return 0;
}
