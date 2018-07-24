#ifndef OPERACOES_COMPLEXAS_H
#define OPERACOES_COMPLEXAS_H

#include "tipos/matriz.h"
#include "tipos/vetor.h"

/* ------------------------------------------------------------- */
/*                      Constantes  Operações                    */
/* ------------------------------------------------------------- */

/* ------------------------------------------------------------- */
/*                      Estruturas  Globais                      */
/* ------------------------------------------------------------- */

/* ------------------------------------------------------------- */
/*                        Funções Operações                      */
/* ------------------------------------------------------------- */

/* Executa o metodo de Gauss para encontrar as raizes do sistema de equação */
Vetor* operacaoGaussMatriz(Matriz *matriz);

/* Executa metodo de Gauss-Jordan para encontrar as raizes do sistema de equação */
Vetor* operacaoGausJordanMatriz(Matriz *matriz);

/* Encontra o Kernel de uma Matriz */
Vetor* operacaoKernelMatriz(Matriz *matriz);

/* Encontra uma base para a matriz */
Matriz* operacaoBaseMatriz(Matriz* matriz);

/* Encontra o determinante da matriz */
double operacaoDeterminanteMatriz(Matriz *matriz, bool *erro);

/* ------------------------------------------------------------- */

#endif
