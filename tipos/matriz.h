#ifndef MATRIZ_H
#define MATRIZ_H

/**
 * @file matriz.h
 * @author Alana Bispo e Jeferson Lima
 * @date 27 Jul 2018
 * @brief Estrutura Matriz, util para algebra e matemática.
 *
 * TODO!!!
 *
 */

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
#define TAM_ESPACADOR 3
#define TAM_PONTO_FLUTUANTE 3

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

/**
 *
 * Cria uma nova matriz A(n x m) (n - linhas por m - colunas)
 *
 * @param linhas Número de linhas
 * @param colunas Número de colunas
 * @param tipoValor Tipo do valor
 * @param valores Valores constantes ou nulos para serem assignados a matriz
 * @return Retorna uma nova matriz alocada
 */
Matriz* newMatriz(int linhas, int colunas, int tipoValor, MatrizCelula* valores[]);

/**
 * Desaloca uma matriz
 *
 * @param matriz Ponteiro da matriz a ser desalocada
 * @return true se matriz foi desalocada e falso caso contrário
 */
bool deleteMatriz(ptrMatriz *matriz);

/**
 *
 * Clona uma matriz. Retorna um ponteiro para uma nova matriz que representa
 * uma cópia exata da matriz passada por parametro.
 *
 * @brief cloneMatriz Clona uma matriz
 * @param matriz Matriz a ser clonada
 * @return Retorna o ponteiro para o clone da matriz
 */
Matriz* cloneMatriz(Matriz* matriz);

/**
 *
 * Atualiza maior valor da lista. Essa informação é importante ao exibir
 * os valores da lista visto que sabendo o maior valor é possível imprimir
 * a lista de valores adequadamente.
 *
 * @brief atualizaMaiorValorMatriz Atualiza o maior valor da lista
 * @param matriz Matriz cujo maior valor irá ser atualizado
 */
void atualizaMaiorValorMatriz(Matriz* matriz);

/**
 *
 * Imprime a matriz com as colunas com tamanho fixo e formatado, a precisão
 * dos números é impressa com 2 digitos de precisão.
 *
 * @brief imprimeMatriz Imprime a matriz formatada
 * @param matriz Matriz a ser impressa
 */
void imprimeMatriz(Matriz* matriz);

/* ------------------------------------------------------------- */

#endif
