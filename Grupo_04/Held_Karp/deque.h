#ifndef DEQUE_H_
#define DEQUE_H_

#include <stdbool.h>
#include "item.h"

/* TAD DEQUE */

/* Constante para representar erro */
#define ERRO -1

/* Tamanho máximo do deque */
#define MAX_TAMANHO 20

/* Define 'DEQUE' como um alias para 'struct deque_' */
typedef struct deque_ DEQUE;

/* Cria um novo deque, inicializando 'tamanho', 'inicio' e 'fim' com 0. */
DEQUE* deque_criar();

/* Libera a memória alocada para o deque e seus itens. */
void deque_apagar(DEQUE** deque);

/* Insere um item no início do deque. Retorna true se a inserção for bem-sucedida. */
bool deque_inserir_inicio(DEQUE* deque, ITEM* item);

/* Insere um item no fim do deque. Retorna true se a inserção for bem-sucedida. */
bool deque_inserir_fim(DEQUE* deque, ITEM* item);

/* Remove e retorna o item no início do deque. */
ITEM* deque_remover_inicio(DEQUE* deque);

/* Remove e retorna o item no fim do deque. */
ITEM* deque_remover_fim(DEQUE* deque);

/* Retorna o item no início do deque sem removê-lo. */
ITEM* deque_primeiro(DEQUE* deque);

/* Retorna o item no fim do deque sem removê-lo. */
ITEM* deque_ultimo(DEQUE* deque);

/* Retorna a quantidade de elementos no deque. */
int deque_contar(DEQUE* deque);

/* Retorna true se o deque estiver vazio. */
bool deque_vazia(DEQUE* deque);

/* Retorna true se o deque estiver cheio (tamanho >= MAX_TAMANHO). */
bool deque_cheia(DEQUE* deque);

/* Copia os itens de um deque de origem para um deque de destino sem modificar o deque de origem. */
void deque_copiar(DEQUE* origem, DEQUE* destino);

#endif
