#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "item.h"

typedef struct item_{
    int chave;
    void *dado;
} ITEM;

ITEM *item_criar (int chave, void *comp){
    ITEM *item = (ITEM *) malloc(sizeof(ITEM));

    if(item != NULL){
        item->chave = chave;
        item->dado = comp;
    }

    return(item);
}

bool item_apagar (ITEM **item){
    if(*item != NULL){
        if((*item)->dado != NULL){
            free((*item)->dado);
            (*item)->dado = NULL;
        }
        free(*item);
        *item = NULL;
        return(true);
    }

    return(false);
}

int item_get_chave (ITEM *item){
    if(item != NULL)
        return(item->chave);
    
    exit(1);
}

bool item_set_chave (ITEM *item, int chave){
    if(item != NULL){
        item->chave = chave;
        return(true);
    }

    return(false);
}

void *item_get_dados (ITEM *item){
    if(item != NULL){
        return(item->dado);
    }

    return(NULL);
}

