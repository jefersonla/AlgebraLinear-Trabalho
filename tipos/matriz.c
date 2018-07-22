#include "./matriz.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*------------ Matriz Structure Methods ------------ */

/**
 *
 * Cria uma nova matriz A(n x m) (n - linhas por m - colunas)
 *
 * @param linhas Número de linhas
 * @param colunas Número de colunas
 * @return Retorna uma nova matriz alocada
 */
Matriz* newMatriz(int linhas, int colunas){
	Matriz *_new_matriz;

	/* Tenta alocar a estrutura da nova matriz */
	_new_matriz = mallocIt(_new_token_node);

	/* Imprime um erro caso não seja possível alocar */
	if(_new_matriz == NULL){
		print("ERRO FATAL NAO FOI POSSIVEL ALOCAR A ESTRUTURA!");
		exit(EXIT_FAILURE);
	}

	/* Numero de linhas ou colunas não pode ser negativo */
	if(linhas < 0 || colunas < 0){
		print("ERRO NUMERO DE LINHAS OU COLUNAS NAO PODE SER NEGATIVO!");
		return NULL;
	}

	/* Número de celulas */
	int n_celulas = linhas * colunas;

	TIPO_CELULAS *_new_celulas;

	/* Tenta alocar o vetor de celulas */
	_new_celulas = mallocItArray(TIPO_CELULAS, n_celulas);

	/* Imprime um erro caso não seja possível alocar as celulas */
	if(_new_celulas == NULL){
		print("ERRO FATAL NAO FOI POSSIVEL ALOCAR AS CELULAS!");
		exit(EXIT_FAILURE);
	}

	/* Zera o vetor para evitar a presença de lixo */
	memset(_new_celulas, 0, n_celulas);

	TIPO_CELULAS **_new_linhas;

	/* Tenta alocar o vetor de linhas */
	_new_linhas = mallocItArray(*TIPO_CELULAS, linhas);

	/* Imprime um erro caso não seja possível alocar as linhas */
	if(_new_linhas == NULL){
		print("ERRO FATAL NAO FOI POSSIVEL ALOCAR AS LINHAS!");
		exit(EXIT_FAILURE);
	}

	/* Cria alias para facilitar o posicionamento dos itens da matriz */
	int i;
	for(i = 0; i < linhas; i++){
		/* Atalho para as linhas, podem ser feitos diretamente */
		_new_linhas[i] = &_new_celulas[i * colunas];
	}

	/* Inicializa os dados da estrutura */
	_new_matriz->n_linhas = linhas;
	_new_matriz->n_colunas = colunas;
	_new_matriz->n_celulas = n_celulas;
	_new_matriz->celulas = _new_celulas;
	_new_matriz->linhas = _new_linhas;

	/* Retorna um ponteiro para a matriz */
	return _new_matriz;
}

/**
 * Desaloca uma matriz
 *
 * @param matriz Ponteiro da matriz a ser desalocada
 * @return true se matriz foi desalocada e falso caso contrário
 */
bool deleteMatriz(ptrMatriz *matriz){
	/* Checa se a matriz existe */
	if(matriz == NULL){
		printError("NAO E POSSIVEL DESTRUIR A MATRIZ POIS ELA NAO EXISTE");
		return false;
	}

	/* Checa se a matriz e valida */
	if((*matriz) == NULL){
		printError("NAO E POSSIVEL DESTRUIR A MATRIZ POIS E INVALIDA");
		return false;
	}

	/* Desalocar linhas da matriz */
	if((*matriz)->linhas != NULL){
		secureFree((*matriz)->linhas);
	}

	/* Desalocar celulas da matriz */
	if((*matriz)->celulas != NULL){
		secureFree((*matriz)->celulas);
	}

	/* Desalucar a matriz */
	secureFree((*matriz));

	/* Return success */
	return true;
}
