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
#define OPERACOES_MATRIZ_MENU 4
#define SAIR_MENU 0

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

/* Inseri matriz a lista de matrizes */
void inserirMatriz(Lista *listaMatrizes);

/* Listar matrizes já inseridas */
void listarMatrizes(Lista *listaMatrizes);

/* Deletar matriz presentes na memória */
void deletarMatriz(Lista *listaMatrizes);

/* Executar operações elementares sobre a matriz */
void operacoesMatriz(Lista *listaMatrizes);

/* ------------------------------------------------------------- */

#endif
