#ifndef LISTA_H 
#define LISTA_H

#define TAM_MAX 20
#define ERRO -1

#include <stdbool.h>
#include "item.h"

/* TAD LISTA */

/* Define 'LISTA' como um alias para 'struct lista_' */
typedef struct lista_ LISTA;

/* Cria uma nova lista. Inicializa os campos 'tamanho', 'inicio' e 'fim' com 0, e define se a lista será ordenada com base no parâmetro 'ordenada'. */
LISTA *lista_criar(bool ordenada);

/* Insere um item na lista. Retorna true se a inserção for bem-sucedida. */
bool lista_inserir(LISTA *lista, ITEM *item);

/* Remove o item da lista na posição especificada. Retorna o item removido ou NULL se a posição for inválida. */
ITEM *lista_remover(LISTA *lista, int pos);

/* Retorna o item na posição especificada. */
ITEM *lista_item(LISTA *lista, int pos);

/* Retorna o tamanho atual da lista (número de elementos). */
int lista_tamanho(LISTA *lista);

/* Retorna true se a lista estiver cheia (tamanho >= TAM_MAX). */
bool lista_cheia(LISTA *lista);

/* Retorna true se a lista estiver vazia (tamanho == 0). */
bool lista_vazia(LISTA *lista);

/* Libera a memória alocada para a lista e seus itens. */
void lista_apagar(LISTA **lista);


#endif
