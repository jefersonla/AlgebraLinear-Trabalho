/**           ******* Algebra Linear  *******            **/

/** Desenvolvido por Alana Bispo                         **/
/**              e   Jeferson Lima                       **/
/** Versão      0.7                                      **/
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
#include "utils/ajuda.h"
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

   

    /* Verifica os parametros */
    switch(argc){
        case 1:
            loopModoCLI();
        break;
    
        default:
            printf( "Número incorreto de parametros!\n"   \
                    "\n"                                  \
            );
            mostrarAjuda();

            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
