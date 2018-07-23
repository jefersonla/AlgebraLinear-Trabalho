#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdbool.h>

/* ------------------------------------------------------------- */
/*                       Constantes Matriz                       */
/* ------------------------------------------------------------- */

/* Tipos de matriz */
#define MATRIZ_VAZIA 0
#define MATRIZ_CONSTANTE 1
#define MATRIZ_IDENTIDADE 2
#define MATRIZ_VALORES 3

/* Tamanho do range de tipos */
#define MATRIZ_TIPO_MIN 0
#define MATRIZ_TIPO_MAX 3

/* Tamanho do espaçador */
#define TAM_ESPACADOR 6

/* ------------------------------------------------------------- */
/*                     Prototype definitions                     */
/* ------------------------------------------------------------- */

/* Matriz */
typedef struct strMatriz Matriz;

/* ------------------------------------------------------------- */
/*                       Matriz Structure                        */
/* ------------------------------------------------------------- */

typedef double MatrizCelula;

typedef struct strMatriz{
	/* Dimensões da matriz */
    int nLinhas;
    int nColunas;
    int nCelulas;

    /* Maior valor da matriz */
    MatrizCelula maiorValor;

	/* Conteúdo da matriz */
    MatrizCelula *celulas;

	/* Estruturas da matriz */
    MatrizCelula **linhas;
} Matriz, *ptrMatriz;

/* ------------------ Matriz Structure Methods ----------------- */

/* Cria uma nova matriz */
Matriz* newMatriz(int linhas, int colunas, int tipoValor, MatrizCelula* valores[]);

/* Desaloca uma matriz */
bool deleteMatriz(ptrMatriz *matriz);

/* Clona uma matriz */
Matriz* cloneMatriz(Matriz* matriz);

/* Exibe a matriz formatada */
void imprimeMatriz(Matriz* matriz);

/* ------------------------------------------------------------- */

#endif
