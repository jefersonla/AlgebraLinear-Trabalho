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


/**
 * @brief Vetor de n coordenadas.
 *
 * Este tipo define a estrutura matemática vetor. Um vetor de n coordenadas
 * é uma estrutura similar a um array, porém diferentemente desta o Vetor
 * propriamente dito tem propriedades matemáticas importantes
 * por isso a existência deste.
 */
typedef struct strVetor{
	/* Dimensão do vetor */
    unsigned int dimensao; /**< Dimensão é o número de coordenadas que um vetor possui. */

	/* Dados */
    double *coordenadas; /**< As coordenadas são os valores ordenados em cada posição do vetor. */

    /* Id do vetor */
    char *idVetor; /**< String que contém a identificação do vetor. */
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

/**
 *
 * Clona um vetor qualquer. O resultado do clone é retornado por essa função
 * em caso de erro é retornado um ponteiro NULL.
 *
 * @brief cloneVetor Clona um vetor
 * @param vetor Vetor a ser clonado
 * @return Ponteiro para vetor clonado
 */
Vetor* cloneVetor(Vetor *vetor);

/* Soma dois vetores */
// TODO
Vetor* somaVetor(Vetor *vetor1, Vetor *vetor2);

/* Subtrais dois vetores */
// TODO
Vetor* subtraiVetor(Vetor *vetor1, Vetor *vetor2);

/* Produto interno entre dois vetores */
// TODO
double produtoInterno(Vetor *vetor1, Vetor *vetor2, bool *erro);

/* Norma do vetor */
// TODO
double normaVetor(Vetor *vetor, bool *erro);

/* Imprime vetor */
// TODO
void imprimeVetor(Vetor *vetor);

/* ------------------------------------------------------------- */

#endif
