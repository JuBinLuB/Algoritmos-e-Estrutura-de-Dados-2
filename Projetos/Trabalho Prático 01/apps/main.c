#include <stdio.h>
#include <stdlib.h>

#include "interface.h"

int main() {
    // Declaracao de ponteiros para arquivo.
    FILE *arq;
    FILE *livro;
    FILE *log;

    // Abre o arquivo.
    if ((arq = fopen("funcionario.dat", "w+b")) == NULL || 
        (log = fopen("log.txt", "w+")) == NULL || 
        (livro = fopen("livro.dat", "w+b")) == NULL) {
        printf("\tErro ao abrir arquivo\n");
        exit(1);
    } else {
        // Cria uma base de dados contendo 1000 funcionarios.
        criarBase(arq, 1000);

        // Inicia o modulo de menu.
        menuPrincipal(arq, livro, log);
    }
    return 0;
}
