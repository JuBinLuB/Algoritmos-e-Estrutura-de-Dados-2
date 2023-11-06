#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "funcionario.h"
#include "buscaSequencial.h"
#include "buscaBinaria.h"
#include "insertionSort.h"

// Funcao para imprimir o menu principal.
void imprimirMenuPrincipal() {
    system("cls");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\n\t1. IMPRIMIR");
    printf("  \n\t2. BUSCAR");
    printf("  \n\t3. EMPRESTIMO");
    printf("  \n\t4. ORDENAR");
    printf("  \n\t5. SAIR");
}

// Funcao para imprimir submenu com opcoes especificas.
void imprimirSubMenu(char *str) {
    system("cls");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU %s <<<<<<<<<<<<<<<<<<<<<<<<", str);
    printf("\n\n\t1. LIVRO");
    printf("  \n\t2. FUNCIONARIO");
    printf("  \n\t3. VOLTAR");
}

// Funcao para imprimir mensagem para imprimir o submenu de busca.
void imprimirSubMenuBuscar() {
    system("cls");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE BUSCA <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\n\t1. BUSCA SEQUENCIAL");
    printf("  \n\t2. BUSCA BINARIA");
    printf("  \n\t3. VOLTAR");
}

// Funcao para imprimir mensagem de opcao invalida.
void imprimirMensagemOpcaoInvalida() {
    system("cls");
    printf("\n\n\n\t >>>>>> MSG: Digite uma opcao valida!!! <<<<<<\n");
    system("pause");
}

// Funcao para imprimir mensagem de saida.
void imprimirMensagemSair() {
    system("cls");
    printf("\n\n\n\t >>>>>> MSG: Saindo do MODULO...!!! <<<<<<\n");
    system("pause");
}

// Funcao de menu principal.
void menuPrincipal(FILE *arqFuncionario, FILE *arqLivro, FILE *log) {
    int opcao = 0;

    do {
        imprimirMenuPrincipal();
        printf("\n\n\tDigite uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            /**
                Codigo para opcao de menu Imprimir.
            */
            imprimirSubMenu("IMPRIMIR");
            menuImprimir(arqFuncionario, arqLivro);
            break;
        case 2:
            /**
                Codigo para opcao de menu Buscar.
            */
            imprimirSubMenu("BUSCAR");
            menuBuscar(arqFuncionario, arqLivro, log);
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
            imprimirSubMenu("ORDENAR");
            menuOrdenar(arqFuncionario, arqLivro, log);
            break;
        case 5:
            imprimirMensagemSair();
            break;
        default:
            imprimirMensagemOpcaoInvalida();
        } // Fim do bloco switch.
    } while (opcao != 5);
}

// Funcao de submenu para a opcao de IMPRIMIR.
void menuImprimir(FILE *arqFuncionario, FILE *arqLivro) {
    int opcao = 0;

    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
        // Codigo para opcao de menu Livro.
        imprimirBase(arqLivro);
        system("pause");
        break;
    case 2:
        // Codigo para opcao de menu Funcionario.
        imprimirBase(arqFuncionario);
        system("pause");
        break;
    case 3:
        break;
    default:
        imprimirMensagemOpcaoInvalida();
    }
}

// Funcao de submenu para a opcao de BUSCAR.
void menuBuscar(FILE *arqFuncionario, FILE *arqLivro, FILE *log) {
    int opcao = 0;

    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
        // Codigo para opcao de menu Buscar Livro.
        imprimirSubMenuBuscar();
        subMenuBuscar(arqLivro, log, "Livro");
        system("pause");
        break;
    case 2:
        // Codigo para opcao de menu Buscar Funcionario.
        imprimirSubMenuBuscar();
        subMenuBuscar(arqFuncionario, log, "Funcionario");
        system("pause");
        break;
    case 3:
        break;
    default:
        imprimirMensagemOpcaoInvalida();
    }
}

// Funcao de submenu para a opcao de BUSCA SEQUENCIAL e BUSCA BINARIA.
void subMenuBuscar(FILE *arqFuncionario, FILE *log, char *str) {
    TFunc *f = NULL;
    int opcao = 0;
    int codigo = 0;

    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);
    system("cls");

    switch (opcao) {
    case 1:
        // Codigo de menu Buscar Sequencial.
        printf("\n\tBusca Sequencial...\n");
        printf("\n\tDigite o codigo: ");
        scanf("%d", &codigo);

        f = buscaSequencial(codigo, arqFuncionario, log);

        if (f) {
            imprime(f);
        } else {
            printf("\n\t%s nao encontrado!\n", str);
        }
        break;
    case 2:
        // Codigo de menu Buscar Binario.
        printf("\n\tBusca Binaria...\n");
        printf("\n\tDigite o codigo: ");
        scanf("%d", &codigo);

        f = buscaBinaria(codigo, arqFuncionario, log, 0, tamanhoArquivo(arqFuncionario));

        if (f) {
            imprime(f);
        } else {
            printf("\n\t%s nao encontrado.\n", str);
        }
        break;
    case 3:
        break;
    default:
        imprimirMensagemOpcaoInvalida();
    }
    free(f);
}

// Funcao de submenu para a opcao de ORDENAR.
void menuOrdenar(FILE *arqFuncionario, FILE *arqLivro, FILE *log) {
    int opcao = 0;

    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
        // Codigo para opcao de menu Ordenar Livro.
        insertionSort(arqLivro, log, tamanhoArquivo(arqLivro));
        break;
    case 2:
        // Codigo para opcao de menu Ordenar Funcionario.
        insertionSort(arqFuncionario, log, tamanhoArquivo(arqFuncionario));
        break;
    case 3:
        break;
    default:
        imprimirMensagemOpcaoInvalida();
    }
}
