#include <stdio.h>
#include <stdlib.h>

#include "funcionario.h"
#include "buscaSequencial.h"
#include "buscaBinaria.h"
#include "ordenarArquivo.h"
#include "interface.h"

// Aplicacao para gerenciamento de uma biblioteca.
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
        f = buscaSequencial(50, arq, log);
        if (f) {
            imprime(f);
        } else {
            printf("\n\tFuncionario nao encontrado!\n");
        }
        
        system("pause");
        system("cls");

        // Ordena o arquivo de registros armazenados num arquivo binario em ordem crescente de codigo.
        selectionSort(arq, tamanhoArquivo(arq));
        imprimirBase(arq);

        system("pause");
        system("cls");
        
        // Teste da busca binaria.
        printf("\n\tBusca Binaria...\n");
        f = buscaBinaria(50, arq, log, 0, tamanhoArquivo(arq) - 1);
        if (f) {
            imprime(f);
        } else {
            printf("\n\tFuncionario nao encontrado.\n");
        }
        free(f);
    }
    return 0;
}
