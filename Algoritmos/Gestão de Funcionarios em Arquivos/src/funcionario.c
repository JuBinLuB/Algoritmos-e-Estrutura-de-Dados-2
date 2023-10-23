#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "funcionario.h"

// Retorna tamanho do funcionario em bytes.
int tamanho_registro() {
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //cpf
           + sizeof(char) * 11 //data_nascimento
           + sizeof(double); //salario
}

// Cria funcionario.
TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    //inicializa espaco de memoria com ZEROS
    if (func) memset(func, 0, sizeof(TFunc));
    //copia valores para os campos de func
    func->cod = cod;
    strcpy(func->nome, nome);
    strcpy(func->cpf, cpf);
    strcpy(func->data_nascimento, data_nascimento);
    func->salario = salario;
    return func;
}

// Salva funcionario no arquivo out, na posicao atual do cursor.
void salva(TFunc *func, FILE *out) {
    fwrite(&func->cod, sizeof(int), 1, out);
    //func->nome ao inves de &func->nome, pois string ja eh um ponteiro
    fwrite(func->nome, sizeof(char), sizeof(func->nome), out);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), out);
    fwrite(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), out);
    fwrite(&func->salario, sizeof(double), 1, out);
}

// Le um funcionario do arquivo in na posicao atual do cursor.
// Retorna um ponteiro para funcionario lido do arquivo.
TFunc *le(FILE *in) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    if (0 >= fread(&func->cod, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), in);
    fread(&func->salario, sizeof(double), 1, in);
    return func;
}

// Imprime funcionario.
void imprime(TFunc *func) {
    printf("\t**********************************************");
    printf("\n\tFuncionario de codigo ");
    printf("%d", func->cod);
    printf("\n\tNome: ");
    printf("%s", func->nome);
    printf("\n\tCPF: ");
    printf("%s", func->cpf);
    printf("\n\tData de Nascimento: ");
    printf("%s", func->data_nascimento);
    printf("\n\tSalario: ");
    printf("%4.2f", func->salario);
    printf("\n\t**********************************************\n\n");
}

/*
TFunc *busca_sequencial_cod(int chave, FILE *out) {
    TFunc *f;
    int encontrado = 0;
    int contador = 0;

    rewind(out);
    while ((f = le(out)) != NULL) {
        if (f->cod == chave) {
            encontrado = 1;
            break;
        } else {
            contador++;
        }
        printf("\tComparacoes: %d\n", contador);
    }
    if (encontrado) {
        return f;
    }
    return NULL;
}

TFunc *busca_sequencial_func(char *nome, FILE *out) {
    TFunc *f;
    int encontrado = 0;
    int contador = 0;

    rewind(out);
    while ((f = le(out)) != NULL) {
        if (strcmp(nome, f->nome) == 0) {
            encontrado = 1;
            break;
        } else {
            contador++;
        }
        printf("\tComparacoes: %d\n", contador);
    }
    if (encontrado) {
        return f;
    }
    return NULL;
}
*/

// Cria base de dados.
void criarBase(FILE *out, int tam) {
    int vet[tam];
    TFunc *f;

    for (int i = 0; i < tam; i++) {
        vet[i] = i + 1;
    }

    //suffle(vet, tam, (tam * 60) / 100)

    printf("\nGerando a base de dados...\n");
    for (int i = 9; i < tam; i++) {
        f = funcionario(vet[i], "A", "000.000.000-00", "01/01/1990", 3000 * i);
        salva(f, out);
    }
    free(f);
}

// Embaralha base de dados.
void shuffle(int *vet, int MAX, int MIN) {
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i++) {
        int j = rand() % (i);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

// Imprime a base de dados.
void imprimirBase(FILE *out) {
    printf("\nImprimindo a base de dados...\n");

    rewind(out);
    TFunc *f;

    while ((f = le(out)) != NULL) {
        imprime(f);
    }
    free(f);
}
