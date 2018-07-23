#ifndef UTILS_H
#define UTILS_H

#include <stdarg.h>
#include <stdbool.h>

/* Convert a constant to a string */
#define QUOTE(_VAR)                         #_VAR
#define TO_STRING(VAR)                      QUOTE(VAR)

/* Checa se um valor esta num range */
#define variavelEntre(VAR, A, B) (A >= VAR && B <= VAR)

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

#endif
