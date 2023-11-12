#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "livro.h"

int main() {
    // Declaracao de ponteiros para arquivo.
    FILE *livro;
    FILE *emprestimo;
    FILE *log;

    // Abre o arquivo.
    if ((livro = fopen("livro.dat", "w+b")) == NULL || 
        (emprestimo = fopen("emprestimo.dat", "w+b")) == NULL || 
        (log = fopen("log.txt", "w+")) == NULL) {
        printf("\tErro ao abrir arquivo\n");
        exit(1);
    } else {
        // Inicia o modulo de menu.
        menuPrincipal(livro, emprestimo, log);
    }
    return 0;
}
