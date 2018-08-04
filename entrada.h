#ifndef ENTRADA_H
#define ENTRADA_H

/**
 * @file entrada.h
 * @author Alana Bispo e Jeferson Lima
 * @date 27 Jul 2018
 * @brief Metodos de entrada para modo interativo.
 *
 * Este header define, metodos que auxiliam a entrada
 * através de linha de comando.
 *
 */

#include "tipos/lista.h"

/* ------------------------------------------------------------- */
/*                      Constantes  Entrada                      */
/* ------------------------------------------------------------- */

/* Opções do menu */
#define INSERIR_MATRIZ_MENU 1
#define LISTAR_MATRIZ_MENU 2
#define DELETAR_MATRIZ_MENU 3
#define CLONAR_MATRIZ_MENU 4
#define OPERACOES_MATRIZ_MENU 5
#define OPERACOES_ENTRE_MATRIZES_MENU 6
#define OPERACOES_COMPLEXAS_MENU 7
#define SALVAR_RESULTADOS_MENU 8
#define SAIR_MENU 0

/* Opções menu de operações elementares */
#define TROCA_LINHA_MENU 1
#define MULTIPLICA_LINHA_MENU 2
#define SOMA_LINHA_MENU 3

/* Opções menu de operações aritméticas */
#define SOMA_MATRIZ_MENU 1
#define SUBTRACAO_MATRIZ_MENU 2
#define PRODUTO_MATRIZ_MENU 3
#define MULTIPLICACAO_ESCALAR_MATRIZ_MENU 4
#define TRANSPOSTA_MATRIZ_MENU 5

/* Menu de operações complexas */
#define METODO_GAUS_MATRIZ_MENU 1
#define METODO_GAUSS_JORDAN_MATRIZ_MENU 2
#define ENCONTRAR_DETERMINANTE_MATRIZ_MENU 3
#define ENCONTRAR_KERNEL_MATRIZ_MENU 4
#define ENCONTRAR_BASE_MATRIZ 5
#define INVERSA_MATRIZ_MENU 6
#define DIVISAO_MATRIZ_MENU 7

/* Operação comum */
#define VOLTAR_MENU 0

/* Destino para salvar operações entre matrizes */
#define SALVAR_NA_MATRIZ_ENTRADA 1
#define SALVAR_NOVA_MATRIZ 2

/* ------------------------------------------------------------- */
/*                      Estruturas  Globais                      */
/* ------------------------------------------------------------- */

/* ------------------------------------------------------------- */
/*                        Funções Entrada                        */
/* ------------------------------------------------------------- */

/**
 *
 * Modo de entrada interativa, neste modo o usuario tem um menu e pode realizar
 * diversas operações sobre as matrizes armazenadas nesse sistema
 *
 * @brief Ativa o modo de entrada de usuario
 */
void loopModoCLI(void);

/**
 *
 * Exibe o menu de opções para o usuario.
 *
 * @brief Exibe o menu
 */
void mostraMenu(void);

/**
 *
 * Menu de opções elementares, sobre as linhas de uma matriz.
 * Essas opções são executadas conforme entrada do usuario.
 *
 * @brief menuOpcoesElementares Menu opções elementares
 */
void menuOpcoesElementares(void);

/**
 *
 * Menu de operações aritméticas entre matrizes.
 * Essas opções são executadas entre matrizes definidas pelo usuario.
 *
 * @brief menuOpcoesAritmeticas Menu de operações aritméticas
 */
void menuOpcoesAritmeticas(void);

/**
 *
 * Menu de operações mais complexas que as operações anteriores.
 * Aqui existe um compilado de operações que envolvem escalonamento
 *
 * @brief menuOperacoesComplexas Menu de operações complexas
 */
void menuOperacoesComplexas(void);

/**
 *
 * Insere uma matriz definida pelo usuario a lista de matrizes.
 * Essa matriz poderá ser utilizada para fins futuros, como operações
 * entre matrizes, ou entre linhas de uma matriz.
 *
 * @brief inserirMatriz Insere uma matriz a lista de matrizes
 * @param listaMatrizes Lista contendo todas as matrizes já cadastradas
 */
void inserirMatriz(Lista *listaMatrizes);

/**
 *
 * Lista todas as matrizes presentes na memória.
 *
 * @brief listarMatrizes Lista todas as matrizes presentes na memória
 * @param listaMatrizes Lista de matrizes presente na memória
 */
void listarMatrizes(Lista *listaMatrizes);

/**
 *
 * Deleta matrizes presentes na lista de matrizes.
 *
 * @brief deletarMatriz Deletar matriz presentes na memória
 * @param listaMatrizes Lista todas as matrizes presentes na memória
 */
void deletarMatriz(Lista *listaMatrizes);

/**
 *
 * Clona as matrizes presentes na memória, qualquer matriz pode ser clonada
 * e seu id sempre será o próximo ID disponível. O objetivo aqui é permitir
 * que um usuario possa utilizar uma instância antiga da matriz para operações
 * futuras.
 *
 * @brief clonarMatriz Clonar matriz presentes na memória
 * @param listaMatrizes Lista com todas as matrizes do sistema
 */
void clonarMatriz(Lista *listaMatrizes);

/**
 *
 * Executa operações elementares sobre a matriz.
 * Podem ser efetuadas em operações elementares sobre qualquer matriz
 * da lista de matrizes.
 *
 * @brief operacoesMatriz Executar operações elementares sobre a matriz
 * @param listaMatrizes Lista com todas as matrizes do sistema
 */
void operacoesMatriz(Lista *listaMatrizes);

/**
 *
 * Realiza operações aritméticas entre matrizes. As operações permitidas
 * são:
 * - Soma
 * - Subtração
 * - Produto
 * - Multiplicação por escalar
 * - Transposta
 * - Inversa -- TODO
 * - Divisão -- TODO
 *
 * @brief operacoesEntreMatrizes Executa operações (soma, multiplicação, ...) entre matrizes
 * @param listaMatrizes Lista de matrizes
 */
void operacoesEntreMatrizes(Lista *listaMatrizes);

/**
 *
 * Executa o metodo de gauss em uma matriz. O objetivo aqui é gerar uma matriz
 * escalonada na forma escada de Gauss. Além da matriz ser modificada na forma de Gauss
 * é exibido um vetor com as respostas do sistema de equação linear.
 *
 * @brief metodoGaussMatriz Executa metodo de Gauss para encontrar as raizes do sistema de equação
 * @param listaMatrizes Lista com todas as matrizes do sistema
 */
void metodoGaussMatriz(Lista *listaMatrizes);

/**
 *
 * Executa o metodo de Gauss Jordan, de forma similiar ao metodo anterior a maior diferença
 * é que aqui teremos a forma de Gauss-Jordan aonde as linhas acimas de cada coluna pivô
 * também são zeradas.
 *
 * @brief metodoGaussJordanMatriz Executa metodo de Gauss-Jordan para encontrar as raizes do sistema de equação
 * @param listaMatrizes Lista com todas as matrizes do sistema
 */
void metodoGaussJordanMatriz(Lista *listaMatrizes);

/**
 *
 * Através da forma de Gauss-Jordan encontrar o kernel de qualquer matriz.
 * Essa função é bastante interessante, e melhor descrita na função
 * em operacoes_complexas.h .
 *
 * @brief encontrarKernelMatriz Encontra o Kernel de uma Matriz
 * @param listaMatrizes Lista com todas as matrizes do sistema
 */
void encontrarKernelMatriz(Lista *listaMatrizes);

/* Encontra uma base para a matriz */
// TODO
void encontrarBaseMatriz(Lista *listaMatrizes);

/**
 *
 * Encontra o determinante de qualquer matriz quadradada, através
 * de operações de escalonamento. Serve qualquer matriz de formato
 * n x n.
 *
 * @brief encontrarDeterminante Encontra o determinaten de uma dada matriz
 * @param listaMatrizes Lista com todas as matrizes do sistema
 */
void encontrarDeterminante(Lista *listaMatrizes);

/**
 *
 * Realiza a operação de troca entre duas linhas, com base na linha informada
 * pelo usuario e duas linhas de uma matriz já cadastrada. No caso da falta da
 * matriz ou das linhas informadas a aplicação volta ao menu anterior.
 *
 * @brief operacaoMatrizTrocaLinha Realiza a operação elementar de troca entre linhas
 * @param listaMatrizes Lista com todas as matrizes do sistema
 */
void operacaoMatrizTrocaLinha(NoLista *noMatriz);

/**
 *
 * Aplica a operação elementar de multiplicação de linha por escalar, tendo uma matriz previamente
 * selecionada.
 *
 * @brief operacaoMatrizMultiplicaLinha Executa a operação de multiplicação de linha por escalar
 * @param noMatriz Nó da lista de matrizes
 */
void operacaoMatrizMultiplicaLinha(NoLista *noMatriz);

/**
 *
 * Executa operação de soma entre linhas, tendo uma matriz previamente
 * selecionada.
 *
 * @brief operacaoMatrizSomaLinha Executa a operação de soma entre linhas
 * @param noMatriz Nó da lista de matrizes
 */
void operacaoMatrizSomaLinha(NoLista *noMatriz);

/**
 *
 * Aplica a operação de soma entre matrizes. A soma de matrizes só pode
 * ser realizada se as matrizes tiverem o mesmo tamanho.
 *
 * @brief somaMatrizOperacao Executa a operação de soma entre matrizes
 * @param listaMatrizes Lista de matrizes
 * @param salvaResultadoOperacao Indica se o resultado deve ser salvo em uma nova matriz, ou na mesma
 */
void somaMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao);

/**
 *
 * Aplica a operação de subtração entre matrizes. A subtração de matrizes só pode
 * ser realizada se as matrizes tiverem o mesmo tamanho.
 *
 * @brief somaMatrizOperacao Executa a operação de subtração entre matrizes
 * @param listaMatrizes Lista de matrizes
 * @param salvaResultadoOperacao Indica se o resultado deve ser salvo em uma nova matriz, ou na mesma
 */
void subtracaoMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao);

/**
 *
 * Aplica a operação de produto entre matrizes. O destino da matriz resultante
 * pode ser a matriz de entrada ou uma nova matriz.
 *
 * @brief produtoMatrizOperacao Executa a operação de produto entre matrizes
 * @param listaMatrizes Lista de matrizes
 * @param salvaResultadoOperacao Indica se o resultado deve ser salvo em uma nova matriz, ou na mesma
 */
void produtoMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao);

/**
 *
 * Multiplica uma matriz por um escalar qualquer. Tal como as outras operações
 * é possível escolher se a nova matriz sera salva na matriz de entrada ou em uma nova matriz.
 *
 * @brief multiplicacaoEscalarMatrizOperacao Executa a operação de multiplicação de matriz por escalar
 * @param listaMatrizes Lista de matrizes
 * @param salvaResultadoOperacao Indica se o resultado deve ser salvo em uma nova matriz, ou na mesma
 */
void multiplicacaoEscalarMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao);

/**
 *
 * Gera uma matriz transposta e salva esta na mesma matriz de origem, ou
 * em uma nova matriz.
 *
 * @brief transpostaMatrizOperacao Executa operação para encontrar a transposta de uma matriz
 * @param listaMatrizes Lista de matrizes
 * @param salvaResultadoOperacao Indica se o resultado deve ser salvo em uma nova matriz, ou na mesma
 */
void transpostaMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao);

/**
 *
 * Menu de operações que envolvem escalonamento. Por padrão essas funções aqui
 * estão sinalizadas com o nome de operações complexas, porém o que temos na
 * verdade é um conjunto de metodos algebricos para solução de problemas comuns
 * como é o caso de encontrar o kernel de uma matriz, encontrar a solução de
 * equações lineares e afins.
 *
 * @brief operacaoMatrizComplexas Realiza operações complexas, que envolvem escalonamento
 * @param listaMatrizes Lista de matrizes disponiveis na memoria
 */
void operacaoMatrizComplexas(Lista *listaMatrizes);

/* ------------------------------------------------------------- */

#endif
