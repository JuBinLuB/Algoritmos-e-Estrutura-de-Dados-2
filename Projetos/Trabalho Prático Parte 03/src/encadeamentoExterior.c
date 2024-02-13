#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "encadeamentoExterior.h"
#include "listaCompartimentos.h"
#include "compartimentoHash.h"
#include "listaLivros.h"
#include "livro.h"

// Cria uma tabela hash vazia de tamanho "tam", e salva no arquivo nomeArquivoHash.
void criarHash(char *nomeArquivoHash, int M) {
	// Cria uma lista de compartimentos inicialmente vazia.
	ListaCompartimentos *lc = criaCompartimentos(0);
	
	// Loop para adicionar compartimentos vazios a lista de compartimentos.
	for (int i = 0; i < M; i++) {
		// Adiciona um compartimento vazio a lista.
		addCompartimento(lc, -1);
	}
	// Salva a lista de compartimentos no arquivo hash.
	salvaCompartimentos(nomeArquivoHash, lc);
	// Libera a memoria alocada para a lista de compartimentos.
	liberaCompartimentos(lc);
}

// Executa busca em Arquivos por Encadeamento Exterior (Hash).
// Retorna o endereco onde o cliente foi encontrado, ou -1 se nao for encontrado.
int buscar(int ISBN, char *nomeArquivoHash, char *nomeArquivoDados, int M) {
	TLivro *livro;

	// Calcula o endereco aplicando a funcao h(x) = x mod M.
	int end = ISBN % M; 
	int rc = -1;
	int seguinte = 0;
	
	// Abre o arquivo de hash para leitura binaria.
	FILE *arqHash = fopen(nomeArquivoHash, "rb");

	// Posiciona o cursor no arquivo de hash no endereço correspondente ao compartimento.
	rc = fseek(arqHash, end * tamanhoCompartimento(), SEEK_SET);
	assert(rc == 0 && "Falha no seek\n");

	// Abre o arquivo de livros para leitura binaria.
	FILE *arqLivros = fopen(nomeArquivoDados, "rb");
	
	// Le o compartimento atual do arquivo de hash.
	TCompartimento *lido = leCompartimento(arqHash);

	// O endereço no arquivo de livros e' dado por lido->prox.
	seguinte = lido->prox;

	while (seguinte != -1) {
		// Posiciona o cursor no arquivo de livros no endereco correspondente ao proximo livro na lista encadeada.
		rc = fseek(arqLivros, seguinte * tamanhoRegistroL(), SEEK_SET);
		assert(rc == 0 && "Falha no seek\n");

		// Le o livro no endereco especificado.
		livro = leL(arqLivros);

		if (livro->ISBN == ISBN) {
			if (livro->flag == OCUPADO) {
				fclose(arqHash);
				fclose(arqLivros);
				free(livro);
				free(lido);
				// Retorna o endereço onde o livro foi encontrado.
				return seguinte;
			}
		}
		// Atualiza o proximo endereco na lista encadeada.
		seguinte = livro->prox;
		free(livro);
	}
	free(lido);
	fclose(arqHash);
	fclose(arqLivros);
	return -1;
}

// Executa insercao em Arquivos por Encadeamento Exterior (Hash).
// Retorna o endereco onde o livro foi inserido, ou -1 se nao conseguiu inserir.
int inserir(int ISBN, char *nomeLivro, char* nomeAutor, char* dataPubli, char *nomeArquivoHash, char *nomeArquivoDados, int numRegistros, int M) {
	// Declaracao de ponteiros para livro.
	TLivro *l = NULL;
	TLivro *atual = NULL;

	// Calculo do endereco usando a funcao de hash.
	int end = ISBN % M;

	// Inicializacao do endereco de escrita.
	int endEscrita = numRegistros * tamanhoRegistroL();
	int rc = -1;
	int seguinte = 0;
	int ultimo = 0;
	
	// Abertura do arquivos para leitura e escrita binaria.
	FILE *arqHash = fopen(nomeArquivoHash, "r+b");
	FILE *arqLivros = fopen(nomeArquivoDados, "r+b");

	// Declaracao de ponteiro para compartimento.
	TCompartimento *lido;
	
	// 1ª Tentativa: Obtencao direta do registro via compartimento hash.
	// Posicionamento do cursor no arquivo de hash.
	rc = fseek(arqHash, end * tamanhoCompartimento(), SEEK_SET);
	assert(rc == 0 && "Falha no seek\n");

	// Leitura do compartimento atual.
	lido = leCompartimento(arqHash);

	// Atribuicao do proximo endereco na lista encadeada.
	seguinte = lido->prox;

	// 2ª Tentativa: Busca do registro na lista de tratamento das colisoes.
	while (seguinte != -1) {
		// Posiciona o cursor no registro seguinte.
		rc = fseek(arqLivros, seguinte * tamanhoRegistroL(), SEEK_SET);
		assert(rc == 0 && "Falha no seek\n");

		// Leitura do livro atual.
		atual = leL(arqLivros);
				
		if (atual->ISBN == ISBN) {
			if (atual->flag == OCUPADO) {
				fclose(arqLivros);
				fclose(arqHash);
				free(atual);
				free(lido);
				// Retorna -1 indicando que o livro ja existe.
				return -1;
			}
		}
		// Se um dos registros com chave congruente % M esta liberado,
		// isso significa que ha uma posicao disponivel na lista encadeada para inserir o novo livro.
		if (atual->flag == LIBERADO) {
			// Atualizacao do endereco de escrita.
			endEscrita = seguinte * tamanhoRegistroL();
			// Atualizacao do proximo endereco na lista encadeada.
			seguinte = atual->prox;
			free(atual);
			break;
		}
		// Atualizacao do ultimo endereco na lista encadeada.
		ultimo = seguinte;
		// Atualizacao do proximo endereco na lista encadeada.
		seguinte = atual->prox;
		free(atual);
	}
	
	// Escrita do registro inserido.
	if (atual == NULL) {
		// Atualizacao do campo proximo no compartimento hash, caso a lista nao exista.
		rc = fseek(arqLivros, endEscrita, SEEK_SET);
		assert(rc == 0 && "Falha no seek\n");

		// Cria um novo livro.
		l = livro(ISBN, nomeLivro, nomeAutor, dataPubli, -1, OCUPADO);

		// Salva o livro no arquivo de livros.
		salvaL(l, arqLivros);

		// Atualizacao do campo "prox" no compartimento hash.
		lido->prox = endEscrita / tamanhoRegistroL();
		
		// Posiciona o cursor no arquivo de hash no endereco do calculado.
		rc = fseek(arqHash, end * tamanhoCompartimento(), SEEK_SET);
		assert(rc == 0 && "Falha no seek\n");

		// Salva o compartimento atualizado no arquivo de hash.
		salvaCompartimento(lido, arqHash);
	} else {
		// Escrita do registro sendo inserido.
		rc = fseek(arqLivros, endEscrita, SEEK_SET);
		assert(rc == 0 && "Falha no seek\n");

		// Cria um novo livro.
		l = livro(ISBN, nomeLivro, nomeAutor, dataPubli, seguinte , OCUPADO);

		// Salva o livro no arquivo de livros.
		salvaL(l, arqLivros);

		// Escrita do registro anterior, com seu "prox" atualizado.
		rc = fseek(arqLivros, ultimo * tamanhoRegistroL(), SEEK_SET);
		assert(rc == 0 && "Falha no seek\n");

		// Leitura do livro atual.
		atual = leL(arqLivros);
		atual->prox = endEscrita / tamanhoRegistroL();
		atual->flag = OCUPADO;

		// Posiciona o cursor no arquivo de livros no endereco correspondente ao ultimo livro.
		rc = fseek(arqLivros, ultimo * tamanhoRegistroL(), SEEK_SET);
		assert(rc == 0 && "Falha no seek\n");
		
		// Salva o livro atual no arquivo de livros.
		salvaL(atual, arqLivros);
		free(atual);
	}
	fclose(arqHash);
	fclose(arqLivros);
	free(l);
	free(lido);
    return endEscrita / tamanhoRegistroL();
}

// Executa exclusao em Arquivos por Encadeamento Exterior (Hash).
// Retorna o endereco do cliente que foi excluido, ou -1 se cliente nao existe.
int excluir(int ISBN, char *nomeArquivoHash, char *nomeArquivoDados, int M) {
	// Busca o endereço do livro com base no ISBN.
    int end = buscar(ISBN, nomeArquivoHash, nomeArquivoDados, M);
    int rc = -1;
    FILE *arqLivros;
	TLivro *livro;
	
	// Verifica se o livro foi encontrado.
    if (end != -1) {
		// Abre o arquivo de dados para leitura e escrita binaria.
		arqLivros = fopen(nomeArquivoDados, "r+b");

		// Posiciona o cursor no arquivo de livros no endereco correspondente ao livro a ser excluido.
    	rc = fseek(arqLivros, end * tamanhoRegistroL(), SEEK_SET);
    	assert(rc == 0 && "Falha no seek\n");
		
		// Le o livro no endereco especificado.
		livro = leL(arqLivros);

		// Atualiza o campo "flag" indicando que o livro foi excluido.
		livro->flag = LIBERADO;

		// Posiciona o cursor no arquivo de livros novamente para salvar a alteracao.
    	rc = fseek(arqLivros, end * tamanhoRegistroL(), SEEK_SET);
    	assert(rc == 0 && "Falha no seek\n");

		// Salva o livro com o campo "flag" atualizado.
    	salvaL(livro, arqLivros);
		
    	fclose(arqLivros);
    	free(livro);
	}
	return end;
}
