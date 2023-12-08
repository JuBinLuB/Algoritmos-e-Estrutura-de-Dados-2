#ifndef EMPRESTIMO_H_INCLUDED
#define EMPRESTIMO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Realiza o emprestimo de um livro para um usuario.
void realizarEmprestimo(FILE *arqLivros, FILE *arqEmprestimos);

// Funcao auxiliar para obter dados do usuario.
void obterDadosUsuario(int *ID, char *nome, char *dataNascimento);

#endif // EMPRESTIMO_H_INCLUDED
