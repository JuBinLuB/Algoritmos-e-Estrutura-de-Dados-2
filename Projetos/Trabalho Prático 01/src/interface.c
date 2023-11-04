#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "livro.h"
#include "funcionario.h"
#include "buscaSequencial.h"
#include "buscaBinaria.h"
#include "ordenarArquivo.h"

void MSG_MENU() {
    system("cls");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\n\t1. IMPRIMIR");
    printf("  \n\t2. BUSCAR");
    printf("  \n\t3. EMPRESTIMO");
    printf("  \n\t4. ORDENAR");
    printf("  \n\t5. SAIR");
}

void MSG_SUB_MENU(char *str) {
    system("cls");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU %s <<<<<<<<<<<<<<<<<<<<<<<<", str);
    printf("  \n\t1. LIVRO");
    printf("  \n\t2. FUNCIONARIO");
    printf("  \n\t3. VOLTAR");
}

void MSG_SUB_MENU_BUSCAR() {
    system("cls");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE BUSCA <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("  \n\t1. BUSCA SEQUENCIAL");
    printf("  \n\t2. BUSCA BINARIA");
    printf("  \n\t3. VOLTAR");
}

void MSG_OPCAO_INVALIDA() {
    system("cls");
    printf("\n\n\n\t >>>>>> MSG: Digite uma opcao valida!!! <<<<<<\n");
    system("pause");
}

void MSG_SAIR() {
    system("cls");
    printf("\n\n\n\t >>>>>> MSG: Saindo do MODULO...!!! <<<<<<\n");
    system("pause");
}

void MENU(FILE *arq, FILE *livro, FILE *log) {
    int opcao = 0;

    do {
        MSG_MENU();
        printf("\n\n\tDigite uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            /**
                Codigo para opcao de menu Imprimir.
            */
            MENU_IMPRIMIR(arq, livro);
            break;
        case 2:
            /**
                Codigo para opcao de menu Buscar.
            */
            MENU_BUSCAR(arq, livro, log);
            break;
        case 3:
            /**
                Codigo para opcao de menu Emprestimo.
            */
            break;
        case 4:
            /**
                Codigo para opcao de menu Ordenar.
            */
            MENU_ORDENAR(arq, livro);
            break;
        case 6:
            MSG_SAIR();
            break;
        default:
            MSG_OPCAO_INVALIDA();
        } // Fim do bloco switch.
    } while (opcao != 5);
}

void MENU_IMPRIMIR(FILE *arq, FILE *livro) {
    int opcao = 0;

    MSG_SUB_MENU("IMPRIMIR");
    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
        /**
            Codigo para opcao de menu Livro.
        */
        imprimirBase(livro);
        system("pause");
        break;
    case 2:
        /**
            Codigo para opcao de menu Funcionario.
        */
        imprimirBase(arq);
        system("pause");
        break;
    case 3:
        MSG_SAIR();
        break;
    default:
        MSG_OPCAO_INVALIDA();
    }
}

void MENU_ORDENAR(FILE *arq, FILE *livro) {
    int opcao = 0;

    MSG_SUB_MENU("ORDENAR");
    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
        /**
            Codigo para opcao de menu Ordenar Livro.
        */
        selectionSort(livro, tamanhoArquivo(livro));
        break;
    case 2:
        /**
            Codigo para opcao de menu Ordenar Funcionario.
        */
        selectionSort(arq, tamanhoArquivo(arq));
        break;
    case 3:
        MSG_SAIR();
        break;
    default:
        MSG_OPCAO_INVALIDA();
    }
}

void MENU_BUSCAR(FILE *arq, FILE *livro, FILE *log) {
    int opcao = 0;

    MSG_SUB_MENU("BUSCAR");
    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
        /**
            Codigo para opcao de menu Buscar Livro.
        */
        SUB_MENU_BUSCAR(livro, log, "Livro");
        system("pause");
        break;
    case 2:
        /**
            Codigo para opcao de menu Buscar Funcionario.
        */
        SUB_MENU_BUSCAR(arq, log, "Funcionario");
        system("pause");
        break;
    case 3:
        MSG_SAIR();
        break;
    default:
        MSG_OPCAO_INVALIDA();
    }
}

void SUB_MENU_BUSCAR(FILE *arq, FILE *log, char *str) {
    TFunc *f = NULL;
    int opcao = 0;
    int codigo = 0;

    MSG_SUB_MENU_BUSCAR();
    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);
    system("cls");

    switch (opcao) {
    case 1:
        /**
            Codigo de menu Buscar Sequencial.
        */
        printf("\n\tBusca Sequencial...\n");
        printf("\n\tDigite o codigo: ");
        scanf("%d", &codigo);

        f = buscaSequencial(codigo, arq, log);

        if (f) {
            imprime(f);
        } else {
            printf("\n\t%s nao encontrado!\n", str);
        }
        break;
    case 2:
        /**
            Codigo de menu Buscar Binario.
        */
        printf("\n\tBusca Binaria...\n");
        printf("\n\tDigite o codigo: ");
        scanf("%d", &codigo);

        f = buscaBinaria(codigo, arq, log, 0, tamanhoArquivo(arq) - 1);

        if (f) {
            imprime(f);
        } else {
            printf("\n\t%s nao encontrado.\n", str);
        }
        break;
    case 3:
        MSG_SAIR();
        break;
    default:
        MSG_OPCAO_INVALIDA();
    }
    free(f);
}
