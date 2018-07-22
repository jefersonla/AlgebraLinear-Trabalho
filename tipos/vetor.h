#ifndef VETOR_H
#define VETOR_H

/* ------------------------------------------------------------- */
/*                       Constantes  Vetor                       */
/* ------------------------------------------------------------- */


/* ------------------------------------------------------------- */
/*                     Prototype definitions                     */
/* ------------------------------------------------------------- */

/* Vetor */
typedef struct strVetor Vetor;

/* ------------------------------------------------------------- */
/*                       Vetor  Structure                        */
/* ------------------------------------------------------------- */

typedef struct strVetor{
	/* Dimensão do vetor */
	int dimensao;

	/* Dados */
	double *coordenadas;
} Vetor, *ptrVetor;

/* ------------------ Token Structure Methods ------------------ */

/* Cria um novo vetor */
Matriz* newVetor(int dimensao);

/* Desaloca uma matriz */
bool deleteVetor(ptrVetor *vetor);

/* ------------------------------------------------------------- */

#endif
