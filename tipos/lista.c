#include "./lista.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*------------ Lista Structure Methods ------------ */

/**
 *
 * Cria uma lista de matrizes, que pode conter a história de modificações
 * ou servir de variavel.
 *
 * @brief newLista Cria uma nova lista
 * @return Retorna uma nova lista alocada
 */
Lista* newLista(void){
    Lista *_new_lista;

    /* Tenta alocar uma nova lista */
    _new_lista = malloc(sizeof(Lista));

    /* Checa se não houve erros ao alocar a nova lista */
    if(_new_lista == NULL){
        printFatalError("ERRO FATAL AO ALOCAR NOVA LISTA!");
        exit(EXIT_FAILURE);
    }

    /* Inicializa os valores da lista */
    _new_lista->ultimoIndice = 0;
    _new_lista->nItems = 0;
    _new_lista->filho = NULL;

    /* Retorna lista alocada */
    return _new_lista;
}


/* PRIVATE - Remove todos os items da lista */
bool removeNoListaRecursivo(NoLista *noLista){
    /* Checa se o item da lista existe */
    if(noLista == NULL){
        printError("ERRO NO DA LISTA INEXISTENTE!");
        return false;
    }

    /* Remoção recursiva começa a partir do último item da lista */
    if(noLista->prox != NULL){
        if(!removeNoListaRecursivo(noLista->prox)){
            printError("ERRO NA REMOCAO RECURSIVA!");
            return false;
        }
    }

    /* Remove o item atual da lista, informando se a remoção ocorreu bem */
    ptrNoLista *_noLista = &noLista;
    return deleteNoLista(_noLista);
}

/**
 *
 * Deleta uma lista duplamente encadeada. As matrizes associadas a esta lista
 * só serão deletadas se forem cópias ou seja se forem listas que estão
 * armazenando um estado anterior de uma matriz ou uma lista de variaveis
 * utilizadas pelo sistema, caso a lista não seja uma cópia, ela não será
 * modificada pois pode estar sendo usada por outra instância.
 *
 * @brief deleteLista Deleta uma lista
 * @param lista Lista a ser removida
 * @return True se não houve erros ao remover a lista e falso caso contrário
 */
bool deleteLista(ptrLista *lista){
    /* Checa se o ponteiro para a lista existe */
    if(lista == NULL){
        printError("PONTEIRO PARA LISTA NAO EXISTE!");
        return false;
    }

    /* Checa se a lista ainda é consisntente */
    if((*lista) == NULL){
        printError("LISTA INEXISNTENTE. NAO FOI POSSIVEL REMOVER!");
        return false;
    }

    /* Caso a lista exista checa o numero de items */
    if((*lista)->nItems > 0){
        if(!removeNoListaRecursivo((*lista)->filho)){
            printError("ERRO NA REMOCAO DOS ITEMS DA LISTA!");
            return false;
        }
    }

    /* Desaloca a lista */
    secureFree((*lista));

    return true;
}

/* PRIVATE - Procura item recursivamente */
NoLista* buscaNoListaRecursivo(NoLista *noLista, int idItem){
    /* Item não encontrado */
    if(noLista == NULL){
        printError("ITEM NAO ENCONTRADO!");
        return NULL;
    }

    /* Nó encontrado */
    if(noLista->idItem == idItem){
        return noLista;
    }

    /* Procura recursivamente */
    return buscaNoListaRecursivo(noLista->prox, idItem);
}

/**
 *
 * Procura um item na lista, dado seu indice. A lista pode conter infinitos
 * indices, porém estes não podem ser repetidos, indicando um erro na hora
 * da inserção.
 *
 * @brief buscaNoLista Busca um nó na lista, pelo seu ID
 * @param lista Lista a procurar item
 * @param idItem Indíce do item a ser procurado
 * @return Retorna o ponteiro para Matriz, ou nullo caso não exista
 */
NoLista* buscaNoLista(Lista *lista, int idItem){
    /* Checa se a lista existe */
    if(lista == NULL){
        printError("LISTA NAO EXISTE!");
        return NULL;
    }

    /* Checa se o id é válido, qualquer id > 0 é válido */
    if(idItem < 0){
        printError("ID INVALIDO! ID NAO PODE SER MENOR QUE 0!");
        return NULL;
    }

    /* Checa se existe algum item na lista caso exista realiza a busca recursivamente */
    if(lista->nItems == 0){
        printError("LISTA VAZIA!");
        return false;
    }

    return buscaNoListaRecursivo(lista->filho, idItem);
}

/**
 *
 * Adiciona um novo nó a lista, o nó precisa ter um id único para poder ser adicionado
 * caso não queira ser utilizado um indíce, pode ser utilizado um indice aleatório
 * utilizando a flag INDICE_ALEATORIO.
 *
 * @brief adicionaNoLista Adiciona nova lista
 * @param lista Lista a ser adicionado item
 * @param idItem Indice para adição, passar (INDICE_ALEATORIO), para evitar item
 * @param matriz Matriz a ser adicionada a lista
 * @param copiaItem Indica se a matriz será copiada, ou apenas referenciada
 * @return Retorna sobre a execução da adição do item, true caso tudo ocorreu bem, falso caso contrário
 */
bool adicionaNoLista(Lista *lista, int idItem, Matriz *matriz, bool copiaItem){
    /* Checa se a lista é válida */
    if(lista == NULL){
        printError("LISTA NULA! NAO E POSSIVEL ADICIONAR!");
        return false;
    }

    /* Checa se o id é válido */
    if(idItem != INDICE_ALEATORIO && idItem < 0){
        printError("INDICE INVALIDO! INDICE NAO PODE SER MENOR QUE ZERO!");
        return false;
    }

    /* Checa se a matriz é válida */
    if(matriz == NULL){
        printError("MATRIZ INVALIDA! NAO E POSSIVEL ADICIONAR");
        return false;
    }

    /* Checa se já existe algum item com o id indicado */
    if(idItem != INDICE_ALEATORIO && buscaNoLista(lista, idItem) != NULL){
        printError("ITEM EXISTENTE! NAO E POSSIVEL ADICIONAR A LISTA!");
        return false;
    }

    /* Se o indice não é necessário adiciona um indice qualquer */
    if(idItem == INDICE_ALEATORIO){
        idItem = lista->ultimoIndice++;
    }

    /* Tenta criar um novo nó da lista */
    NoLista *_new_no_lista = newNoLista(idItem, matriz, copiaItem);

    /* Para de adicionar caso não tenha sido possível alocar o item */
    if(_new_no_lista == NULL){
        printError("ERRO AO CRIAR NOVO ITEM DA LISTA!");
        return false;
    }

    /* Adiciona o pai do novo nó */
    _new_no_lista->pai = lista;

    /* Com item adicionado percorre a lista até o último item e adiciona o mesmo */
    if(lista->filho == NULL){
        lista->filho = _new_no_lista;
    } else {
        /* Pega o primeiro item da lista */
        NoLista *_ultimo_item_lista = lista->filho;

        /* Percore a lista até o último item */
        while(_ultimo_item_lista->prox != NULL)
            _ultimo_item_lista->prox = _ultimo_item_lista->prox;

        /* Adiciona o item a lista como sendo o próximo item do último item */
        _ultimo_item_lista->prox = _new_no_lista;
    }

    /* Incrementa o contador de items */
    lista->nItems++;

    return true;
}

/**
 *
 * Remove um item da lista, dado seu indíce.
 *
 * @brief removeNoLista Remove um item da lista
 * @param lista Lista a qual o item deve ser removido
 * @param idItem Indice do item a ser removido
 * @return True se foi possível remover o item ou falso caso contrário
 */
bool removeNoLista(Lista *lista, int idItem){
    /* Checa se a lista é válida */
    if(lista == NULL){
        printError("LISTA INVALIDA! NAO E POSSIVEL REMOVER NO!");
        return false;
    }

    /* Checa se o indice é válido */
    if(idItem < 0){
        printError("INDICE INVALIDO! NAO E POSSIVEL REMOVER NO!");
        return false;
    }

    /* Procura pelo item na lista */
    NoLista *_no_lista = buscaNoLista(lista, idItem);

    /* Verifica se o item foi encontrado */
    if(_no_lista == NULL){
        printError("ITEM NAO ENCONTRADO!");
        return NULL;
    }

    /* Cria um ponteiro para remover o nó da lista */
    ptrNoLista *_ptr_no_lista = &_no_lista;

    return deleteNoLista(_ptr_no_lista);
}

/* PRIVATE - Exibe as matrizes dos nós da lista recursivamente */
void exibeNoRecursivo(NoLista *noLista){
    // Verifica se o nó da lista existe
    if(noLista != NULL){
        quebraLinha();
        printf("Matriz ID = %d\n", noLista->idItem);
        exibeNoLista(noLista);
        exibeNoRecursivo(noLista->prox);
    }
}

/**
 *
 * Exibe todas as matrizes de uma lista.
 *
 * @brief exibeTodasMatrizesLista Exibe todas as matrizes de uma lista
 * @param lista Lista a serem exibidas todas as matrizes
 * @return Retorna true se foi possível exibir as listas, e falso em caso de erro
 */
void exibeTodasMatrizesLista(Lista *lista){
    /* Lista inválida */
    if(lista == NULL){
        printError("LISTA INVALIDA! NAO E POSSIVEL EXIBIR!");
        return;
    }

    /* Exibe cada matriz da lista recursivamente */
    exibeNoRecursivo(lista->filho);
}

/**
 *
 * Cria um nó para uma lista de nós. Este nó contém uma matriz que pode ser
 * passado por cópia ou referência.
 *
 * @brief newNoLista Cria um novo nó para uma lista de nós
 * @param idItem Índice do item para a lista de nós
 * @param matriz Matriz com o conteudo do nó
 * @param copiaItem Indica se deverá ser copiado o item da matriz passado por parametro
 * @return Retorna o ponteiro de um novo nó da lista
 */
NoLista* newNoLista(int idItem, Matriz *matriz, bool copiaItem){
    /* Checa se o indice é válido */
    if(idItem < 0){
        printError("INDICE INVALIDO! NAO E POSSIVEL CRIAR O NO DA LISTA!");
        return NULL;
    }

    /* Checa se a matriz é válida */
    if(matriz == NULL){
        printError("MATRIZ INVALIDA! NAO E POSSIVEL CRIAR O NO DA LISTA!");
        return false;
    }

    /* Tenta alocar um novo nó de lista */
    NoLista *_new_no_lista = malloc(sizeof(NoLista));

    /* Verifica se foi possível alocar o nó da lista */
    if(_new_no_lista == NULL){
        printFatalError("ERRO NAO FOI POSSIVEL ALOCAR O NO DA LISTA!");
        exit(EXIT_FAILURE);
    }

    /* Inicializa o nó da lista */
    _new_no_lista->ante = NULL;
    _new_no_lista->prox = NULL;
    _new_no_lista->pai = NULL;
    _new_no_lista->idItem = idItem;
    _new_no_lista->itemCopiado = copiaItem;

    /* Se o item não for uma cópia apenas referencia o mesmo */
    if(!copiaItem){
        _new_no_lista->conteudo = matriz;
    } else {
        /* No caso de cópia iremos */
        _new_no_lista->conteudo = cloneMatriz(matriz);
    }

    return _new_no_lista;
}

/**
 *
 * Deleta um item da lista, se a matriz contida neste item da lista
 * for uma cópia deleta esse item também, porém caso seja uma referência
 * o item não será removido.
 *
 * @brief deleteNoLista Deleta um nó da lista
 * @param noLista Nó da lista a ser removido
 * @return Retorno da execução da remoção, true se removido e false caso contrário
 */
bool deleteNoLista(ptrNoLista *noLista){
    /* Checa se o ponteiro para o nó existe */
    if(noLista == NULL){
        printError("PONTEIRO PARA O ITEM NAO EXISTE!");
        return false;
    }

    /* Checa se o nó existe */
    if((*noLista) == NULL){
        printError("ITEM NAO EXISTE, ERRO AO REMOVER!");
        return false;
    }

    /* Checa se o item foi copiado, caso sim, remove o mesmo */
    if((*noLista)->itemCopiado){
        ptrMatriz *_conteudo = &(*noLista)->conteudo;
        if(!deleteMatriz(_conteudo)){
            printError("ERRO AO REMOVER MATRIZ!");
            return false;
        }
    }

    /* Reposiciona a navegabilidade de acordo com os seguintes casos */
    if((*noLista)->ante == NULL && (*noLista)->prox == NULL){
        /* Se a lista está vazia insere nulo no pai */
        (*noLista)->pai->filho = NULL;
    } else if ((*noLista)->ante == NULL && (*noLista)->prox != NULL) {
        /* Se existe próximo, porém somos o primeiro item da lista */
        (*noLista)->pai->filho = (*noLista)->prox;
        (*noLista)->prox->ante = NULL;
    } else if ((*noLista)->ante != NULL && (*noLista)->prox == NULL){
        /* Se não existe próximo porém existe anterior */
        (*noLista)->ante->prox = NULL;
    } else {
        /* Se existe próximo e anterior */
        (*noLista)->ante->prox = (*noLista)->prox;
        (*noLista)->prox->ante = (*noLista)->ante;
    }

    /* Desaloca o item atual da lista */
    secureFree((*noLista));

    return true;
}

/**
 *
 * Exibe a matriz de um nó da lista. A matriz será formatada para ser exibida
 * corretamente no terminal do computador. Em caso de matrizes com muitas colunas
 * ou valores de celulas com muitos digitos erros de exibição podem ocorrer.
 *
 * @brief exibeNoLista Exibe a matriz de um nó da lista
 * @param noLista No da lista cuja matriz sera exibido
 */
void exibeNoLista(NoLista *noLista){
    /* Nó da lista inválido ou inexistente */
    if(noLista == NULL){
        printError("NO DE LISTA INVALIDO! NAO SERA POSSIVEL EXIBIR");
        return;
    }

    /* Exibe o conteúdo da matriz */
    imprimeMatriz(noLista->conteudo);
}
