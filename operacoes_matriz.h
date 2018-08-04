#ifndef OPERACOES_MATRIZ_H
#define OPERACOES_MATRIZ_H

/**
 * @file operacoes_matriz.h
 * @author Alana Bispo e Jeferson Lima
 * @date 27 Jul 2018
 * @brief Operacoes simples entre matrizes.
 *
 * Contém as operações mais básicas entre matrizes como as quatro
 * operações, algumas operações de representação e as operações
 * elementares nas linhas de uma matriz. Para maiores informações
 * sobre essas funções ver os links abaixo.
 *
 * @see http://www.professores.uff.br/anamluz/wp-content/uploads/sites/36/2017/07/41.pdf
 * @see http://www.mat.ufmg.br/~rodney/notas_de_aula/matrizes.pdf
 */

#include "tipos/matriz.h"
#include <stdbool.h>

/* ------------------------------------------------------------- */
/*                     Constantes Operacoes                      */
/* ------------------------------------------------------------- */


/* ------------------------------------------------------------- */
/*                     Prototype definitions                     */
/* ------------------------------------------------------------- */


/* ------------------------------------------------------------- */
/*                     Operacoes Structure                       */
/* ------------------------------------------------------------- */


/* ---------------- Operacoes Structure Methods ---------------- */

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
bool operacaoTrocaLinha(Matriz *matriz, unsigned int linha1, unsigned int linha2);

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
bool operacaoMultiplicaPorEscalar(Matriz *matriz, unsigned int linha, double escalar);

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
bool operacaoSomaEntreLinhas(Matriz *matriz, unsigned int linha_res, unsigned int linha_in, double escalar);

/**
 *
 * Soma a matriz 1 a matriz 2 e retorna o resultado da expressão numa nova matriz.
 *
 * @brief somaMatriz Soma de matrizes
 * @param matriz1 Matriz 1
 * @param matriz2 Matriz 2
 * @return Retorna uma nova matriz com a soma das duas matrizes informadas
 */
Matriz* somaMatriz(Matriz *matriz1, Matriz *matriz2);

/**
 *
 * Subtrai a matriz 1 da matriz 2 e retorna o resultado da expressão numa nova matriz.
 *
 * @brief subtracaoMatriz Subtração de matrizes
 * @param matriz1 Matriz 1
 * @param matriz2 Matriz 2
 * @return Nova matriz contendo a subtração das duas matrizes informadas
 */
Matriz* subtracaoMatriz(Matriz *matriz1, Matriz *matriz2);

/**
 *
 * Realiza o produto entre duas matrizes. O produto entre duas matrizes é
 * dado pela multiplicação das linhas de uma matriz com a coluna da outra.
 * No produto de matrizes a matriz resultante tem formato
 * A (n x k) <- M1 (n x m) . M2 (m x k)
 *
 * @brief produtoMatriz Produto de matrizes
 * @param matriz1 Matriz 1
 * @param matriz2 Matriz 2
 * @return Retorna uma nova matriz, resultado do produto entre as matrizes
 */
Matriz *produtoMatriz(Matriz *matriz1, Matriz *matriz2);

/**
 *
 * Multiplica uma matriz por um escalar qualquer. A matriz resultante
 * será o resultado de todas as celulas dessa matriz multiplicada por esse
 * escalar.
 *
 * @brief multiplicacaoEscalarMatriz Multiplicação de matriz por escalar
 * @param matriz Matriz
 * @param escalar Escalar
 * @return Retorna uma nova matriz resultado da multiplicação desta pelo escalar
 */
Matriz *multiplicacaoEscalarMatriz(Matriz *matriz, double escalar);

/**
 *
 * Transposta de uma matriz. Retorna a transposta de uma matriz
 * que é basicamente uma matriz cujas as linhas são as colunas
 * da matriz de entrada.
 *
 * @brief transpostaMatriz Realiza a operação transposta de uma matriz
 * @param matriz Matriz
 * @return Retorna uma nova matriz que representa a transposta desta
 */
Matriz *transpostaMatriz(Matriz *matriz);

/* Inversa de uma matriz */
// TODO
Matriz *inversaMatriz(Matriz *matriz);

/* Divisão de matriz */
// TODO
Matriz *divisaoMatriz(Matriz *matriz1, Matriz *matriz2);

/* ------------------------------------------------------------- */

#endif
