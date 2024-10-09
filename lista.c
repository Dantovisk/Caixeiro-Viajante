#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct lista_{
    ITEM *itens[TAM_MAX];
    int inicio;
    int fim; // O PRÓXIMO ÍNDICE DISPONÍVEL
    int tamanho; // QNTD DE ELEMENTOS DO VETOR DE ITENS
    bool ordenada;
} LISTA;

LISTA *lista_criar(bool ordenada){
    LISTA *l = (LISTA *) malloc(sizeof(LISTA));
    if(l != NULL){
        l->inicio = 0;
        l->fim = 0;
        l->tamanho = 0;
        l->ordenada = ordenada;
    }

    return l;
}

int lista_busca(LISTA *lista, int val){
    int inf = lista->inicio;
    int sup = lista->fim;
    int meio;

    if(lista_vazia(lista))
        return lista->fim;

    while (inf < sup) {
        meio = (inf + sup) / 2;

        if (item_get_chave(lista->itens[meio]) == val) {
            return meio;
        }

        else if (item_get_chave(lista->itens[meio]) > val) {
            sup = meio;
        }

        else {
            inf = meio + 1;
        }
    }

    return inf;
}

bool lista_inserir_posicao(LISTA *lista, int pos, ITEM *item){
    if(!lista_cheia(lista) && pos <= lista->fim){
        for(int i = lista->fim; i > pos; i--){                                                                                                                                                                                                
            lista->itens[i] = lista->itens[i-1];                                                                                                                                                                                              
        }                                                                                                                                                                                                                                     
                                                                                                                                                                                                                                              
        lista->itens[pos] = item;                                                                                                                                                                                                             
        lista->fim++;                                                                                                                                                                                                                         
        lista->tamanho++;                                                                                                                                                                                                                     
        return true;                                                                                                                                                                                                                          
    }                                                                                                                                                                                                                                         
                                                                                                                                                                                                                                              
    return false;                                                                                                                                                                                                                             
}              
bool lista_inserir_fim (LISTA *lista, ITEM *it) {
    if(!lista_cheia(lista)){
        lista->itens[lista->fim] = it;
        lista->fim++;
        lista->tamanho++;
        return(true);
    }
    return(false);
}                                                                                                                                                                                                                               
                                                                                                                                                                                                                                              
bool lista_inserir(LISTA *lista, ITEM *item){                                                                                                                                                                                                 
    if(lista->ordenada){                                                                                                                                                                                                                             
        int x = lista_busca(lista, item_get_chave(item));                                                                                                                                                                                     
        return(lista_inserir_posicao(lista, x, item));                                                                                                                                                                                        
    }                                                                                                                                                                                                                                         
                                                                                                                                                                                                                                              
    return(lista_inserir_fim(lista, item));                                                                                                                                                                                                                                                                                                                                                                          
}        


ITEM *lista_remover(LISTA *lista, int pos){
    if (lista == NULL || lista_vazia(lista) || pos<0 || pos > lista->fim) {
        return NULL;
    }

    ITEM *it = lista->itens[pos];

    for (int j = pos; j < lista->fim - 1; j++) {
        lista->itens[j] = lista->itens[j + 1];
    }

    lista->fim--;
    lista->tamanho--;

    return it;
}

ITEM *lista_item(LISTA *lista, int chave) {
    if(lista != NULL) {
        int i = lista_busca(lista, chave);

        //caso de lista_busca retornar o fim da lista (item nao existe)
        if(i >= lista->fim) return NULL;

        //caso de a chave ser diferente da esperada, não esta na lista
        if(chave != item_get_chave(lista->itens[i])) return NULL;
        
        return (lista->itens[i]);
    }
    return NULL;
}

int lista_tamanho(LISTA *lista) {
    if(lista != NULL) {
        return(lista->tamanho);
    }
    return ERRO;
}

bool lista_vazia(LISTA *lista){                                                                                                                                                                                                               
    if(lista != NULL)                                                                                                                                                                                                                         
        return (lista->tamanho == 0);                                                                                                                                                                                                           
                                                                                                                                                                                                                                              
    return true;                                                                                                                                                                                                                              
}                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                              
bool lista_cheia(LISTA *lista){                                                                                                                                                                                                               
    if(lista != NULL)                                                                                                                                                                                                                         
        return (lista->tamanho >= TAM_MAX);                                                                                                                                                                                                     
                                                                                                                                                                                                                                              
    return true;                                                                                                                                                                                                                              
}  

void lista_apagar(LISTA **lista) {
    if (lista == NULL || *lista == NULL) {
        return;
    }
    while(!lista_vazia(*lista)) {
        ITEM *it = lista_remover(*lista, (*lista)->inicio);
        item_apagar(&it);
    }
    free(*lista);
    *lista = NULL;
    return;
}

void lista_imprimir(LISTA *lista) {
    if (lista == NULL || lista_vazia(lista)) {
        printf("Lista vazia.\n");
        return;
    }
    for (int i = lista->inicio; i < lista->fim; i++) {
        printf("Item %d: chave = %d\n", i, item_get_chave(lista->itens[i]));
    }
    printf("\n");
}