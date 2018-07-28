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

/**
 *
 * Cria um novo vetor. Não confundir com arrays ou vectors de outras linguagens
 * os vetores aqui indicados são os vetores utilizados na fisica, matemática,
 * algébra e afins, ele consiste de uma sequência de valores ou coordenadas,
 * para este programa os valores de um vetor são chamados de coordenadas.
 *
 * @brief newVetor Cria um novo vetor
 * @param dimensao Dimensao do vetor
 * @param valores Valores do vetor
 * @return Ponteiro para o novo vetor
 */
Vetor* newVetor(char *idVetor, unsigned int dimensao, double valores[]);

/**
 *
 * Deleta um vetor qualquer.
 *
 * @brief deleteVetor Deleta um vetor
 * @param vetor Ponteiro do vetor a ser removido
 * @return true se foi possível deletar o vetor, e falso caso contrário
 */
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
