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
#define MATRIZ_VAZIA 0 /**< Define uma matriz vazia, ou seja com 0 em todos os valores */
#define MATRIZ_CONSTANTE 1 /**< Define uma matriz constante que terá o valor recebido pela função */
#define MATRIZ_IDENTIDADE 2 /**< Define a matriz identidade aonde na diagonal principal teremos valor 1 */
#define MATRIZ_VALORES 3 /**< Define uma matriz que sera inicializada pelos valores passados por parametro */

/* Tamanho do range de tipos */
#define MATRIZ_TIPO_MIN 0 /**< Tipo de matriz minimo é a matriz vazia logo 0 */
#define MATRIZ_TIPO_MAX 3 /**< Tipo máximo da matriz é a matriz valores logo 3 */

/* Tamanho do espaçador */
#define TAM_ESPACADOR 3 /**< Tamanho do espaço entre as colunas na impressão de colunas */
#define TAM_PONTO_FLUTUANTE 3 /**< Define quantos caracteres cada double terá */

/* ------------------------------------------------------------- */
/*                     Prototype definitions                     */
/* ------------------------------------------------------------- */

/* Matriz */
typedef struct strMatriz Matriz;

/* ------------------------------------------------------------- */
/*                       Matriz Structure                        */
/* ------------------------------------------------------------- */

/**
 * @brief Tipo a ser utilizado nas celulas da matriz.
 *
 * Esta função define o tipo a ser utilizado nas celulas da matriz.
 * Qualquer tipo pode ser utilizado, porém é válido lembrar que modificações
 * são necessárias caso não se utilize um tipo básico como int, long, float
 * ou double, visto que na linguagem C não é possível modificar o comportamento
 * dos operadores básicos como +, -, *, / porém apesar disto existem funções
 * auxiliares que executam as mesmas operações gerando novos resultados com base
 * nos dados passados. Assim a operação de soma entre duas Matrizes M1 e M2
 * pode ser escrita como Mr <- somaMatriz(M1, M2), o mesmo vale obviamente para
 * o conteúdo das celulas caso utilize um tipo distinto como seria o caso de uma
 * matriz de vetores ou de frações.
 */
typedef double MatrizCelula;

/**
 * @brief Matriz n x m.
 *
 * Este tipo define a estrutura matemática matriz. Uma matriz é um vetor
 * de vetores. As matrizes definidas por esse tipo são bidimensionais
 * aonde cada celula da matriz tem coodenadas i,j logo M(i,j) define uma
 * celula da matriz M de tamanho n x m, sendo n o número de linhas e m
 * o número de colunas. Esse tipo possui metodos auxiliares que auxiliam
 * a execução de todas as operações básicas.
 */
typedef struct strMatriz{
	/* Dimensões da matriz */
    int nLinhas; /**< Número de linhas da matriz */
    int nColunas; /**< Número de colunas da matriz */
    int nCelulas; /**< Número de celulas da matriz */

    /* Maior valor da matriz */
    MatrizCelula maiorValor; /**< Maior valor presente na matriz */

	/* Conteúdo da matriz */
    MatrizCelula *celulas; /**< Contéudo da matriz em forma de array */

	/* Estruturas da matriz */
    MatrizCelula **linhas; /**< Ponteiros para as posições do vetor de celulas que define as linhas */
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
