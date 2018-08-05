/* Inclui biblioteca */
#include "ajuda.h"

#include <stdio.h>

/* Mostra a ajuda do sistema */
void mostrarAjuda(void){
    printf( "Como usar!\n"                                      \
            "\n"                                                \
            "usar:\tmatriz <parametros>\n"                                   \
                       "\n\t--cli\t\t\t\tAtiva o modo interativo\n"                \
          "\n\t--matriz L C Aij ... ain\tRecebe uma matriz de tamanho LxC\n" \
                              "\t\t\t\t\tas celulas desta matriz devem ser informadas sequencialmente\n" \
                              "\t\t\t\t\tapos informados o número de linhas L e o número de colunas C\n" \
                              "\t\t\t\t\trespectivamente, com essas informacoes basta informar cada\n" \
                              "\t\t\t\t\tcelula de cada linha comecando da primeira\n"\
                      "\n\t--kernel\t\t\tEncontrar o Kernel da matriz informada anteriormente.\n" \
                              "\t\t\t\t\tLanca erro se nao houver matrix informada previamente\n" \
            "\nAté o momento sem maiores opções de execução.\n"   \
            "\n"                                                \
    );
}

/* Mensagem de copyright */
void mostrarCopyright(void){
    printf("::: Obrigado por utilizar a aplicação :::\n"
           "Desenvolvido por Alana Bispo e Jeferson Lima\n");
}
