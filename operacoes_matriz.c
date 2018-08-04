#include "operacoes_matriz.h"
#include "utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*------------ Operacoes Structure Methods ------------ */

/* Troca de linhas */
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

/* Multiplica linha por escalar */
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
    if(doubleIgualZero(escalar)){
        printError("ESCALAR NAO PODE SER ZERO!");
        return false;
    }

    /* Multiplica o valor das linhas pelo escalar */
    int i;
    for(i = 0; i < matriz->nColunas; i++){
        matriz->linhas[linha][i] = matriz->linhas[linha][i] * escalar;

        /* Se a operação resultante tiver um valor maior do que o anterior */
        if(matriz->maiorValor < matriz->linhas[linha][i] )
            matriz->maiorValor = fabs(matriz->linhas[linha][i]);
    }

    return true;
}

/* Soma uma linha a outra multiplicada por um escalar */
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
    if(doubleIgualZero(escalar)){
        printError("ESCALAR NAO PODE SER ZERO!");
        return false;
    }

    /* Soma os valores da linha com os valores da outra multiplicada pelo escalar */
    int i;
    for(i = 0; i < matriz->nColunas; i++){
        matriz->linhas[linha_res][i] = matriz->linhas[linha_res][i] + (matriz->linhas[linha_in][i] * escalar);

        /* Se a operação resultante tiver um valor maior do que o anterior */
        if(matriz->maiorValor < matriz->linhas[linha_res][i] )
            matriz->maiorValor = fabs(matriz->linhas[linha_res][i]);
    }

    return true;
}

/* Soma de matrizes */
Matriz* somaMatriz(Matriz *matriz1, Matriz *matriz2){
    /* Verifica se as matrizes são consistentes */
    if(matriz1 == NULL || matriz2 == NULL){
        printError("MATRIZES INVALIDAS UTILIZADAS! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return NULL;
    }

    /* Verifica se as matrizes tem o mesmo tamanho */
    if(matriz1->nLinhas != matriz2->nLinhas || matriz1->nColunas != matriz2->nColunas){
        printError("AS MATRIZES PRECISAM TER AS MESMAS DIMENSOES! (M1(n x k) e M2(n x k)");
        return NULL;
    }

    /* Satisfeita as duas condições acima criamos uma nova matriz vazia */
    Matriz *matriz_resultado = newMatriz(matriz1->nLinhas, matriz1->nColunas, MATRIZ_VAZIA, NULL);

    /* Checa se não houve erros ao alocar a matriz resultante */
    if(matriz_resultado == NULL){
        printError("PROBLEMAS AO CRIAR A NOVA MATRIZ! NAO E POSSIVEL CONTINUAR!");
        return NULL;
    }

    /* Escreve o resultado da operação na nova matriz */
    int i, j;
    for(i = 0; i < matriz1->nLinhas; i++)
        for(j = 0; j < matriz1->nColunas; j++)
            matriz_resultado->linhas[i][j] = matriz1->linhas[i][j] + matriz2->linhas[i][j];
    atualizaMaiorValorMatriz(matriz_resultado);

    return matriz_resultado;

}

/* Subtração de matrizes */
Matriz* subtracaoMatriz(Matriz *matriz1, Matriz *matriz2){
    /* Verifica se as matrizes são consistentes */
    if(matriz1 == NULL || matriz2 == NULL){
        printError("MATRIZES INVALIDAS UTILIZADAS! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return NULL;
    }

    /* Verifica se as matrizes tem o mesmo tamanho */
    if(matriz1->nLinhas != matriz2->nLinhas || matriz1->nColunas != matriz2->nColunas){
        printError("AS MATRIZES PRECISAM TER AS MESMAS DIMENSOES! (M1(n x k) e M2(n x k)");
        return NULL;
    }

    /* Satisfeita as duas condições acima criamos uma nova matriz vazia */
    Matriz *matriz_resultado = newMatriz(matriz1->nLinhas, matriz1->nColunas, MATRIZ_VAZIA, NULL);

    /* Checa se não houve erros ao alocar a matriz resultante */
    if(matriz_resultado == NULL){
        printError("PROBLEMAS AO CRIAR A NOVA MATRIZ! NAO E POSSIVEL CONTINUAR!");
        return NULL;
    }

    /* Escreve o resultado da operação na nova matriz */
    int i, j;
    for(i = 0; i < matriz1->nLinhas; i++)
        for(j = 0; j < matriz1->nColunas; j++)
            matriz_resultado->linhas[i][j] = matriz1->linhas[i][j] - matriz2->linhas[i][j];
    atualizaMaiorValorMatriz(matriz_resultado);

    return matriz_resultado;
}

/* Produto de matrizes */
Matriz *produtoMatriz(Matriz *matriz1, Matriz *matriz2){
    /* Verifica se as matrizes são consistentes */
    if(matriz1 == NULL || matriz2 == NULL){
        printError("MATRIZES INVALIDAS UTILIZADAS! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return NULL;
    }

    /* Verifica se a matriz tem o formato desejado */
    if(matriz1->nColunas != matriz2->nLinhas){
        printError("A MATRIZ 1 PRECISA TER UM NUMERO DE COLUNAS IGUAL AO NUMERO DE LINHAS DA MATRIZ 2! (M1(n x k) e M2(k x m)");
        return NULL;
    }

    /* Satisfeita as duas condições acima criamos uma nova matriz vazia */
    Matriz *matriz_resultado = newMatriz(matriz1->nLinhas, matriz2->nColunas, MATRIZ_VAZIA, NULL);

    /* Checa se não houve erros ao alocar a matriz resultante */
    if(matriz_resultado == NULL){
        printError("PROBLEMAS AO CRIAR A NOVA MATRIZ! NAO E POSSIVEL CONTINUAR!");
        return NULL;
    }

    /* Escreve o resultado da operação na nova matriz */
    int i, j, k;
    for(i = 0; i < matriz1->nLinhas; i++)
        for(j = 0; j < matriz2->nColunas; j++)
            for(k = 0; k < matriz1->nColunas; k++)
                matriz_resultado->linhas[i][j] += matriz1->linhas[i][k] * matriz1->linhas[k][j];
    atualizaMaiorValorMatriz(matriz_resultado);

    return matriz_resultado;
}

/* Multiplicação de matriz por escalar */
Matriz *multiplicacaoEscalarMatriz(Matriz *matriz, double escalar){
    /* Verifica se as matrizes são consistentes */
    if(matriz == NULL){
        printError("MATRIZ INVALIDA UTILIZADA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return NULL;
    }

    /* Criamos uma nova matriz vazia */
    Matriz *matriz_resultado = newMatriz(matriz->nLinhas, matriz->nColunas, MATRIZ_VAZIA, NULL);

    /* Checa se não houve erros ao alocar a matriz resultante */
    if(matriz_resultado == NULL){
        printError("PROBLEMAS AO CRIAR A NOVA MATRIZ! NAO E POSSIVEL CONTINUAR!");
        return NULL;
    }

    /* Escreve o resultado da operação na nova matriz */
    int i, j;
    for(i = 0; i < matriz->nLinhas; i++)
        for(j = 0; j < matriz->nColunas; j++)
            matriz_resultado->linhas[i][j] = matriz->linhas[i][j] * escalar;
    atualizaMaiorValorMatriz(matriz_resultado);

    return matriz_resultado;
}

/* Transposta de uma matriz */
Matriz *transpostaMatriz(Matriz *matriz){
    /* Verifica se as matrizes são consistentes */
    if(matriz == NULL){
        printError("MATRIZ INVALIDA UTILIZADA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return NULL;
    }

    /* Criamos uma nova matriz vazia */
    Matriz *matriz_resultado = newMatriz(matriz->nColunas, matriz->nLinhas, MATRIZ_VAZIA, NULL);

    /* Checa se não houve erros ao alocar a matriz resultante */
    if(matriz_resultado == NULL){
        printError("PROBLEMAS AO CRIAR A NOVA MATRIZ! NAO E POSSIVEL CONTINUAR!");
        return NULL;
    }

    /* Escreve o resultado da operação na nova matriz */
    int i, j;
    for(i = 0; i < matriz->nColunas; i++)
        for(j = 0; j < matriz->nLinhas; j++)
            matriz_resultado->linhas[i][j] = matriz->linhas[j][i];
    atualizaMaiorValorMatriz(matriz_resultado);

    return matriz_resultado;
}

/**
 *
 * Escalona uma matriz para obter sua inversa
 *
 * @brief inversaMatriz Inversa de uma matriz
 * @param matriz
 * @return
 */
Matriz *inversaMatriz(Matriz *matriz);

/* Divisão de matriz */
Matriz *divisaoMatriz(Matriz *matriz1, Matriz *matriz2);
