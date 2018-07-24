#include "tipos/lista.h"
#include "tipos/matriz.h"
#include "tipos/operacoes_matriz.h"
#include "utils/utils.h"
#include "entrada.h"

#include <stdio.h>
#include <math.h>

/**
 *
 * Exibe o menu de opções para o usuario.
 *
 * @brief Exibe o menu
 */
void mostraMenu(void){
    printf("::: Menu :::\n\n"
           "1 > Inserir Matriz\n"
           "2 > Listar Matrizes\n"
           "3 > Deletar Matriz\n"
           "4 > Clonar Matriz\n"
           "5 > Realizar operacoes elementares numa matriz\n"
           "6 > Realizar operacoes entre matrizes\n"
           "7 > Realizar operacoes complexas (metodo gauss, kernel, ...)\n"
           "8 > Salvar resultado\n"
           "0 > Sair\n");
}

/**
 *
 * Menu de opções elementares, sobre as linhas de uma matriz.
 * Essas opções são executadas conforme entrada do usuario.
 *
 * @brief menuOpcoesElementares Menu opções elementares
 */
void menuOpcoesElementares(void){
    printf("::: Operacoes Elementares :::\n\n"
           "1 > Troca entre linhas (L1 <-> L2)\n"
           "2 > Multiplicar linha por escalar (L1 <- E * L1)\n"
           "3 > Soma entre uma linha, com outra multiplicada por escalar (L1 <- L1 + E * L2)\n"
           "0 > Voltar\n");
}

/**
 *
 * Menu de operações aritméticas entre matrizes.
 * Essas opções são executadas entre matrizes definidas pelo usuario.
 *
 * @brief menuOpcoesAritmeticas Menu de operações aritméticas
 */
void menuOpcoesAritmeticas(void){
    printf("::: Operacoes Aritmeticas :::\n\n"
           "1 > Soma de matrizes (M <- M1 + M2)\n"
           "2 > Subtracao de matrizes (M <- M1 - M2)\n"
           "3 > Produto de matrizes (M <- M1 * M2)\n"
           "4 > Multiplicação por escalar (M <- M1 * E)\n"
           "5 > Transpota da matriz (M <- M^t)\n"
           "6 > Inversa da matriz (M <- M^-1)\n"
           "7 > Divisão de matrizes (M <- M1 / M2)\n"
           "0 > Voltar\n");
}

/**
 *
 * Insere uma matriz definida pelo usuario a lista de matrizes.
 * Essa matriz poderá ser utilizada para fins futuros, como operações
 * entre matrizes, ou entre linhas de uma matriz.
 *
 * @brief inserirMatriz Insere uma matriz a lista de matrizes
 * @param listaMatrizes Lista contendo todas as matrizes já cadastradas
 */
void inserirMatriz(Lista *listaMatrizes){
    unsigned int nLinhas;
    unsigned int nColunas;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL INSERIR!");
        return;
    }

    /* Recebe o numero de linhas */
    do {
        quebraLinha();
        printf("Insira o número de linhas da matriz => ");
        scanf("%u", &nLinhas);

        if(nLinhas == 0){
            printError("NUMERO DE LINHAS NAO PODE SER ZERO!");
        }
    } while(nLinhas == 0);

    /* Recebe o número de colunas */
    do {
        printf("Insira o número de colunas da matriz => ");
        scanf("%u", &nColunas);

        if(nColunas == 0){
            printError("NUMERO DE COLUNAS NAO PODE SER ZERO!");
        }
    } while(nColunas == 0);

    /* Cria uma matriz vazia */
    Matriz *nova_matriz = newMatriz((int)nLinhas, (int)nColunas, MATRIZ_VAZIA, NULL);

    /* Verifica se a matriz alocada é válida */
    if(nova_matriz == NULL){
        printError("ERROS AO ALOCAR A NOVA MATRIZ!");
        return;
    }

    /* Pega os valores restantes do usuario */
    printf("Insira os valores da matriz...\n");
    unsigned int i, j;
    for(i = 0; i < nLinhas; i++)
        for(j = 0; j < nColunas; j++)
            scanf("%lf", &nova_matriz->linhas[i][j]);
    quebraLinha();

    /* Atualiza o maior valor da matriz */
    atualizaMaiorValorMatriz(nova_matriz);

    /* Adiciona a matriz construida a lista */
    adicionaNoLista(listaMatrizes, INDICE_ALEATORIO, nova_matriz, true);

    /* Deleta matriz temporária */
    ptrMatriz *ptr_matriz = &nova_matriz;
    deleteMatriz(ptr_matriz);
}

/**
 *
 * Lista todas as matrizes presentes na memória.
 *
 * @brief listarMatrizes Lista todas as matrizes presentes na memória
 * @param listaMatrizes Lista de matrizes presente na memória
 */
void listarMatrizes(Lista *listaMatrizes){
    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL INSERIR!");
        return;
    }

    /* Lista todas as matrizes */
    exibeTodasMatrizesLista(listaMatrizes);
    quebraLinha();
}

/* Deletar matriz presentes na memória */
void deletarMatriz(Lista *listaMatrizes){
    unsigned int indiceRemover;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL INSERIR!");
        return;
    }

    /* Pega a entrada do usuario */
    do {
        quebraLinha();
        printf("ID do item a remover => ");
        scanf("%u", &indiceRemover);

        if(indiceRemover == 0){
            printError("AS MATRIZES SAO INDEXADAS DE 1 A N!");
        }
    } while(indiceRemover == 0);
    quebraLinha();

    removeNoLista(listaMatrizes, (int)indiceRemover);
}

/**
 *
 * Clona as matrizes presentes na memória, qualquer matriz pode ser clonada
 * e seu id sempre será o próximo ID disponível. O objetivo aqui é permitir
 * que um usuario possa utilizar uma instância antiga da matriz para operações
 * futuras.
 *
 * @brief clonarMatriz Clonar matriz presentes na memória
 * @param listaMatrizes Lista com todas as matrizes do sistema
 */
void clonarMatriz(Lista *listaMatrizes){
    NoLista *noMatriz;
    unsigned int idMatriz;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL INSERIR!");
        return;
    }

    /* Recebe o indice da matriz */
    quebraLinha();
    printf("Insira o indice da matriz a ser clonada => ");
    scanf("%u", &idMatriz);
    quebraLinha();

    /* Busca pelo id informado */
    noMatriz = buscaNoLista(listaMatrizes, (int)idMatriz);

    /* Checa se a matriz foi encontrada */
    if(noMatriz == NULL){
        printError("MATRIZ NAO ENCONTRADA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Clona a matriz */
    adicionaNoLista(listaMatrizes,INDICE_ALEATORIO, noMatriz->conteudo, true);
}

/* Executa a operação de soma entre matrizes */
void somaMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao){
    NoLista *noMatriz1;
    NoLista *noMatriz2;
    unsigned int idMatriz1;
    unsigned int idMatriz2;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Formato da operação */
    quebraLinha();
    printf("Formato -- M <- M1 + M2\n");
    quebraLinha();

    /* Recebe o indice da matriz 1 */
    quebraLinha();
    printf("Insira o indice de M1 => ");
    scanf("%u", &idMatriz1);

    /* Busca pelo id informado */
    noMatriz1 = buscaNoLista(listaMatrizes, (int)idMatriz1);

    /* Checa se a matriz foi encontrada */
    if(noMatriz1 == NULL){
        printError("MATRIZ NAO ENCONTRADA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Recebe o indice da matriz 2 */
    printf("Insira o indice de M2 => ");
    scanf("%u", &idMatriz2);
    quebraLinha();

    /* Busca pelo id informado */
    noMatriz2 = buscaNoLista(listaMatrizes, (int)idMatriz2);

    /* Checa se a matriz foi encontrada */
    if(noMatriz2 == NULL){
        printError("MATRIZ NAO ENCONTRADA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Exibe a matriz 1 */
    imprimeMatriz(noMatriz1->conteudo);
    quebraLinha();

    /* Simbolo da operação */
    printf("+\n");
    quebraLinha();

    /* Exibe a matriz 2 */
    imprimeMatriz(noMatriz2->conteudo);
    quebraLinha();

    /* Simbolo de resultado operação */
    printf("=\n");
    quebraLinha();

    /* Realiza a operação */
    Matriz *matrizResultado = somaMatriz(noMatriz1->conteudo, noMatriz2->conteudo);

    /* Checa se não houve erros ao executar a operação */
    if(matrizResultado == NULL){
        printError("ERRO AO ALOCAR MATRIZ DE RESULTADO DA OPERACAO!");
        return;
    }

    /* Exibe o resultado */
    imprimeMatriz(matrizResultado);
    quebraLinha();

    /* Verifica aonde o resultado deve ser salvo */
    if(salvaResultadoOperacao == SALVAR_NA_MATRIZ_ENTRADA){
        ptrMatriz *ptrMatriz1 = &noMatriz1->conteudo;
        if(!deleteMatriz(ptrMatriz1)){
            printError("ERRO AO DELETAR MATRIZ DE RESULTADO!");
            return;
        }

        /* Salva o ponteiro do resultado para a matriz de conteudo do nó */
        noMatriz1->conteudo = matrizResultado;
    } else {
        /* Salvar a matriz como uma nova matriz da lista de matrizes */
        if(!adicionaNoLista(listaMatrizes, INDICE_ALEATORIO, matrizResultado, false)){
            printError("NAO FOI POSSIVEL SALVAR O RESULTADO DA MATRIZ EM UM NOVO INDICE!");
            return;
        }
        printf("Indice da matriz de resultado => %d\n", listaMatrizes->ultimoIndice - 1);
        quebraLinha();
    }
}

/* Executa a operacao de subtracao entre matrizes */
void subtracaoMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao){
    NoLista *noMatriz1;
    NoLista *noMatriz2;
    unsigned int idMatriz1;
    unsigned int idMatriz2;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Formato da operação */
    quebraLinha();
    printf("Formato -- M <- M1 - M2\n");
    quebraLinha();

    /* Recebe o indice da matriz 1 */
    quebraLinha();
    printf("Insira o indice de M1 => ");
    scanf("%u", &idMatriz1);

    /* Busca pelo id informado */
    noMatriz1 = buscaNoLista(listaMatrizes, (int)idMatriz1);

    /* Checa se a matriz foi encontrada */
    if(noMatriz1 == NULL){
        printError("MATRIZ NAO ENCONTRADA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Recebe o indice da matriz 2 */
    printf("Insira o indice de M2 => ");
    scanf("%u", &idMatriz2);
    quebraLinha();

    /* Busca pelo id informado */
    noMatriz2 = buscaNoLista(listaMatrizes, (int)idMatriz2);

    /* Checa se a matriz foi encontrada */
    if(noMatriz2 == NULL){
        printError("MATRIZ NAO ENCONTRADA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Exibe a matriz 1 */
    imprimeMatriz(noMatriz1->conteudo);
    quebraLinha();

    /* Simbolo da operação */
    printf("-\n");
    quebraLinha();

    /* Exibe a matriz 2 */
    imprimeMatriz(noMatriz2->conteudo);
    quebraLinha();

    /* Simbolo de resultado operação */
    printf("=\n");
    quebraLinha();

    /* Realiza a operação */
    Matriz *matrizResultado = subtracaoMatriz(noMatriz1->conteudo, noMatriz2->conteudo);

    /* Checa se não houve erros ao executar a operação */
    if(matrizResultado == NULL){
        printError("ERRO AO ALOCAR MATRIZ DE RESULTADO DA OPERACAO!");
        return;
    }

    /* Exibe o resultado */
    imprimeMatriz(matrizResultado);
    quebraLinha();

    /* Verifica aonde o resultado deve ser salvo */
    if(salvaResultadoOperacao == SALVAR_NA_MATRIZ_ENTRADA){
        ptrMatriz *ptrMatriz1 = &noMatriz1->conteudo;
        if(!deleteMatriz(ptrMatriz1)){
            printError("ERRO AO DELETAR MATRIZ DE RESULTADO!");
            return;
        }

        /* Salva o ponteiro do resultado para a matriz de conteudo do nó */
        noMatriz1->conteudo = matrizResultado;
    } else {
        /* Salvar a matriz como uma nova matriz da lista de matrizes */
        if(!adicionaNoLista(listaMatrizes, INDICE_ALEATORIO, matrizResultado, false)){
            printError("NAO FOI POSSIVEL SALVAR O RESULTADO DA MATRIZ EM UM NOVO INDICE!");
            return;
        }
        printf("Indice da matriz de resultado => %d\n", listaMatrizes->ultimoIndice - 1);
        quebraLinha();
    }
}

/* Executa a operação de produto entre matrizes */
void produtoMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao){
    NoLista *noMatriz1;
    NoLista *noMatriz2;
    unsigned int idMatriz1;
    unsigned int idMatriz2;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Formato da operação */
    quebraLinha();
    printf("Formato -- M <- M1 . M2\n");
    quebraLinha();

    /* Recebe o indice da matriz 1 */
    quebraLinha();
    printf("Insira o indice de M1 => ");
    scanf("%u", &idMatriz1);

    /* Busca pelo id informado */
    noMatriz1 = buscaNoLista(listaMatrizes, (int)idMatriz1);

    /* Checa se a matriz foi encontrada */
    if(noMatriz1 == NULL){
        printError("MATRIZ NAO ENCONTRADA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Recebe o indice da matriz 2 */
    printf("Insira o indice de M2 => ");
    scanf("%u", &idMatriz2);
    quebraLinha();

    /* Busca pelo id informado */
    noMatriz2 = buscaNoLista(listaMatrizes, (int)idMatriz2);

    /* Checa se a matriz foi encontrada */
    if(noMatriz2 == NULL){
        printError("MATRIZ NAO ENCONTRADA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Exibe a matriz 1 */
    imprimeMatriz(noMatriz1->conteudo);
    quebraLinha();

    /* Simbolo da operação */
    printf(".\n");
    quebraLinha();

    /* Exibe a matriz 2 */
    imprimeMatriz(noMatriz2->conteudo);
    quebraLinha();

    /* Simbolo de resultado operação */
    printf("=\n");
    quebraLinha();

    /* Realiza a operação */
    Matriz *matrizResultado = produtoMatriz(noMatriz1->conteudo, noMatriz2->conteudo);

    /* Checa se não houve erros ao executar a operação */
    if(matrizResultado == NULL){
        printError("ERRO AO ALOCAR MATRIZ DE RESULTADO DA OPERACAO!");
        return;
    }

    /* Exibe o resultado */
    imprimeMatriz(matrizResultado);
    quebraLinha();

    /* Verifica aonde o resultado deve ser salvo */
    if(salvaResultadoOperacao == SALVAR_NA_MATRIZ_ENTRADA){
        ptrMatriz *ptrMatriz1 = &noMatriz1->conteudo;
        if(!deleteMatriz(ptrMatriz1)){
            printError("ERRO AO DELETAR MATRIZ DE RESULTADO!");
            return;
        }

        /* Salva o ponteiro do resultado para a matriz de conteudo do nó */
        noMatriz1->conteudo = matrizResultado;
    } else {
        /* Salvar a matriz como uma nova matriz da lista de matrizes */
        if(!adicionaNoLista(listaMatrizes, INDICE_ALEATORIO, matrizResultado, false)){
            printError("NAO FOI POSSIVEL SALVAR O RESULTADO DA MATRIZ EM UM NOVO INDICE!");
            return;
        }
        printf("Indice da matriz de resultado => %d\n", listaMatrizes->ultimoIndice - 1);
        quebraLinha();
    }
}

/* Executa a operação de multiplicação de matriz por escalar */
void multiplicacaoEscalarMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao){
    NoLista *noMatriz;
    unsigned int idMatriz;
    double escalar;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Formato da operação */
    quebraLinha();
    printf("Formato -- M <- M1 * E\n");
    quebraLinha();

    /* Recebe o indice da matriz 1 */
    quebraLinha();
    printf("Insira o indice de M1 => ");
    scanf("%u", &idMatriz);

    /* Busca pelo id informado */
    noMatriz = buscaNoLista(listaMatrizes, (int)idMatriz);

    /* Checa se a matriz foi encontrada */
    if(noMatriz == NULL){
        printError("MATRIZ NAO ENCONTRADA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Pega o valor do escalar */
    printf("Insira o valor do escalar => ");
    scanf("%lf", &escalar);
    quebraLinha();

    /* Exibe a matriz 1 */
    imprimeMatriz(noMatriz->conteudo);
    quebraLinha();

    /* Simbolo da operação */
    printf("*\n");
    quebraLinha();

    /* Exibe o valor do escalar */
    printf("%.2lf\n", escalar);
    quebraLinha();

    /* Simbolo de resultado operação */
    printf("=\n");
    quebraLinha();

    /* Realiza a operação */
    Matriz *matrizResultado = multiplicacaoEscalarMatriz(noMatriz->conteudo, escalar);

    /* Checa se não houve erros ao executar a operação */
    if(matrizResultado == NULL){
        printError("ERRO AO ALOCAR MATRIZ DE RESULTADO DA OPERACAO!");
        return;
    }

    /* Exibe o resultado */
    imprimeMatriz(matrizResultado);
    quebraLinha();

    /* Verifica aonde o resultado deve ser salvo */
    if(salvaResultadoOperacao == SALVAR_NA_MATRIZ_ENTRADA){
        ptrMatriz *ptrMatriz1 = &noMatriz->conteudo;
        if(!deleteMatriz(ptrMatriz1)){
            printError("ERRO AO DELETAR MATRIZ DE RESULTADO!");
            return;
        }

        /* Salva o ponteiro do resultado para a matriz de conteudo do nó */
        noMatriz->conteudo = matrizResultado;
    } else {
        /* Salvar a matriz como uma nova matriz da lista de matrizes */
        if(!adicionaNoLista(listaMatrizes, INDICE_ALEATORIO, matrizResultado, false)){
            printError("NAO FOI POSSIVEL SALVAR O RESULTADO DA MATRIZ EM UM NOVO INDICE!");
            return;
        }
        printf("Indice da matriz de resultado => %d\n", listaMatrizes->ultimoIndice - 1);
        quebraLinha();
    }
}

/* Executa operação para encontrar a transposta de uma matriz */
void transpostaMatrizOperacao(Lista *listaMatrizes, unsigned int salvaResultadoOperacao){
    NoLista *noMatriz;
    unsigned int idMatriz;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Formato da operação */
    quebraLinha();
    printf("Formato -- M <- M1^t\n");
    quebraLinha();

    /* Recebe o indice da matriz 1 */
    quebraLinha();
    printf("Insira o indice de M1 => ");
    scanf("%u", &idMatriz);
    quebraLinha();

    /* Busca pelo id informado */
    noMatriz = buscaNoLista(listaMatrizes, (int)idMatriz);

    /* Checa se a matriz foi encontrada */
    if(noMatriz == NULL){
        printError("MATRIZ NAO ENCONTRADA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Exibe a matriz 1 */
    imprimeMatriz(noMatriz->conteudo);
    quebraLinha();

    /* Simbolo de resultado operação */
    printf("=\n");
    quebraLinha();

    /* Realiza a operação */
    Matriz *matrizResultado = transpostaMatriz(noMatriz->conteudo);

    /* Checa se não houve erros ao executar a operação */
    if(matrizResultado == NULL){
        printError("ERRO AO ALOCAR MATRIZ DE RESULTADO DA OPERACAO!");
        return;
    }

    /* Exibe o resultado */
    imprimeMatriz(matrizResultado);
    quebraLinha();

    /* Verifica aonde o resultado deve ser salvo */
    if(salvaResultadoOperacao == SALVAR_NA_MATRIZ_ENTRADA){
        ptrMatriz *ptrMatriz1 = &noMatriz->conteudo;
        if(!deleteMatriz(ptrMatriz1)){
            printError("ERRO AO DELETAR MATRIZ DE RESULTADO!");
            return;
        }

        /* Salva o ponteiro do resultado para a matriz de conteudo do nó */
        noMatriz->conteudo = matrizResultado;
    } else {
        /* Salvar a matriz como uma nova matriz da lista de matrizes */
        if(!adicionaNoLista(listaMatrizes, INDICE_ALEATORIO, matrizResultado, false)){
            printError("NAO FOI POSSIVEL SALVAR O RESULTADO DA MATRIZ EM UM NOVO INDICE!");
            return;
        }
        printf("Indice da matriz de resultado => %d\n", listaMatrizes->ultimoIndice - 1);
        quebraLinha();
    }
}

/**
 *
 * Realiza operações aritméticas entre matrizes. As operações permitidas
 * são:
 * - Soma
 * - Subtração
 * - Produto
 * - Multiplicação por escalar
 * - Transposta
 * - Inversa -- TODO
 * - Divisão -- TODO
 *
 * @brief operacoesEntreMatrizes Executa operações (soma, multiplicação, ...) entre matrizes
 * @param listaMatrizes Lista de matrizes
 */
void operacoesEntreMatrizes(Lista *listaMatrizes){
    unsigned int operacao;
    unsigned int salvaResultadoOperacao;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL INSERIR!");
        return;
    }

    /* Define aonde salvar o resultado das operações */
    do {
        printf("Aonde deseja salvar os resultados?\n"
               "1 > Salvar na matriz de entrada\n"
               "2 > Salvar em uma nova matriz\n");
        quebraLinha();
        printf("> ");
        scanf("%u", &salvaResultadoOperacao);

        if(salvaResultadoOperacao != SALVAR_NOVA_MATRIZ &&
           salvaResultadoOperacao != SALVAR_NA_MATRIZ_ENTRADA){
            printError("OPCAO INVALIDA DE SALVAMENTO!");
        }
    } while(salvaResultadoOperacao != SALVAR_NOVA_MATRIZ &&
            salvaResultadoOperacao != SALVAR_NA_MATRIZ_ENTRADA);
    quebraLinha();

    do{
        /* Mostra menu de opções aritmeticas */
        quebraLinha();
        menuOpcoesAritmeticas();

        /* Entrada de opção */
        quebraLinha();
        printf("> ");
        scanf("%u", &operacao);

        /* Executa a opção escolhida no menu */
        switch(operacao){

        case SOMA_MATRIZ_MENU:
            somaMatrizOperacao(listaMatrizes, salvaResultadoOperacao);
            break;

        case SUBTRACAO_MATRIZ_MENU:
            subtracaoMatrizOperacao(listaMatrizes, salvaResultadoOperacao);
            break;

        case PRODUTO_MATRIZ_MENU:
            produtoMatrizOperacao(listaMatrizes, salvaResultadoOperacao);
            break;

        case MULTIPLICACAO_ESCALAR_MATRIZ_MENU:
            multiplicacaoEscalarMatrizOperacao(listaMatrizes, salvaResultadoOperacao);
            break;

        case TRANSPOSTA_MATRIZ_MENU:
            transpostaMatrizOperacao(listaMatrizes, salvaResultadoOperacao);
            break;

        case METODO_GAUS_MATRIZ_MENU:
            metodoGausJordanMatriz(listaMatrizes);
            break;

        case ENCONTRAR_KERNEL_MATRIZ_MENU:
            encontrarKernelMatriz(listaMatrizes);
            break;

        case ENCONTRAR_BASE_MATRIZ:
            encontrarBaseMatriz(listaMatrizes);
            break;

        case INVERSA_MATRIZ_MENU:
            printInfo("TODO - NAO IMPLEMENTADO AINDA!");
            break;

        case DIVISAO_MATRIZ_MENU:
            printInfo("TODO - NAO IMPLEMENTADO AINDA!");
            break;

        case VOLTAR_MENU:
            break;

        default:
            printError("OPCAO INVALIDA ESCOLHIDA! FAVOR ESCOLHER UMA OPCAO VALIDA!");
        }

    } while(operacao != SAIR_MENU);
    quebraLinha();
}

/* Executa metodo de Gaus Jordan para encontrar as raizes do sistema de equação */
void metodoGausJordanMatriz(Lista *listaMatrizes){
    printInfo("TODO!");
}

/* Encontra o Kernel de uma Matriz */
void encontrarKernelMatriz(Lista *listaMatrizes){
    printInfo("TODO!");
}

/* Encontra uma base para a matriz */
void encontrarBaseMatriz(Lista *listaMatrizes){
    printInfo("TODO!");
}

/**
 *
 * Realiza a operação de troca entre duas linhas, com base na linha informada
 * pelo usuario e duas linhas de uma matriz já cadastrada. No caso da falta da
 * matriz ou das linhas informadas a aplicação volta ao menu anterior.
 *
 * @brief operacaoMatrizTrocaLinha Realiza a operação elementar de troca entre linhas
 * @param listaMatrizes Lista com todas as matrizes do sistema
 */
void operacaoMatrizTrocaLinha(NoLista *noMatriz){
    unsigned int l1, l2;

    /* Checa se o no da matriz é válido */
    if(noMatriz == NULL){
        printError("NO DA MATRIZ INVALIDO! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Formato da operação */
    quebraLinha();
    printf("Formato -- L1 <-> L2\n");
    quebraLinha();

    /* Exibe a matriz */
    imprimeMatriz(noMatriz->conteudo);
    quebraLinha();

    /* Pega a primeira linha da tabela */
    do {
        printf("Indice L1 => ");
        scanf("%u", &l1);

        if(l1 == 0){
            printError("AS MATRIZES SAO INDEXADAS DE 1 A N!");
        } else if ((int)l1 > noMatriz->conteudo->nLinhas){
            printError("LINHA NAO PRESENTE NA MATRIZ!");
        }
    } while(l1 == 0 || (int)l1 > noMatriz->conteudo->nLinhas);

    /* Pega a segunda linha da tabela */
    do {
        printf("Indice L2 => ");
        scanf("%u", &l2);

        if(l2 == 0){
            printError("AS MATRIZES SAO INDEXADAS DE 1 A N!");
        } else if ((int)l2 > noMatriz->conteudo->nLinhas){
            printError("LINHA NAO PRESENTE NA MATRIZ!");
        }
    } while(l2 == 0 || (int)l2 > noMatriz->conteudo->nLinhas);

    /* Imprime matriz entrada */
    quebraLinha();
    imprimeMatriz(noMatriz->conteudo);

    /* Imprime o formato da operação */
    quebraLinha();
    printf("L%u <-> L%u\n", l1, l2);

    /* Executa a operação */
    operacaoTrocaLinha(noMatriz->conteudo, l1, l2);

    /* Imprime a matriz resultante */
    quebraLinha();
    imprimeMatriz(noMatriz->conteudo);
}

/* Executa a operação de multiplicação de linha por escalar */
void operacaoMatrizMultiplicaLinha(NoLista *noMatriz){
    unsigned int l1;
    double escalar;

    /* Checa se o no da matriz é válido */
    if(noMatriz == NULL){
        printError("NO DA MATRIZ INVALIDO! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Formato da operação */
    quebraLinha();
    printf("Formato -- L1 <- E * L1\n");
    quebraLinha();

    /* Exibe a matriz */
    imprimeMatriz(noMatriz->conteudo);
    quebraLinha();

    /* Pega a primeira linha da tabela */
    do {
        printf("Indice L1 => ");
        scanf("%u", &l1);

        if(l1 == 0){
            printError("AS MATRIZES SAO INDEXADAS DE 1 A N!");
        } else if ((int)l1 > noMatriz->conteudo->nLinhas){
            printError("LINHA NAO PRESENTE NA MATRIZ!");
        }
    } while(l1 == 0 || (int)l1 > noMatriz->conteudo->nLinhas);

    /* Pega o valor do escalar */
    do {
        printf("Escalar => ");
        scanf("%lf", &escalar);

        if(fabs(escalar) <= 10e-7){
            printError("ESCALAR NAO PODE SER ZERO!");
        }
    } while(fabs(escalar) <= 10e-7);

    /* Imprime matriz entrada */
    quebraLinha();
    imprimeMatriz(noMatriz->conteudo);

    /* Imprime o formato da operação */
    quebraLinha();
    printf("L%u <- (L%u * %.2f)\n", l1, l1, escalar);

    /* Executa a operação */
    operacaoMultiplicaPorEscalar(noMatriz->conteudo, l1, escalar);

    /* Imprime a matriz resultante */
    quebraLinha();
    imprimeMatriz(noMatriz->conteudo);
}

/* Executa a operação de soma entre linhas */
void operacaoMatrizSomaLinha(NoLista *noMatriz){
    unsigned int l1, l2;
    double escalar;

    /* Checa se o no da matriz é válido */
    if(noMatriz == NULL){
        printError("NO DA MATRIZ INVALIDO! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Formato da operação */
    quebraLinha();
    printf("Formato -- L1 <- L1 + L2 * E\n");

    /* Exibe a matriz */
    quebraLinha();
    imprimeMatriz(noMatriz->conteudo);
    quebraLinha();

    /* Pega a primeira linha da tabela */
    do {
        printf("Indice L1 => ");
        scanf("%u", &l1);

        if(l1 == 0){
            printError("AS MATRIZES SAO INDEXADAS DE 1 A N!");
        } else if ((int)l1 > noMatriz->conteudo->nLinhas){
            printError("LINHA NAO PRESENTE NA MATRIZ!");
        }
    } while(l1 == 0 || (int)l1 > noMatriz->conteudo->nLinhas);

    /* Pega a segunda linha da tabela */
    do {
        printf("Indice L2 => ");
        scanf("%u", &l2);

        if(l2 == 0){
            printError("AS MATRIZES SAO INDEXADAS DE 1 A N!");
        } else if ((int)l2 > noMatriz->conteudo->nLinhas){
            printError("LINHA NAO PRESENTE NA MATRIZ!");
        }
    } while(l2 == 0 || (int)l2 > noMatriz->conteudo->nLinhas);

    /* Pega o valor do escalar */
    do {
        printf("Escalar => ");
        scanf("%lf", &escalar);

        if(fabs(escalar) <= 10e-7){
            printError("ESCALAR NAO PODE SER ZERO!");
        }
    } while(fabs(escalar) <= 10e-7);


    /* Imprime matriz entrada */
    quebraLinha();
    imprimeMatriz(noMatriz->conteudo);

    /* Imprime o formato da operação */
    quebraLinha();
    printf("L%u <- L%u + (L%u * %.2f)\n", l1, l1, l2, escalar);

    /* Executa a operação */
    operacaoSomaEntreLinhas(noMatriz->conteudo, l1, l2, escalar);

    /* Imprime a matriz resultante */
    quebraLinha();
    imprimeMatriz(noMatriz->conteudo);
}

/* Executar operações elementares sobre a matriz */
void operacoesMatriz(Lista *listaMatrizes){
    NoLista *noMatriz;
    unsigned int operacao;
    unsigned int idMatriz;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL INSERIR!");
        return;
    }

    /* Recebe o indice da matriz */
    quebraLinha();
    printf("Insira o indice da matriz => ");
    scanf("%u", &idMatriz);
    quebraLinha();

    /* Busca pelo id informado */
    noMatriz = buscaNoLista(listaMatrizes, (int)idMatriz);

    /* Checa se a matriz foi encontrada */
    if(noMatriz == NULL){
        printError("MATRIZ NAO ENCONTRADA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    do{
        /* Mostra menu de opções elementares */
        quebraLinha();
        menuOpcoesElementares();

        /* Entrada de opção */
        quebraLinha();
        printf("> ");
        scanf("%u", &operacao);

        /* Executa a opção escolhida no menu */
        switch(operacao){

        case TROCA_LINHA_MENU:
            operacaoMatrizTrocaLinha(noMatriz);
            break;

        case MULTIPLICA_LINHA_MENU:
            operacaoMatrizMultiplicaLinha(noMatriz);
            break;

        case SOMA_LINHA_MENU:
            operacaoMatrizSomaLinha(noMatriz);
            break;

        case VOLTAR_MENU:
            break;

        default:
            printError("OPCAO INVALIDA ESCOLHIDA! FAVOR ESCOLHER UMA OPCAO VALIDA!");
        }

    } while(operacao != SAIR_MENU);
    quebraLinha();
}

/**
 *
 * Modo de entrada interativa, neste modo o usuario tem um menu e pode realizar
 * diversas operações sobre as matrizes armazenadas nesse sistema
 * 
 * @brief Ativa o modo de entrada de usuario
 */
void loopModoCLI(void){
    printf("::: Modo de entrada de usuario :::\n\n");

    /* Cria uma lista de matrizes */
    Lista *listaMatrizes = newLista();

    /* Checa se não houve erros ao criar a lista de matrizes */
    if(listaMatrizes == NULL){
        printError("ERRO AO CRIAR LISTA DE MATRIZES!");
        return;
    }

    /* Mantém o loop enquanto a opção escolhida não for a de sair */
    unsigned int opcao;
    do{
        /* Mostra o MENU */
        mostraMenu();

        /* Entrada de opção */
        printf("\n> ");
        scanf("%u", &opcao);

        /* Executa a opção escolhida no menu */
        switch(opcao){
        case INSERIR_MATRIZ_MENU:
            inserirMatriz(listaMatrizes);
            break;

        case LISTAR_MATRIZ_MENU:
            listarMatrizes(listaMatrizes);
            break;

        case DELETAR_MATRIZ_MENU:
            deletarMatriz(listaMatrizes);
            break;

        case CLONAR_MATRIZ_MENU:
            clonarMatriz(listaMatrizes);
            break;

        case OPERACOES_MATRIZ_MENU:
            operacoesMatriz(listaMatrizes);
            break;

        case OPERACOES_ENTRE_MATRIZES_MENU:
            operacoesEntreMatrizes(listaMatrizes);
            break;

        case OPERACOES_COMPLEXAS_MENU:
            printInfo("TODO - NAO IMPLEMENTADO AINDA!");
            break;

        case SALVAR_RESULTADOS_MENU:
            printInfo("TODO - NAO IMPLEMENTADO AINDA!");
            break;

        case SAIR_MENU:
            break;

        default:
            printError("OPCAO INVALIDA ESCOLHIDA! FAVOR ESCOLHER UMA OPCAO VALIDA!");
        }

    } while(opcao != SAIR_MENU);

    /* Desaloca a lista de matrizes */
    deleteLista(&listaMatrizes);

    printf("::: Obrigado por utilizar a aplicação :::\n"
           "Desenvolvido por Alana Bispo e Jeferson Lima\n");
}
