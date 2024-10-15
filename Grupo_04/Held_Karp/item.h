#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>

/* TAD ITEM */

/* Define 'ITEM' como um alias para 'struct item_' */
typedef struct item_ ITEM;

/* Cria um novo item com a chave e dados fornecidos. A memória é alocada dinamicamente. */
ITEM *item_criar(int chave, void *comp);

/* Libera a memória alocada para o item. Retorna true se a operação for bem-sucedida. */
bool item_apagar(ITEM **item);

/* Retorna a chave do item. */
int item_get_chave(ITEM *item);

/* Define ou altera a chave do item. Retorna true se a operação for bem-sucedida. */
bool item_set_chave(ITEM *item, int chave);

/* Retorna os dados armazenados no item. Cabe ao usuário controlar qual é o tipo armazenado nos dados e realizar
o respectivo casting. */
void *item_get_dados(ITEM *item);

#endif
