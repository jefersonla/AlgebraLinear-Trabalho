#ifndef OPERACOES_MATRIZ_H
#define OPERACOES_MATRIZ_H

#include "matriz.h"
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

/* Troca de linhas */
bool operacaoTrocaLinha(Matriz *matriz, unsigned int linha1, unsigned int linha2);

/* Multiplica linha por escalar */
bool operacaoMultiplicaPorEscalar(Matriz *matriz, unsigned int linha, double escalar);

/* Soma uma linha a outra multiplicada por um escalar */
bool operacaoSomaEntreLinhas(Matriz *matriz, unsigned int linha_res, unsigned int linha_in, double escalar);

/* Soma de matrizes */
Matriz* somaMatriz(Matriz *matriz1, Matriz *matriz2);

/* Subtração de matrizes */
Matriz* subtracaoMatriz(Matriz *matriz1, Matriz *matriz2);

/* Produto de matrizes */
Matriz *produtoMatriz(Matriz *matriz1, Matriz *matriz2);

/* Multiplicação de matriz por escalar */
Matriz *multiplicacaoEscalarMatriz(Matriz *matriz, double escalar);

/* Transposta de uma matriz */
Matriz *transpostaMatriz(Matriz *matriz);

/* Inversa de uma matriz */
Matriz *inversaMatriz(Matriz *matriz);

/* Divisão de matriz */
Matriz *divisaoMatriz(Matriz *matriz1, Matriz *matriz2);

/* ------------------------------------------------------------- */

#endif
