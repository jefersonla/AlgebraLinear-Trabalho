#include "utils.h"

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
