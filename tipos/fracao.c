#include "./fracao.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*------------ Fracao Structure Methods ------------ */

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
Fracao* newFracao(long long numerador, long long denominador){
    /* Denominador não pode ser 0 */
    if(denominador == 0){
        printError("DENOMINADOR NAO PODE SER ZERO!");
        return NULL;
    }

    /* Tenta alocar o espaço de memória para uma fracao */
    Fracao *_new_fracao = malloc(sizeof(Fracao));

    /* Checa se a fração foi bem alocada, caso contrário erro fatal */
    if(_new_fracao == NULL){
        printFatalError("ERRO AO ALOCAR NOVA FRACAO!");
        exit(EXIT_FAILURE);
    }

    /* Inicializa os valores da estrutura */
    _new_fracao->exata = ((numerador % denominador) == 0);
    _new_fracao->sinal = ((numerador >= 0 && denominador >= 0) ||
                          (numerador < 0 && denominador < 0)) ? 1 : -1;
    _new_fracao->valorFracionario = (double)(numerador) / (double)denominador;

    /* Salvamos o numerador e o denominador da expressão como sendo seus valores absolutos */
    _new_fracao->numerador = llabs(numerador);
    _new_fracao->denominador = llabs(denominador);

    return _new_fracao;
}

/**
 *
 * Desaloca uma fracao qualquer.
 *
 * @brief deleteFracao Desaloca uma fracao
 * @param vetor Ponteiro para a fracao
 * @return Retorna true se foi possível deletar e falso caso contrário
 */
bool deleteFracao(ptrFracao *fracao){
    /* Verifica se a fração é válida */
    if(fracao == NULL){
        printError("FRACAO INVALIDA! PONTEIRO NAO EXISTE!");
        return false;
    }

    /* Verifica se a fração é consistente */
    if((*fracao) == NULL){
        printError("FRACAO INEXISTENTE! NAO E POSSIVEL DELETAR!");
        return false;
    }

    /* Desaloca fracao */
    secureFree((*fracao));

    return true;
}

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
Fracao* cloneFracao(Fracao *fracao){
    /* Verifica se a fração é consistente */
    if(fracao == NULL){
        printError("FRACAO INEXISTENTE! NAO E POSSIVEL CLONAR!");
        return NULL;
    }

    /* Tenta alocar uma nova fração */
    Fracao *_new_cloned_fracao = newFracao(fracao->numerador, fracao->denominador);

    /* Verifica se não houve erros ao alocar a nova fração */
    if(_new_cloned_fracao == NULL){
        printError("ERRO AO ALOCAR NOVA FRACAO! NAO E POSSIVEL CLONAR!");
        return NULL;
    }

    return _new_cloned_fracao;
}

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
Fracao* somaFracao(Fracao *fracao1, Fracao *fracao2){
    /* Verifica a consistência das frações */
    if(fracao1 == NULL || fracao2 == NULL){
        printError("FRACOES INEXISTENTES! NAO E POSSIVEL EXECUTAR A OPERACAO!");
        return NULL;
    }

    /* Encontra o MMC entre os denominadores das duas frações */
    long long novo_denominador = MMC(fracao1->denominador, fracao2->denominador);

    /* Aplica o novo denominador as duas fracoes, gerando novos numeradores e somando ambos */
    long long numerador_soma = (fracao1->sinal * ((fracao1->numerador) * (novo_denominador / fracao1->denominador))) +
        (fracao2->sinal * ((fracao2->numerador) * (novo_denominador / fracao2->denominador)));

    /* Se as frações são consistentes tentamos alocar uma nova fração */
    Fracao *fracao_resultado = newFracao(numerador_soma, novo_denominador);

    /* Verifica se não houve erros ao alocar a nova fração */
    if(fracao_resultado == NULL){
        printError("ERRO AO ALOCAR NOVA FRACAO! NAO E POSSIVEL EXECUTAR OPERACAO!");
        return NULL;
    }

    return fracao_resultado;
}

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
Fracao* subtracaoFracao(Fracao *fracao1, Fracao *fracao2){
    /* Verifica a consistência das frações */
    if(fracao1 == NULL || fracao2 == NULL){
        printError("FRACOES INEXISTENTES! NAO E POSSIVEL EXECUTAR A OPERACAO!");
        return NULL;
    }

    /* Encontra o MMC entre os denominadores das duas frações */
    long long novo_denominador = MMC(fracao1->denominador, fracao2->denominador);

    /* Aplica o novo denominador as duas fracoes, gerando novos numeradores e subtraindo ambos */
    long long numerador_subtracao = (fracao1->sinal * ((fracao1->numerador) * (novo_denominador / fracao1->denominador))) -
        (fracao2->sinal * ((fracao2->numerador) * (novo_denominador / fracao2->denominador)));

    /* Se as frações são consistentes tentamos alocar uma nova fração */
    Fracao *fracao_resultado = newFracao(numerador_subtracao, novo_denominador);

    /* Verifica se não houve erros ao alocar a nova fração */
    if(fracao_resultado == NULL){
        printError("ERRO AO ALOCAR NOVA FRACAO! NAO E POSSIVEL EXECUTAR OPERACAO!");
        return NULL;
    }

    return fracao_resultado;
}

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
Fracao* produtoFracao(Fracao *fracao1, Fracao *fracao2){
    /* Verifica a consistência das frações */
    if(fracao1 == NULL || fracao2 == NULL){
        printError("FRACOES INEXISTENTES! NAO E POSSIVEL EXECUTAR A OPERACAO!");
        return NULL;
    }

    /* Se as frações são consistentes tentamos alocar uma nova fração */
    Fracao *fracao_resultado = newFracao(fracao1->numerador * fracao2->numerador,
                                         fracao1->denominador * fracao2->denominador);

    /* Como numerador e denominador são sempre positivos, pegamos o resultado do sinal das frações */
    fracao_resultado->sinal = fracao1->sinal * fracao2->sinal;

    /* Verifica se não houve erros ao alocar a nova fração */
    if(fracao_resultado == NULL){
        printError("ERRO AO ALOCAR NOVA FRACAO! NAO E POSSIVEL EXECUTAR OPERACAO!");
        return NULL;
    }

    return fracao_resultado;
}

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
Fracao* multiplicacaoEscalarFracao(long long escalar, Fracao *fracao){
    /* Verifica a consistência das frações */
    if(fracao == NULL){
        printError("FRACAO INEXISTENTE! NAO E POSSIVEL EXECUTAR A OPERACAO!");
        return NULL;
    }

    /* Se as frações são consistentes tentamos alocar uma nova fração */
    Fracao *fracao_resultado = newFracao(fracao->numerador * escalar, fracao->denominador);

    /* Verifica se não houve erros ao alocar a nova fração */
    if(fracao_resultado == NULL){
        printError("ERRO AO ALOCAR NOVA FRACAO! NAO E POSSIVEL EXECUTAR OPERACAO!");
        return NULL;
    }

    return fracao_resultado;
}

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
Fracao* divisaoFracao(Fracao *fracao1, Fracao *fracao2){
    /* Verifica a consistência das frações */
    if(fracao1 == NULL || fracao2 == NULL){
        printError("FRACOES INEXISTENTES! NAO E POSSIVEL EXECUTAR A OPERACAO!");
        return NULL;
    }

    /* A divisao de fração é igual a multiplicação da fração 1 pela 2 invertida */
    Fracao *fracao_resultado = newFracao(fracao1->numerador * fracao2->denominador,
                                         fracao1->denominador * fracao2->numerador);

    /* Como numerador e denominador são sempre positivos, pegamos o resultado do sinal das frações */
    fracao_resultado->sinal = fracao1->sinal * fracao2->sinal;

    /* Verifica se não houve erros ao alocar a nova fração */
    if(fracao_resultado == NULL){
        printError("ERRO AO ALOCAR NOVA FRACAO! NAO E POSSIVEL EXECUTAR OPERACAO!");
        return NULL;
    }

    return fracao_resultado;
}

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
Fracao* divisaoFracaoEscalar(Fracao *fracao, long long escalar){
    /* Verifica a consistência das frações */
    if(fracao == NULL){
        printError("FRACAO INEXISTENTE! NAO E POSSIVEL EXECUTAR A OPERACAO!");
        return NULL;
    }

    /* A divisao de fração por um escalar ou seja e/1 é igual a multiplicação da fração por 1/e */
    Fracao *fracao_resultado = newFracao(fracao->numerador,
                                         fracao->denominador * escalar);

    /* Verifica se não houve erros ao alocar a nova fração */
    if(fracao_resultado == NULL){
        printError("ERRO AO ALOCAR NOVA FRACAO! NAO E POSSIVEL EXECUTAR OPERACAO!");
        return NULL;
    }

    return fracao_resultado;
}

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
Fracao* divisaoEscalarFracao(long long escalar, Fracao *fracao){
    /* Verifica a consistência das frações */
    if(fracao == NULL){
        printError("FRACAO INEXISTENTE! NAO E POSSIVEL EXECUTAR A OPERACAO!");
        return NULL;
    }

    /* A divisao de um escalar por uma fração é igual a multiplicação do escalar pelo inverso da fração */
    Fracao *fracao_resultado = newFracao(fracao->denominador * escalar,
                                         fracao->numerador);

    /* Verifica se não houve erros ao alocar a nova fração */
    if(fracao_resultado == NULL){
        printError("ERRO AO ALOCAR NOVA FRACAO! NAO E POSSIVEL EXECUTAR OPERACAO!");
        return NULL;
    }

    return fracao_resultado;
}

/**
 *
 * Troca o sinal do numerador e denominador de uma fração aplicando assim
 * o operador unário (-).
 *
 * @brief trocaSinal Realiza operação unária de menos numa fração
 * @param fracao Fração
 * @return Retorna uma nova fração porém com o sinal invertido
 */
Fracao* trocaSinal(Fracao *fracao){
    /* Verifica a consistência das frações */
    if(fracao == NULL){
        printError("FRACAO INEXISTENTE! NAO E POSSIVEL EXECUTAR A OPERACAO!");
        return NULL;
    }

    /* Multiplica a fração por (-1) invertendo assim o sinal da mesma */
    Fracao *fracao_resultado = newFracao(fracao->numerador * (-1),
                                         fracao->denominador);

    /* Verifica se não houve erros ao alocar a nova fração */
    if(fracao_resultado == NULL){
        printError("ERRO AO ALOCAR NOVA FRACAO! NAO E POSSIVEL EXECUTAR OPERACAO!");
        return NULL;
    }

    return fracao_resultado;
}

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
byte comparaFracoes(Fracao *fracao1, Fracao *fracao2){
    /* Verifica a consistência das frações */
    if(fracao1 == NULL || fracao2 == NULL){
        printError("FRACOES INEXISTENTES! NAO E POSSIVEL EXECUTAR A OPERACAO!");
        return FRACAO_ERRO;
    }

    /* Encontra o MMC entre os denominadores das duas frações */
    long long novo_denominador = MMC(fracao1->denominador, fracao2->denominador);

    /* Aplica o novo denominador as duas fracoes, gerando novos numeradores e subtraindo ambos */
    long long numerador_subtracao = (fracao1->sinal * ((fracao1->numerador) * (novo_denominador / fracao1->denominador))) -
        (fracao2->sinal * ((fracao2->numerador) * (novo_denominador / fracao2->denominador)));

    /* Envia 1 caso maior, -1 caso menor e 0 caso iguais */
    if(numerador_subtracao > 0)
        return FRACAO_MAIOR;
    else if(numerador_subtracao < 0)
        return FRACAO_MENOR;
    return  FRACAO_IGUAL;
}

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
bool compararFracoes(byte operador, Fracao *fracao1, Fracao *fracao2){
    /* Verifica a consistência das frações */
    if(fracao1 == NULL || fracao2 == NULL){
        printError("FRACOES INEXISTENTES! NAO E POSSIVEL EXECUTAR A OPERACAO!");
        return false;
    }

    /* Verifica se o operador esta definido */
    if(operador != COMPARA_IGUAL &&
            operador != COMPARA_MAIOR &&
            operador != COMPARA_MAIOR_IGUAL &&
            operador != COMPARA_MENOR &&
            operador != COMPARA_MENOR_IGUAL){
        printError("FRACAO NAO DEFINIDA!");
        return false;
    }

    /* Verifica as frações */
    int comparacao = comparaFracoes(fracao1, fracao2);

    /* Verifica de acordo o operador */
    switch(operador){
    case COMPARA_IGUAL:
        return (comparacao == 0);

    case COMPARA_MAIOR:
        return (comparacao == 1);

    case COMPARA_MAIOR_IGUAL:
        return (comparacao >= 0);

    case COMPARA_MENOR:
        return (comparacao == -1);

    case COMPARA_MENOR_IGUAL:
        return (comparacao <= 0);
    }

    /* O código não deve chegar até este ponto */
    printError("ERRO AO COMPARAR FUNCOES! OPERADOR NAO DEFINIDO!");
    return false;
}

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
bool simplificarFracao(Fracao *fracao){
    /* Checa se o ponteiro é válido */
    if(fracao == NULL){
        printError("FRACAO INEXISTENTE! PONTEIRO INVALIDO!");
        return false;
    }

    /* Encontra um fator comum para esta fração */
    long long fator_comum = MDC(fracao->numerador, fracao->denominador);

    /* Divide ambas as partes da fracao pelo fator comum */
    fracao->numerador = fracao->numerador / fator_comum;
    fracao->denominador = fracao->denominador / fator_comum;

    return true;
}

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
Fracao* leFracao(void){
    char separador;
    long long numerador;
    long long denominador;

    /* Lê a primeira parte da fração */
    scanf("%lld%c", &numerador, &separador);

    /* Checa o tipo de separador, na falta de um separador nosso denominador é 1  */
    if(separador != FRACAO_DIGITO_SEPARADOR){
        denominador = 1;
    } else {
        /* Na presença de um separador nós lemos o denominador */
        scanf("%lld", &denominador);
    }

    /* Com os números lidos, tenta alocar a nova fração */
    Fracao *_new_fracao = newFracao(numerador, denominador);

    /* Verifica a fração */
    if(_new_fracao != NULL){
        printError("FRACAO INVALIDA! ERRO NA LEITURA!");
        return NULL;
    }

    return _new_fracao;
}

/**
 *
 * Imprime uma fração no formato n/d na saída padrão.
 *
 * @brief imprimeFracao Imprime uma fração
 * @param fracao Fração a ser impressa
 * @return Retorna true caso tudo tenha ocorrido bem e falso caso contrário
 */
bool imprimeFracao(Fracao *fracao){
    /* Checa se a fração é válida */
    if(fracao == NULL){
        printError("FRACAO INVALIDA NAO SERA POSSIVEL IMPRIMIR!");
        return false;
    }

    /* Imprime os valores, adicionando o negativo caso necessário */
    if(fracao->sinal < 0)
        printf("-");
    printf("%lld/%lld", fracao->numerador, fracao->denominador);

    return true;
}

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
long long MDC(long long a, long long b){
    long long c;

    while ( a != 0 ) {
       c = a;
       a = b % a;
       b = c;
    }

    return b;
}

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
long long MMC(long long a, long long b){
    return (a * b) / MDC(a, b);
}
