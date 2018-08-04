#ifndef UTILS_H
#define UTILS_H

/**
 * @file utils.h
 * @author Alana Bispo e Jeferson Lima
 * @date 27 Jul 2018
 * @brief Metodos auxiliares para funções básicas.
 *
 * Este header define, metodos utils para qualquer projeto em C.
 *
 */

#include "../tipos/matriz.h"

#include <stdarg.h>
#include <stdbool.h>

/* Tipo Byte */
typedef signed char byte;

/* Convert a constant to a string */
#define QUOTE(_VAR)                         #_VAR
#define TO_STRING(VAR)                      QUOTE(VAR)

/* Checa se um valor esta num range */
#define variavelEntre(VAR, A, B) (A >= VAR && VAR <= B)

/* Secure free memory */
#define secureFree(VAR)                     do{ free(VAR); VAR = NULL; } while(false)

/* Get a secure string size */
#define secureStringSize(VAR)               (strlen(VAR) + SECURE_STRING_TERMINATOR)

/* Secure  String Copy */
#define secureStringCopy(DEST, SRC)         do{ strncpy(DEST, SRC, secureStringSize(SRC)); DEST[secureStringSize(SRC) - 1] = 0; }while(false)

/* Print debug messages */
#define printMsg(TYPE, FORMAT, ...)         fprintf(stderr, "[" TYPE "] [%s:%d] " FORMAT "\n", __FILE__, __LINE__, ##__VA_ARGS__)

/* Print a nice formated error msg */
#define printFatalError(FORMAT, ...)        printMsg("FATAL ERROR", FORMAT, ##__VA_ARGS__)

/* Print a nice formated error msg */
#define printError(FORMAT, ...)             printMsg("ERROR", FORMAT, ##__VA_ARGS__)

/* Print a nice formated warning msg */
#define printWarning(FORMAT, ...)           printMsg("WARNING", FORMAT, ##__VA_ARGS__)

/* Print a nice formated info msg */
#define printInfo(FORMAT, ...)              printMsg("INFO", FORMAT, ##__VA_ARGS__)

/* Print a nice formated info msg */
#define printTodo(FORMAT, ...)              printMsg("TODO", FORMAT, ##__VA_ARGS__)

/* Imprime uma linha vazia */
#define quebraLinha()                       printf("\n");

/* Verifica se o double é nulo */
#define doubleIgualZero(NUM)                (fabs(NUM) <= 10e-7)

/**
 *
 * Troca os valores entre as celulas de uma matriz
 *
 * @brief swapMatrizCelula Troca os valores entre celulas de uma matriz
 * @param a Primeiro valor
 * @param b Segundo valor
 */
void swapMatrizCelula(MatrizCelula *a, MatrizCelula *b);

/**
 *
 * Imprime um número com um número fixado de digitos, ou seja imprime um numero
 * para colunas de tamanho fixado.
 *
 * @brief imprimeColunaFixa Imprime um numero com uma quantidade especifica de digitos
 * @param buf Buffer para armazenar a string do numero
 * @param num Numero a ser impresso
 * @param tamColuna Tamanho da coluna do número em questão
 */
void imprimeColunaFixa(char *buf, MatrizCelula a, int tamColuna);

#endif
