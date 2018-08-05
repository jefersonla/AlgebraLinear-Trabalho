/**           ******* Algebra Linear  *******            **/

/** Desenvolvido por Alana Bispo                         **/
/**              e   Jeferson Lima                       **/
/** Versão      1.0                                      **/
/** Linguagem   C                                        **/
/** Licença     MIT                                      **/
/** Descrição:  Aplicação para demonstrar o conceito de  **/
/**             Kernel de uma matriz. A aplicação também **/
/**             possui outros utilitários que podem      **/
/**             servir para visualizar e demonstrar      **/
/**             outros conceitos associados a disciplina **/
/**                                                      **/
/**            1º  TRABALHO DE ALGEBRA LINEAR            **/
/** **************************************************** **/

/** **************************************************** **/
/**          Compilar este  projeto usando make          **/
/** **************************************************** **/

/** **************************************************** **/
/**         LEIA O README PARA MAIS INFORMAÇÔES          **/
/** **************************************************** **/
#include "operacoes_complexas.h"
#include "utils/ajuda.h"
#include "utils/utils.h"
#include "entrada.h"

#include <stdio.h>
#include <stdlib.h>

/* Código principal */
int main(int argc, char *argv[]){
    
    /* Remove o nome do programa */
    ++argv; --argc;

    /* Mensagem de boas vindas  */
    printf( " ::: Algebra Linear - Calculadora de Matrizes ::: \n"  \
            "Version 0.1 - Pre Alpha\n"                             \
            "Developed by Alana Bispo e Jeferson Lima\n"       \
            "\n");

    /* Variaveis temporarias */
    Matriz *matriz_tmp = NULL;
    Vetor *vetor_tmp = NULL;
    Vetor** vetores_tmp = NULL;
    unsigned int tamanho_vetores_tmp;

    /* Percorre a lista de parametros */
    int i, j;
    for(i = 0; i < argc; i++){
        /* Pega o parametro corrente */
        unsigned long long parametro = hashDjb2(argv[i]);

        /* Verifica os parametros */
        switch(parametro){

        case PARAMETRO_CLI:
            loopModoCLI();
            break;

        case PARAMETRO_AJUDA:
        case PARAMETRO_HELP:
            mostrarAjuda();
            mostrarCopyright();
            break;

        case PARAMETRO_MATRIZ:
            matriz_tmp = parametroMatriz(&i, argc, argv);
            imprimeMatriz(matriz_tmp);
            break;

        case PARAMETRO_KERNEL:
            vetores_tmp = operacaoKernelMatriz(matriz_tmp, &tamanho_vetores_tmp);
            for(j = 0; j < (int)tamanho_vetores_tmp; j++){
                imprimeVetor(vetores_tmp[j]);
                printf("\n");
            }
            break;

        default:
            printf( "Parâmetro inválido!\n"   \
                    "\n"                      \
            );
            mostrarAjuda();
            mostrarCopyright();

            return EXIT_FAILURE;
        }

    }

    /* Execução sem parametros não é válida */
    if(argc == 0){
        mostrarAjuda();
        mostrarCopyright();
        return EXIT_FAILURE;
    }

    /* Finaliza a aplicação com sucesso */
    return EXIT_SUCCESS;
}
