#ifndef MATRIZ_H
#define MATRIZ_H

/* ------------------------------------------------------------- */
/*                       Constantes Matriz                       */
/* ------------------------------------------------------------- */


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

	/* Conteúdo da matriz */
	double *celulas;

	/* Estruturas da matriz */
	double **linhas;
	double **colunas;
	double **diagonais_principais;
	double **diagonais_secundarias;
} Matriz, *ptrMatriz;

/* ------------------ Token Structure Methods ------------------ */

/* Cria uma nova matriz */
Matriz* newMatriz(int linhas, int colunas);

/* Desaloca uma matriz */
bool deleteMatriz(ptrMatriz *matriz);

/* ------------------------------------------------------------- */

#endif
