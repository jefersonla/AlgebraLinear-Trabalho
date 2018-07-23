#include "./matriz.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*------------ Matriz Structure Methods ------------ */

/**
 *
 * Cria uma nova matriz A(n x m) (n - linhas por m - colunas)
 *
 * @param linhas Número de linhas
 * @param colunas Número de colunas
 * @param tipoValor Tipo do valor
 * @param valores Valores constantes ou nulos para serem assignados a matriz
 * @return Retorna uma nova matriz alocada
 */
Matriz* newMatriz(int linhas, int colunas, int tipoValor, MatrizCelula* valores[]){
    int i, j;

    /* Numero de linhas ou colunas não pode ser negativo */
    if(linhas < 0 || colunas < 0){
        printError("ERRO NUMERO DE LINHAS OU COLUNAS NAO PODE SER NEGATIVO!");
        return NULL;
    }

    /* Checa se o parametro do tipo de valor é válido */
    if(!variavelEntre(tipoValor, MATRIZ_TIPO_MIN, MATRIZ_TIPO_MAX)){
        printError("TIPO DE VALOR INCORRETO");
    }

    Matriz *_new_matriz;

	/* Tenta alocar a estrutura da nova matriz */
    _new_matriz = malloc(sizeof(Matriz));

	/* Imprime um erro caso não seja possível alocar */
	if(_new_matriz == NULL){
        printFatalError("ERRO FATAL NAO FOI POSSIVEL ALOCAR A ESTRUTURA!");
		exit(EXIT_FAILURE);
	}

	/* Número de celulas */
	int n_celulas = linhas * colunas;

    MatrizCelula *_new_celulas;

	/* Tenta alocar o vetor de celulas */
    _new_celulas = malloc(sizeof(MatrizCelula) * ((size_t)n_celulas));

	/* Imprime um erro caso não seja possível alocar as celulas */
	if(_new_celulas == NULL){
        printError("ERRO FATAL NAO FOI POSSIVEL ALOCAR AS CELULAS!");
		exit(EXIT_FAILURE);
	}

    MatrizCelula **_new_linhas;

	/* Tenta alocar o vetor de linhas */
    _new_linhas = malloc(sizeof(MatrizCelula*) * ((size_t)linhas));

	/* Imprime um erro caso não seja possível alocar as linhas */
	if(_new_linhas == NULL){
        printFatalError("ERRO FATAL NAO FOI POSSIVEL ALOCAR AS LINHAS!");
		exit(EXIT_FAILURE);
	}

	/* Cria alias para facilitar o posicionamento dos itens da matriz */
	for(i = 0; i < linhas; i++){
		/* Atalho para as linhas, podem ser feitos diretamente */
		_new_linhas[i] = &_new_celulas[i * colunas];
	}

    /* Checa o tipo de variavel e preenche a matriz conforme o pedido */
    switch(tipoValor){
        case MATRIZ_CONSTANTE:
            /* Insere o valor em todas as celulas */
            for(i = 0; i < n_celulas; i++)
                _new_celulas[i] = valores[0][0];
        break;

        case MATRIZ_VAZIA:
            /* Zera o vetor para evitar a presença de lixo */
            memset(_new_celulas, 0, (size_t) n_celulas);
        break;

        case MATRIZ_IDENTIDADE:
            /* Constroi uma matriz identidade */
            for(i = 0; i < linhas; i++)
                for(j = 0; j < colunas; j++)
                    _new_linhas[i][j] = (i == j)? 1 : 0;
        break;

        case MATRIZ_VALORES:
            /* Completa a matriz com todos os valores */
            for(i = 0; i < linhas; i++)
                for(j = 0; j < colunas; j++)
                    _new_linhas[i][j] = valores[i][j];
        break;

        default:
            printFatalError("ERRO FATAL TIPO DE VARIAVEL INVALIDO!");
            exit(EXIT_FAILURE);
    }

	/* Inicializa os dados da estrutura */
    _new_matriz->nLinhas = linhas;
    _new_matriz->nColunas = colunas;
    _new_matriz->nCelulas = n_celulas;
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

/**
 *
 * Clona uma matriz. Retorna um ponteiro para uma nova matriz que representa
 * uma cópia exata da matriz passada por parametro.
 *
 * @brief cloneMatriz Clona uma matriz
 * @param matriz Matriz a ser clonada
 * @return Retorna o ponteiro para o clone da matriz
 */
Matriz* cloneMatriz(Matriz* matriz){
    /* Verifica se a matriz é válida */
    if(matriz == NULL){
        printError("MATRIZ INVALIDA NAO E POSSIVEL CLONAR!");
        return NULL;
    }

    /* Cria uma matriz vazia */
    Matriz *_cloned_matriz = newMatriz(matriz->nLinhas, matriz->nColunas, MATRIZ_VAZIA, NULL);

    /* Copia todos os valores da matriz antiga para a nova cópia */
    int i, j;
    for(i = 0; i < matriz->nLinhas; i++)
        for(j = 0; j < matriz->nColunas; j++)
            _cloned_matriz->linhas[i][j] = matriz->linhas[i][j];

    return _cloned_matriz;
}
