#include "tipos/vetor.h"
#include "tipos/matriz.h"
#include "operacoes_matriz.h"
#include "utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* PRIVATE - Realiza o pivoteamento parcial */
bool pivoteamentoParcial(Matriz *matriz, unsigned int pivo, unsigned int *trocas){
    unsigned int i, j;

    /* Verifica se a matriz é válida */
    if(matriz == NULL){
        printError("MATRIZ INVALIDA NAO E POSSIVEL REALIZAR OPERACAO!");
        return false;
    }

    /* Verifica se pivot está presente na tabela */
    if((int)pivo > matriz->nLinhas){
        printError("PIVO NAO ESTA ESTA NO RANGE DE LINHAS DISPONIVEL!");
        return false;
    }

    /* Valor de i é igual ao pivot */
    i = pivo;

    /* Checa se é necessária a troca */
    bool troca = false;

    /* Procura em uma dada coluna o maior valor desta, a partir do pivot */
    double maxValor = matriz->linhas[i][i];
    unsigned int maxLinha = (unsigned int)i;
    for(j = i + 1; j < (unsigned int)matriz->nLinhas; j++){
        /* Checa se encontramos uma linha com um valor maior na coluna do pivot */
        if(fabs(maxValor) < fabs(matriz->linhas[j][i])){
            maxValor = matriz->linhas[j][i];
            maxLinha = (unsigned int)j;
            troca = true;
        }
    }

    /* Troca a linha do pivot com a linha de maior valor nesta coluna */
    if(troca){
        operacaoTrocaLinha(matriz, (maxLinha + 1), (unsigned int)(i + 1));
        (*trocas) += 1;
    }

    return true;
}

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
Vetor* operacaoGaussMatriz(Matriz *matriz){
    /* Verifica se a matriz é válida */
    if(matriz == NULL){
        printError("MATRIZ INEXISTENTE! NAO E POSSIVEL EXECUTAR A OPERACAO!");
        return NULL;
    }

    /* A matriz precisa ter ao menos duas colunas */
    if(matriz->nColunas < 2){
        printError("A MATRIZ TEM QUE TER AO MENOS DUAS COLUNAS!");
        return NULL;
    }

    /* A matriz precisa estar na forma aumentada com o número de colunas sendo igual ao de linhas + 1 */
    if((matriz->nLinhas + 1) != matriz->nColunas){
        printError("NAO E POSSIVEL RESOLVER ESTE SISTEMA DE EQUACOES!");
        return NULL;
    }

    /* Vetor de respostas */
    Vetor *vetor_resposta = newVetor("R", (unsigned int)matriz->nLinhas, NULL);

    /* Verifica se não houve erros ao alocar o vetor de resposta */
    if(vetor_resposta == NULL){
        printError("ERRO AO INICIALIZAR O VETOR RESPOSTA NAO E POSSIVEL CONTINUAR");
        return NULL;
    }

    /* Satisfeita as condições acima aplicamos o algoritmo */
    int i, j;

    /* Iremos percorrer os n-1 elementos da diagonal principal (obs.: a última sempre estara correta) */
    for(i = 0; i < (matriz->nLinhas - 1); i++){
        /* Realizamos o pivoteamento parcial */
        if(!pivoteamentoParcial(matriz, (unsigned int)i, NULL)){
            printError("ERRO NO PIVOTEAMENTO PARCIAL NAO E POSSIVEL CONTINUAR!");
            return NULL;
        }

        /* Percore todos os elementos abaixo do pivot executando a operacao Lj <- Lj - Li * (Aji/Aii)*/
        for(j = i + 1; j < matriz->nLinhas; j++){
            /* Obtem o fator que irá reduzir essa coluna */
            double fator = -(matriz->linhas[j][i] / matriz->linhas[i][i]);

            /* Executa a operação elementar */
            if(!operacaoSomaEntreLinhas(matriz,
                                       (unsigned int)(j + 1),
                                       (unsigned int)(i + 1),
                                        fator)){
                printError("ERRO AO EXECUTAR OPERACAO ELEMENTAR SOBRE A LINHA!");
                return NULL;
            }
        }
    }

    /* Terminado o algoritmo verificamos se o determinante da matriz é diferente de 0 */
    double determinante = 0;
    for(i = 0; i < matriz->nLinhas; i++){
        determinante *= matriz->linhas[i][i];
    }

    /* Se determinante igual a 0 não temos uma resposta exata */
    if(doubleIgualZero(determinante)){
        printError("SISTEMA POSSIVEL E INDETERMINADO OU SISTEMA IMPOSSIVEL! NAO E POSSIVEL CONTINUAR!");
        return NULL;
    }

    /* Se o determinante não é igual a zero temos resultado */
    int ultima_linha = matriz->nLinhas - 1;
    int ultima_coluna = ultima_linha;
    int coluna_resultado = matriz->nColunas - 1;

    /* Verifica o resultado da ultima variavel */
    double ultima_variavel = (matriz->linhas[ultima_linha][ultima_coluna] / matriz->linhas[ultima_linha][coluna_resultado]);

    /* Salva este valor no vetor de resultado */
    vetor_resposta->coordenadas[ultima_coluna] = ultima_variavel;

    /* Aplica a substituição regressiva */
    for(i = (ultima_linha - 1); i >= 0; i--){
        double soma_sistema = matriz->linhas[i][coluna_resultado];
        for(j = i + 1; j < matriz->nLinhas; j++)
            soma_sistema -= (vetor_resposta->coordenadas[j] * matriz->linhas[i][j]);
        vetor_resposta->coordenadas[i] = soma_sistema / matriz->linhas[i][i];
    }

    return vetor_resposta;
}

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
Vetor* operacaoGausJordanMatriz(Matriz *matriz){
    /* Verifica se a matriz é válida */
    if(matriz == NULL){
        printError("MATRIZ INEXISTENTE! NAO E POSSIVEL EXECUTAR A OPERACAO!");
        return NULL;
    }

    /* A matriz precisa ter ao menos duas colunas */
    if(matriz->nColunas < 2){
        printError("A MATRIZ TEM QUE TER AO MENOS DUAS COLUNAS!");
        return NULL;
    }

    /* A matriz precisa estar na forma aumentada com o número de colunas sendo igual ao de linhas + 1 */
    if((matriz->nLinhas + 1) != matriz->nColunas){
        printError("NAO E POSSIVEL RESOLVER ESTE SISTEMA DE EQUACOES!");
        return NULL;
    }

    /* Vetor de respostas */
    Vetor *vetor_resposta = newVetor("R", (unsigned int)matriz->nLinhas, NULL);

    /* Verifica se não houve erros ao alocar o vetor de resposta */
    if(vetor_resposta == NULL){
        printError("ERRO AO INICIALIZAR O VETOR RESPOSTA NAO E POSSIVEL CONTINUAR");
        return NULL;
    }

    /* Satisfeita as condições acima aplicamos o algoritmo */
    int i, j;

    /* Iremos percorrer os n elementos da diagonal principal, limpando os valores acima e abaixo da coluna de cada pivot */
    for(i = 0; i < matriz->nLinhas; i++){
        /* Realizamos o pivoteamento parcial */
        if(!pivoteamentoParcial(matriz, (unsigned int)i, NULL)){
            printError("ERRO NO PIVOTEAMENTO PARCIAL NAO E POSSIVEL CONTINUAR!");
            return NULL;
        }

        /* Percore todos os elementos excluindo o pivot executando a operacao Lj <- Lj - Li * (Aji/Aii)*/
        for(j = 0; j < matriz->nLinhas; j++){
            if(i != j){
                /* Obtem o fator que irá reduzir essa coluna */
                double fator = -(matriz->linhas[j][i] / matriz->linhas[i][i]);

                /* Executa a operação elementar */
                if(!operacaoSomaEntreLinhas(matriz,
                                           (unsigned int)(j + 1),
                                           (unsigned int)(i + 1),
                                            fator)){
                    printError("ERRO AO EXECUTAR OPERACAO ELEMENTAR SOBRE A LINHA!");
                    return NULL;
                }
            }
        }
    }

    /* Terminado o algoritmo verificamos se o determinante da matriz é diferente de 0 */
    double determinante = 0;
    for(i = 0; i < matriz->nLinhas; i++){
        determinante *= matriz->linhas[i][i];
    }

    /* Se determinante igual a 0 não temos uma resposta exata */
    if(doubleIgualZero(determinante)){
        printError("SISTEMA POSSIVEL E INDETERMINADO OU SISTEMA IMPOSSIVEL! NAO E POSSIVEL CONTINUAR!");
        return NULL;
    }

    /* Se o determinante não é igual a zero temos resultado */
    int ultima_linha = matriz->nLinhas - 1;
    int ultima_coluna = ultima_linha;
    int coluna_resultado = matriz->nColunas - 1;

    /* Verifica o resultado da ultima variavel */
    double ultima_variavel = (matriz->linhas[ultima_linha][ultima_coluna] / matriz->linhas[ultima_linha][coluna_resultado]);

    /* Salva este valor no vetor de resultado */
    vetor_resposta->coordenadas[ultima_coluna] = ultima_variavel;

    /* Aplica a substituição regressiva */
    for(i = (ultima_linha - 1); i >= 0; i--){
        double soma_sistema = matriz->linhas[i][coluna_resultado];
        for(j = i + 1; j < matriz->nLinhas; j++)
            soma_sistema -= (vetor_resposta->coordenadas[j] * matriz->linhas[i][j]);
        vetor_resposta->coordenadas[i] = soma_sistema / matriz->linhas[i][i];
    }

    return vetor_resposta;
}

/* Encontra o determinante da matriz */
double operacaoDeterminanteMatriz(Matriz *matriz, bool *erro){
    /* Verifica se a matriz é válida */
    if(matriz == NULL){
        printError("MATRIZ INEXISTENTE! NAO E POSSIVEL EXECUTAR A OPERACAO!");
        (*erro) = true;
        return 0;
    }

    /* A matriz precisa ser quadrada para encontrarmos um determinante */
    if(matriz->nLinhas != matriz->nColunas){
        printError("A MATRIZ PRECISA SER QUADRADA PARA TER UM DETERMINANTE!");
        (*erro) = true;
        return 0;
    }

    /* Conta o número de trocas devido a aplicação de pivoteamento parcial */
    unsigned int nTrocas = 0;

    /* Satisfeita as condições acima aplicamos o algoritmo de Gauss */
    int i, j;

    /* Iremos percorrer os n-1 elementos da diagonal principal (obs.: a última sempre estara correta) */
    for(i = 0; i < (matriz->nLinhas - 1); i++){
        /* Realizamos o pivoteamento parcial */
        if(!pivoteamentoParcial(matriz, (unsigned int)i, &nTrocas)){
            printError("ERRO NO PIVOTEAMENTO PARCIAL NAO E POSSIVEL CONTINUAR!");
            (*erro) = true;
            return 0;
        }

        /* Percore todos os elementos abaixo do pivot executando a operacao Lj <- Lj - Li * (Aji/Aii)*/
        for(j = i + 1; j < matriz->nLinhas; j++){
            /* Obtem o fator que irá reduzir essa coluna */
            double fator = -(matriz->linhas[j][i] / matriz->linhas[i][i]);

            /* Executa a operação elementar */
            if(!operacaoSomaEntreLinhas(matriz,
                                       (unsigned int)(j + 1),
                                       (unsigned int)(i + 1),
                                        fator)){
                printError("ERRO AO EXECUTAR OPERACAO ELEMENTAR SOBRE A LINHA!");
                (*erro) = true;
                return 0;
            }
        }
    }

    /* Calcula o determinante da Matriz */
    double determinante = 0;
    for(i = 0; i < matriz->nLinhas; i++){
        determinante *= matriz->linhas[i][i];
    }

    /* Para cada troca teremos a inversão do sinal do determinante */
    determinante *= (double)(-1 * (int)nTrocas);

    return determinante;
}

/* Encontra o Kernel de uma Matriz */
Vetor* operacaoKernelMatriz(Matriz *matriz){

}

/* Encontra uma base para a matriz */
Matriz* operacaoBaseMatriz(Matriz *matriz){
    printWarning("TODO - NAO IMPLEMENTADO!");
    return NULL;
}
