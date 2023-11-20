# ifndef INTERFACE_H_INCLUDED
# define INTERFACE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

void imprimirMenuPrincipal(); // MENSAGEM PARA EXIBIR O MENU PRINCIPAL.

void imprimirSubMenuCriarBase(); // MENSAGEM PARA EXIBIR O MENU DE CRIAR BASE.

void imprimirSubMenu(char *str); // MENSAGEM PARA EXIBIR O MENU DE BUSCA.

void imprimirSubMenuBuscar(); // MENSAGEM PARA EXIBIR O SUB MENU DE BUSCA.

void imprimirMensagemOpcaoInvalida(); // MENSAGEM DE ALERTA DE DIGITO INVALIDO.

void imprimirMensagemSair(); // MENSAGEM DE SAIDA DO MODULO.

void menuPrincipal(FILE *arqFunc, FILE *arqLivro, FILE *log); // MODULO DE MENU.

void menuCriarBaseDados(FILE *arq); // MODULO CRIAR BASE DE DADOS.

void menuImprimir(FILE *arqFunc, FILE *arqLivro); // MODULO IMPRIMIR.

void menuBuscar(FILE *arqFunc, FILE *arqLivro, FILE *log); // MODULO DE BUSCAR.

void subMenuBuscarLivro(FILE *arqLivros, FILE* log); // MODULO DE SUB MENU BUSCAR LIVRO.

void subMenuBuscarEmprestimo(FILE *arqEmprestimos, FILE* log); // MODULO DE SUB MENU BUSCAR EMPRESTIMO.

void menuOrdenar(FILE *arqFunc, FILE *arqLivro, FILE *log); // MODULO DE ORDENAR.

# endif // INTERFACE_H_INCLUDED
