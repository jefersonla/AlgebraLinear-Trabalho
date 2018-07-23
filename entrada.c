#include "tipos/lista.h"
#include "tipos/matriz.h"
#include "tipos/operacoes_matriz.h"
#include "utils/utils.h"
#include "entrada.h"

#include <stdio.h>

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
           "4 > Realizar operacoes numa matriz\n"
           "0 > Sair\n");
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
        printf("\nInsira o número de linhas da matriz => ");
        scanf("%d", &nLinhas);

        if(nLinhas == 0){
            printError("NUMERO DE LINHAS NAO PODE SER ZERO!");
        }
    } while(nLinhas == 0);

    /* Recebe o número de colunas */
    do {
        printf("Insira o número de colunas da matriz => ");
        scanf("%d", &nColunas);

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

    /* Adiciona a matriz construida a lista */
    adicionaNoLista(listaMatrizes, INDICE_ALEATORIO, nova_matriz, false);
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
    printf("TODO!\n");
}

/* Executar operações elementares sobre a matriz */
void operacoesMatriz(Lista *listaMatrizes){
    printf("TODO!\n");
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

        case OPERACOES_MATRIZ_MENU:
            operacoesMatriz(listaMatrizes);
            break;

        case SAIR_MENU:
            break;

        default:
            printError("OPCAO INVALIDA ESCOLHIDA! FAVOR ESCOLHER UMA OPCAO VALIDA!");
        }

    } while(opcao != SAIR_MENU);

    printf("::: Obrigado por utilizar a aplicação :::\n"
           "Desenvolvido por Alana Bispo e Jeferson Lima\n");
}
