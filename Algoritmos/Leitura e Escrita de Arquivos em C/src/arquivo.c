#include <stdio.h>
#include <stdlib.h>

// Escrever arquivo de texto.
void writex(char *f, int *vector, int n) {
    FILE *file = fopen(f, "w");

    if (file != NULL) {
        for (int i = 0; i < n; i++) {
            // fprintf e' uma funcao de output para arquivos.
            // 1) O primeiro parametro e' um ponteiro para o arquivo onde iremos escrever.
            // 2) O segundo parametro e' uma string que formata os dados.
            // 3) O ultimo parametro e' de onde virao estes dados.
            fprintf(file, "%d\n", vector[i]);
        }
    }
    fclose(file);
}

// Ler arquivo de texto.
void readx(char *f) {
    FILE *file = fopen(f, "r");
    int value;

    if (file != NULL) {
        while (fscanf(file, "%d", &value) != -1) {
            printf("%d\n", value);
        }
    }
    fclose(file);
}

// Escrever arquivo binario.
void writeb(char *f, int *vector, int n) {
    FILE *file = fopen(f, "wb");

    if (file != NULL) {
        for (int i = 0; i < n; i++) {
            fwrite(&vector[i], sizeof(int), 1, file);
        }
    }
    fclose(file);
}

// Ler arquivo binario.
void readb(char *f) {
    FILE *file = fopen(f, "rb");
    int value;

    if (file != NULL) {
        // A função feof retorna um valor diferente de zero se uma operação de leitura tentou ler após o final do arquivo.
        // Caso contrário, retorna 0.
        while (!feof(file)) {
            if (fread(&value, sizeof(value), 1, file)) {
                printf("%d\n", value);
            }
        }
    }
    fclose(file);
}
