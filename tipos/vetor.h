#ifndef VETOR_H
#define VETOR_H

#include <stdbool.h>

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

/* ------------------ Vetor Structure Methods ------------------ */

/* Cria um novo vetor */
Vetor* newVetor(int dimensao, double valores[]);

/* Desaloca um vetor */
bool deleteVetor(ptrVetor *vetor);

/* Clona um vetor */
Vetor* cloneVetor(Vetor *vetor);

/* ------------------------------------------------------------- */

#endif
