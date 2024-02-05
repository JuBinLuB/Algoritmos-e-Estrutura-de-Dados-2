#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define BEFORE_TEST before();

#define NOME_ARQUIVO_HASH "tabHash.dat"
#define NOME_ARQUIVO_DADOS "livros.dat"
#define M 7

#include <limits.h>
#include <stdlib.h>

#include "ufftest.h"
#include "listaLivros.h"
#include "livro.h"
#include "listaCompartimentos.h"
#include "compartimentoHash.h"
#include "encadeamentoExterior.h"

void before() {
	remove(NOME_ARQUIVO_HASH);
	remove(NOME_ARQUIVO_DADOS);
}

BEGIN_TESTS();

TEST("Cria Tabela Vazia. Testa o caso de tabela hash com compartimentos vazios");
if (!skip) {
	// Estamos usando tabela hash de tamanho 7 nos testes.
	// Adicionar 7 compartimentos que nao apontam para ninguem (prox = -1).
	ListaCompartimentos *tab_hash, *tab_hash_saida;

	tab_hash = criaCompartimentos(7,
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1));

	// M = 7 conforme definido no cabecalho desse arquivo.
	criarHash(NOME_ARQUIVO_HASH, M);

	tab_hash_saida = leCompartimentos(NOME_ARQUIVO_HASH);

	ASSERT_EQUAL_CMP(tab_hash, tab_hash_saida, cmpCompartimentos);
	liberaCompartimentos(tab_hash);
	liberaCompartimentos(tab_hash_saida);
}

TEST("Busca chave que eh encontrada na primeira tentativa");
if (!skip) {
	ListaCompartimentos *tab_hash;
	ListaLivros *tab_livro;

	tab_hash = criaCompartimentos(7,
		compartimentoHash(-1),
		compartimentoHash(0),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1));
	salvaCompartimentos(NOME_ARQUIVO_HASH, tab_hash);

	tab_livro = criaLivros(1,
		livro(50, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, OCUPADO));
	salvaLivros(NOME_ARQUIVO_DADOS, tab_livro);

	int end = buscar(50, NOME_ARQUIVO_HASH, NOME_ARQUIVO_DADOS, M);

	ASSERT_EQUAL(end, 0);
	// Endereco retornado deve ser igual a 0.
	liberaCompartimentos(tab_hash);
	liberaLivros(tab_livro);
}

TEST("Busca chave que existia mas foi removida");
if (!skip) {
	ListaCompartimentos *tab_hash;
	ListaLivros *tab_livro;

	tab_hash = criaCompartimentos(7,
		compartimentoHash(-1),
		compartimentoHash(0),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1));
	salvaCompartimentos(NOME_ARQUIVO_HASH, tab_hash);

	tab_livro = criaLivros(1,
		livro(50, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, LIBERADO));
	salvaLivros(NOME_ARQUIVO_DADOS, tab_livro);

	int end = buscar(50, NOME_ARQUIVO_HASH, NOME_ARQUIVO_DADOS, M);

	ASSERT_EQUAL(end, -1);
	// Endereco retornado deve ser igual a -1.
	liberaCompartimentos(tab_hash);
	liberaLivros(tab_livro);
}

TEST("Busca chave que eh encontrada na segunda tentativa");
if (!skip) {
	ListaCompartimentos *tab_hash;
	ListaLivros *tab_livro;

	tab_hash = criaCompartimentos(7,
		compartimentoHash(0),
		compartimentoHash(-1),
		compartimentoHash(4),
		compartimentoHash(1),
		compartimentoHash(-1),
		compartimentoHash(2),
		compartimentoHash(-1));
	salvaCompartimentos(NOME_ARQUIVO_HASH, tab_hash);

	tab_livro = criaLivros(6,
		livro(49, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, OCUPADO),
		livro(59, "O Hobbit", "J.R.R. Tolkien", "21/09/1937", 3, OCUPADO),
		livro(103, "Harry Potter", "J.K. Rowling", "26/06/1997", -1, OCUPADO),
		livro(10, "As Crônicas de Narnia", "C.S. Lewis", "16/10/1950", 5, OCUPADO),
		livro(51, "A Guerra dos Tronos", "George R.R. Martin", "06/08/1996", -1, OCUPADO),
		livro(87, "O Nome do Vento", "Patrick Rothfuss", "27/03/2007", -1, OCUPADO));
	salvaLivros(NOME_ARQUIVO_DADOS, tab_livro);

	int end = buscar(10, NOME_ARQUIVO_HASH, NOME_ARQUIVO_DADOS, M);

	ASSERT_EQUAL(end, 3);
	// Endereco retornado deve ser igual a 3.
	liberaCompartimentos(tab_hash);
	liberaLivros(tab_livro);
}

TEST("Busca chave inexistente");
if (!skip) {
	ListaCompartimentos *tab_hash;
	ListaLivros *tab_livro;

	tab_hash = criaCompartimentos(7,
		compartimentoHash(0),
		compartimentoHash(-1),
		compartimentoHash(4),
		compartimentoHash(1),
		compartimentoHash(-1),
		compartimentoHash(2),
		compartimentoHash(-1));
	salvaCompartimentos(NOME_ARQUIVO_HASH, tab_hash);

	tab_livro = criaLivros(6,
		livro(49, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, OCUPADO),
		livro(59, "O Hobbit", "J.R.R. Tolkien", "21/09/1937", 3, OCUPADO),
		livro(103, "Harry Potter", "J.K. Rowling", "26/06/1997", -1, OCUPADO),
		livro(3, "As Crônicas de Narnia", "C.S. Lewis", "16/10/1950", 5, OCUPADO),
		livro(51, "A Guerra dos Tronos", "George R.R. Martin", "06/08/1996", -1, OCUPADO),
		livro(87, "O Nome do Vento", "Patrick Rothfuss", "27/03/2007", -1, OCUPADO));
	salvaLivros(NOME_ARQUIVO_DADOS, tab_livro);

	int end = buscar(10, NOME_ARQUIVO_HASH, NOME_ARQUIVO_DADOS, M);

	ASSERT_EQUAL(end, -1);
	// Endereco retornado deve ser igual a -1.
	liberaCompartimentos(tab_hash);
	liberaLivros(tab_livro);
}

TEST("Busca chave que havia sido removida, mas foi reinserida mais adiante no arquivo");
if (!skip) {
	ListaCompartimentos *tab_hash;
	ListaLivros *tab_livro;
	tab_hash = criaCompartimentos(7,
		compartimentoHash(0),
		compartimentoHash(-1),
		compartimentoHash(4),
		compartimentoHash(1),
		compartimentoHash(-1),
		compartimentoHash(2),
		compartimentoHash(-1));
	salvaCompartimentos(NOME_ARQUIVO_HASH, tab_hash);

	tab_livro = criaLivros(7,
		livro(49, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, OCUPADO),
		livro(59, "O Hobbit", "J.R.R. Tolkien", "21/09/1937", 3, OCUPADO),
		livro(103, "Harry Potter", "J.K. Rowling", "26/06/1997", -1, OCUPADO),
		livro(10, "As Crônicas de Narnia", "C.S. Lewis", "16/10/1950", 5, LIBERADO),
		livro(51, "A Guerra dos Tronos", "George R.R. Martin", "06/08/1996", -1, OCUPADO),
		livro(87, "O Nome do Vento", "Patrick Rothfuss", "27/03/2007", 6, OCUPADO),
		livro(10, "O Ultimo Desejo", "Andrzej Sapkowski", "02/11/1993", -1, OCUPADO));
	salvaLivros(NOME_ARQUIVO_DADOS, tab_livro);

	int end = buscar(10, NOME_ARQUIVO_HASH, NOME_ARQUIVO_DADOS, M);

	ASSERT_EQUAL(end, 6);
	// Endereco retornado deve ser igual a 6.
	liberaCompartimentos(tab_hash);
	liberaLivros(tab_livro);
}

TEST("Insercao na 1 tentativa. Existe compartimento vazio na tabela para receber o registro");
if (!skip) {
	ListaCompartimentos *tab_hash, *tab_hash_saida;
	ListaLivros *tab_livro, *tab_livro_saida;

	tab_hash = criaCompartimentos(7,
		compartimentoHash(0),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1));
	salvaCompartimentos(NOME_ARQUIVO_HASH, tab_hash);

	tab_livro = criaLivros(1,
		livro(49, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, OCUPADO));
	salvaLivros(NOME_ARQUIVO_DADOS, tab_livro);

	int end = inserir(50, "O Hobbit", "J.R.R. Tolkien", "21/09/1937", NOME_ARQUIVO_HASH, NOME_ARQUIVO_DADOS, 1, M);
	ASSERT_EQUAL(end, 1);


	tab_hash->lista[1]->prox = 1;
	tab_hash_saida = leCompartimentos(NOME_ARQUIVO_HASH);
	ASSERT_EQUAL_CMP(tab_hash, tab_hash_saida, cmpCompartimentos);

	liberaLivros(tab_livro);
	tab_livro = criaLivros(2,
		livro(49, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, OCUPADO),
		livro(50, "O Hobbit", "J.R.R. Tolkien", "21/09/1937", -1, OCUPADO));
	tab_livro_saida = leLivros(NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL_CMP(tab_livro, tab_livro_saida, cmpLivros);

	liberaCompartimentos(tab_hash);
	liberaCompartimentos(tab_hash_saida);
	liberaLivros(tab_livro);
	liberaLivros(tab_livro_saida);
}

TEST("Insercao de registro com chave que ja existe");
if (!skip) {
	ListaCompartimentos *tab_hash, *tab_hash_saida;
	ListaLivros *tab_livro, *tab_livro_saida;

	tab_hash = criaCompartimentos(7,
		compartimentoHash(0),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1),
		compartimentoHash(-1));
	salvaCompartimentos(NOME_ARQUIVO_HASH, tab_hash);

	tab_livro = criaLivros(1,
		livro(49, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, OCUPADO));
	salvaLivros(NOME_ARQUIVO_DADOS, tab_livro);

	int end = inserir(49, "O Retorno do Rei", "J.R.R. Tolkien", "20/10/1955", NOME_ARQUIVO_HASH, NOME_ARQUIVO_DADOS, 1, M);
	ASSERT_EQUAL(end, -1);


	tab_hash_saida = leCompartimentos(NOME_ARQUIVO_HASH);
	ASSERT_EQUAL_CMP(tab_hash, tab_hash_saida, cmpCompartimentos);

	tab_livro_saida = leLivros(NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL_CMP(tab_livro, tab_livro_saida, cmpLivros);

	liberaCompartimentos(tab_hash);
	liberaCompartimentos(tab_hash_saida);
	liberaLivros(tab_livro);
	liberaLivros(tab_livro_saida);
}

TEST("Insercao no final da lista encadeada");
if (!skip) {
	ListaCompartimentos *tab_hash, *tab_hash_saida;
	ListaLivros *tab_livro, *tab_livro_saida;

	tab_hash = criaCompartimentos(7,
		compartimentoHash(0),
		compartimentoHash(-1),
		compartimentoHash(4),
		compartimentoHash(1),
		compartimentoHash(-1),
		compartimentoHash(2),
		compartimentoHash(-1));
	salvaCompartimentos(NOME_ARQUIVO_HASH, tab_hash);

	tab_livro = criaLivros(6,
		livro(49, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, OCUPADO),
		livro(59, "O Hobbit", "J.R.R. Tolkien", "21/09/1937", 3, OCUPADO),
		livro(103, "Harry Potter", "J.K. Rowling", "26/06/1997", -1, OCUPADO),
		livro(3, "As Crônicas de Narnia", "C.S. Lewis", "16/10/1950", 5, OCUPADO),
		livro(51, "A Guerra dos Tronos", "George R.R. Martin", "06/08/1996", -1, OCUPADO),
		livro(87, "O Nome do Vento", "Patrick Rothfuss", "27/03/2007", -1, OCUPADO));
	salvaLivros(NOME_ARQUIVO_DADOS, tab_livro);

	int end = inserir(10, "O Ultimo Desejo", "Andrzej Sapkowski", "02/11/1993", NOME_ARQUIVO_HASH, NOME_ARQUIVO_DADOS, 6, M);
	ASSERT_EQUAL(end, 6);

	tab_hash_saida = leCompartimentos(NOME_ARQUIVO_HASH);
	ASSERT_EQUAL_CMP(tab_hash, tab_hash_saida, cmpCompartimentos);

	liberaLivros(tab_livro);
	tab_livro = criaLivros(7,
		livro(49, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, OCUPADO),
		livro(59, "O Hobbit", "J.R.R. Tolkien", "21/09/1937", 3, OCUPADO),
		livro(103, "Harry Potter", "J.K. Rowling", "26/06/1997", -1, OCUPADO),
		livro(3, "As Crônicas de Narnia", "C.S. Lewis", "16/10/1950", 5, OCUPADO),
		livro(51, "A Guerra dos Tronos", "George R.R. Martin", "06/08/1996", -1, OCUPADO),
		livro(87, "O Nome do Vento", "Patrick Rothfuss", "27/03/2007", 6, OCUPADO),
		livro(10, "O Ultimo Desejo", "Andrzej Sapkowski", "02/11/1993", -1, OCUPADO));
	tab_livro_saida = leLivros(NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL_CMP(tab_livro, tab_livro_saida, cmpLivros);

	liberaCompartimentos(tab_hash);
	liberaCompartimentos(tab_hash_saida);
	liberaLivros(tab_livro);
	liberaLivros(tab_livro_saida);
}

TEST("Insercao de registro no espaco vazio deixado por registro excluido");
if (!skip) {
	ListaCompartimentos *tab_hash, *tab_hash_saida;
	ListaLivros *tab_livro, *tab_livro_saida;

	tab_hash = criaCompartimentos(7,
		compartimentoHash(0),
		compartimentoHash(-1),
		compartimentoHash(4),
		compartimentoHash(1),
		compartimentoHash(-1),
		compartimentoHash(2),
		compartimentoHash(-1));
	salvaCompartimentos(NOME_ARQUIVO_HASH, tab_hash);

	tab_livro = criaLivros(6,
		livro(49, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, OCUPADO),
		livro(59, "O Hobbit", "J.R.R. Tolkien", "21/09/1937", 3, OCUPADO),
		livro(103, "Harry Potter", "J.K. Rowling", "26/06/1997", -1, OCUPADO),
		livro(3, "As Crônicas de Narnia", "C.S. Lewis", "16/10/1950", 5, LIBERADO),
		livro(51, "A Guerra dos Tronos", "George R.R. Martin", "06/08/1996", -1, OCUPADO),
		livro(87, "O Nome do Vento", "Patrick Rothfuss", "27/03/2007", -1, OCUPADO));
	salvaLivros(NOME_ARQUIVO_DADOS, tab_livro);

	int end = inserir(10, "A Guerra dos Tronos", "George R.R. Martin", "06/08/1996", NOME_ARQUIVO_HASH, NOME_ARQUIVO_DADOS, 6, M);
	ASSERT_EQUAL(end, 3);

	tab_hash_saida = leCompartimentos(NOME_ARQUIVO_HASH);
	ASSERT_EQUAL_CMP(tab_hash, tab_hash_saida, cmpCompartimentos);

	liberaLivros(tab_livro);
	tab_livro = criaLivros(6,
		livro(49, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, OCUPADO),
		livro(59, "O Hobbit", "J.R.R. Tolkien", "21/09/1937", 3, OCUPADO),
		livro(103, "Harry Potter", "J.K. Rowling", "26/06/1997", -1, OCUPADO),
		livro(10, "A Guerra dos Tronos", "George R.R. Martin", "06/08/1996", 5, OCUPADO),
		livro(51, "A Guerra dos Tronos", "George R.R. Martin", "06/08/1996", -1, OCUPADO),
		livro(87, "O Nome do Vento", "Patrick Rothfuss", "27/03/2007", -1, OCUPADO));
	tab_livro_saida = leLivros(NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL_CMP(tab_livro, tab_livro_saida, cmpLivros);

	liberaCompartimentos(tab_hash);
	liberaCompartimentos(tab_hash_saida);
	liberaLivros(tab_livro);
	liberaLivros(tab_livro_saida);
}

TEST("Exclusao de chave inexistente");
if (!skip) {
	ListaCompartimentos *tab_hash, *tab_hash_saida;
	ListaLivros *tab_livro, *tab_livro_saida;

	tab_hash = criaCompartimentos(7,
		compartimentoHash(0),
		compartimentoHash(-1),
		compartimentoHash(4),
		compartimentoHash(1),
		compartimentoHash(-1),
		compartimentoHash(2),
		compartimentoHash(-1));
	salvaCompartimentos(NOME_ARQUIVO_HASH, tab_hash);

	tab_livro = criaLivros(6,
		livro(49, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, OCUPADO),
		livro(59, "O Hobbit", "J.R.R. Tolkien", "21/09/1937", 3, OCUPADO),
		livro(103, "Harry Potter", "J.K. Rowling", "26/06/1997", -1, OCUPADO),
		livro(3, "As Crônicas de Narnia", "C.S. Lewis", "16/10/1950", 5, LIBERADO),
		livro(51, "A Guerra dos Tronos", "George R.R. Martin", "06/08/1996", -1, OCUPADO),
		livro(87, "O Nome do Vento", "Patrick Rothfuss", "27/03/2007", -1, OCUPADO));
	salvaLivros(NOME_ARQUIVO_DADOS, tab_livro);

	int end = excluir(10, NOME_ARQUIVO_HASH, NOME_ARQUIVO_DADOS, M);
	ASSERT_EQUAL(end, -1);

	tab_hash_saida = leCompartimentos(NOME_ARQUIVO_HASH);
	ASSERT_EQUAL_CMP(tab_hash, tab_hash_saida, cmpCompartimentos);

	tab_livro_saida = leLivros(NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL_CMP(tab_livro, tab_livro_saida, cmpLivros);

	liberaCompartimentos(tab_hash);
	liberaCompartimentos(tab_hash_saida);
	liberaLivros(tab_livro);
	liberaLivros(tab_livro_saida);
}

TEST("Exclusao do primeiro noh da lista encadeada de um determinado compartimento");
if (!skip) {
	ListaCompartimentos *tab_hash, *tab_hash_saida;
	ListaLivros *tab_livro, *tab_livro_saida;

	tab_hash = criaCompartimentos(7,
		compartimentoHash(0),
		compartimentoHash(-1),
		compartimentoHash(4),
		compartimentoHash(1),
		compartimentoHash(-1),
		compartimentoHash(2),
		compartimentoHash(-1));
	salvaCompartimentos(NOME_ARQUIVO_HASH, tab_hash);

	tab_livro = criaLivros(6,
		livro(49, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, OCUPADO),
		livro(59, "O Hobbit", "J.R.R. Tolkien", "21/09/1937", 3, OCUPADO),
		livro(103, "Harry Potter", "J.K. Rowling", "26/06/1997", -1, OCUPADO),
		livro(3, "As Crônicas de Narnia", "C.S. Lewis", "16/10/1950", 5, LIBERADO),
		livro(51, "A Guerra dos Tronos", "George R.R. Martin", "06/08/1996", -1, OCUPADO),
		livro(87, "O Nome do Vento", "Patrick Rothfuss", "27/03/2007", -1, OCUPADO));
	salvaLivros(NOME_ARQUIVO_DADOS, tab_livro);

	int end = excluir(59, NOME_ARQUIVO_HASH, NOME_ARQUIVO_DADOS, M);
	ASSERT_EQUAL(end, 1);

	tab_hash_saida = leCompartimentos(NOME_ARQUIVO_HASH);
	ASSERT_EQUAL_CMP(tab_hash, tab_hash_saida, cmpCompartimentos);

	tab_livro->lista[1]->flag = LIBERADO;
	tab_livro_saida = leLivros(NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL_CMP(tab_livro, tab_livro_saida, cmpLivros);

	liberaCompartimentos(tab_hash);
	liberaCompartimentos(tab_hash_saida);
	liberaLivros(tab_livro);
	liberaLivros(tab_livro_saida);
}

TEST("Exclusao do ultimo noh da lista encadeada de um determinado compartimento");
if (!skip) {
	ListaCompartimentos *tab_hash, *tab_hash_saida;
	ListaLivros *tab_livro, *tab_livro_saida;

	tab_hash = criaCompartimentos(7,
		compartimentoHash(0),
		compartimentoHash(-1),
		compartimentoHash(4),
		compartimentoHash(1),
		compartimentoHash(-1),
		compartimentoHash(2),
		compartimentoHash(-1));
	salvaCompartimentos(NOME_ARQUIVO_HASH, tab_hash);

	tab_livro = criaLivros(6,
		livro(49, "A Sociedade do Anel", "J.R.R. Tolkien", "29/07/1954", -1, OCUPADO),
		livro(59, "O Hobbit", "J.R.R. Tolkien", "21/09/1937", 3, OCUPADO),
		livro(103, "Harry Potter", "J.K. Rowling", "26/06/1997", -1, OCUPADO),
		livro(3, "As Crônicas de Narnia", "C.S. Lewis", "16/10/1950", 5, LIBERADO),
		livro(51, "A Guerra dos Tronos", "George R.R. Martin", "06/08/1996", -1, OCUPADO),
		livro(87, "O Nome do Vento", "Patrick Rothfuss", "27/03/2007", -1, OCUPADO));
	salvaLivros(NOME_ARQUIVO_DADOS, tab_livro);

	int end = excluir(87, NOME_ARQUIVO_HASH, NOME_ARQUIVO_DADOS, M);
	ASSERT_EQUAL(end, 5);

	tab_hash_saida = leCompartimentos(NOME_ARQUIVO_HASH);
	ASSERT_EQUAL_CMP(tab_hash, tab_hash_saida, cmpCompartimentos);

	tab_livro->lista[5]->flag = LIBERADO;
	tab_livro_saida = leLivros(NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL_CMP(tab_livro, tab_livro_saida, cmpLivros);

	liberaCompartimentos(tab_hash);
	liberaCompartimentos(tab_hash_saida);
	liberaLivros(tab_livro);
	liberaLivros(tab_livro_saida);
}

END_TESTS();
