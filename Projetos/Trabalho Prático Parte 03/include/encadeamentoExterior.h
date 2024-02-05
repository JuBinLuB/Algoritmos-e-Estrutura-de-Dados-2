#ifndef ENCADEAMENTOEXTERIOR_H_INCLUDED
#define ENCADEAMENTOEXTERIOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Cria uma tabela hash vazia de tamanho "tam", e salva no arquivo nomeArquivoHash.
// Compartimento que nao tem lista encadeada associada deve ter valor igual a -1.
// nomeArquivoHash: nome do arquivo hash a ser criado.
// M: tamanho da tabela hash a ser criada.
void criarHash(char *nomeArquivoHash, int m);

// Executa busca em Arquivos por Encadeamento Exterior (Hash).
// Assumir que ponteiro para proximo noh eh igual a -1 quando nao houver proximo noh.
// ISBN: Chave do livro que esta sendo buscado.
// nomeArquivoHash: Nome do arquivo que contem a tabela hash.
// nomeArquivoDados: Nome do arquivo onde os dados estao armazenados.
// M: Tamanho da tabela hash (a funcao de hash e' h(x) = x mod m).
// Retorna o endereco onde o livro foi encontrado, ou -1 se nao for encontrado.
int buscar(int ISBN, char *nomeArquivoHash, char *nomeArquivoDados, int m);

// Executa insercao em Arquivos por Encadeamento Exterior (Hash).
// ISBN: Chave do livro que esta sendo inserido.
// nomeLivro: Nome do livro a ser inserido.
// nomeArquivoHash: Nome do arquivo que contem a tabela hash.
// nomeArquivoDados: Nome do arquivo onde os dados estao armazenados.
// numRegistros: Numero de registros que ja existem gravados no arquivo.
// Retorna o endereco onde o livro foi inserido, ou -1 se nao conseguiu inserir.
int inserir(int ISBN, char *nomeLivro, char* nomeAutor, char* dataPubli, char *nomeArquivoHash, char *nomeArquivoDados, int numRegistros, int m);

// Executa exclusao em Arquivos por Encadeamento Exterior (Hash).
// ISBN: Chave do livro a ser excluido.
// nomeArquivoHash: Nome do arquivo que contem a tabela hash.
// nomeArquivoDados: Nome do arquivo onde os dados estao armazenados.
// Retorna o endereco do livro que foi excluido, ou -1 se livro nao existe.
int excluir(int ISBN, char *nomeArquivoHash, char *nomeArquivoDados, int m);

#endif // ENCADEAMENTOEXTERIOR_H_INCLUDED
