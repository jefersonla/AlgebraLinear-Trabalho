#ifndef OPERACOES_COMPLEXAS_H
#define OPERACOES_COMPLEXAS_H

/**
 * @file operacoes_complexas.h
 * @author Alana Bispo e Jeferson Lima
 * @date 27 Jul 2018
 * @brief Operacoes complexas entre matrizes.
 *
 * Contém as operações mais complexas em matrizes, estas operações
 * incluem metodos que utilizam escalonamento e forma escada
 * tanto a de Gauss como a de Gauss-Jordan. Além disso também
 * é possível encontrar o kernel de qualquer matriz, uma base
 * para uma dada matriz entre outras funções a serem adicionadas.
 *
 * @see http://www.cpdee.ufmg.br/~palhares/aula4_introbusto.pdf
 * @see https://www.dca.ufrn.br/~ivan/DCA0399/SistemasLineares.pdf
 * @see http://www.dcc.ufrj.br/~rincon/Disciplinas/Algebra%20Linear/Aula_013.pdf
 * @see http://www.mat.ufmg.br/~rodney/notas_de_aula/sistemas_lineares.pdf
 * @see https://www.ime.unicamp.br/~marcia/AlgebraLinear/Arquivos%20PDF/exemplos_nucleo_imagem.pdf
 * @see https://www.ime.unicamp.br/~marcia/AlgebraLinear/Arquivos%20PDF/demo_nucleo.pdf
 */

#include "tipos/matriz.h"
#include "tipos/vetor.h"

/* ------------------------------------------------------------- */
/*                      Constantes  Operações                    */
/* ------------------------------------------------------------- */

/* ------------------------------------------------------------- */
/*                      Estruturas  Globais                      */
/* ------------------------------------------------------------- */

/* ------------------------------------------------------------- */
/*                        Funções Operações                      */
/* ------------------------------------------------------------- */

/**
 *
 * Realiza o metodo de Gauss para encontrar as raizes de um sistema de equações. Essa função
 * assume que a matriz contém ao menos duas colunas e a última é sempre o resultado.
 * O retorno dessa função é um vetor de doubles com a dimensão do número de colunas - 1
 * de todas as raizes dessa equação, caso o resultado não seja possível o resultado é nulo
 * e caso existam múltiplas sóluções o retorno é nulo também. Esses casos podem ser melhor
 * tratados no futuro. O procedimento para execução do metodo de Gauss é o metodo de Gauss
 * com pivotamento a fim de evitar divisões por zero. Antes de executar o algoritmo é checado
 * se a matriz é quadradada, e temos uma matriz aumentada
 *
 * @brief operacaoGaussMatriz Executa o metodo de Gauss para encontrar as raizes do sistema de equação
 * @param matriz Matriz com o sistema de equações lineares
 * @return Retorna um vetor com os valores únicos do sistema de equação, ou nulo caso contrário
 */
Vetor* operacaoGaussMatriz(Matriz *matriz);

/**
 *
 * Realiza o metodo de Gauss-Jordan para encontrar as raizes de um sistema de equações.
 * Essa função aplica o algoritmo de Gauus-Jordan para encontrar as raizes do sistema de equação.
 * Analisando os dois metodos a maior diferença de um sistema para o outro é que não precisamos
 * aplicar o
 *
 * @brief operacaoGausJordanMatriz Executa o metodo de Gauss-Jordan para encontrar as raizes do sistema de equação
 * @param matriz Matriz com o sistema de equações lineares
 * @return Retorna um vetor com os valores únicos do sistema de equação, ou nulo caso contrário
 */
Vetor* operacaoGausJordanMatriz(Matriz *matriz);

/* Encontra o Kernel de uma Matriz */
// TODO
Vetor** operacaoKernelMatriz(Matriz *matriz, unsigned int *numeroVetoresResposta);

/* Encontra uma base para a matriz */
// TODO
Matriz* operacaoBaseMatriz(Matriz* matriz);

/* Encontra o determinante da matriz */
// TODO
double operacaoDeterminanteMatriz(Matriz *matriz, bool *erro);

/* ------------------------------------------------------------- */

#endif
