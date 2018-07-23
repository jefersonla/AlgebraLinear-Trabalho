#include "utils.h"

#include <stdio.h>
#include <string.h>

/**
 *
 * Troca os valores entre as celulas de uma matriz
 *
 * @brief swapMatrizCelula Troca os valores entre celulas de uma matriz
 * @param a Primeiro valor
 * @param b Segundo valor
 */
void swapMatrizCelula(MatrizCelula *a, MatrizCelula *b){
    MatrizCelula aux = (*a);

    /* Realiza a troca */
    (*a) = (*b);
    (*b) = aux;
}

/**
 *
 * Imprime um número com um número fixado de digitos, ou seja imprime um numero
 * para colunas de tamanho fixado.
 *
 * @brief imprimeColunaFixa Imprime um numero com uma quantidade especifica de digitos
 * @param buf Buffer para armazenar a string do numero
 * @param num Numero a ser impresso
 * @param tamColuna Tamanho da coluna do número em questão
 */
void imprimeColunaFixa(char *buf, MatrizCelula num, int tamColuna){

    /* Copia o numero para o buffer */
    int digitosImpressos = snprintf(buf, (size_t)tamColuna, "%.2lf", num);

    /* Preenche o buffer com o caractere ' ' */
    int i;
    for(i = digitosImpressos; i < (tamColuna - 1); i++)
        buf[i] = ' ';

    /* Caractere de fim de string */
    buf[tamColuna - 1] = 0;

    /* Imprime o numero formatado */
    printf("%s", buf);
}
