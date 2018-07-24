#ifndef ENTRADA_H
#define ENTRADA_H

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
#define ENCONTRAR_KERNEL_MATRIZ_MENU 3
#define ENCONTRAR_BASE_MATRIZ 4
#define INVERSA_MATRIZ_MENU 5
#define DIVISAO_MATRIZ_MENU 6

/* Operação comum */
#define VOLTAR_MENU 0

/* Destino para salvar operações entre matrizes */
#define SALVAR_NA_MATRIZ_ENTRADA 0
#define SALVAR_NOVA_MATRIZ 1

/* ------------------------------------------------------------- */
/*                      Estruturas  Globais                      */
/* ------------------------------------------------------------- */

/* ------------------------------------------------------------- */
/*                        Funções Entrada                        */
/* ------------------------------------------------------------- */

/* Pega a entrada do usuario */
void loopModoCLI(void);

/* Mostra o menu de opções */
void mostraMenu(void);

/* Menu opções elementares */
void menuOpcoesElementares(void);

/* Menu de operações, complexas em algebra que envolvem escalonamento. */
void menuOperacoesComplexas(void);

/* Inseri matriz a lista de matrizes */
void inserirMatriz(Lista *listaMatrizes);

/* Listar matrizes já inseridas */
void listarMatrizes(Lista *listaMatrizes);

/* Deletar matriz presentes na memória */
void deletarMatriz(Lista *listaMatrizes);

/* Clonar matriz presentes na memória */
void clonarMatriz(Lista *listaMatrizes);

/* Executar operações elementares sobre a matriz */
void operacoesMatriz(Lista *listaMatrizes);

/* Executa operações (soma, multiplicação, ...) entre matrizes */
void operacoesEntreMatrizes(Lista *listaMatrizes);

/* Executa metodo de Gauss para encontrar as raizes do sistema de equação */
void metodoGaussMatriz(Lista *listaMatrizes);

/* Executa metodo de Gauss-Jordan para encontrar as raizes do sistema de equação */
void metodoGaussJordanMatriz(Lista *listaMatrizes);

/* Encontra o Kernel de uma Matriz */
void encontrarKernelMatriz(Lista *listaMatrizes);

/* Encontra uma base para a matriz */
void encontrarBaseMatriz(Lista *listaMatrizes);

/* Executa a operação de troca entre linhas */
void operacaoMatrizTrocaLinha(NoLista *noMatriz);

/* Executa a operação de multiplicação de linha por escalar */
void operacaoMatrizMultiplicaLinha(NoLista *noMatriz);

/* Executa a operação de soma entre linhas */
void operacaoMatrizSomaLinha(NoLista *noMatriz);

/* Executa a operação de soma entre matrizes */
void somaMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao);

/* Executa a operacao de subtracao entre matrizes */
void subtracaoMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao);

/* Executa a operação de produto entre matrizes */
void produtoMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao);

/* Executa a operação de multiplicação de matriz por escalar */
void multiplicacaoEscalarMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao);

/* Executa operação para encontrar a transposta de uma matriz */
void transpostaMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao);

/* Realiza operações complexas, que envolvem escalonamento */
void operacaoMatrizComplexas(Lista *listaMatrizes);

/* ------------------------------------------------------------- */

#endif
