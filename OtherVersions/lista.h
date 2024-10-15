#ifndef LISTA_H
    #define LISTA_H
    #define TAM_MAX 20
    #define ERRO -1
    
    #include <stdbool.h>
    #include "item.h"

    typedef struct lista_ LISTA;

    LISTA *lista_criar(bool ordenada);
    bool lista_inserir(LISTA *lista, ITEM *item);
    ITEM *lista_remover(LISTA *lista, int pos);
    ITEM *lista_item(LISTA *lista, int pos);
    
    int lista_tamanho(LISTA *lista);
    bool lista_cheia(LISTA *lista);
    bool lista_vazia(LISTA *lista);
	void lista_apagar(LISTA **lista);
    void lista_imprimir(LISTA *lista);

#endif