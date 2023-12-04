#include <stdio.h>
#include <stdlib.h>

#include "gerarParticoes.h"
#include "livro.h"

#define PARTICOES 20

// Executa o algoritmo de geracao de particoes por Selecao com Substituicao.
int selecaoSubstituicao(FILE *in, int M) {
    // Declaracao de variaveis.
    FILE *out;
    char nomeParticao[PARTICOES];
    int particoes = 0;
    int registros = 0;
    int tamRegistro = tamanhoRegistroL();
    int numLivros = tamanhoArquivoL(in);
    int gravado = 0;
    int congelados[M];
    memset(congelados, 0, sizeof(congelados));
    
    // Posiciona cursor no inicio do arquivo.
    rewind(in);
    
    // 1. Ler M registros do arquivo para a memoria.
    // Variavel para armazenar os M registros em memoria.
    TLivro *livro[M];
    int i = 0;
        
    while ((livro[i] = leL(in)) != NULL) {
        fseek(in, registros * tamanhoRegistroL(), SEEK_SET);
        registros++;
        i++;
        if (i >= M) {
            break;
        }
    }

    for (int i = 0; i < PARTICOES; i++) {
        // Abre um novo arquivo de saida.
        sprintf(nomeParticao, "particao%d.dat", particoes);
        
        if (existeNaoCongelado(congelados, M)) {
            out = fopen(nomeParticao, "wb");
        } else {
            // Pula para a proxima iteracao se todos os registros estao congelados.
            continue;
        }

        // Variavel de controle do loop, responsavel pelos passos de 2 ate 6.
        int houverNaoCongelados = 1;

        while (houverNaoCongelados) {
            // 2. Selecionar, no array em memoria, o registro "r" com menor chave.
            TLivro *registroR = NULL;
            int menorISBN = INT_MAX;
            int r = 0;

            for (int i = 0; i < M; i++) {
                if (livro[i]->ISBN < menorISBN) {
                    menorISBN = livro[i]->ISBN;
                    registroR = livro[i];
                    r = i;
                }
            }
            // 3. Gravar o registro "r" na particao de saida.
            salvaL(registroR, out);
            
            // 4. Substituir, no array em memoria, o registro "r" pelo proximo registro do arquivo de entrada.
            gravado = menorISBN;
            if ((livro[r] = le(in)) == NULL) {
                // Marca a posicao no array como NULL se nao ha mais registros para ler.
                livro[r] = NULL;
            }

            // 5. Caso a chave deste ultimo seja menor do que a chave recem gravada,
            //  considera-lo congelado e ignora-lo no restante do processamento.
            if ((livro[r] == NULL) || (livro[r]->ISBN <= gravado)) {
                congelados[r] = 1;
            }

            // 6. Caso existam em memoria registros nao congelados, voltar ao passo 2.
            houverNaoCongelados = existemNaoCongelados(congelados, M);
        }
        // 7. Caso contrario.
        // - Fecha o arquivo de saida.
        if (out != NULL) {
            fclose(out);
        }

        // - Descongelar os registros congelados.
        for (int i = 0; i < M; i++) {
            if (livro[i] != NULL) {
                congelados[i] = 0;
            }
        }

        // - Abrir nova particao de saida.
        particoes++;
        sprintf(nomeParticao, "particao%d.dat", particoes);

        out = fopen(nomeParticao, "wb");

        if (out == NULL) {
            perror("Erro ao abrir novo arquivo de saida.");
            exit(EXIT_FAILURE);
        }
    }
    // Libera a memoria alocada para os registros em memoria.
    for (int i = 0; i < M; i++) {
        if (livro[i] != NULL) {
            free(livro[i]);
        }
    }
    // Retorna o numero total de particoes criadas.
    return particoes;
}

// Verifica se ha pelo menos um registro nao congelado.
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
