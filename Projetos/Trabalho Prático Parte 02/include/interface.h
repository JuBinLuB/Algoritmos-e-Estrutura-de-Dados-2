# ifndef INTERFACE_H_INCLUDED
# define INTERFACE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// MENSAGEM PARA EXIBIR O MENU PRINCIPAL.
void imprimirMenuPrincipal();

// MENSAGEM PARA EXIBIR O MENU DE CRIAR BASE.
void imprimirSubMenuCriarBase();

// MENSAGEM PARA EXIBIR O MENU DE BUSCA.
void imprimirSubMenu(char *str);

// MENSAGEM PARA EXIBIR O SUB MENU DE BUSCA.
void imprimirSubMenuBuscar();

// MENSAGEM PARA EXIBIR O SUB MENU DE ORDENAR.
void imprimirSubMenuOrdenar();

// MENSAGEM DE ALERTA DE DIGITO INVALIDO.
void imprimirMensagemOpcaoInvalida();

// MENSAGEM DE SAIDA DO MODULO.
void imprimirMensagemSair();

// MODULO DE MENU.
void menuPrincipal(FILE *arqLivros, FILE *arqEmprestimos, FILE *log);

// MODULO CRIAR BASE DE DADOS.
void menuCriarBaseDados(FILE *arq);

// MODULO IMPRIMIR.
void menuImprimir(FILE *arqLivros, FILE *arqEmprestimos);

// MODULO DE BUSCAR.
void menuBuscar(FILE *arqLivros, FILE *arqEmprestimos, FILE *log);

// MODULO DE SUB MENU BUSCAR LIVRO.
void subMenuBuscarLivro(FILE *arqLivros, FILE* log);

// MODULO DE SUB MENU BUSCAR EMPRESTIMO.
void subMenuBuscarEmprestimo(FILE *arqEmprestimos, FILE* log);

// MODULO DE ORDENAR.
void menuOrdenar(FILE *arqLivros, FILE *arqEmprestimos, FILE *log);

// MODULO DE SUB MENU ORDENAR LIVRO.
void subMenuOrdenarLivro(FILE *arqLivros, FILE *log);

// MODULO DE SUB MENU ORDENAR EMPRESTIMO.
void subMenuOrdenarEmprestimo(FILE *arqEmprestimos, FILE *log);

# endif // INTERFACE_H_INCLUDED
