#ifndef LISTA_H
#define LISTA_H

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

/* ------------------------------------------------------------- */

#endif
