#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "funcionario.h"

int main() {
    // Armazena o tempo de execução do código.
    double time_spent = 0.0;
 
    clock_t begin = clock();

    sleep(3);

    // Declara ponteiro para arquivo.
    FILE *out;

    // Declara funcao para gerar numeros aleatorios.
    srand(time(NULL));

    // Abre arquivo
    if ((out = fopen("funcionario.dat", "w+b")) == NULL) {
        printf("\tErro ao abrir arquivo\n");
        exit(1);
    } else {
        TFunc *f;
        int codigo;
        double salario;

        // 1) Inserindo 50 funcionarios no arquivo, ordenados pelo codigo.
        for (int i = 0; i < 50; i++) {
            // Gerando valores aleatorios para a variavel salario atraves da funcao rand().
            salario = rand() % 20000;
            f = funcionario(i + 1, "Ana", "000.000.000-00", "01/01/1980", salario);
            salva(f, out);
        }

        // Imprimindo os funcionarios inseridos.
        rewind(out);

        while ((f = le(out)) != NULL) {
            imprime(f);
        }

        system("pause");
        system("cls");

        // 2) Busca sequencial dos funcionarios atraves do codigo.
        system("cls");
        printf("\n\tBuscando um funcionario no arquivo...\n\n");
        f = busca_sequencial_cod(4, out);

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
            fseek(out, tamanho_registro() * i, SEEK_SET);
            
            f = funcionario(codigo, "Ana", "000.000.000-00", "01/01/1980", salario);
            salva(f, out);
        }

        // Sobrescrevendo os 5 primeiros funcionarios.
        fseek(out, tamanho_registro() * 0, SEEK_SET);
        f = funcionario(713, "Ana", "000.000.000-00", "01/01/1980", 3000);
        salva(f, out);

        fseek(out, tamanho_registro() * 1, SEEK_SET);
        f = funcionario(550, "Carlos", "111.111.111-11", "01/01/1990", 500);
        salva(f, out);

        fseek(out, tamanho_registro() * 2, SEEK_SET);
        f = funcionario(534, "Fatima", "222.222.222-22", "02/02/1980", 1000);
        salva(f, out);

        fseek(out, tamanho_registro() * 3, SEEK_SET);
        f = funcionario(673, "Marcelo", "333.333.333-33", "03/03/1990", 1500);
        salva(f, out);

        fseek(out, tamanho_registro() * 4, SEEK_SET);
        f = funcionario(599, "Silvia", "444.444.444-44", "04/04/1980", 900);
        salva(f, out);
        
        // Imprimindo os funcionarios inseridos.
        rewind(out);

        while ((f = le(out)) != NULL) {
            imprime(f);
        }

        system("pause");
        system("cls");
        
        // 4) Busca sequencial dos funcionarios atraves do nome.
        system("cls");
        printf("\n\tBuscando um funcionario no arquivo...\n\n");
        f = busca_sequencial_func("Silvia", out);

        if (f != NULL) {
            printf("\n\tFuncionario encontrado:\n\n");
            imprime(f);
        } else {
            printf("\n\tFuncionario nao encontrado...\n\n");
        }

        system("pause");
        system("cls"); 
    }
    clock_t end = clock();

    // Calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos.
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    
    // Exibindo o tempo de CPU consumido pela aplicacao.
    printf("The elapsed time is %f seconds\n", time_spent);
    system("pause");
    system("cls");
    return 0;
}
