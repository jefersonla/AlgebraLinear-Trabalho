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
    unsigned int dimensao;

	/* Dados */
	double *coordenadas;

    /* Id do vetor */
    char *idVetor;
} Vetor, *ptrVetor;

/* ------------------ Vetor Structure Methods ------------------ */

/* Cria um novo vetor */
Vetor* newVetor(char *idVetor, unsigned int dimensao, double valores[]);

/* Desaloca um vetor */
bool deleteVetor(ptrVetor *vetor);

/* Clona um vetor */
Vetor* cloneVetor(Vetor *vetor);

/* Soma dois vetores */
Vetor* somaVetor(Vetor *vetor1, Vetor *vetor2);

/* Subtrais dois vetores */
Vetor* subtraiVetor(Vetor *vetor1, Vetor *vetor2);

/* Produto interno entre dois vetores */
double produtoInterno(Vetor *vetor1, Vetor *vetor2, bool *erro);

/* Norma do vetor */
double normaVetor(Vetor *vetor, bool *erro);

/* Imprime vetor */
void imprimeVetor(Vetor *vetor);

/* ------------------------------------------------------------- */

#endif
