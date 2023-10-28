#include <stdio.h>
#include <stdlib.h>

#include "funcionario.h"
#include "buscasequencial.h"
#include "buscaBinaria.h"

int main() {
    // Declara um ponteiro para arquivo.
    FILE *arq;
    FILE *log;

    // Declara um ponteiro para funcionario.
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

        printf("\tBusca Binaria...\n\n");
        f = buscaBinaria(10, arq, log, 0, tamanhoArquivo(arq) - 1);
        imprime(f);

        free(f);

        /*
        int codigo;
        double salario;

        // 1) Inserindo 50 funcionarios no arquivo, ordenados pelo codigo.
        for (int i = 0; i < 50; i++) {
            // Gerando valores aleatorios para a variavel salario atraves da funcao rand().
            salario = rand() % 20000;
            f = funcionario(i + 1, "Ana", "000.000.000-00", "01/01/1980", salario);
            salva(f, arq);
        }

        // Imprimindo os funcionarios inseridos.
        rewind(arq);

        while ((f = le(arq)) != NULL) {
            imprime(f);
        }

        system("pause");
        system("cls");

        // 2) Busca sequencial dos funcionarios atraves do codigo.
        system("cls");
        printf("\n\tBuscando um funcionario no arquivo...\n\n");
        f = busca_sequencial_cod(4, arq);

        if (f != NULL) {
            printf("\n\tFuncionario encontrado:\n\n");
            imprime(f);
        } else {
            printf("\n\tFuncionario nao encontrado...\n\n");
        }

        system("pause");
        system("cls");

        // 3) Inserindo 50 funcionarios no arquivo, desordenados pelo codigo.
        for (int i = 0; i < 50; i++) {
            // Gerando valores aleatorios para as variaveis codigo e salario atraves da funcao rand().
            // Para a variavel codigo sao gerados valores entre 6 e 505.
            codigo = 6 + rand() % 500;
            salario = rand() % 20000;

            // Sobrescrevendo "n" funcionarios, pulando de registro em registro.
            // fseek esta pulando "i" registros, posicionando o cursor no inicio de cada registro.
            fseek(arq, tamanho_registro() * i, SEEK_SET);

            f = funcionario(codigo, "Ana", "000.000.000-00", "01/01/1980", salario);
            salva(f, arq);
        }

        // Sobrescrevendo os 5 primeiros funcionarios.
        fseek(arq, tamanho_registro() * 0, SEEK_SET);
        f = funcionario(713, "Ana", "000.000.000-00", "01/01/1980", 3000);
        salva(f, arq);

        fseek(arq, tamanho_registro() * 1, SEEK_SET);
        f = funcionario(550, "Carlos", "111.111.111-11", "01/01/1990", 500);
        salva(f, arq);

        fseek(arq, tamanho_registro() * 2, SEEK_SET);
        f = funcionario(534, "Fatima", "222.222.222-22", "02/02/1980", 1000);
        salva(f, arq);

        fseek(arq, tamanho_registro() * 3, SEEK_SET);
        f = funcionario(673, "Marcelo", "333.333.333-33", "03/03/1990", 1500);
        salva(f, arq
        fseek(arq, tamanho_registro() * 4, SEEK_SET);
        f = funcionario(599, "Silvia", "444.444.444-44", "04/04/1980", 900);
        salva(f, arq);

        // Imprimindo os funcionarios inseridos.
        rewind(arq);

        while ((f = le(arq)) != NULL) {
            imprime(f);
        }

        system("pause");
        system("cls");

        // 4) Busca sequencial dos funcionarios atraves do nome.
        system("cls");
        printf("\n\tBuscando um funcionario no arquivo...\n\n");
        f = busca_sequencial_func("Silvia", arq);

        if (f != NULL) {
            printf("\n\tFuncionario encontrado:\n\n");
            imprime(f);
        } else {
            printf("\n\tFuncionario nao encontrado...\n\n");
        }
        */
        system("pause");
        system("cls");
    }
    return 0;
}
