#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "randomizer.h"

// Gera datas aleatorias no formato "DD/MM/AAAA".
void gerarDataAleatoria(char *data) {
    // Define o intervalo de anos.
    int anoInicio = 1980;
    int anoFim = 2023;
    int bissexto = 0;

    // Gera um dia aleatorio no intervalo de 1 a 30.
    int dia = 1 + rand() % 30;
    // Gera um mes aleatorio no intervalo de 1 a 12.
    int mes = 1 + rand() % 12;
    // Gera um ano aleatorio no intervalo de 1980 a 2023.
    int ano = anoInicio + rand() % (anoFim - anoInicio + 1);

    // Verifica se o ano e' bissexto.
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        bissexto = 1;
    }

    // Se for bissexto e o mes for fevereiro, ajusta o dia para ate 29.
    if (bissexto && mes == 2) {
        dia = 1 + rand() % 29;
    } else if (!bissexto && mes == 2) {
        // Se nao for bissexto e for fevereiro, ajusta o dia para ate 28.
        dia = 1 + rand() % 28;
    }
    
    // Formata a data no estilo "DD/MM/AAAA" e armazena em "data".
    // Utiliza sprintf para formatar em string as partes da data.
    sprintf(data, "%02d/%02d/%d", dia, mes, ano);
}
