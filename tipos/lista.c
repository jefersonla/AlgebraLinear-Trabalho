#include "./lista.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*------------ Lista Structure Methods ------------ */

/* Cria uma nova matriz */
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

/* Desaloca uma matriz */
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

/* Pega item da matriz */
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

/* Adiciona item a lista */
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
            _ultimo_item_lista = _ultimo_item_lista->prox;

        /* Adiciona o item a lista como sendo o próximo item do último item */
        _ultimo_item_lista->prox = _new_no_lista;

        /* Configura o anterior como sendo o nó anterior a este */
        _new_no_lista->ante = _ultimo_item_lista;
    }

    /* Incrementa o contador de items */
    lista->nItems++;

    return true;
}

/* Remove item da matriz */
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

    /* Decrementa o número de nós na lista */
    lista->nItems--;

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

/* Exibe todas as matrizes de uma lista */
void exibeTodasMatrizesLista(Lista *lista){
    /* Lista inválida */
    if(lista == NULL){
        printError("LISTA INVALIDA! NAO E POSSIVEL EXIBIR!");
        return;
    }

    /* Exibe cada matriz da lista recursivamente */
    exibeNoRecursivo(lista->filho);
}

/* Cria um novo nó para lista */
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

/* Desaloca um item da tabela */
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

    Lista *pai_lista = (*noLista)->pai;
    NoLista *prox_no = (*noLista)->prox;
    NoLista *ante_no = (*noLista)->ante;

    /* Desaloca o item atual da lista */
    secureFree((*noLista));

    /* Reposiciona a navegabilidade de acordo com os seguintes casos */
    if(ante_no == NULL && prox_no == NULL){
        /* Se a lista está vazia insere nulo no pai */
        pai_lista->filho = NULL;
    } else if (ante_no == NULL && prox_no != NULL) {
        /* Se existe próximo, porém somos o primeiro item da lista */
        pai_lista->filho = prox_no;
        prox_no->ante = NULL;
    } else if (ante_no != NULL && prox_no == NULL){
        /* Se não existe próximo porém existe anterior */
        ante_no->prox = NULL;
    } else {
        /* Se existe próximo e anterior */
        ante_no->prox = prox_no;
        prox_no->ante = ante_no;
    }

    return true;
}

/* Exibe no da lista */
void exibeNoLista(NoLista *noLista){
    /* Nó da lista inválido ou inexistente */
    if(noLista == NULL){
        printError("NO DE LISTA INVALIDO! NAO SERA POSSIVEL EXIBIR");
        return;
    }

    /* Exibe o conteúdo da matriz */
    imprimeMatriz(noLista->conteudo);
}
