#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int ID;
    char nome[50];
    char cpf[15];
    char dataNascimento[11];
    int emprestimos[5];
} TUsuario;

// Imprime Usuario.
void imprime(TUsuario *usuario) {
    printf("\n\t**********************************************");
    printf("\n\tID: ");
    printf("%d", usuario->ID);
    printf("\n\tNome: ");
    printf("%s", usuario->nome);
    printf("\n\tCPF: ");
    printf("%s", usuario->cpf);
    printf("\n\tData de Nascimento: ");
    printf("%s", usuario->dataNascimento);
    printf("\n\tEmprestimos: ");
    printf("%s", usuario->emprestimos);
    printf("\n\t**********************************************\n");
}

#endif // USUARIO_H_INCLUDED
