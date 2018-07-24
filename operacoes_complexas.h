#include "tipos/vetor.h"
#include "tipos/matriz.h"
#include "operacoes_matriz.h"
#include "utils/utils.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 *
 * Realiza o metodo de Gauss para encontrar as raizes de um sistema de equações. Essa função
 * assume que a matriz contém ao menos duas colunas e a última é sempre o resultado.
 * O retorno dessa função é um vetor de doubles com a dimensão do número de colunas - 1
 * de todas as raizes dessa equação, caso o resultado não seja possível o resultado é nulo
 * e caso existam múltiplas sóluções o retorno é nulo também. Esses casos serão tratados no
 * futuro.
 *
 * @brief operacaoGaussMatriz Executa o metodo de Gauss para encontrar as raizes do sistema de equação
 * @param matriz Matriz com o sistema de equações lineares
 * @return Retorna um vetor com os valores únicos do sistema de equação
 */
Vetor* operacaoGaussMatriz(Matriz *matriz){

}

/* Executa metodo de Gauss-Jordan para encontrar as raizes do sistema de equação */
Vetor* operacaoGausJordanMatriz(Matriz *matriz){

}

/* Encontra o Kernel de uma Matriz */
Vetor* operacaoKernelMatriz(Matriz *matriz){

}

/* Encontra uma base para a matriz */
Matriz* operacaoBaseMatriz(Matriz* matriz){

}
