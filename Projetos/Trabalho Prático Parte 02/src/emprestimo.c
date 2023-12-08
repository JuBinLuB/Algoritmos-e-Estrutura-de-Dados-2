#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "emprestimo.h"
#include "livro.h"
#include "usuario.h"
#include "buscaBinaria.h"

// Funcao para realizar emprestimo de um livro para um usuario.
void realizarEmprestimo(FILE *arqLivros, FILE *arqEmprestimos) {
    // Declaracao de variaveis.
    TLivro *livro = NULL;
    TUsuario *u = NULL;
    int ISBN;
    int ID;
    char nome[50];
    char dataNascimento[11];

    // Obter o ISBN do livro a ser emprestado.
    printf("\n\tInforme o ISBN do livro a ser emprestado: ");
    scanf("%d", &ISBN);

     // Realiza a busca binaria do livro pelo ISBN.
    livro = buscaBinariaL(ISBN, arqLivros, NULL, 0, tamanhoArquivoL(arqLivros));
    
    // Limpa a tela.
    system("cls");

    // Verificar se o livro existe na base de dados.
    if (livro != NULL) {
        // Verificar se o livro nao esta emprestado.
        if (!livro->emprestado) {
            // Realiza o cadastro dos dados do usuario.
            printf("\n\tCadastrando o usuario...\n\n");
            obterDadosUsuario(&ID, nome, dataNascimento);

            // Busca o usuario pelo ID.
            u = buscaBinariaU(ID, arqEmprestimos, NULL, 0, tamanhoArquivoU(arqEmprestimos));

            // Cadastra o usuario caso o mesmo nao exista.
            if (u == NULL) {
                // Cria um usuario.
                u = usuario(ID, nome, dataNascimento);
                
                // Realiza o emprestimo.
                livro->emprestado = 1;
                u->emprestimo = *livro;

                // Atualiza o livro no arquivo.
                fseek(arqLivros, -tamanhoRegistroL(), SEEK_CUR);
                salvaL(livro, arqLivros);

                // Atualiza o usuario no arquivo.
                fseek(arqEmprestimos, 0, SEEK_CUR);
                salvaU(u, arqEmprestimos);

                // Limpa a tela.
                system("cls");
                printf("\n\tEmprestimo realizado com sucesso!\n");
            } else {
                printf("\n\tUsuario nao encontrado!\n");
            }
            free(u);
        } else {
            printf("\n\tLivro ja esta emprestado!\n\n");
        }
    } else {
        printf("\n\tLivro nao encontrado...\n\n");
    }
    free(livro);
}

// Funcao auxiliar para obter dados do usuario.
void obterDadosUsuario(int *ID, char *nome, char *dataNascimento) {
    // Ler ID.
    printf("\tID: ");
    fflush(stdin);
    scanf("%d", ID);

    // Ler nome.
    printf("\tNome: ");
    fflush(stdin);
    fgets(nome, 50, stdin);

    // Remover o caractere de nova linha.
    nome[strcspn(nome, "\n")] = '\0';

    // Ler data de nascimento.
    printf("\tData de Nascimento: ");
    fflush(stdin);
    fgets(dataNascimento, 11, stdin);

    // Remover o caractere de nova linha.
    dataNascimento[strcspn(dataNascimento, "\n")] = '\0';
}
