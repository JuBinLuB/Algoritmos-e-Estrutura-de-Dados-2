#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "intercalacao.h"
#include "livro.h"
#include "usuario.h"
#include "sobrescrever.h"

// Estruturas para armazenar informacoes sobre cada arquivo de entrada.
typedef struct {
    TLivro *livro;
    FILE *arquivo;
    int posicao;
} TVetorL;

typedef struct {
    TUsuario *usuario;
    FILE *arquivo;
    int posicao;
} TVetorU;

// Executa o algoritmo de Intercalacao Otima de particoes para livros.
void intercalacaoL(FILE *out, FILE *log, char *nome, int totalParticoes, int F) {
    // Registra o tempo de inicio da execucao do codigo.
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Declaracao de variaveis.
    TVetorL *vetor = (TVetorL *)malloc(F * sizeof(TVetorL));
    int particoesLidas = 0;
    int particoesGeradas = 0;
    int particoesGeradasAtualmente = 1;
    int particoesProcessadas = F - 1;
    int numParticoes = totalParticoes;
    char nomeParticao[20];

    fprintf(log, "\n\tIntercalacao Otima Livros...\n\n");

    // Loop principal para intercalacao de particoes.
    while (numParticoes > 1) {
        // Abre "F - 1" arquivos de entrada.
        for (int i = 0; i < particoesProcessadas; i++) {
            // Gera o nome do arquivo da proxima particao a ser lida.
            snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, particoesLidas);

            // Abre um arquivo binario para leitura.
            vetor[i].arquivo = fopen(nomeParticao, "rb");
            
            // Inicializa a posicao do cursor dos arquivos de entrada.
            vetor[i].posicao = 0;

            if (vetor[i].arquivo != NULL) {
                // Move o cursor para a posicao do registro a ser lido.
                fseek(vetor[i].arquivo, vetor[i].posicao * tamanhoRegistroL(), SEEK_SET);
                
                // Le o primeiro registro do arquivo de entrada.
                TLivro *l = leL(vetor[i].arquivo);

                if (l != NULL) {
                    // Armazena o livro lido na estrutura de controle.
                    vetor[i].livro = l;
                } else {
                    // Arquivo estava vazio, coloca HIGH VALUE nessa posicao do vetor.
                    vetor[i].livro = livro(INT_MAX, "", "", "");
                }
            }
            // Incrementa o numero de particoes lidas.
            particoesLidas++;
        }
        // Gera o nome do arquivo da proxima particao a ser gerada.
        snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, totalParticoes + particoesGeradas);

        // Incrementa o numero de particoes geradas.
        particoesGeradas++;

        // Abre o arquivo de saida, no formato binario para escrita.
        vetor[particoesProcessadas].arquivo = fopen(nomeParticao, "w+b");

        // Verifica se houve erro na abertura do arquivo de saida.
        if (vetor[particoesProcessadas].arquivo == NULL) {
            perror("Erro ao abrir novo arquivo de saida.");
            exit(EXIT_FAILURE);
        }

        // Inicializa a posicao do cursor do arquivo de saida.
        vetor[particoesProcessadas].posicao = 0;

        // Intercalacao.
        while (1) {
            int menorISBN = INT_MAX;
            int indiceMenor = -1;

            // Encontrar o menor registro entre as particoes.
            for (int i = 0; i < particoesProcessadas; i++) {
                // Verifica se o ISBN do livro atual e' menor do que o menor ISBN encontrado ate agora.
                if (vetor[i].livro->ISBN < menorISBN) {
                    // Atualiza menorISBN com o ISBN do livro atual.
                    menorISBN = vetor[i].livro->ISBN;
                    // Atualiza a variavel "indiceMenor" para o indice do livro com o menor ISBN.
                    indiceMenor = i;
                }
            }
            // Verifica se ha um ISBN valido no vetor de livros.
            if (menorISBN == INT_MAX) {
                // Terminou o processamento.
                break;
            }
            // Move o cursor para a posicao de gravacao na particao de saida.
            fseek(vetor[particoesProcessadas].arquivo, vetor[particoesProcessadas].posicao * tamanhoRegistroL(), SEEK_SET);

            // Grava o registro de menor ISBN na particao de saida.
            salvaL(vetor[indiceMenor].livro, vetor[particoesProcessadas].arquivo);

            // Incrementa a posicao no arquivo de saida.
            vetor[particoesProcessadas].posicao++;

            // Incrementa a posicao no arquivo da particao de onde o registro foi lido.
            vetor[indiceMenor].posicao++;

            // Move o cursor para a posicao do proximo registro a ser lido.
            fseek(vetor[indiceMenor].arquivo, vetor[indiceMenor].posicao * tamanhoRegistroL(), SEEK_SET);

            // Le o proximo registro do arquivo de entrada.
            TLivro *proximoRegistro = leL(vetor[indiceMenor].arquivo);

            // Verifica se ha mais registros para serem lidos no arquivo.
            if (proximoRegistro != NULL) {
                // Substitui o registro atual no array pelo proximo registro lido do arquivo.
                vetor[indiceMenor].livro = proximoRegistro;
            } else {
                // Coloca HIGH VALUE na posicao vazia do vetor.
                vetor[indiceMenor].livro = livro(INT_MAX, "", "", "");
            }
        }
        // Atualiza o numero de particoes restantes.
        // Do conjunto inicial de particoes removem-se as particoes intercaladas
        // e a ele agrega-se a particao gerada na intercalacao.
        numParticoes += particoesGeradasAtualmente - particoesProcessadas;
    }
    // Realiza a sobrescrita do conteudo do arquivo original pelo conteudo do novo arquivo.
    sobrescreverArquivoL(out, vetor[particoesProcessadas].arquivo, tamanhoRegistroL());

    // Fecha os arquivos das particoes de entrada e libera memoria alocada para cada livro.
    for (int i = 0; i < particoesProcessadas; i++) {
        fclose(vetor[i].arquivo);
        free(vetor[i].livro);
    }
    // Libera memoria alocada para o vetor.
    free(vetor);

    // Registra o tempo de fim da execucao do codigo.
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calcula o tempo decorrido pelo programa, encontrando a diferenca entre end e start,
    // e, em seguida, divide a diferenca por 1e9 para converter para segundos.
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Registra o tempo de CPU consumido pela aplicacao no arquivo de log.
    fprintf(log, "\n\tThe elapsed time is %f seconds\n", time_spent);
}

// Executa o algoritmo de Intercalacao Otima de particoes para usuarios.
void intercalacaoU(FILE *out, FILE *log, char *nome, int totalParticoes, int F) {
    // Registra o tempo de inicio da execucao do codigo.
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Declaracao de variaveis.
    TVetorU *vetor = (TVetorU *)malloc(F * sizeof(TVetorU));
    int particoesLidas = 0;
    int particoesGeradas = 0;
    int particoesGeradasAtualmente = 1;
    int particoesProcessadas = F - 1;
    int numParticoes = totalParticoes;
    char nomeParticao[20];

    fprintf(log, "\n\tIntercalacao Otima Usuarios...\n\n");

    // Loop principal para intercalacao de particoes.
    while (numParticoes > 1) {
        // Abre "F - 1" arquivos de entrada.
        for (int i = 0; i < particoesProcessadas; i++) {
            // Gera o nome do arquivo da proxima particao a ser lida.
            snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, particoesLidas);

            // Abre um arquivo binario para leitura.
            vetor[i].arquivo = fopen(nomeParticao, "rb");
            
            // Inicializa a posicao do cursor dos arquivos de entrada.
            vetor[i].posicao = 0;

            if (vetor[i].arquivo != NULL) {
                // Move o cursor para a posicao do registro a ser lido.
                fseek(vetor[i].arquivo, vetor[i].posicao * tamanhoRegistroU(), SEEK_SET);
                
                // Le o primeiro registro do arquivo de entrada.
                TUsuario *u = leU(vetor[i].arquivo);

                if (u != NULL) {
                    // Armazena o usuario lido na estrutura de controle.
                    vetor[i].usuario = u;
                } else {
                    // Arquivo estava vazio, coloca HIGH VALUE nessa posicao do vetor.
                    vetor[i].usuario = usuario(INT_MAX, "", "");
                }
            }
            // Incrementa o numero de particoes lidas.
            particoesLidas++;
        }
        // Gera o nome do arquivo da proxima particao a ser gerada.
        snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, totalParticoes + particoesGeradas);

        // Incrementa o numero de particoes geradas.
        particoesGeradas++;

        // Abre o arquivo de saida, no formato binario para escrita.
        vetor[particoesProcessadas].arquivo = fopen(nomeParticao, "w+b");

        // Verifica se houve erro na abertura do arquivo de saida.
        if (vetor[particoesProcessadas].arquivo == NULL) {
            perror("Erro ao abrir novo arquivo de saida.");
            exit(EXIT_FAILURE);
        }

        // Inicializa a posicao do cursor do arquivo de saida.
        vetor[particoesProcessadas].posicao = 0;

        // Intercalacao.
        while (1) {
            int menorID = INT_MAX;
            int indiceMenor = -1;

            // Encontrar o menor registro entre as particoes.
            for (int i = 0; i < particoesProcessadas; i++) {
                // Verifica se o ID do usuario atual e' menor do que o menor ID encontrado ate agora.
                if (vetor[i].usuario->ID < menorID) {
                    // Atualiza menorID com o ID do usuario atual.
                    menorID = vetor[i].usuario->ID;
                    // Atualiza a variavel "indiceMenor" para o indice do usuario com o menor ID.
                    indiceMenor = i;
                }
            }
            // Verifica se ha um ID valido no vetor de usuarios.
            if (menorID == INT_MAX) {
                // Terminou o processamento.
                break;
            }
            // Move o cursor para a posicao de gravacao na particao de saida.
            fseek(vetor[particoesProcessadas].arquivo, vetor[particoesProcessadas].posicao * tamanhoRegistroU(), SEEK_SET);

            // Grava o registro de menor ID na particao de saida.
            salvaU(vetor[indiceMenor].usuario, vetor[particoesProcessadas].arquivo);

            // Incrementa a posicao no arquivo de saida.
            vetor[particoesProcessadas].posicao++;

            // Incrementa a posicao no arquivo da particao de onde o registro foi lido.
            vetor[indiceMenor].posicao++;

            // Move o cursor para a posicao do proximo registro a ser lido.
            fseek(vetor[indiceMenor].arquivo, vetor[indiceMenor].posicao * tamanhoRegistroU(), SEEK_SET);

            // Le o proximo registro do arquivo de entrada.
            TUsuario *proximoRegistro = leU(vetor[indiceMenor].arquivo);

            // Verifica se ha mais registros para serem lidos no arquivo.
            if (proximoRegistro != NULL) {
                // Substitui o registro atual no array pelo proximo registro lido do arquivo.
                vetor[indiceMenor].usuario = proximoRegistro;
            } else {
                // Coloca HIGH VALUE na posicao vazia do vetor.
                vetor[indiceMenor].usuario = usuario(INT_MAX, "", "");
            }
        }
        // Atualiza o numero de particoes restantes.
        numParticoes += particoesGeradasAtualmente - particoesProcessadas;
    }
    // Realiza a sobrescrita do conteudo do arquivo original pelo conteudo do novo arquivo.
    sobrescreverArquivoU(out, vetor[particoesProcessadas].arquivo, tamanhoRegistroU());

    // Fecha os arquivos das particoes de entrada e libera memoria alocada para cada usuario.
    for (int i = 0; i < particoesProcessadas; i++) {
        fclose(vetor[i].arquivo);
        free(vetor[i].usuario);
    }
    // Libera memoria alocada para o vetor.
    free(vetor);

    // Registra o tempo de fim da execucao do codigo.
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calcula o tempo decorrido pelo programa, encontrando a diferenca entre end e start,
    // e, em seguida, divide a diferenca por 1e9 para converter para segundos.
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Registra o tempo de CPU consumido pela aplicacao no arquivo de log.
    fprintf(log, "\n\tThe elapsed time is %f seconds\n", time_spent);
}
