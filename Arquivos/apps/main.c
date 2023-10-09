#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

int main(void) {
    // Alocando espaco para o nome do arquivo.
    char file_name[20];

    // Dados a serem escritos no arquivo.
    int vector[5] = {2, 4, 6, 8, 10};
    
    // Copia para a string "file_name" o nome e extensao do arquivo a ser criado.
    strcpy(file_name, "testex.txt");

    // 1. Teste Escrever e Ler Texto.
    // Escreve os dados em um arquivo txt.
    writex(file_name, vector, 5);

    // Efetua a leitura dos dados do arquivo "txt" e imprime seu conteudo no console.
    readx(file_name);
    printf("\n");

    // 2. Teste Escrever e Ler Binario.
    strcpy(file_name, "testeb.dat");

    // Escreve os dados em um arquivo dat.
    writeb(file_name, vector, 5);

    // Efetua a leitura dos dados do arquivo "dat" e imprime seu conteudo no console.
    readb(file_name);

    return 0;
}
