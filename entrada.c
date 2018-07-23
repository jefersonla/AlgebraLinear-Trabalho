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
 * Menu de opções elementares, sobre as linhas de uma matriz.
 * Essas opções são executadas conforme entrada do usuario.
 *
 * @brief menuOpcoesElementares Menu opções elementares
 */
void menuOpcoesElementares(void){
    printf("::: Opções Elementares :::\n\n"
           "1 > Troca entre linhas (L1 <-> L2)\n"
           "2 > Multiplicar linha por escalar (L1 <- E * L1)\n"
           "3 > Soma entre uma linha, com outra multiplicada por escalar (L1 <- L1 + E * L2)\n"
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
 * Realiza a operação de troca entre duas linhas, com base na linha informada
 * pelo usuario e duas linhas de uma matriz já cadastrada. No caso da falta da
 * matriz ou das linhas informadas a aplicação volta ao menu anterior.
 *
 * @brief operacaoMatrizTrocaLinha Realiza a operação elementar de troca entre linhas
 * @param listaMatrizes Lista com todas as matrizes do sistema
 */
void operacaoMatrizTrocaLinha(Lista *listaMatrizes){
    NoLista *noMatriz;
    unsigned int idMatriz;
    unsigned int l1, l2;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL INSERIR!");
        return;
    }

    /* Formato da operação */
    printf("L1 <-> L2\n");

    /* Recebe o numero de linhas */
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
    } while(l1 == 0 || (int)l2 > noMatriz->conteudo->nLinhas);

    /* Executa a operação */
    operacaoTrocaLinha(noMatriz->conteudo, l1, l2);

    /* Imprime a matriz resultante */
    quebraLinha();
    imprimeMatriz(noMatriz->conteudo);
}

/* Executa a operação de multiplicação de linha por escalar */
void operacaoMatrizMultiplicaLinha(Lista *listaMatrizes){

}

/* Executa a operação de soma entre linhas */
void operacaoMatrizSomaLinha(Lista *listaMatrizes){

}

/* Executar operações elementares sobre a matriz */
void operacoesMatriz(Lista *listaMatrizes){
    unsigned int operacao;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL INSERIR!");
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
            operacaoMatrizTrocaLinha(listaMatrizes);
            break;

        case MULTIPLICA_LINHA_MENU:
            operacaoMatrizMultiplicaLinha(listaMatrizes);
            break;

        case SOMA_LINHA_MENU:
            operacaoMatrizSomaLinha(listaMatrizes);
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

        case OPERACOES_MATRIZ_MENU:
            operacoesMatriz(listaMatrizes);
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
