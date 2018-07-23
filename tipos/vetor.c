#include "./vetor.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
Vetor* newVetor(int dimensao, double valores[]){
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

    /* Copia os valores */
    memcpy(_new_coordenadas, valores, (size_t)dimensao);

    /* Inicializa o vetor */
    _new_vetor->dimensao = dimensao;
    _new_vetor->coordenadas = _new_coordenadas;

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
    Vetor *_clone_vetor = newVetor(vetor->dimensao, vetor->coordenadas);

    /* Verifica se foi possível clonar */
    if(_clone_vetor == NULL){
        printError("ERRO AO CRIAR CLONE!");
        return NULL;
    }

    return _clone_vetor;
}
