#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "buscaBinaria.h"
#include "livro.h"
#include "usuario.h"

// Realiza uma busca binaria por um livro na base de dados.
TLivro *buscaBinariaL(int chave, FILE *in, FILE *log, int inicio, int fim) {
    // Registra o tempo de inicio da execucao do codigo.
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Declaracao de variaveis.
    TLivro *livro = NULL;
    int codigo = -1;
    int contador = 0;

    if (log != NULL) {
        fprintf(log, "\n\tBusca Binaria Livros...\n\n");
    }

    // Verifica se existe apenas um registro no arquivo.
    if (tamanhoArquivoU(in) <= 1) {
        // Se houver apenas um registro, realiza uma busca direta.
        fseek(in, 0, SEEK_SET);
        livro = leL(in);
        
        // Verifica se a leitura foi bem-sucedida e se o ISBN do livro e' igual a chave fornecida.
        if (livro != NULL && livro->ISBN == chave) {
            // Registra o numero de comparacoes no arquivo de log, se fornecido.
            if (log != NULL) {
                fprintf(log, "\tComparacoes: %d\n", 1);
            }
            return livro;
        } else {
            // Retorna NULL indicando que o registro nao foi encontrado.
            free(livro);
            return NULL;
        }
    }

    while (inicio <= fim && codigo != chave) {
        int meio = trunc((inicio + fim) / 2);
        fseek(in, (meio - 1) * tamanhoRegistroL(), SEEK_SET);
        livro = leL(in);
        codigo = livro->ISBN;

        if (livro) {
            if (codigo > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
        contador++;
        if (log != NULL) {
            // Registra o numero de comparacoes realizadas pela busca no arquivo de log.
            fprintf(log, "\tComparacoes: %d\n", contador);
        }
    }
    // Registra o tempo de fim da execucao do código.
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calcula o tempo decorrido pelo programa, encontrando a diferenca entre end e start,
    // e, em seguida, divide a diferenca por 1e9 para converter para segundos.
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    if (log != NULL) {
        // Registra o tempo de CPU consumido pela aplicacao no arquivo de log.
        fprintf(log, "\n\tThe elapsed time is %f seconds\n", time_spent);
    }

    if (codigo == chave) {
        return livro;
    }
    free(livro);
    return NULL;
}

// Realiza uma busca binaria por um usuario na base de dados.
TUsuario *buscaBinariaU(int chave, FILE *in, FILE *log, int inicio, int fim) {
    // Registra o tempo de inicio da execucao do codigo.
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Declaracao de variaveis.
    TUsuario *usuario = NULL;
    int codigo = -1;
    int contador = 0;

    if (log != NULL) {
        fprintf(log, "\n\tBusca Binaria Livros...\n\n");
    }

    // Verifica se existe apenas um registro no arquivo.
    if (tamanhoArquivoU(in) <= 1) {
        // Se houver apenas um registro, realiza uma busca direta.
        fseek(in, 0, SEEK_SET);
        usuario = leU(in);
        
        // Verifica se a leitura foi bem-sucedida e se o ID do usuario e' igual a chave fornecida.
        if (usuario != NULL && usuario->ID == chave) {
            // Registra o numero de comparacoes no arquivo de log, se fornecido.
            if (log != NULL) {
                fprintf(log, "\tComparacoes: %d\n", 1);
            }
            return usuario;
        } else {
            // Retorna NULL indicando que o registro nao foi encontrado.
            free(usuario);
            return NULL;
        }
    }

    while (inicio <= fim && codigo != chave) {
        int meio = trunc((inicio + fim) / 2);
        fseek(in, (meio - 1) * tamanhoRegistroU(), SEEK_SET);
        usuario = leU(in);
        codigo = usuario->ID;

        if (usuario) {
            if (codigo > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
        contador++;
        if (log != NULL) {
            // Registra o numero de comparacoes realizadas pela busca no arquivo de log.
            fprintf(log, "\tComparacoes: %d\n", contador);
        }
    }
    // Registra o tempo de fim da execucao do código.
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calcula o tempo decorrido pelo programa, encontrando a diferenca entre end e start,
    // e, em seguida, divide a diferenca por 1e9 para converter para segundos.
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    if (log != NULL) {
        // Registra o tempo de CPU consumido pela aplicacao no arquivo de log.
        fprintf(log, "\n\tThe elapsed time is %f seconds\n", time_spent);
    }

    if (codigo == chave) {
        return usuario;
    }
    free(usuario);
    return NULL;
}
