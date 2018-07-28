#include "./matriz.h"
#include "../utils/utils.h"
#include "../utils/ajuda.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*------------ Matriz Structure Methods ------------ */

/* Cria uma nova matriz */
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
        return NULL;
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

    /* Inicializa o maior valor da matriz */
    _new_matriz->maiorValor = 0;

    /* Checa o tipo de variavel e preenche a matriz conforme o pedido */
    switch(tipoValor){
        case MATRIZ_CONSTANTE:
            /* Insere o valor em todas as celulas */
            for(i = 0; i < n_celulas; i++)
                _new_celulas[i] = valores[0][0];

            /* Maior valor */
            _new_matriz->maiorValor = fabs(valores[0][0]);

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

            /* Maior valor */
            _new_matriz->maiorValor = 1.0;

        break;

        case MATRIZ_VALORES:

            /* Completa a matriz com todos os valores */
            for(i = 0; i < linhas; i++)
                for(j = 0; j < colunas; j++){
                    _new_linhas[i][j] = valores[i][j];

                    /* Maior valor */
                    if(_new_matriz->maiorValor < fabs(_new_linhas[i][j]))
                        _new_matriz->maiorValor = fabs(_new_linhas[i][j]);
                }

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

/* Desaloca uma matriz */
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

/* Clona uma matriz */
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

    /* Copia o valor da variavel de maior valor para o clone */
    _cloned_matriz->maiorValor = matriz->maiorValor;

    return _cloned_matriz;
}

/* Exibe a matriz formatada */
void imprimeMatriz(Matriz* matriz){
    /* Checa se a matriz é válida */
    if(matriz == NULL){
        printError("MATRIZ INVALIDA NAO E POSSIVEL IMPRIMIR!");
        return;
    }

    /* Verifica o nome de digitos do maior número da matriz */
    /* Obrigado SF - https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c/23840699 */
    int numDigitos = snprintf(NULL, 0, "%.2lf", matriz->maiorValor) + TAM_ESPACADOR + 1;

#ifdef DEBUG
    printInfo("TAMANHO COLUNA");
    printf("=> %d, %lf\n", numDigitos, matriz->maiorValor);
#endif

    /* Buffer para cada string com tamanho formatado */
    char *buf = malloc(sizeof (char) * (size_t)numDigitos);

    /* Imprime a matriz formatada */
    int i, j;
    for(i = 0; i < matriz->nLinhas; i++){
        for(j = 0; j < matriz->nColunas; j++){
            imprimeColunaFixa(buf, matriz->linhas[i][j], numDigitos);
        }

        /* Quebra a linha após imprimir cada coluna de cada linha */
        quebraLinha();
    }

    /* Limpa o buffer alocado anteriormente */
    free(buf);
}

/* Atualiza maior valor */
void atualizaMaiorValorMatriz(Matriz* matriz){
    int i, j;

    /* Maior valor */
    for(i = 0; i < matriz->nLinhas; i++)
        for(j = 0; j < matriz->nColunas; j++)
            if(matriz->maiorValor < fabs(matriz->linhas[i][j]))
                matriz->maiorValor = fabs(matriz->linhas[i][j]);
}
