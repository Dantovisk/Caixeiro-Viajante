#ifndef LISTA_H
    #define LISTA_H
    #define TAM_MAX 12
    #define ERRO -1
    #include <stdbool.h>
    #include "item.h"

    /* ESTE É O TAD LISTA */

    /* TYPEDEF utilizado para representar o tipo 'struct lista_' apenas por 'LISTA' */
    typedef struct lista_ LISTA;

    /* A função "lista_criar" tem o papel de criar a estrutura de uma lista, alocando a sua memória dinamicamente e inicializando os campos da struct LISTA. */
    LISTA *lista_criar(void);

    /* A função "lista_apagar", recebe o endereço de um lista e libera a memória alocada de cada item da estrutura e, por fim,
    libera o espaço alocado para a estrutura do lista. */
	void lista_apagar(LISTA **lista);

    /* A função "lista_inserir" recebe uma lista e um item que se deseja inserir na lista ordenada.*/
    bool lista_inserir(LISTA *lista, ITEM *item);

    /* A função "lista_remover" recebe uma lista e um valor da posição do item que se deseja remover. */
    ITEM *lista_remover(LISTA *lista, int pos);

    /* A função "lista_item" recebe uma lista e uma chave, retornando ao usuário o item da lista com essa determinada chave. */
    ITEM *lista_item(LISTA *lista, int pos);
    
    /* A função "lista_tamanho" recebe uma lista e retorna o seu tamanho (a quantidade de elementos) dentro da lista em questão.*/
    int lista_tamanho(LISTA *lista);

    /* A função "lista_vazia" recebe um lista e retorna se o lista é vazio ou não.*/
    bool lista_vazia(LISTA *lista);

    /* A função "lista_cheia" recebe um lista e retorna se o lista está cheio ou não. */
    bool lista_cheia(LISTA *lista);
#endif