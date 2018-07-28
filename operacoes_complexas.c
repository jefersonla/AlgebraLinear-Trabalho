#include "tipos/vetor.h"
#include "tipos/matriz.h"
#include "operacoes_matriz.h"
#include "utils/utils.h"
#include "utils/ajuda.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* PRIVATE - Realiza o pivoteamento parcial */
bool pivoteamentoParcial(Matriz *matriz, unsigned int linPivo, unsigned int colPivo, unsigned int *trocas){
    unsigned int j;

    /* Verifica se a matriz é válida */
    if(matriz == NULL){
        printError("MATRIZ INVALIDA NAO E POSSIVEL REALIZAR OPERACAO!");
        return false;
    }

    /* Verifica se pivot está presente na tabela */
    if((int)colPivo >= matriz->nColunas && (int) linPivo >= matriz->nLinhas){
        printError("PIVO NAO ESTA ESTA DENTRO DA MATRIZ!");
        return false;
    }

    /* Checa se é necessária a troca */
    bool troca = false;

    /* Procura em uma dada coluna o maior valor desta, a partir do pivot */
    double maxValor = fabs(matriz->linhas[linPivo][colPivo]);
    unsigned int maxLinha = linPivo;
    for(j = linPivo + 1; j < (unsigned int)matriz->nLinhas; j++){
        /* Checa se encontramos uma linha com um valor maior na coluna do pivot */
        if(fabs(maxValor) < fabs(matriz->linhas[j][colPivo]) && !doubleIgualZero(matriz->linhas[j][colPivo])){
            maxValor = matriz->linhas[j][colPivo];
            maxLinha = j;
            troca = true;
        }
    }

    /* Troca a linha do pivot com a linha de maior valor nesta coluna */
    if(troca){
        operacaoTrocaLinha(matriz, (maxLinha + 1), (unsigned int)(linPivo + 1));

        /* Se ponteiro para variavél de trocas não for nulo incrementa */
        if(trocas != NULL)
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

    /* Corrige o valor do determinante */
    double correcao_fator = 1;

    /* Satisfeita as condições acima aplicamos o algoritmo */
    int i, j;

    /* Iremos percorrer os n-1 elementos da diagonal principal (obs.: a última sempre estara correta) */
    for(i = 0; i < (matriz->nLinhas - 1); i++){
        /* Realizamos o pivoteamento parcial */
        if(!pivoteamentoParcial(matriz, (unsigned int)i, (unsigned int)j, NULL)){
            printError("ERRO NO PIVOTEAMENTO PARCIAL NAO E POSSIVEL CONTINUAR!");
            return NULL;
        }

        /* Percore todos os elementos abaixo do pivot executando a operacao Lj <- Lj - Li * (Aji/Aii)*/
        for(j = i + 1; j < matriz->nLinhas; j++){
            /* Para executar a operação primeiro verificamos se o pivo e a linha é não nula */
            if(!doubleIgualZero(matriz->linhas[i][i]) && !doubleIgualZero(matriz->linhas[j][i])){
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

        /* Para executar a operação primeiro verificamos se o pivo é não nulo */
        if(!doubleIgualZero(matriz->linhas[i][i])){
            /* Reduz o valor da linha para que o pivo seja 1 e seja positivo */
            /* Obs.: Reduzir um fator implica em multiplicar por um numero que resulte em 1
                     ou seja '(1 / valor_coluna) * linha' vai resultar em uma linha que
                     contém o pivo com o valor 1, porém ao mesmo tempo, multiplicar a linha
                     pelo mesmo sinal do valor da coluna implica em realizar a operação
                     como uma potência par o que modifica o sinal dela para o positivo
                     ou seja o fato de corrigir o valor do pivo transforma ele em um número
                     positivo. */
            double fator_reducao = 1 / matriz->linhas[i][i];
            correcao_fator *= matriz->linhas[i][i];

            if(!operacaoMultiplicaPorEscalar(matriz,
                                       (unsigned int)(i + 1),
                                        fator_reducao)){
                printError("ERRO AO EXECUTAR OPERACAO ELEMENTAR SOBRE A LINHA!");
                return NULL;
            }
        }
    }

    /* Ultimas posições do vetor */
    int ultima_linha = matriz->nLinhas - 1;
    int ultima_coluna = ultima_linha;
    int coluna_resultado = matriz->nColunas - 1;

    /* Para executar a operação primeiro verificamos se o pivo é não nulo */
    if(!doubleIgualZero(matriz->linhas[ultima_linha][ultima_coluna])){
        /* Reduz o valor da linha para que o pivo seja 1 */
        double fator_reducao = 1 / matriz->linhas[ultima_linha][ultima_coluna];
        correcao_fator *= matriz->linhas[ultima_linha][ultima_coluna];
        if(!operacaoMultiplicaPorEscalar(matriz,
                                   (unsigned int)(ultima_linha + 1),
                                    fator_reducao)){
            printError("ERRO AO EXECUTAR OPERACAO ELEMENTAR SOBRE A LINHA!");
            return NULL;
        }
    }

    /* Terminado o algoritmo verificamos se o determinante da matriz é diferente de 0 */
    double determinante = correcao_fator;
    for(i = 0; i < matriz->nLinhas; i++){
        determinante *= matriz->linhas[i][i];
    }

    /* Se determinante igual a 0 não temos uma resposta exata */
    if(doubleIgualZero(determinante)){
        printError("SISTEMA POSSIVEL E INDETERMINADO OU SISTEMA IMPOSSIVEL! NAO E POSSIVEL CONTINUAR!");
        return NULL;
    }

    /* Verifica o resultado da ultima variavel */
    double ultima_variavel = matriz->linhas[ultima_linha][coluna_resultado];

    /* Salva este valor no vetor de resultado */
    vetor_resposta->coordenadas[ultima_coluna] = ultima_variavel;

    /* Aplica a substituição regressiva */
    for(i = (ultima_linha - 1); i >= 0; i--){
        double soma_sistema = matriz->linhas[i][coluna_resultado];
        for(j = i + 1; j < matriz->nLinhas; j++)
            soma_sistema -= (vetor_resposta->coordenadas[j] * matriz->linhas[i][j]);
        vetor_resposta->coordenadas[i] = soma_sistema;
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

    /* Corrige o valor do determinante */
    double correcao_fator = 1;

    /* Satisfeita as condições acima aplicamos o algoritmo */
    int i, j;

    /* Iremos percorrer os n elementos da diagonal principal, limpando os valores acima e abaixo da coluna de cada pivot */
    for(i = 0; i < matriz->nLinhas; i++){
        /* Realizamos o pivoteamento parcial */
        if(!pivoteamentoParcial(matriz, (unsigned int)i, (unsigned int)j, NULL)){
            printError("ERRO NO PIVOTEAMENTO PARCIAL NAO E POSSIVEL CONTINUAR!");
            return NULL;
        }

        /* Percore todos os elementos excluindo o pivot executando a operacao Lj <- Lj - Li * (Aji/Aii)*/
        for(j = 0; j < matriz->nLinhas; j++){
            if(i != j){
                /* Para executar a operação primeiro verificamos se o pivo e a linha é não nula */
                if(!doubleIgualZero(matriz->linhas[i][i]) && !doubleIgualZero(matriz->linhas[j][i])){
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

        /* Para executar a operação primeiro verificamos se o pivo é não nulo */
        if(!doubleIgualZero(matriz->linhas[i][i])){
            /* Reduz o valor da linha para que o pivo seja 1 e seja positivo */
            /* Obs.: Reduzir um fator implica em multiplicar por um numero que resulte em 1
                     ou seja '(1 / valor_coluna) * linha' vai resultar em uma linha que
                     contém o pivo com o valor 1, porém ao mesmo tempo, multiplicar a linha
                     pelo mesmo sinal do valor da coluna implica em realizar a operação
                     como uma potência par o que modifica o sinal dela para o positivo
                     ou seja o fato de corrigir o valor do pivo transforma ele em um número
                     positivo. */
            double fator_reducao = 1 / matriz->linhas[i][i];
            correcao_fator *= matriz->linhas[i][i];
            if(!operacaoMultiplicaPorEscalar(matriz,
                                       (unsigned int)(i + 1),
                                        fator_reducao)){
                printError("ERRO AO EXECUTAR OPERACAO ELEMENTAR SOBRE A LINHA!");
                return NULL;
            }
        }
    }

    /* Terminado o algoritmo verificamos se o determinante da matriz é diferente de 0 */
    double determinante = correcao_fator;
    for(i = 0; i < matriz->nLinhas; i++){
        determinante *= matriz->linhas[i][i];
    }

    /* Se determinante igual a 0 não temos uma resposta exata */
    if(doubleIgualZero(determinante)){
        printError("SISTEMA POSSIVEL E INDETERMINADO OU SISTEMA IMPOSSIVEL! NAO E POSSIVEL CONTINUAR!");
        return NULL;
    }

    /* Se o determinante não é igual a zero temos resultado */
    int coluna_resultado = matriz->nColunas - 1;

    /* Aplica a substituição regressiva, na forma de Jordan, cada coluna de variavel tem apenas o resultado */
    for(i = 0; i < matriz->nLinhas; i++){
        vetor_resposta->coordenadas[i] = matriz->linhas[i][coluna_resultado];
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
        if(!pivoteamentoParcial(matriz, (unsigned int)i, (unsigned int)j, &nTrocas)){
            printError("ERRO NO PIVOTEAMENTO PARCIAL NAO E POSSIVEL CONTINUAR!");
            (*erro) = true;
            return 0;
        }

        /* Percore todos os elementos abaixo do pivot executando a operacao Lj <- Lj - Li * (Aji/Aii)*/
        for(j = i + 1; j < matriz->nLinhas; j++){
            /* Para executar a operação primeiro verificamos se o pivo e a linha é não nula */
            if(!doubleIgualZero(matriz->linhas[i][i]) && !doubleIgualZero(matriz->linhas[j][i])){
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
    }

    /* Calcula o determinante da Matriz */
    double determinante = 1;
    for(i = 0; i < matriz->nLinhas; i++){
        determinante *= matriz->linhas[i][i];
    }

    /* Para cada troca teremos a inversão do sinal do determinante */
    determinante *= pow(-1, (int)nTrocas);

    return determinante;
}

/* Encontra o Kernel de uma Matriz */
Vetor** operacaoKernelMatriz(Matriz *matriz, unsigned int *numeroVetoresResposta){
    /* Verifica se a matriz é válida */
    if(matriz == NULL){
        printError("MATRIZ INEXISTENTE! NAO E POSSIVEL EXECUTAR A OPERACAO!");
        return NULL;
    }

    /* Verificamos se o ponteiro para o numero de vetores de resposta é válido */
    if(numeroVetoresResposta == NULL){
        printError("E PRECISO ESPECIFICAR UM PONTEIRO PARA INFORMAR O TAMANHO DA RESPOSTA!");
        return NULL;
    }

    /* Iremos percorrer os n elementos da diagonal principal, limpando os valores acima e abaixo da coluna de cada pivot */
    int i, j;
    unsigned int colunaPivo;
    for(i = 0, colunaPivo = 0; i < matriz->nLinhas; i++){
        /* Tenta realizar o pivoteamento parcial em todas as colunas, até achar uma não nula */
        do{
            /* Realizamos o pivoteamento parcial para a coluna do pivo atual */
            if(!pivoteamentoParcial(matriz, (unsigned int)i, colunaPivo, NULL)){
                printError("ERRO NO PIVOTEAMENTO PARCIAL NAO E POSSIVEL CONTINUAR!");
                return NULL;
            }

            /* Incrementa o tamanho da coluna do pivo */
            colunaPivo++;
        }while(doubleIgualZero(matriz->linhas[i][colunaPivo]) && (int)colunaPivo < matriz->nColunas);

        /* Verifica se a coluna é nula se for nula paramos a execucao do for */
        if((int)colunaPivo >= matriz->nColunas && doubleIgualZero(matriz->linhas[i][colunaPivo - 1]))
            break;

        /* Decrementa o tamanho do pivo */
        colunaPivo--;

        /* Percore todos os elementos excluindo o pivot executando a operacao Lj <- Lj - Lc * (Ajc/Aic)*/
        for(j = 0; j < matriz->nLinhas; j++){
            if(i != j){
                /* Para executar a operação primeiro verificamos se o pivo e a linha é não nula */
                if(!doubleIgualZero(matriz->linhas[i][colunaPivo]) && !doubleIgualZero(matriz->linhas[j][colunaPivo])){
                    /* Obtem o fator que irá reduzir essa coluna */
                    double fator = -(matriz->linhas[j][colunaPivo] / matriz->linhas[i][colunaPivo]);

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

        /* Para executar a operação primeiro verificamos se o pivo é não nulo */
        if(!doubleIgualZero(matriz->linhas[i][colunaPivo])){
            /* Reduz o valor da linha para que o pivo seja 1 e seja positivo */
            /* Obs.: Reduzir um fator implica em multiplicar por um numero que resulte em 1
                     ou seja '(1 / valor_coluna) * linha' vai resultar em uma linha que
                     contém o pivo com o valor 1, porém ao mesmo tempo, multiplicar a linha
                     pelo mesmo sinal do valor da coluna implica em realizar a operação
                     como uma potência par o que modifica o sinal dela para o positivo
                     ou seja o fato de corrigir o valor do pivo transforma ele em um número
                     positivo. */
            double fator_reducao = 1 / matriz->linhas[i][colunaPivo];
            if(!operacaoMultiplicaPorEscalar(matriz,
                                       (unsigned int)(i + 1),
                                        fator_reducao)){
                printError("ERRO AO EXECUTAR OPERACAO ELEMENTAR SOBRE A LINHA!");
                return NULL;
            }
        }

        /* Incrementa o valor do pivo para olhar a próxima coluna */
        colunaPivo++;
    }

    /* Precisamos indicar quais linhas são variaveis livres da nossa matriz */
    bool *variaveisLivres = malloc(sizeof(bool) * (unsigned int)matriz->nColunas);
    memset(variaveisLivres, true, (unsigned int)matriz->nColunas);

    /* Iremos varrer a matriz completa e parar assim que encontrar uma linha nula */
    for(i = 0; i < matriz->nLinhas; i++){
        /* Verifica se a linha é nula */
        for(j = 0; j < matriz->nColunas; j++)
            if(!doubleIgualZero(matriz->linhas[i][j]))
                break;

        /* Se encontramos uma linha nula inteira então as linhas restantes também são nulas */
        if(j == matriz->nColunas)
            break;

        /* Se a linha é não nula então paramos no endereço da coluna */
        variaveisLivres[j] = false;
    }

    /* Com a matriz finalizada agora iremos encontrar a nulidade da matriz na forma de Jordan
       para isso precisamos verificar o nosso posto lembrando que o posto é o numero de linhas
       não nulas da nossa matriz escalonada na forma de Jordan e a nulidade é o número de linhas
       nulas ou seja sabendo o posto a nulidade é basicamente N(A) = nColunas - P(A) */
    unsigned int posto = (unsigned int)i;
    unsigned int nulidade = (unsigned int)matriz->nColunas - posto;

    /* Com essas informações iremos criar uma matriz que irá conter os valores resultantes do kernel
       Essa matriz tera o numero de colunas igual a nulidade e o número de linhas igual ao número de colunas */
    Matriz *matriz_resposta = newMatriz(matriz->nColunas, (int)nulidade, MATRIZ_VAZIA, NULL);

    /* Verifica se não houve problemas ao alocar essa matriz */
    if(matriz_resposta == NULL){
        printError("ERRO AO ALOCAR MATRIZ DE RESPOSTA!");
        return NULL;
    }

    /* Para cada linha que for uma variavel livre iremos inserir 1 para a variavél e 0 para as outras colunas */
    int k;
    int colunaVariavelLivre = 0;
    int linhaVariavelNaoLivre = 0;
    for(i = 0; i < matriz_resposta->nLinhas; i++){
        /* Se a variavel é livre seu valor é zero para todas colunas exceto a coluna desta */
        if(variaveisLivres[i]){
            for(j = 0; j < matriz_resposta->nColunas; j++)
                if(j == colunaVariavelLivre)
                    matriz_resposta->linhas[i][j] = 1;
                else
                    matriz_resposta->linhas[i][j] = 0;

            /* Incrementa o contador da coluna da variavel livre */
            colunaVariavelLivre++;
        }
        else {
            /* Caso contrário iremos colocar o valor da linha negado com exceção da coluna usada */
            for(k = 0, j = 0; j < matriz->nColunas; j++)
                /* Se a variavel é livre copiamos o valor da linha */
                if(variaveisLivres[j]){
                    matriz_resposta->linhas[i][k] = -matriz->linhas[linhaVariavelNaoLivre][j];
                    k++;
                }

            /* Incrementa o contador da linha da variavel nao livre */
            linhaVariavelNaoLivre++;
        }
    }

#ifdef DEBUG
    printInfo("MATRIZ RESPOSTA:");
    imprimeMatriz(matriz_resposta);
#endif

    /* Apesar de básico a separação ajuda na criação dos vetores de resposta, o numero de vetores de resposta é
     * do tamanho da nulidade com ponteiros para vetores especificos */
    Vetor **vetores_resposta = malloc(sizeof (Vetor*) * nulidade);

    /* Verifica se os vetores de resposta são válidos */
    if(vetores_resposta == NULL){
        printFatalError("ERRO AO ALOCAR VETOR DE RESPOSTA!");
        exit(EXIT_FAILURE);
    }

    /* Cria um vetor temporário para novas variaveis */
    double *vetor_tmp = malloc(sizeof(double) * (size_t)matriz_resposta->nLinhas);

    /* Verifica se o vetor temporario foi bem alocado */
    if(vetor_tmp == NULL){
        printFatalError("ERRO AO ALOCAR VETOR TEMPORARIO!");
        exit(EXIT_FAILURE);
    }

    /* ID do vetor */
    char *idVariavelLivre = malloc(sizeof(char) * 5);
    int numVariavelLivre = 0;

    /* Aloca cada vetor resposta, tendo como resultado uma coluna da matriz de resposta */
    for(i = 0; i < matriz_resposta->nColunas; i++){
        /* Copia as linhas de cada coluna do vetor de resposta */
        for(j = 0; j < matriz_resposta->nLinhas; j++)
            vetor_tmp[j] = matriz_resposta->linhas[j][i];

        /* Procura uma variavel livre */
        while(numVariavelLivre < matriz_resposta->nLinhas && !variaveisLivres[numVariavelLivre])
            numVariavelLivre++;

        /* Aloca um vetor de resposta com base nesses valores */
        snprintf(idVariavelLivre, 5, "X%d", (numVariavelLivre + 1));
        vetores_resposta[i] = newVetor(idVariavelLivre, (unsigned int)matriz_resposta->nLinhas, vetor_tmp);
        numVariavelLivre++;
    }

    /* Salva o numero de vetores resultado */
    *numeroVetoresResposta = (unsigned int)matriz_resposta->nColunas;

    /* Desaloca variaveis temporarias */
    ptrMatriz *ptr_matriz_resposta = &matriz_resposta;
    deleteMatriz(ptr_matriz_resposta);
    free(vetor_tmp);
    free(idVariavelLivre);
    free(variaveisLivres);

    return vetores_resposta;
}

/* Encontra uma base para a matriz */
Matriz* operacaoBaseMatriz(Matriz *matriz){
    printWarning("TODO - NAO IMPLEMENTADO!");
    return NULL;
}
