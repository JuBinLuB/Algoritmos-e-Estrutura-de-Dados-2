#include <stdio.h>
#include <stdlib.h>

#include "sobrescrever.h"
#include "livro.h"
#include "usuario.h"

// Funcao para sobrescrever registros de livros do arquivo original pelo conteudo do novo arquivo.
void sobrescreverArquivoL(FILE *arquivoOriginal, FILE *novoArquivo, int tamanhoRegistro) {
    for (int i = 0; i < tamanhoArquivoL(arquivoOriginal); i++) {
        // Move o cursor para o registro "i" do arquivo original.
        fseek(arquivoOriginal, i * tamanhoRegistro, SEEK_SET);
        // Move o cursor para o registro "i" do novo arquivo.
        fseek(novoArquivo, i * tamanhoRegistro, SEEK_SET);
        // Le o registro "i" do novo arquivo.
        TLivro *l = leL(novoArquivo);
        if (l != NULL) {
            // Grava o registro "i" do novo arquivo na posicao "i" do arquivo original.
            salvaL(l, arquivoOriginal);
        }
    }
}

// Funcao para sobrescrever registros de usuarios do arquivo original pelo conteudo do novo arquivo.
void sobrescreverArquivoU(FILE *arquivoOriginal, FILE *novoArquivo, int tamanhoRegistro) {
    for (int i = 0; i < tamanhoArquivoU(arquivoOriginal); i++) {
        // Move o cursor para o registro "i" do arquivo original.
        fseek(arquivoOriginal, i * tamanhoRegistro, SEEK_SET);
        // Move o cursor para o registro "i" do novo arquivo.
        fseek(novoArquivo, i * tamanhoRegistro, SEEK_SET);
        // Le o registro "i" do novo arquivo.
        TUsuario *u = leU(novoArquivo);
        if (u != NULL) {
            // Grava o registro "i" do novo arquivo na posicao "i" do arquivo original.
            salvaU(u, arquivoOriginal);
        }
    }
}
