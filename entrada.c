#include "entrada.h"
#include "tipos/lista.h"
#include "tipos/vetor.h"
#include "tipos/matriz.h"
#include "utils/utils.h"
#include "operacoes_matriz.h"
#include "operacoes_complexas.h"
#include "utils/ajuda.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Mostra o menu de opções */
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

/* Menu opções elementares */
void menuOpcoesElementares(void){
    printf("::: Operacoes Elementares :::\n\n"
           "1 > Troca entre linhas (L1 <-> L2)\n"
           "2 > Multiplicar linha por escalar (L1 <- E * L1)\n"
           "3 > Soma entre uma linha, com outra multiplicada por escalar (L1 <- L1 + E * L2)\n"
           "0 > Voltar\n");
}

/* Menu de operações, aritmeticas entre matrizes. */
void menuOpcoesAritmeticas(void){
    printf("::: Operacoes Aritmeticas :::\n\n"
           "1 > Soma de matrizes (M <- M1 + M2)\n"
           "2 > Subtracao de matrizes (M <- M1 - M2)\n"
           "3 > Produto de matrizes (M <- M1 * M2)\n"
           "4 > Multiplicação por escalar (M <- M1 * E)\n"
           "5 > Transpota da matriz (M <- M^t)\n"
           "0 > Voltar\n");
}

/* Menu de operações, complexas em algebra que envolvem escalonamento. */
void menuOperacoesComplexas(void){
    printf("::: Operacoes Complexas :::\n\n"
           "1 > Metodo de Gauss\n"
           "2 > Metodo de Gauss-Jordan\n"
           "3 > Determinante Matriz\n"
           "4 > Encontrar Kernel\n"
           "5 > Encontrar Base\n"
           "6 > Inversa Matriz\n"
           "7 > Divisao Matriz\n"
           "0 > Voltar\n");
}

/* Inseri matriz a lista de matrizes */
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

/* Listar matrizes já inseridas */
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

/* Clonar matriz presentes na memória */
void clonarMatriz(Lista *listaMatrizes){
    NoLista *noMatriz;
    unsigned int idMatriz;
    unsigned int nCopias;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL INSERIR!");
        return;
    }

    /* Recebe o indice da matriz */
    quebraLinha();
    printf("Insira o indice da matriz a ser clonada => ");
    scanf("%u", &idMatriz);

    /* Busca pelo id informado */
    noMatriz = buscaNoLista(listaMatrizes, (int)idMatriz);

    /* Checa se a matriz foi encontrada */
    if(noMatriz == NULL){
        printError("MATRIZ NAO ENCONTRADA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Copia a tabela várias vezes */
    printf("Insira o numero de copias => ");
    scanf("%u", &nCopias);
    quebraLinha();

    /* Clona a matriz */
    int i;
    for(i = 0; i < (int)nCopias; i++)
        adicionaNoLista(listaMatrizes, INDICE_ALEATORIO, noMatriz->conteudo, true);
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

/* Executa operações (soma, multiplicação, ...) entre matrizes */
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
        quebraLinha();
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

        case VOLTAR_MENU:
            break;

        default:
            printError("OPCAO INVALIDA ESCOLHIDA! FAVOR ESCOLHER UMA OPCAO VALIDA!");
        }

    } while(operacao != SAIR_MENU);
    quebraLinha();
}

/* Encontra o determinaten de uma dada matriz */
void encontrarDeterminante(Lista *listaMatrizes){
    NoLista *noMatriz;
    unsigned int idMatriz;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Formato da operação */
    quebraLinha();
    printf("Determinante -- det(M)\n");
    quebraLinha();

    /* Recebe o indice da matriz 1 */
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

    /* Realiza a operação */
    bool erro = false;
    double determinante = operacaoDeterminanteMatriz(noMatriz->conteudo, &erro);

    /* verifica se houve erros na execução */
    if(erro){
        printError("ERRO AO ENCONTRAR O DETERMINANTE!");
        return;
    }

    /* Exibe o valor do determinante */
    printf("det(M) => %.2lf\n", determinante);
}

/* Executa metodo de Gauss para encontrar as raizes do sistema de equação */
void metodoGaussMatriz(Lista *listaMatrizes){
    NoLista *noMatriz;
    unsigned int idMatriz;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Formato da operação */
    quebraLinha();
    printf("Metodo de Gauss -- meg(M)\n");
    quebraLinha();

    /* Recebe o indice da matriz 1 */
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

    /* Imprime a matriz antes da operação */
    imprimeMatriz(noMatriz->conteudo);
    quebraLinha();

    /* Realiza a operação */
    Vetor *vetor_resultado = operacaoGaussMatriz(noMatriz->conteudo);

    /* Verifica se houve erros na execução da operação */
    if(vetor_resultado == NULL){
        printError("ERRO AO REALIZAR METODO DE GAUSS!");
        return;
    }

    /* Divisão entre o resultado */
    printf("Matriz na forma de Gauss\n");
    quebraLinha();

    /* Imprime a matriz após as operações*/
    imprimeMatriz(noMatriz->conteudo);
    quebraLinha();

    /* Imprime o resultado do vetor */
    printf("Vetor Resultante\n");
    imprimeVetor(vetor_resultado);
    quebraLinha();

    /* Remove vetor */
    ptrVetor *ptrVetor = &vetor_resultado;
    deleteVetor(ptrVetor);
}

/* Executa metodo de Gauss-Jordan para encontrar as raizes do sistema de equação */
void metodoGaussJordanMatriz(Lista *listaMatrizes){
    NoLista *noMatriz;
    unsigned int idMatriz;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Formato da operação */
    quebraLinha();
    printf("Metodo de Gauss-Jordan -- megj(M)\n");
    quebraLinha();

    /* Recebe o indice da matriz 1 */
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

    /* Imprime a matriz antes da operação */
    imprimeMatriz(noMatriz->conteudo);
    quebraLinha();

    /* Realiza a operação */
    Vetor *vetor_resultado = operacaoGausJordanMatriz(noMatriz->conteudo);

    /* Verifica se houve erros na execução da operação */
    if(vetor_resultado == NULL){
        printError("ERRO AO REALIZAR METODO DE GAUSS!");
        return;
    }

    /* Divisão entre o resultado */
    printf("Matriz na forma de Gauss Jordan\n");
    quebraLinha();

    /* Imprime a matriz após as operações*/
    imprimeMatriz(noMatriz->conteudo);
    quebraLinha();

    /* Imprime o resultado do vetor */
    printf("Vetor Resultante\n");
    imprimeVetor(vetor_resultado);
    quebraLinha();

    /* Remove vetor */
    ptrVetor *ptrVetor = &vetor_resultado;
    deleteVetor(ptrVetor);
}

/* Encontra o Kernel de uma Matriz */
void encontrarKernelMatriz(Lista *listaMatrizes){
    NoLista *noMatriz;
    unsigned int idMatriz;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return;
    }

    /* Formato da operação */
    quebraLinha();
    printf("Encontrar Kernel -- ker(M)\n");
    quebraLinha();

    /* Recebe o indice da matriz 1 */
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

    /* Imprime a matriz antes da operação */
    imprimeMatriz(noMatriz->conteudo);
    quebraLinha();

    /* Realiza a operação */
    unsigned int numeroVetoresResposta = 0;
    Vetor **vetores_resultado = operacaoKernelMatriz(noMatriz->conteudo, &numeroVetoresResposta);

    /* Verifica se houve erros na execução da operação */
    if(vetores_resultado == NULL){
        printError("ERRO AO ENCONTRAR KERNEL!");
        return;
    }

    /* Mostra o resultado */
    printf("Matriz na forma de Gauss Jordan\n");
    quebraLinha();

    /* Imprime a matriz após as operações*/
    imprimeMatriz(noMatriz->conteudo);
    quebraLinha();

    /* Imprime os vetores resultado do vetor */
    printf("Vetores Resultados\n");
    unsigned int i;
    for(i = 0; i < numeroVetoresResposta; i++){
        imprimeVetor(vetores_resultado[i]);
        quebraLinha();
    }

    /* Remove os vetores */
    ptrVetor *ptrVetor;
    for(i = 0; i < numeroVetoresResposta; i++){
        ptrVetor = &vetores_resultado[i];
        deleteVetor(ptrVetor);
    }
    free(vetores_resultado);
}

/* Encontra uma base para a matriz */
void encontrarBaseMatriz(Lista *listaMatrizes){
    printInfo("TODO!");
}

/* Realiza operações complexas, que envolvem escalonamento */
void operacaoMatrizComplexas(Lista *listaMatrizes){
    unsigned int operacao;

    /* Checa se a lista de matrizes é válida */
    if(listaMatrizes == NULL){
        printError("LISTA DE MATRIZES INVALIDA! NAO E POSSIVEL INSERIR!");
        return;
    }

    do{
        /* Mostra menu de opções elementares */
        quebraLinha();
        menuOperacoesComplexas();

        /* Entrada de opção */
        quebraLinha();
        printf("> ");
        scanf("%u", &operacao);

        /* Executa a opção escolhida no menu */
        switch(operacao){

        case METODO_GAUS_MATRIZ_MENU:
            metodoGaussMatriz(listaMatrizes);
            break;

        case METODO_GAUSS_JORDAN_MATRIZ_MENU:
            metodoGaussJordanMatriz(listaMatrizes);
            break;

        case ENCONTRAR_DETERMINANTE_MATRIZ_MENU:
            encontrarDeterminante(listaMatrizes);
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

/* Executa a operação de troca entre linhas */
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

        if(doubleIgualZero(escalar)){
            printError("ESCALAR NAO PODE SER ZERO!");
        }
    } while(doubleIgualZero(escalar));

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

        if(doubleIgualZero(escalar)){
            printError("ESCALAR NAO PODE SER ZERO!");
        }
    } while(doubleIgualZero(escalar));


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

/* Pega a entrada do usuario */
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
            operacaoMatrizComplexas(listaMatrizes);
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

    mostrarCopyright();
}

/* Le uma matriz passada como parametro pela linha de comando */
Matriz* parametroMatriz(int *narg, int argc, char *argv[]){
    /* Checa se a matriz foi informada corretamente */
    if(((*narg) + 2) >= argc){
        printFatalError("Erro no formato. --matriz n m a11 a12 a13 ... ann");
        exit(EXIT_FAILURE);
    }

    /* Pega as dimensões da matriz */
    int nLinhas = atoi(argv[(*narg) + 1]);
    int nColunas = atoi(argv[(*narg) + 2]);

    /* Cria uma matriz vazia */
    Matriz *nova_matriz = newMatriz(nLinhas, nColunas, MATRIZ_VAZIA, NULL);

    /* Verifica se a matriz alocada é válida */
    if(nova_matriz == NULL){
        printError("ERROS AO ALOCAR A NOVA MATRIZ!");
        return NULL;
    }

    /* Pega os valores restantes na linha de comando */
    int i, j, c;
    for(i = 0, c = (*narg) + 3; i < nLinhas && c < argc; i++)
        for(j = 0; j < nColunas && c < argc; j++, c++)
            nova_matriz->linhas[i][j] = atof(argv[c]);

    /* Atualiza o maior valor */
    atualizaMaiorValorMatriz(nova_matriz);

    /* Atualiza o valor para a posição do parametro após ler tudo */
    (*narg) = c;

    return nova_matriz;
}
