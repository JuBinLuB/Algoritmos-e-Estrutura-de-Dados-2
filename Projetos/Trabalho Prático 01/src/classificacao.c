#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "string.h"

#include "classificacao.h"
#include "livro.h"

// Executa o algoritmo de geracao de particoes por Selecao com Substituicao para livros.
int selecaoSubstituicaoL(FILE *in, FILE *log, int M) {
    // Registra o tempo de inicio da execucao do codigo.
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Posiciona cursor no inicio do arquivo.
    rewind(in);

    // Arquivo de saida.
    FILE *out;

    // Declaracao de variaveis.
    char nomeParticao[20];
    int totalParticoes = 0;
    int totalRegistrosLidos = 0;
    int ultimaChaveGravada = 0;
    int totalRegistros = tamanhoArquivoL(in);
    int congelados[M];

    // Preenche o vetor congelados com zeros.
    memset(congelados, 0, sizeof(congelados));
    
    // Variavel para armazenar os M registros em memoria.
    TLivro *livro[M];

    fprintf(log, "\n\tSelecao com Substituicao Livros...\n\n");

    // 1. Ler M registros do arquivo para a memoria.
    while (!feof(in)) {
        // Posiciona o cursor no registro a ser lido.
        fseek(in, totalRegistrosLidos * tamanhoRegistroL(), SEEK_SET);
        // Le um registro e o armazena na memoria.
        livro[totalRegistrosLidos] = leL(in);
        // Incrementa o contador de registros lidos.
        totalRegistrosLidos++;
        // Sai do loop se ja leu M registros.
        if (totalRegistrosLidos >= M) {
            break;
        }
    }

    // Abre um novo arquivo de saida.
    sprintf(nomeParticao, "particao%d.dat", totalParticoes);

    // Loop responsavel pela execucao dos passos de 2 ate 7.
    while (totalRegistrosLidos < totalRegistros) {
        // Verifica se ha registros nao congelados para criar uma nova particao.
        if (existemNaoCongelados(congelados, M)) {
            // - Abre um arquivo binario para gravacao.
            out = fopen(nomeParticao, "wb");
            if (out == NULL) {
                perror("Erro ao abrir novo arquivo de saida.");
                exit(EXIT_FAILURE);
            }
        } else {
            // Pula para a proxima iteracao se todos os registros estao congelados.
            continue;
        }

        // Variavel de controle do loop, responsavel pelos passos de 2 ate 6.
        int temNaoCongelados = 1;

        while (temNaoCongelados) {
            // 2. Selecionar, no array em memoria, o registro "r" com menor chave.
            TLivro *registroR = NULL;
            int menorISBN = INT_MAX;
            int indiceR = 0;
            
            for (int i = 0; i < M; i++) {
                // Ignora os registros congelados.
                if (congelados[i]) {
                    continue;
                }
                // Verifica se o ISBN do livro atual e' menor do que o menor ISBN encontrado ate agora.
                if (livro[i]->ISBN < menorISBN) {
                    // Atualiza menorISBN com o ISBN do livro atual.
                    menorISBN = livro[i]->ISBN;
                    // Atualiza "registroR" para o livro com o menor ISBN.
                    registroR = livro[i];
                    // Atualiza a variavel "indiceR" para o indice do livro com o menor ISBN.
                    indiceR = i;
                }
            }
            // 3. Gravar o registro "r" na particao de saida.
            salvaL(registroR, out);

            // 4. Substituir, no array em memoria, o registro "r" pelo proximo registro do arquivo de entrada.
            ultimaChaveGravada = menorISBN;
            if ((livro[indiceR] = leL(in)) == NULL) {
                // Marca a posicao no array como NULL se nao ha mais registros para ler.
                livro[indiceR] = NULL;
            }

            // Incrementa o numero total de registros lidos do arquivo de entrada.
            totalRegistrosLidos++;

            // 5. Caso a chave deste ultimo seja menor do que a chave recem gravada,
            //  considera-lo congelado e ignora-lo no restante do processamento.
            if ((livro[indiceR] == NULL) || (livro[indiceR]->ISBN < ultimaChaveGravada)) {
                congelados[indiceR] = 1;
            }

            // 6. Caso existam em memoria registros nao congelados, voltar ao passo 2.
            temNaoCongelados = existemNaoCongelados(congelados, M);
        }
        // 7. Caso contrario.
        // - 7.1. Fecha o arquivo de saida.
        if (out != NULL) {
            fclose(out);
        }
        // - 7.2. Descongelar os registros congelados.
        for (int i = 0; i < M; i++) {
            if (livro[i] != NULL) {
                congelados[i] = 0;
            }
        }
        // - 7.3. Abrir nova particao de saida.
        totalParticoes++;
        sprintf(nomeParticao, "particao%d.dat", totalParticoes);
    }
    // Registra o tempo de fim da execucao do codigo.
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calcula o tempo decorrido pelo programa, encontrando a diferenca entre end e start,
    // e, em seguida, divide a diferenca por 1e9 para converter para segundos.
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Registra o tempo de CPU consumido pela aplicacao no arquivo de log.
    fprintf(log, "\n\tThe elapsed time is %f seconds\n", time_spent);

    // Descarrega o buffer para ter certeza que dados foram gravados.
    fflush(in);

    // Libera a memoria alocada para os registros em memoria.
    liberarRegistrosL(livro, M);

    // Retorna o numero total de particoes criadas.
    return totalParticoes;
}

// Executa o algoritmo de geracao de particoes por Selecao com Substituicao para usuarios.
int selecaoSubstituicaoU(FILE *in, FILE *log, int M) {
    // Registra o tempo de inicio da execucao do codigo.
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Posiciona cursor no inicio do arquivo.
    rewind(in);

    // Arquivo de saida.
    FILE *out;

    // Declaracao de variaveis.
    char nomeParticao[20];
    int totalParticoes = 0;
    int totalRegistrosLidos = 0;
    int ultimaChaveGravada = 0;
    int totalRegistros = tamanhoArquivoL(in);
    int congelados[M];

    // Preenche o vetor congelados com zeros.
    memset(congelados, 0, sizeof(congelados));
    
    // Variavel para armazenar os M registros em memoria.
    TUsuario *usuario[M];

    fprintf(log, "\n\tSelecao com Substituicao Usuarios...\n\n");

    // 1. Ler M registros do arquivo para a memoria.
    while (!feof(in)) {
        // Posiciona o cursor no registro a ser lido.
        fseek(in, totalRegistrosLidos * tamanhoRegistroU(), SEEK_SET);
        // Le um registro e o armazena na memoria.
        usuario[totalRegistrosLidos] = leU(in);
        // Incrementa o contador de registros lidos.
        totalRegistrosLidos++;
        // Sai do loop se ja leu M registros.
        if (totalRegistrosLidos >= M) {
            break;
        }
    }

    // Abre um novo arquivo de saida.
    sprintf(nomeParticao, "particao%d.dat", totalParticoes);

    // Loop responsavel pela execucao dos passos de 2 ate 7.
    while (totalRegistrosLidos < totalRegistros) {
        // Verifica se ha registros nao congelados para criar uma nova particao.
        if (existemNaoCongelados(congelados, M)) {
            // - Abre um arquivo binario para gravacao.
            out = fopen(nomeParticao, "wb");
            if (out == NULL) {
                perror("Erro ao abrir novo arquivo de saida.");
                exit(EXIT_FAILURE);
            }
        } else {
            // Pula para a proxima iteracao se todos os registros estao congelados.
            continue;
        }

        // Variavel de controle do loop, responsavel pelos passos de 2 ate 6.
        int temNaoCongelados = 1;

        while (temNaoCongelados) {
            // 2. Selecionar, no array em memoria, o registro "r" com menor chave.
            TUsuario *registroR = NULL;
            int menorID = INT_MAX;
            int indiceR = 0;
            
            for (int i = 0; i < M; i++) {
                // Ignora os registros congelados.
                if (congelados[i]) {
                    continue;
                }
                // Verifica se o ID do usuario atual e' menor do que o menor ID encontrado ate agora.
                if (usuario[i]->ID < menorID) {
                    // Atualiza menorID com o ID do usuario atual.
                    menorID = usuario[i]->ID;
                    // Atualiza "registroR" para o usuario com o menor ID.
                    registroR = usuario[i];
                    // Atualiza a variavel "indiceR" para o indice do usuario com o menor ID.
                    indiceR = i;
                }
            }
            // 3. Gravar o registro "r" na particao de saida.
            salvaU(registroR, out);

            // 4. Substituir, no array em memoria, o registro "r" pelo proximo registro do arquivo de entrada.
            ultimaChaveGravada = menorID;
            if ((usuario[indiceR] = leU(in)) == NULL) {
                // Marca a posicao no array como NULL se nao ha mais registros para ler.
                usuario[indiceR] = NULL;
            }

            // Incrementa o numero total de registros lidos do arquivo de entrada.
            totalRegistrosLidos++;

            // 5. Caso a chave deste ultimo seja menor do que a chave recem gravada,
            //  considera-lo congelado e ignora-lo no restante do processamento.
            if ((usuario[indiceR] == NULL) || (usuario[indiceR]->ID < ultimaChaveGravada)) {
                congelados[indiceR] = 1;
            }

            // 6. Caso existam em memoria registros nao congelados, voltar ao passo 2.
            temNaoCongelados = existemNaoCongelados(congelados, M);
        }
        // 7. Caso contrario.
        // - 7.1. Fecha o arquivo de saida.
        if (out != NULL) {
            fclose(out);
        }
        // - 7.2. Descongelar os registros congelados.
        for (int i = 0; i < M; i++) {
            if (usuario[i] != NULL) {
                congelados[i] = 0;
            }
        }
        // - 7.3. Abrir nova particao de saida.
        totalParticoes++;
        sprintf(nomeParticao, "particao%d.dat", totalParticoes);
    }
    // Registra o tempo de fim da execucao do codigo.
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calcula o tempo decorrido pelo programa, encontrando a diferenca entre end e start,
    // e, em seguida, divide a diferenca por 1e9 para converter para segundos.
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Registra o tempo de CPU consumido pela aplicacao no arquivo de log.
    fprintf(log, "\n\tThe elapsed time is %f seconds\n", time_spent);

    // Descarrega o buffer para ter certeza que dados foram gravados.
    fflush(in);

    // Libera a memoria alocada para os registros em memoria.
    liberarRegistrosU(usuario, M);

    // Retorna o numero total de particoes criadas.
    return totalParticoes;
}

// Verifica se existe pelo menos um registro nao congelado.
int existemNaoCongelados(int *congelados, int n) {
    for (int i = 0; i < n; i++) {
        if (!congelados[i]) {
            // Retorna 1 se pelo menos um registro nao estiver congelado.
            return 1;
        }
    }
    // Retorna 0 se todos os registros estiverem congelados.
    return 0;
}

// Libera a memoria alocada para os registros de livros em memoria.
void liberarRegistrosL(TLivro **livro, int M) {
    for (int i = 0; i < M; i++) {
        if (livro[i] != NULL) {
            free(livro[i]);
        }
    }
}

// Libera a memoria alocada para os registros de usuarios em memoria.
void liberarRegistrosU(TUsuario **usuario, int M) {
    for (int i = 0; i < M; i++) {
        if (usuario[i] != NULL) {
            free(usuario[i]);
        }
    }
}
