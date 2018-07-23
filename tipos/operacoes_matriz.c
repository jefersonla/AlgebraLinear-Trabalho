#include "./operacoes_matriz.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*------------ Operacoes Structure Methods ------------ */

/**
 *
 * Troca uma linha da matriz com outra da mesma. Esta operação elementar
 * apenas trocar o valor das linhas, não é possível modificar os valores
 * das mesmas nesta operação. Formato L1 <-> L2 .
 *
 * @brief operacaoTrocaLinha Troca os valores de uma linha com o de outra
 * @param matriz Matriz a ser utilizada na operação
 * @param linha1 Linha 1 da matriz que receberá a operação
 * @param linha2 Linha 2 da matriz que receberá a operação
 * @return Retorna true se a operação ocorreu bem e falso caso contrário
 */
bool operacaoTrocaLinha(Matriz *matriz, unsigned int linha1, unsigned int linha2){
    /* Verifica se a matriz */
    if(matriz == NULL){
        printError("MATRIZ INVALIDA! NAO E POSSIVEL REALIZAR A TROCA!");
        return false;
    }

    /* Verifica se as linhas são validas */
    if(linha1 == 0 || linha2 == 0){
        printError("AS LINHAS DA MATRIZ SAO INDEXADAS DE 1 A N");
        return false;
    }

    /* Decrementa o valor das linhas */
    linha1--;
    linha2--;

    /* Troca os valores de cada coluna das linhas indicadas */
    int i;
    for(i = 0; i < matriz->nColunas; i++)
        swapMatrizCelula(&matriz->linhas[linha1][i], &matriz->linhas[linha2][i]);

    return true;
}

/**
 *
 * Multiplica uma linha por um escalar qualquer. Esta operação dada uma linha da matriz
 * multiplica a mesma por um escalar que pode ser positivo ou negativo. Este escalar
 * tem que ser diferente de 0. Formato L1 <- L1 * E .
 *
 * @brief operacaoMultiplicaPorEscalar Multiplica uma linha por um escalar
 * @param matriz Matriz que receberá a operação
 * @param linha Numero da linha que receberá a operação
 * @param escalar Número diferente de 0 a qual as celulas da linha receberão a operação
 * @return Retorna true se a operação não teve erros e falso caso contrário
 */
bool operacaoMultiplicaPorEscalar(Matriz *matriz, unsigned int linha, double escalar){
    /* Checa se a matriz é válida */
    if(matriz == NULL){
        printError("MATRIZ INVALIDA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return false;
    }

    /* Verifica se as linhas são validas */
    if(linha == 0){
        printError("AS LINHAS DA MATRIZ SAO INDEXADAS DE 1 A N");
        return false;
    }

    /* Decrementa o valor da linha para acompanhar o endereçamento da linguagem C */
    linha--;

    /* Checa se o escalar é válido */
    if(fabs(escalar) <= 10e-7){
        printError("ESCALAR NAO PODE SER ZERO!");
        return false;
    }

    /* Multiplica o valor das linhas pelo escalar */
    int i;
    for(i = 0; i < matriz->nColunas; i++)
        matriz->linhas[linha][i] = matriz->linhas[linha][i] * escalar;

    return true;
}

/**
 *
 * Soma uma linha a outra multiplicada por um escalar. Esta operação aplica uma soma
 * de uma linha com outra, com a outra linha podendo ser modificada por um escalar
 * no formato L1 <- L1 + E * L2. É importante lembrar que L1 nesse formato não pode
 * ser modificado nesta operação e somente L2 será multiplicado pelo escalar.
 * O escalar não pode ser igual a 0, porém pode ser um número negativo ou uma fração.
 *
 * @brief operacaoSomaEntreLinhas Soma uma linha a outra multiplicada por um escalar
 * @param matriz Matriz que irá receber a operação
 * @param linha_res Linha do resultado
 * @param linha_in Linha que será somada a linha que irá receber o resultado
 * @param escalar Escalar que irá ser multiplicado pela outra linha
 * @return Retorna true se a operação ocorreu bem, e falso caso contrário
 */
bool operacaoSomaEntreLinhas(Matriz *matriz, unsigned int linha_res, unsigned int linha_in, double escalar){
    /* Verifica se a matriz */
    if(matriz == NULL){
        printError("MATRIZ INVALIDA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return false;
    }

    /* Verifica se as linhas são validas */
    if(linha_res == 0 || linha_in == 0){
        printError("AS LINHAS DA MATRIZ SAO INDEXADAS DE 1 A N");
        return false;
    }

    /* Decrementa o valor das linhas */
    linha_res--;
    linha_in--;

    /* Checa se o escalar é válido */
    if(fabs(escalar) <= 10e-7){
        printError("ESCALAR NAO PODE SER ZERO!");
        return false;
    }

    /* Soma os valores da linha com os valores da outra multiplicada pelo escalar */
    int i;
    for(i = 0; i < matriz->nColunas; i++)
        matriz->linhas[linha_res][i] = matriz->linhas[linha_res][i] + (matriz->linhas[linha_in][i] * escalar);

    return true;
}
