#include "./vetor.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*------------ Vetor Structure Methods ------------ */

/**
 *
 * Cria um novo vetor. Não confundir com arrays ou vectors de outras linguagens
 * os vetores aqui indicados são os vetores utilizados na fisica, matemática,
 * algébra e afins, ele consiste de uma sequência de valores ou coordenadas,
 * para este programa os valores de um vetor são chamados de coordenadas.
 *
 * @brief newVetor Cria um novo vetor
 * @param dimensao Dimensao do vetor
 * @param valores Valores do vetor
 * @return Ponteiro para o novo vetor
 */
Vetor* newVetor(char *idVetor, unsigned int dimensao, double valores[]){
    /* A dimensao de um vetor precisa ser maior que 1 */
    if(dimensao <= 0){
        printError("A DIMENSAO DE UM VETOR PRECISA SER MAIOR QUE ZERO!");
        return NULL;
    }

    Vetor *_new_vetor;

    /* Tenta alocar um novo vetor */
    _new_vetor = malloc(sizeof(Vetor));

    /* Verifica se o vetor foi alocado */
    if(_new_vetor == NULL){
        printFatalError("NAO FOI POSSIVEL ALOCAR O VETOR!");
        exit(EXIT_FAILURE);
    }

    /* Tenta alocar o vetor de valores */
    double *_new_coordenadas = malloc(sizeof(double) * (size_t)dimensao);

    /* Verifica se o vetor de coordenadas foi bem alocado */
    if(_new_coordenadas == NULL){
        printFatalError("NAO FOI POSSIVEL ALOCAR AS COORDENADAS DO VETOR!");
        exit(EXIT_FAILURE);
    }

    /* Tenta alocar o espaço para o id */
    char *_new_id_vetor = malloc(sizeof (char) * (strlen(idVetor) + 1));

    /* Verifica se não houve erros ao alocar o ID do vetor */
    if(_new_id_vetor == NULL){
        printFatalError("NAO FOI POSSIVEL ALOCAR O ID DO VETOR!");
        exit(EXIT_FAILURE);
    }

    /* Copia os valores */
    if(valores != NULL)
        memcpy(_new_coordenadas, valores, (size_t)dimensao);
    else
        memset(_new_coordenadas, 0, (size_t)dimensao);
    strncpy(_new_id_vetor, idVetor, (strlen(idVetor) + 1));

    /* Inicializa o vetor */
    _new_vetor->dimensao = dimensao;
    _new_vetor->coordenadas = _new_coordenadas;
    _new_vetor->idVetor = _new_id_vetor;

    return _new_vetor;
}

/**
 *
 * Deleta um vetor qualquer.
 *
 * @brief deleteVetor Deleta um vetor
 * @param vetor Ponteiro do vetor a ser removido
 * @return true se foi possível deletar o vetor, e falso caso contrário
 */
bool deleteVetor(ptrVetor *vetor){
    /* Verifica se o ponteiro do vetor é válido */
    if(vetor == NULL){
        printError("PONTEIRO DO VETOR INVALIDO!");
        return false;
    }

    /* Verifica se o vetor é válido */
    if((*vetor) == NULL){
        printError("VETOR INVALIDO! NAO E POSSIVEL DELETAR!");
        return false;
    }

    /* Desaloca as coordenadas */
    free((*vetor)->coordenadas);

    /* Desaloca o ID */
    free((*vetor)->idVetor);

    /* Desaloca a estrutura */
    secureFree((*vetor));

    return true;
}

/* Clona um vetor */
Vetor* cloneVetor(Vetor *vetor){
    /* Verifica se o vetor é válido */
    if(vetor == NULL){
        printError("VETOR INVALIDO, NAO E POSSIVEL CLONAR!");
        return NULL;
    }

    /* Cria um novo vetor com cópia dos valores */
    Vetor *_clone_vetor = newVetor("R", vetor->dimensao, vetor->coordenadas);

    /* Verifica se foi possível clonar */
    if(_clone_vetor == NULL){
        printError("ERRO AO CRIAR CLONE!");
        return NULL;
    }

    return _clone_vetor;
}

/* Soma dois vetores */
Vetor* somaVetor(Vetor *vetor1, Vetor *vetor2){
    /* Checa a consistência dos vetoers */
    if(vetor1 == NULL || vetor2 == NULL){
        printError("VETORES INCONSISTENTES! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return NULL;
    }

    /* Verifica se os vetores tem o mesmo tamanho */
    if(vetor1->dimensao != vetor2->dimensao){
        printError("VETORES COM TAMANHOS DISTINTOS! NAO E POSSIVEL REALIZAR A OPERACAO!");
    }

    /* Cria um novo vetor que irá abrigar a soma desses vetores */
    Vetor *vetor_resultado = newVetor("R", vetor1->dimensao, vetor1->coordenadas);

    /* Checa se não houve problemas ao alocar esse vetor */
    if(vetor_resultado == NULL){
        printError("NAO FOI POSSIVEL ALOCAR O VETOR RESULTADO! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return NULL;
    }

    /* Realiza a soma entre os dois vetores */
    int i;
    for(i = 0; i < (int)vetor1->dimensao; i++){
        vetor_resultado->coordenadas[i] += vetor2->coordenadas[i];
    }

    return vetor_resultado;
}

/* Subtrais dois vetores */
Vetor* subtraiVetor(Vetor *vetor1, Vetor *vetor2){
    /* Checa a consistência dos vetoers */
    if(vetor1 == NULL || vetor2 == NULL){
        printError("VETORES INCONSISTENTES! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return NULL;
    }

    /* Verifica se os vetores tem o mesmo tamanho */
    if(vetor1->dimensao != vetor2->dimensao){
        printError("VETORES COM TAMANHOS DISTINTOS! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return NULL;
    }

    /* Cria um novo vetor que irá abrigar a soma desses vetores */
    Vetor *vetor_resultado = newVetor("R", vetor1->dimensao, vetor1->coordenadas);

    /* Checa se não houve problemas ao alocar esse vetor */
    if(vetor_resultado == NULL){
        printError("NAO FOI POSSIVEL ALOCAR O VETOR RESULTADO! NAO E POSSIVEL REALIZAR A OPERACAO!");
        return NULL;
    }

    /* Realiza a subtração entre os dois vetores */
    int i;
    for(i = 0; i < (int)vetor1->dimensao; i++){
        vetor_resultado->coordenadas[i] -= vetor2->coordenadas[i];
    }

    return vetor_resultado;
}

/* Produto interno entre dois vetores */
double produtoInterno(Vetor *vetor1, Vetor *vetor2, bool *erro){
    /* Checa a consistência dos vetoers */
    if(vetor1 == NULL || vetor2 == NULL){
        printError("VETORES INCONSISTENTES! NAO E POSSIVEL REALIZAR A OPERACAO!");
        (*erro) = true;
        return 0;
    }

    /* Verifica se os vetores tem o mesmo tamanho */
    if(vetor1->dimensao != vetor2->dimensao){
        printError("VETORES COM TAMANHOS DISTINTOS! NAO E POSSIVEL REALIZAR A OPERACAO!");
        (*erro) = true;
        return 0;
    }

    /* Resultado do produto interno */
    int i;
    double produto_interno = 0;
    for(i = 0; i < (int)vetor1->dimensao; i++){
        produto_interno += vetor1->coordenadas[i] * vetor2->coordenadas[i];
    }

    (*erro) = false;
    return produto_interno;
}

/* Norma do vetor */
double normaVetor(Vetor *vetor, bool *erro){
    /* Checa a consistência dos vetoers */
    if(vetor == NULL){
        printError("VETOR INCONSISTENTE! NAO E POSSIVEL REALIZAR A OPERACAO!");
        (*erro) = true;
        return 0;
    }

    /* Resultado da norma do vetor */
    int i;
    double somatorio_coordenadas = 0;
    for(i = 0; i < (int)vetor->dimensao; i++){
        somatorio_coordenadas += pow(vetor->coordenadas[i], 2);
    }
    double norma_vetor = sqrt(somatorio_coordenadas);

    (*erro) = false;
    return norma_vetor;
}

/* Imprime vetor */
void imprimeVetor(Vetor *vetor){
    if(vetor == NULL){
        printError("VETOR NAO EXISTE! NAO E POSSIVEL EXIBIR!");
        return;
    }

    /* Imprime o vetor */
    int i;
    printf("%s = (", vetor->idVetor);
    for(i = 0; i < (int)(vetor->dimensao - 1); i++){
        printf("%.2lf, ", vetor->coordenadas[i]);
    }
    printf("%.2lf)", vetor->coordenadas[vetor->dimensao - 1]);
}
