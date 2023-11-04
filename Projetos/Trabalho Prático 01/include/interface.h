# ifndef INTERFACE_H_INCLUDED
# define INTERFACE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "funcionario.h"

void imprimirMenuPrincipal(); // MENSAGEM PARA EXIBIR O MENU PRINCIPAL.

void imprimirSubMenu(char *str); // MENSAGEM PARA EXIBIR O MENU DE BUSCA.

void imprimirSubMenuBuscar(); // MENSAGEM PARA EXIBIR O SUB MENU DE BUSCA.

void imprimirMensagemOpcaoInvalida(); // MENSAGEM DE ALERTA DE DIGITO INVALIDO.

void imprimirMensagemSair(); // MENSAGEM DE SAIDA DO MODULO.

void menuPrincipal(FILE *arq, FILE *livro, FILE *log); // MODULO DE MENU.

void menuImprimir(FILE *arq, FILE *livro); // MODULO IMPRIMIR.

void menuBuscar(FILE *arq, FILE *livro, FILE *log); // MODULO DE BUSCAR.

void subMenuBuscar(FILE *arq, FILE *log, char *str); // MODULO DE SUB MENU BUSCAR.

void menuOrdenar(FILE *arq, FILE *livro); // MODULO DE ORDENAR.

# endif // INTERFACE_H_INCLUDED
