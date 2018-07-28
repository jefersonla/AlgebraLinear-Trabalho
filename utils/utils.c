#include "utils.h"

#include <stdio.h>
#include <string.h>

/* Troca os valores entre celulas da matriz */
void swapMatrizCelula(MatrizCelula *a, MatrizCelula *b){
    MatrizCelula aux = (*a);

    /* Realiza a troca */
    (*a) = (*b);
    (*b) = aux;
}


/* Imprime numeros com tamanho fixo de digitos */
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
