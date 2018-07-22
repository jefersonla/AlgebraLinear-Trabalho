#ifndef MATRIZ_H
#define MATRIZ_H

/* ------------------------------------------------------------- */
/*                       Constantes Matriz                       */
/* ------------------------------------------------------------- */
#define TIPO_CELULAS double

/* ------------------------------------------------------------- */
/*                     Prototype definitions                     */
/* ------------------------------------------------------------- */

/* Matriz */
typedef struct strMatriz Matriz;

/* ------------------------------------------------------------- */
/*                       Matriz Structure                        */
/* ------------------------------------------------------------- */

typedef struct strMatriz{
	/* Dimensões da matriz */
	int n_linhas;
	int n_colunas;
	int n_celulas;

	/* Conteúdo da matriz */
	TIPO_CELULAS *celulas;

	/* Estruturas da matriz */
	TIPO_CELULAS **linhas;
} Matriz, *ptrMatriz;

/* ------------------ Token Structure Methods ------------------ */

/* Cria uma nova matriz */
Matriz* newMatriz(int linhas, int colunas);

/* Desaloca uma matriz */
bool deleteMatriz(ptrMatriz *matriz);

/* ------------------------------------------------------------- */

#endif
