# Manipulação de Arquivos em C

Este é um programa em C que demonstra a manipulação de arquivos de texto e binários. Ele oferece quatro funções principais: `writex`, `readx`, `writeb`, e `readb`, que permitem escrever e ler dados em arquivos de texto e binários. O programa também inclui um exemplo no `main` que demonstra como usar essas funções.

## Funções

### `writex` - Escrever em um arquivo de texto

A função `writex` permite escrever um vetor de inteiros em um arquivo de texto.

**Parâmetros:**
- `f`: Nome do arquivo de texto onde os dados serão gravados.
- `vector`: Um ponteiro para o vetor de inteiros que será escrito no arquivo.
- `n`: O número de elementos a serem escritos.

### `readx` - Ler de um arquivo de texto

A função `readx` lê e imprime os dados armazenados em um arquivo de texto.

**Parâmetros:**
- `f`: Nome do arquivo de texto a ser lido.

### `writeb` - Escrever em um arquivo binário

A função `writeb` permite escrever um vetor de inteiros em um arquivo binário.

**Parâmetros:**
- `f`: Nome do arquivo binário onde os dados serão gravados.
- `vector`: Um ponteiro para o vetor de inteiros que será escrito no arquivo.
- `n`: O número de elementos a serem escritos.

### `readb` - Ler de um arquivo binário

A função `writeb` lê e imprime os dados armazenados em um arquivo binário.

**Parâmetros:**
- `f`: Nome do arquivo binário a ser lido.

### Exemplo no `main`

O código no `main` deste programa demonstra como usar as funções para escrever e ler dados em arquivos de texto e binários. Ele cria um vetor de inteiros chamado `vector` e realiza as seguintes ações:

1. Escreve os dados em um arquivo de texto chamado "testex.txt".
2. Lê os dados do arquivo de texto "testex.txt" e imprime seu conteúdo no console.
3. Escreve os dados em um arquivo binário chamado "testeb.dat".
4. Lê os dados do arquivo binário "testeb.dat" e imprime seu conteúdo no console.
