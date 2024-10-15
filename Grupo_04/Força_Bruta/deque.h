#include <stdbool.h>
#include "item.h"

#ifndef DEQUE_H_
    #define DEQUE_H_

    /* ESSE É O TAD DEQUE */

    /* DEFINIÇÃO DE CONSTANTE PARA ERRO */
    #define ERRO -1

    /* DEFINIÇÃO DE CONSTANTE PARA TAMANHO MÁXIMO DO DEQUE */
    #define MAX_TAMANHO 12

    /* TYPEDEF utilizado para representar o tipo DEQUE */
    typedef struct deque_ DEQUE;

    /* A função "deque_criar", cujo retorno tem tipo DEQUE*, tem o papel de criar a estrutura de um deque, alocando a sua memória dinamicamente e retornando-o. */
    DEQUE* deque_criar();

    /* A função "deque_apagar", recebe o endereço de um deque e libera a memória alocada de cada item da estrutura e, por fim,
    libera o espaço alocado para a estrutura do deque. */
    void deque_apagar(DEQUE** deque);

    /* A função "deque_inserir_inicio" recebe um deque e um item, tendo o objetivo de inserir um item no início do deque, retornando se a operação
    foi bem sucedida ou não. */
    bool deque_inserir_inicio(DEQUE* deque, ITEM* item);

    /* A função "deque_inserir_fim" recebe um deque e um item, tendo o objetivo de inserir um item no fim do deque, retornando se a operação
    foi bem sucedida ou não. */
    bool deque_inserir_fim(DEQUE* deque, ITEM* item);

    /* A função "deque_remover_inicio", recebe um deque e retira o item que estava localizado em seu início, retornando-o. */
    ITEM* deque_remover_inicio(DEQUE* deque);

    /* A função "deque_remover_inicio", recebe um deque e retira o item que estava localizado em seu fim, retornando-o. */
    ITEM* deque_remover_fim(DEQUE* deque);

    /* A função "deque_primeiro", recebe um deque e mostra o item que está localizado em seu início, retornando-o. */
    ITEM* deque_primeiro(DEQUE* deque);

    /* A função "deque_ultimo", recebe um deque e mostra o item que está localizado em seu fim, retornando-o. */
    ITEM* deque_ultimo(DEQUE* deque);

    /* A função "deque_contar" recebe um deque e retornar o seu tamanho (a quantidade de elementos). */
    int deque_contar(DEQUE* deque);

    /* A função "deque_vazia" recebe um deque e retorna se o deque é vazio ou não. */
    bool deque_vazia(DEQUE* deque);

    /* A função "deque_cheia" recebe um deque e retorna se o deque está cheio ou não. */
    bool deque_cheia(DEQUE* deque);

    // FUNÇÃO USADA SOMENTE PARA DEBUG
    // /* A função "deque_printar", cujo retorno é do tipo void e cujo parâmetro recebido é o próprio deque, tem o objetivo de printar o conteúdo guardado
    // em cada item da estrutura. */
    // void deque_printar(DEQUE *deque);

    /* A função "deque_copiar" recebe um deque de origem e um deque de destino e copia o conteúdo da origem para o destino. */
    void deque_copiar(DEQUE* origem, DEQUE* destino);

#endif
