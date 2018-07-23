#ifndef LISTA_H
#define LISTA_H

#include "matriz.h"
#include <stdbool.h>

/* ------------------------------------------------------------- */
/*                       Constantes Lista                        */
/* ------------------------------------------------------------- */

#define INDICE_ALEATORIO -1

/* ------------------------------------------------------------- */
/*                     Prototype definitions                     */
/* ------------------------------------------------------------- */

/* Lista */
typedef struct strLista Lista;

/* Nó Lista */
typedef struct strNoLista NoLista;

/* ------------------------------------------------------------- */
/*                       Lista  Structure                        */
/* ------------------------------------------------------------- */

typedef struct strLista{
    /* Número de itens na lista */
    int nItems;

    /* Nó Filho */
    NoLista *filho;

    /* Último indice usado */
    int ultimoIndice;
} Lista, *ptrLista;

typedef struct strNoLista{
    /* Ponteiro para o próximo e o anterior */
    NoLista *prox;
    NoLista *ante;

    /* Pai */
    Lista *pai;

    /* ID do Item */
    int idItem;

    /* Armazena história */
    /* TODO */

    /* Conteúdo */
    bool itemCopiado;
    Matriz *conteudo;
}NoLista, *ptrNoLista;

/* ------------------ Lista Structure Methods ------------------ */

/* Cria uma nova matriz */
Lista* newLista(void);

/* Desaloca uma matriz */
bool deleteLista(ptrLista *lista);

/* Pega item da matriz */
NoLista* buscaNoLista(Lista *lista, int idItem);

/* Adiciona item a lista */
bool adicionaNoLista(Lista *lista, int idItem, Matriz *matriz, bool copiaItem);

/* Remove item da matriz */
bool removeNoLista(Lista *lista, int idItem);

/* Exibe todas as matrizes de uma lista */
void exibeTodasMatrizesLista(Lista *lista);

/* Cria um novo nó para lista */
NoLista* newNoLista(int idItem, Matriz *matriz, bool copiaItem);

/* Desaloca um item da tabela */
bool deleteNoLista(ptrNoLista *lista);

/* Exibe no da lista */
void exibeNoLista(NoLista *noLista);

/* ------------------------------------------------------------- */

#endif
