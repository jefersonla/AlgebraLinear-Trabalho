#include "./fracao.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*------------ Fracao Structure Methods ------------ */

/* Cria uma novo fracao */
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

/* Desaloca uma fracao */
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

/* Clona uma fracao */
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

/* Soma de fracoes */
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

/* Subtracao de fracoes */
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

/* Produto de fracoes */
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

/* Multiplicacao de Fracao por escalar */
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

/* Divisão de frações */
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

/* Divisao de Fração por escalar */
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

/* Divisao de escalar por fracao */
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

/* Realiza operação unária de menos numa fração */
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

/* Compara duas fracoes */
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

/* Compara duas frações usando um operador */
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


/* Reduz uma fração */
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

/* Lê fração */
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

/* Imprime fracao */
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

/* MDC - Maior Divisor Comum */
long long MDC(long long a, long long b){
    long long c;

    while ( a != 0 ) {
       c = a;
       a = b % a;
       b = c;
    }

    return b;
}

/* MMC - Minimo Multiplo Comum */
long long MMC(long long a, long long b){
    return (a * b) / MDC(a, b);
}
