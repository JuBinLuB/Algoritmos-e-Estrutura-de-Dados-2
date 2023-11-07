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
    printf("\n\n\t1. CRIAR BASE DE DADOS");
    printf("  \n\t2. IMPRIMIR");
    printf("  \n\t3. BUSCAR");
    printf("  \n\t4. EMPRESTIMO");
    printf("  \n\t5. ORDENAR");
    printf("  \n\t6. SAIR");
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
void menuPrincipal(FILE *arqFunc, FILE *arqLivro, FILE *log) {
    int opcao = 0;

    do {
        imprimirMenuPrincipal();

        printf("\n\n\tDigite uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            /**
                Codigo para opcao de menu Criar Base de Dados.
            */
            imprimirSubMenu("CRIAR BASE DE DADOS");
            menuCriarBaseDados(arqFunc, arqLivro);
            break;
        case 2:
            /**
                Codigo para opcao de menu Imprimir.
            */
            imprimirSubMenu("IMPRIMIR");
            menuImprimir(arqFunc, arqLivro);
            break;
        case 3:
            /**
                Codigo para opcao de menu Buscar.
            */
            imprimirSubMenu("BUSCAR");
            menuBuscar(arqFunc, arqLivro, log);
            break;
        case 4:
            /**
                Codigo para opcao de menu Emprestimo.
            */
            break;
        case 5:
            /**
                Codigo para opcao de menu Ordenar.
            */
            imprimirSubMenu("ORDENAR");
            menuOrdenar(arqFunc, arqLivro, log);
            break;
        case 6:
            /**
                Codigo para opcao de menu Sair.
            */
            imprimirMensagemSair();
            break;
        default:
            /**
                Codigo para opcao de menu Invalida.
            */
            imprimirMensagemOpcaoInvalida();
        } // Fim do bloco switch.
    } while (opcao != 6);
}

void menuCriarBaseDados(FILE *arqFunc, FILE *arqLivro) {
    int opcao = 0;
    int tam = 0;
    
    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);
    system("cls");

    switch (opcao) {
    case 1:
        printf("\tCriar base de dados de livros...\n\n");
        printf("\n\tInforme o tamanho da base de dados: ");
        fflush(stdin);
        scanf("%d", &tam);

        // Cria uma base de dados contendo "n" livros.
        criarBase(arqLivro, tam);
        break;
    case 2:
        printf("\tCriar base de dados de funcionarios...\n\n");
        printf("\n\tInforme o tamanho da base de dados: ");
        fflush(stdin);
        scanf("%d", &tam);
        
        // Cria uma base de dados contendo "n" funcionarios.
        criarBase(arqFunc, tam);
        break;
    case 3:
        break;
    default:
        // Codigo para opcao de menu Invalida.
        imprimirMensagemOpcaoInvalida();
    }
}

// Funcao de submenu para a opcao de IMPRIMIR.
void menuImprimir(FILE *arqFunc, FILE *arqLivro) {
    int opcao = 0;

    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);
    system("cls");

    switch (opcao) {
    case 1:
        // Codigo para opcao de menu Livro.
        if (tamanhoArquivo(arqLivro) == 0) {
            printf("\n\tBase de dados vazia...\n\n");
        } else {
            imprimirBase(arqLivro);
        }
        system("pause");
        break;
    case 2:
        // Codigo para opcao de menu Funcionario.
        if (tamanhoArquivo(arqFunc) == 0) {
            printf("\n\tBase de dados vazia...\n\n");
        } else {
            imprimirBase(arqFunc);
        }
        system("pause");
        break;
    case 3:
        break;
    default:
        // Codigo para opcao de menu Invalida.
        imprimirMensagemOpcaoInvalida();
    }
}

// Funcao de submenu para a opcao de BUSCAR.
void menuBuscar(FILE *arqFunc, FILE *arqLivro, FILE *log) {
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
        subMenuBuscar(arqFunc, log, "Funcionario");
        system("pause");
        break;
    case 3:
        break;
    default:
        // Codigo para opcao de menu Invalida.
        imprimirMensagemOpcaoInvalida();
    }
}

// Funcao de submenu para a opcao de BUSCA SEQUENCIAL e BUSCA BINARIA.
void subMenuBuscar(FILE *arq, FILE *log, char *str) {
    if (tamanhoArquivo(arq) == 0) {
        system("cls");
        printf("\n\n\tBase de dados vazia.\n\n");
    } else {
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
            fflush(stdin);
            scanf("%d", &codigo);

            f = buscaSequencial(codigo, arq, log);
            
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

            f = buscaBinaria(codigo, arq, log, 0, tamanhoArquivo(arq));

            if (f) {
                imprime(f);
            } else {
                printf("\n\t%s nao encontrado!\n", str);
            }
            break;
        case 3:
            break;
        default:
            // Codigo para opcao de menu Invalida.
            imprimirMensagemOpcaoInvalida();
        }
        free(f);
    }
}

// Funcao de submenu para a opcao de ORDENAR.
void menuOrdenar(FILE *arqFunc, FILE *arqLivro, FILE *log) {
    int opcao = 0;

    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);
    system("cls");

    switch (opcao) {
    case 1:
        // Codigo para opcao de menu Ordenar Livro.
        if (tamanhoArquivo(arqLivro) == 0) {
            printf("\n\tBase de dados vazia.\n\n");
        } else {
            printf("\n\tOrdenando arquivo...\n\n");
            insertionSort(arqLivro, log, tamanhoArquivo(arqLivro));
            system("cls");
            printf("\n\tArquivo ordenado.\n\n");
        }
        system("pause");
        break;
    case 2:
        // Codigo para opcao de menu Ordenar Funcionario.
        if (tamanhoArquivo(arqFunc) == 0) {
            printf("\n\tBase de dados vazia.\n\n");
        } else {
            printf("\n\tOrdenando arquivo...\n\n");
            insertionSort(arqFunc, log, tamanhoArquivo(arqFunc));
            system("cls");
            printf("\n\tArquivo ordenado.\n\n");
        }
        system("pause");
        break;
    case 3:
        break;
    default:
        // Codigo para opcao de menu Invalida.
        imprimirMensagemOpcaoInvalida();
    }
}
