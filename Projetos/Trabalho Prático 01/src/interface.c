#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "livro.h"
#include "usuario.h"
#include "buscaSequencial.h"
#include "buscaBinaria.h"
#include "insertionSort.h"
#include "emprestimo.h"
#include "classificacao.h"

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

// Funcao para imprimir mensagem de submenu de criar base de dados.
void imprimirSubMenuCriarBase() {
    system("cls");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU CRIAR BASE DE DADOS <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\n\t1. BASE ORDENADA");
    printf("  \n\t2. BASE DESORDENADA");
    printf("  \n\t3. VOLTAR");
}

// Funcao para imprimir submenu com opcoes especificas.
void imprimirSubMenu(char *str) {
    system("cls");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU %s <<<<<<<<<<<<<<<<<<<<<<<<", str);
    printf("\n\n\t1. LIVRO");
    printf("  \n\t2. EMPRESTIMO");
    printf("  \n\t3. VOLTAR");
}

// Funcao para imprimir mensagem de submenu de busca.
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
void menuPrincipal(FILE *arqLivros, FILE *arqEmprestimos, FILE *log) {
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
            imprimirSubMenuCriarBase();
            menuCriarBaseDados(arqLivros);
            break;
        case 2:
            /**
                Codigo para opcao de menu Imprimir.
            */
            imprimirSubMenu("IMPRIMIR");
            menuImprimir(arqLivros, arqEmprestimos);
            break;
        case 3:
            /**
                Codigo para opcao de menu Buscar.
            */
            imprimirSubMenu("BUSCAR");
            menuBuscar(arqLivros, arqEmprestimos, log);
            break;
        case 4:
            /**
                Codigo para opcao de menu Emprestimo.
            */
            if (tamanhoArquivoL(arqLivros) == 0) {
                printf("\n\tBase de dados vazia...\n\n");
            } else {
                system("cls");
                printf("\n\tEmprestimo...\n");
                realizarEmprestimo(arqLivros, arqEmprestimos);
                system("pause");
            }
            break;
        case 5:
            /**
                Codigo para opcao de menu Ordenar.
            */
            imprimirSubMenu("ORDENAR");
            menuOrdenar(arqLivros, arqEmprestimos, log);
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

void menuCriarBaseDados(FILE *arq) {
    int opcao = 0;
    int tam = 0;

    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);
    system("cls");

    switch (opcao) {
    case 1:
        // Codigo para opcao de menu criar base ordenada.
        printf("\tCriando base de dados ordenada de livros...\n");
        printf("\n\tInforme o tamanho da base de dados: ");
        fflush(stdin);
        scanf("%d", &tam);
        
        // Cria uma base de dados ordenada contendo "tam" livros.
        criarBaseOrdenada(arq, tam);
        break;
    case 2:
        // Codigo para opcao de menu criar base ordenada.
        printf("\tCriando base de dados nao ordenada de livros...\n");
        printf("\n\tInforme o tamanho da base de dados: ");
        fflush(stdin);
        scanf("%d", &tam);

        // Cria uma base de dados nao ordenada contendo "tam" livros.
        criarBase(arq, tam);
        break;
    case 3:
        break;
    default:
        imprimirMensagemOpcaoInvalida();
    }
}

// Funcao de submenu para a opcao de IMPRIMIR.
void menuImprimir(FILE *arqLivros, FILE *arqEmprestimos) {
    int opcao = 0;

    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);
    system("cls");

    switch (opcao) {
    case 1:
        // Codigo para opcao de menu Livro.
        if (tamanhoArquivoL(arqLivros) == 0) {
            printf("\n\tBase de dados vazia...\n\n");
        } else {
            imprimirBaseL(arqLivros);
        }
        system("pause");
        break;
    case 2:
        // Codigo para opcao de menu Emprestimo.
        if (tamanhoArquivoU(arqEmprestimos) == 0) {
            printf("\n\tNao houve emprestimos...\n\n");
        } else {
            imprimirBaseU(arqEmprestimos);
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
void menuBuscar(FILE *arqLivros, FILE *arqEmprestimos, FILE *log) {
    int opcao = 0;

    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
        // Codigo para opcao de menu Buscar Livro.
        imprimirSubMenuBuscar();
        subMenuBuscarLivro(arqLivros, log);
        system("pause");
        break;
    case 2:
        // Codigo para opcao de menu Buscar Emprestimo.
        imprimirSubMenuBuscar();
        subMenuBuscarEmprestimo(arqEmprestimos, log);
        system("pause");
        break;
    case 3:
        break;
    default:
        // Codigo para opcao de menu Invalida.
        imprimirMensagemOpcaoInvalida();
    }
}

// Funcao de submenu para a opcao de Busca Sequencial.
void subMenuBuscarLivro(FILE *arqLivros, FILE* log) {
    if (tamanhoArquivoL(arqLivros) == 0) {
        system("cls");
        printf("\n\tBase de dados vazia...\n\n");
    } else {
        TLivro *livro = NULL;
        int opcao = 0;
        int ISBN = 0;

        printf("\n\n\tDigite uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);
        system("cls");

        switch (opcao) {
        case 1:
            // Codigo de menu Buscar Sequencial.
            printf("\n\tBusca Sequencial...\n");
            printf("\n\tDigite o ISBN: ");
            fflush(stdin);
            scanf("%d", &ISBN);

            livro = buscaSequencialL(ISBN, arqLivros, log);
            
            if (livro) {
                imprimeL(livro);
            } else {
                printf("\n\tLivro nao encontrado!\n");
            }
            break;
        case 2:
            // Codigo de menu Buscar Binario.
            printf("\n\tBusca Binaria...\n");
            printf("\n\tDigite o ISBN: ");
            scanf("%d", &ISBN);

            livro = buscaBinariaL(ISBN, arqLivros, log, 0, tamanhoArquivoL(arqLivros));
            
            if (livro) {
               imprimeL(livro);
            } else {
                printf("\n\tLivro nao encontrado!\n");
            }
            break;
        case 3:
            break;
        default:
            // Codigo para opcao de menu Invalida.
            imprimirMensagemOpcaoInvalida();
        }
        free(livro);
    }
}

// Funcao de submenu para a opcao de Busca Binaria.
void subMenuBuscarEmprestimo(FILE *arqEmprestimos, FILE* log) {
    if (tamanhoArquivoU(arqEmprestimos) == 0) {
        system("cls");
        printf("\n\tNao houve emprestimos...\n\n");
    } else {
        TUsuario *usuario = NULL;
        int opcao = 0;
        int ID = 0;

        printf("\n\n\tDigite uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);
        system("cls");

        switch (opcao) {
        case 1:
            // Codigo de menu Buscar Sequencial.
            printf("\n\tBusca Sequencial...\n");
            printf("\n\tDigite o ID: ");
            fflush(stdin);
            scanf("%d", &ID);

            usuario = buscaSequencialU(ID, arqEmprestimos, log);

            if (usuario) {
                imprimeU(usuario);
            } else {
                printf("\n\tID nao encontrado!\n");
            }
            break;
        case 2:
            // Codigo de menu Buscar Binario.
            printf("\n\tBusca Binaria...\n");
            printf("\n\tDigite o ID: ");
            fflush(stdin);
            scanf("%d", &ID);
            
            usuario = buscaBinariaU(ID, arqEmprestimos, log, 0, tamanhoArquivoU(arqEmprestimos));

            if (usuario) {
                imprimeU(usuario);
            } else {
                printf("\n\tID nao encontrado!\n");
            }
            break;
        case 3:
            break;
        default:
            // Codigo para opcao de menu Invalida.
            imprimirMensagemOpcaoInvalida();
        }
        free(usuario);
    }
}

// Funcao de submenu para a opcao de ORDENAR.
void menuOrdenar(FILE *arqLivros, FILE *arqEmprestimos, FILE *log) {
    int opcao = 0;

    printf("\n\n\tDigite uma opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);
    system("cls");

    switch (opcao) {
    case 1:
        // Codigo para opcao de menu Ordenar Livro.
        if (tamanhoArquivoL(arqLivros) == 0) {
            printf("\n\tBase de dados vazia...\n\n");
        } else {
            printf("\n\tOrdenando arquivo de Livros...\n\n");
            selecaoSubstituicao(arqLivros, log, 6);
            system("cls");
            printf("\n\tArquivo ordenado.\n\n");
        }
        system("pause");
        break;
    case 2:
        // Codigo para opcao de menu Ordenar Emprestimo.
        if (tamanhoArquivoU(arqEmprestimos) == 0) {
            printf("\n\tBase de dados vazia...\n\n");
        } else {
            printf("\n\tOrdenando arquivo de Emprestimos...\n\n");
            selecaoSubstituicao(arqEmprestimos, log, 6);
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
