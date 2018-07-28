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

/**
 *
 * Cria uma lista de matrizes, que pode conter a história de modificações
 * ou servir de variavel.
 *
 * @brief newLista Cria uma nova lista
 * @return Retorna uma nova lista alocada
 */
Lista* newLista(void);

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
bool deleteLista(ptrLista *lista);

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
NoLista* buscaNoLista(Lista *lista, int idItem);

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
bool adicionaNoLista(Lista *lista, int idItem, Matriz *matriz, bool copiaItem);

/**
 *
 * Remove um item da lista, dado seu indíce.
 *
 * @brief removeNoLista Remove um item da lista
 * @param lista Lista a qual o item deve ser removido
 * @param idItem Indice do item a ser removido
 * @return True se foi possível remover o item ou falso caso contrário
 */
bool removeNoLista(Lista *lista, int idItem);

/**
 *
 * Exibe todas as matrizes de uma lista.
 *
 * @brief exibeTodasMatrizesLista Exibe todas as matrizes de uma lista
 * @param lista Lista a serem exibidas todas as matrizes
 * @return Retorna true se foi possível exibir as listas, e falso em caso de erro
 */
void exibeTodasMatrizesLista(Lista *lista);

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
NoLista* newNoLista(int idItem, Matriz *matriz, bool copiaItem);

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

bool deleteNoLista(ptrNoLista *lista);

/**
 *
 * Exibe a matriz de um nó da lista. A matriz será formatada para ser exibida
 * corretamente no terminal do computador. Em caso de matrizes com muitas colunas
 * ou valores de celulas com muitos digitos erros de exibição podem ocorrer.
 *
 * @brief exibeNoLista Exibe a matriz de um nó da lista
 * @param noLista No da lista cuja matriz sera exibido
 */
void exibeNoLista(NoLista *noLista);

/* ------------------------------------------------------------- */

#endif
