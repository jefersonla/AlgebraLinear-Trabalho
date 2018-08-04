#ifndef FRACAO_H
#define FRACAO_H

/**
 * @file fracao.h
 * @author Alana Bispo e Jeferson Lima
 * @date 27 Jul 2018
 * @brief Estrutura Fracao, util para matemática.
 *
 * TODO!!!
 *
 */

#include <stdbool.h>
#include "../utils/utils.h"

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
#define FRACAO_DIGITO_SEPARADOR_FIM ' '
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

/**
 *
 * Aloca uma nova fração. Uma fração é uma estrutura que contém
 * um numerador e um denominador (numerador/denominador).
 * Este objeto tem como objetivo evitar a perca de precisão
 * após muitas operações utilizando o tipo double.
 *
 * @brief newFracao Cria uma novo fração
 * @param numerador Numerador da fração
 * @param denominador Denominador da fração
 * @return Retorna o ponteiro para uma nova fração alocada
 */
Fracao* newFracao(long long numerador, long long denominador);

/**
 *
 * Desaloca uma fracao qualquer.
 *
 * @brief deleteFracao Desaloca uma fracao
 * @param vetor Ponteiro para a fracao
 * @return Retorna true se foi possível deletar e falso caso contrário
 */
bool deleteFracao(ptrFracao *fracao);

/**
 *
 * Clona uma fracao. Essa operação é válida para momentos aonde a referência
 * da fração deve ser mantida porém seu conteúdo precise ser clonado ou seja
 * é necessário fazer uma nova referência.
 *
 * @brief cloneFracao Clona uma fracao
 * @param fracao Fracao a ser clonada
 * @return Ponteiro para nova instancia da fracao
 */
Fracao* cloneFracao(Fracao *fracao);

/**
 *
 * Soma duas frações distintas. Se as frações tiverem denominadores diferentes
 * primeiro se encontra um denominador em comum, se aplicam as transformações
 * necessárias e então é efetuada a operação de adição entre as duas funções.
 *
 * @brief somaFracao Soma de fracoes
 * @param fracao1 Fração 1
 * @param fracao2 Fração 2
 * @return Retorna uma nova fração resultado da soma das duas frações
 */
Fracao* somaFracao(Fracao *fracao1, Fracao *fracao2);

/**
 *
 * Subtrai duas frações distintas. Se as frações tiverem denominadores diferentes
 * primeiro se encontra um denominador em comum, se aplicam as transformações
 * necessárias e então é efetuada a operação de subtração entre as duas funções.
 *
 * @brief subtracaoFracao Subtração de fracoes
 * @param fracao1 Fração 1
 * @param fracao2 Fração 2
 * @return Retorna uma nova fração resultado da subtração das duas frações
 */
Fracao* subtracaoFracao(Fracao *fracao1, Fracao *fracao2);

/**
 *
 * Multiplica uma fração por outra. O resultado dessa multiplicação é basicamente
 * a multiplicação dos termos da fração 1 pelos termos da fração 2.
 *
 * @brief produtoFracao Produto de frações
 * @param fracao1 Fração 1
 * @param fracao2 Fração 2
 * @return Retorna uma nova fração resultado do produto das duas frações
 */
Fracao* produtoFracao(Fracao *fracao1, Fracao *fracao2);

/**
 *
 * Multiplica uma fração por um escalar qualquer, o que resulta na multiplicação
 * do escalar pelo numerador.
 *
 * @brief produtoFracao Produto de fração por escalar
 * @param fracao1 Fração 1
 * @param fracao2 Fração 2
 * @return Retorna uma nova fração resultado do produto das duas frações
 */
Fracao* multiplicacaoEscalarFracao(long long escalar, Fracao *fracao);

/**
 *
 * Divide uma fração por outra. A divisão é igual a multiplicação, da fração 1
 * pela inversa da fração 2 logo sejam F1 n1/d1 e F2 n2/d2, F1 / F2 é igual a
 * n1/d1 * d2/n2.
 *
 * @brief divisaoFracao Divisão de frações
 * @param fracao1 Fração 1
 * @param fracao2 Fração 2
 * @return Retorna uma nova fração resultado da divisão entre duas frações
 */
Fracao* divisaoFracao(Fracao *fracao1, Fracao *fracao2);

/**
 *
 * Divide uma fração por um escalar ou seja (n/d / e) o que é o mesmo que
 * (n/d / e/1) o que é equivalente a (n/d * 1/e) logo a divisão por um escalar
 * continua bem próxima da divisão entre frações já definida.
 *
 * @brief divisaoFracaoEscalar Divisao de Fração por escalar
 * @param fracao Fração
 * @param escalar Escalar
 * @return Retorna uma nova fração resultado da divisao da fracao pelo escalar
 */
Fracao* divisaoFracaoEscalar(Fracao *fracao, long long escalar);

/**
 *
 * Divide um escalar por uma fração ou seja (e / n/d) o que é o mesmo que
 * (e/1 / n/d) o que é equivalente a (e/1 * d/n) logo a divisão por um escalar
 * continua bem próxima da divisão entre frações já definida.
 *
 * @brief divisaoEscalarFracao Divisão de escalar por fração
 * @param escalar Escalar
 * @param fracao Fração
 * @return Retorna uma nova fração resultado da divisão da fração pelo escalar
 */
Fracao* divisaoEscalarFracao(long long escalar, Fracao *fracao);

/**
 *
 * Troca o sinal do numerador e denominador de uma fração aplicando assim
 * o operador unário (-).
 *
 * @brief trocaSinal Realiza operação unária de menos numa fração
 * @param fracao Fração
 * @return Retorna uma nova fração porém com o sinal invertido
 */
Fracao* trocaSinal(Fracao *fracao);

/**
 *
 * Compara duas frações. O resultado da comparação entre duas frações é um número que
 * indica se a fração 1 (F1) é menor que a fração 2 (F1 < F2) logo se (F1 < F2) teremos
 * -1 se (F1 > F2) teremos 1 e caso (F1 == F2) teremos 0.
 *
 * @brief comparaFracoes Compara duas fracoes
 * @param fracao1 Fração 1
 * @param fracao2 Fração 2
 * @return Retorna -1 caso a fração 1 seja menor que a fração 2, 1 caso contrário e 0 se iguais
 */

byte comparaFracoes(Fracao *fracao1, Fracao *fracao2);



/**
 *
 * Dado um operador definido, essa função compara as duas frações com base nos operadores
 * (>, >=, ==, <, <=), o retorno da função é a comparação de F1 e F2 com base no operador.
 *
 * @brief compararFracoes Compara duas frações usando um operador
 * @param operador Operador
 * @param fracao1 Fração 1
 * @param fracao2 Fração 2
 * @return Retorna true caso a operação seja verdade e falso caso contrário (pode ser erro verifique LOG)
 */
bool compararFracoes(byte operador, Fracao *fracao1, Fracao *fracao2);

/**
 *
 * Reduz os termos de uma fração. O metodo de simplificar uma fração
 * procura um termo comum entre o numerador e denominador e então divide
 * ambos por este valor resultando assim numa fracao equivalente a
 * fracao inicial porém com menores valores. Se a fracao nao puder
 * ser simplificada ela nao sera modificada.
 *
 * @brief simplificarFracao Reduz uma fração
 * @param fracao
 * @return
 */
bool simplificarFracao(Fracao *fracao);

/**
 *
 * Lê uma fração da entrada padrão (STDIN). Esta função assume que
 * NÃO EXISTEM ESPAÇOS NA FRAÇÂO e que ela é sempre escrita na forma
 * n/d sem espaços antes ou depois do sinal (/). Numeros negativos
 * são aceitos tanto no numerador como no denominador.
 *
 * @brief leFracao Lê fração
 * @return Retorna uma nova fração vinda da entrada padrão
 */
Fracao* leFracao(void);

/**
 *
 * Imprime uma fração no formato n/d na saída padrão.
 *
 * @brief imprimeFracao Imprime uma fração
 * @param fracao Fração a ser impressa
 * @return Retorna true caso tudo tenha ocorrido bem e falso caso contrário
 */
bool imprimeFracao(Fracao *fracao);

/**
 *
 * Encontra o maior divisor comum entre dois números. Esta função
 * esta otimizada e é uma contribuição do site Geeks for Geeks
 * (link: https://www.geeksforgeeks.org/program-to-add-two-fractions/)
 * O fato dela estar otimizada faz com que a complexidade dela não torne
 * a execução deste programa lenta se comparada as operações de ponto
 * flutuante que podem ser executadas diretamente no processador as vezes
 * até mesmo em um único ciclo de clock. Como funções recursivas tem como
 * desvantagem ter que alocar os recursos referentes a ela a função abaixo
 * está com uma pequena variação interativa, de forma a não comprometer
 * a performance da aplicação.
 *
 * @brief MDC MDC - Maior Divisor Comum
 * @param a Numero A
 * @param b Numero B
 * @return Retorna o maior divisor comum entre dois números A e B
 */
long long MDC(long long a, long long b);

/**
 *
 * Encontra o minimo multiplo comum entre dois números. Para realizar
 * essa operação utilizamos a propriedade MMC(a, b) * MDC(a, b) = a * b
 * (link: https://math.stackexchange.com/questions/349858/easiest-and-most-complex-proof-of-gcd-a-b-times-operatornamelcm-a-b-a)
 * A ideia aqui é que o MMC(a,b) = (a * b) / MDC(a, b), a prova para esta
 * propriedade é apresentada no artigo acima do StackExchange. Novamente
 * o objetivo de utilizar esse tipo de operação é evitar ao máximo a perca
 * de perfomance causada por algoritmos lentos ou mal otimizados.
 *
 * @brief MMC MMC - Minimo Multiplo Comum
 * @param a Numero A
 * @param b Numero B
 * @return Retorna o minimo multiplo comum entre dois números A e B
 */
long long MMC(long long a, long long b);

/* ------------------------------------------------------------- */

#endif
