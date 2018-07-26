#ifndef FRACAO_H
#define FRACAO_H

#include <stdbool.h>
#include "utils/utils.h"

/* ------------------------------------------------------------- */
/*                       Constantes Fracao                       */
/* ------------------------------------------------------------- */

/* Relacoes entre fracao */
#define FRACAO_MAIOR 1
#define FRACAO_IGUAL 0
#define FRACAO_MENOR -1

/* Erro na execução */
#define FRACAO_ERRO -2

/* Comparadores */
#define COMPARA_IGUAL 0
#define COMPARA_MAIOR 1
#define COMPARA_MAIOR_IGUAL 2
#define COMPARA_MENOR 3
#define COMPARA_MENOR_IGUAL 4

/* Tamanho digitos */
#define FRACAO_DIGITO_SEPARADOR '/'
#define FRACAO_MAX_DIGITOS

/* ------------------------------------------------------------- */
/*                     Prototype definitions                     */
/* ------------------------------------------------------------- */

/* Fracao */
typedef struct strFracao Fracao;

/* ------------------------------------------------------------- */
/*                       Fracao Structure                        */
/* ------------------------------------------------------------- */

typedef struct strFracao{
    /* Numerador */
    long long numerador;

    /* Denominador */
    long long denominador;

    /* Sinal da fração */
    byte sinal;

    /* Checa se a fração é ou não exata */
    bool exata;

    /* Valor fracionário */
    double valorFracionario;
} Fracao, *ptrFracao;

/* ------------------ Fracao Structure Methods ----------------- */

/* Cria uma novo fracao */
Fracao* newFracao(long long numerador, long long denominador);

/* Desaloca uma fracao */
bool deleteFracao(ptrFracao *fracao);

/* Clona uma fracao */
Fracao* cloneFracao(Fracao *fracao);

/* Soma de fracoes */
Fracao* somaFracao(Fracao *fracao1, Fracao *fracao2);

/* Subtracao de fracoes */
Fracao* subtracaoFracao(Fracao *fracao1, Fracao *fracao2);

/* Produto de fracoes */
Fracao* produtoFracao(Fracao *fracao1, Fracao *fracao2);

/* Multiplicacao de Fracao por escalar */
Fracao* multiplicacaoEscalarFracao(long long escalar, Fracao *fracao);

/* Divisão de frações */
Fracao* divisaoFracao(Fracao *fracao1, Fracao *fracao2);

/* Divisao de Fração por escalar */
Fracao* divisaoFracaoEscalar(Fracao *fracao, long long escalar);

/* Divisao de escalar por fracao */
Fracao* divisaoEscalarFracao(long long escalar, Fracao *fracao);

/* Realiza operação unária de menos numa fração */
Fracao* trocaSinal(Fracao *fracao);

/* Compara duas fracoes */
byte comparaFracoes(Fracao *fracao1, Fracao *fracao2);

/* Compara duas frações usando um operador */
bool compararFracoes(byte operador, Fracao *fracao1, Fracao *fracao2);

/* Reduz uma fração */
bool simplificarFracao(Fracao *fracao);

/* Lê fração */
Fracao* leFracao(void);

/* Imprime fracao */
bool imprimeFracao(Fracao *fracao);

/* MDC - Maior Divisor Comum */
long long MDC(long long a, long long b);

/* MMC - Minimo Multiplo Comum */
long long MMC(long long a, long long b);

/* ------------------------------------------------------------- */

#endif
