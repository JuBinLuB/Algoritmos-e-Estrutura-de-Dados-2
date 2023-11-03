#include <stdio.h>
#include <stdlib.h>

#include "interface.h"

void MSG_MENU() {
    system("clear");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\n\t1. IMPRIMIR");
    printf("  \n\t2. ORDENAR");
    printf("  \n\t3. BUSCAR LIVRO");
    printf("  \n\t4. BUSCAR FUNCIONARIO");
    printf("  \n\t5. EMPRESTIMO");
    printf("  \n\t6. SAIR");
}

void MENU(TFunc *func){
    int opcao = 0;

    do {
        MSG_MENU();
        printf("\n\nDigite uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                /**
                    Codigo para opcao de menu Imprimir.
                */
                break;
            case 2:
                /**
                    Codigo para opcao de menu Ordenar.
                */
                break;
            case 3:
                /**
                    Codigo para opcao de menu Buscar Livro.
                */
                break;
            case 4:
                /**
                    Codigo para opcao de menu Buscar Funcionario.
                */
                break;
            case 5:
                system("clear");
                printf("\n\n\n\t >>>>>> MSG: Saindo do MODULO...!!! <<<<<<");
                system("PAUSE");
                break;
            default:
                system("clear");
                printf("\n\n\n\t >>>>>> MSG: Digite uma opcao valida!!! <<<<<<");
                system("PAUSE");
            } // fim do bloco switch.
    } while(opcao != 5);
}
