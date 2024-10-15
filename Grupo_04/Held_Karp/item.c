#include <stdio.h>
#include <stdlib.h>
#include "item.h"

/*
A 'struct item_', por meio do typedef feito no TAD "item.h", passa a ser do tipo 'ITEM'. A struct possui apenas dois campos:
01) chave: Um inteiro que representa a chave do item.
02) dado: Um ponteiro genérico que contém os dados associados ao item.
*/
struct item_{
    int chave;
    void *dado;
};

/* 
A função "item_criar", cujo retorno tem tipo ITEM*, tem o papel de criar o item, com os parâmetros recebidos, alocando a sua memória
dinamicamente:
01) Em caso de erro na alocação de memória, apenas retorna NULL sem mudar os campos da struct.
02) Em caso de sucesso na alocação de memória, a partir dos parâmetros da função, a chave e o dado recebidos são colocados dentro do item 
criado e a função retorna um ponteiro para este item 
Complexidade: O(1)
*/
ITEM *item_criar (int chave, void *comp){
    // Declaração da variável ponteiro para item e inicialização dela como NULL.
    ITEM *item = NULL;
    // Alocação da memória a partir da função da <stdlib.h> malloc().
    item = (ITEM *) malloc(sizeof(ITEM));

    // Se a memória para item for corretamente alocada, a chave e o dado recebidos como parâmetro são colocados dentro da struct item nos
    // seus respectivos campos.
    if(item != NULL){
        item->chave = chave;
        item->dado = comp;
    }

    // Possíveis retornos: NULL(Falha na alocação) ou ITEM* (Sucesso na alocação)
    return(item);
}

/* 
A função "item_apagar", cujo retorno é do tipo booleano, tem o papel de liberar a memória alocada do item, a partir do duplo ponteiro que
é recebido como parâmetro, de modo que:
01) Caso o item seja nulo, ou seja, não tenha ocorrido corretamente a alocação dinâmica, o retorno é FALSO
02) Caso o item não seja nulo, ou seja, tenha ocorrido corretamente a alocação dinâmica, o retorno é VERDADEIRO
Complexidade: O(1)
*/
bool item_apagar (ITEM **item){
    // Verificação se o item não é nulo
    if(*item != NULL){
        // Se o dado do item for diferente de nulo, libera-se sua memória
        if((*item)->dado != NULL){
            // Libera-se a memória alocada para o dado
            free((*item)->dado);
            // Como boa prática, faz-se o ponteiro para dado apontar para NULL, evitando acessos indevidos a espaços de memória
            (*item)->dado = NULL;
        }
        // Libera-se a memória
        free(*item);
        // Como boa prática, faz-se o ponteiro para item receber nulo, a fim de não ser possível acessar mais a região de memória liberada
        *item = NULL;
        // Retorna VERDADEIRO, indicando que foi possível apagar o item
        return(true);
    }

    // Retorna FALSO, indicando que o item era nulo, então, não há como apagá-lo
    return(false);
}

/* 
A função "item_get_chave", cujo retorno é do tipo inteiro, tem o papel de acessar o campo da 'chave' dentro da struct de um item recebido
como parâmetro: 
01) Caso o item seja nulo, ou seja, não tenha ocorrido corretamente a alocação dinâmica, o programa se encerra, pois se está querendo 
acessar o campo de um item que não foi alocado devidamente.
02) Caso o item não seja nulo, ou seja, tenha ocorrido corretamente a alocação dinâmica, a função retorna a 'chave' do item recebido.
Complexidade: O(1)
*/
int item_get_chave (ITEM *item){
    // Verificação se o item não é nulo
    if(item != NULL) {
        // Retorna a 'chave' do respectivo item
        return(item->chave);
    }
    // Caso seja nulo e esteja querendo acessar a 'chave', encerra o programa
    exit(1);
}

/* 
A função "item_set_chave", cujo retorno é do tipo booleano, tem o papel de inicializar/alterar o campo 'chave' da struct de item recebido
por uma outra 'chave', que também é recebida como parâmetro da função:
01) Caso o item seja nulo, ou seja, não tenha ocorrido corretamente a alocação dinâmica, o retorno é FALSO
02) Caso o item não seja nulo, ou seja, tenha ocorrido corretamente a alocação dinâmica, a chave é alterada e o retorno é VERDADEIRO
Complexidade: O(1)
*/
bool item_set_chave (ITEM *item, int chave){
    // Verificação se o item não é nulo
    if(item != NULL){
        // Inicialização/Alteração manual do campo 'chave' da struct
        item->chave = chave;
        // Retorna VERDADEIRO, indicando que foi possível inicializar/alterar o campo 'chave' da struct do item
        return(true);
    }
    // Retorna FALSO, indicando que o item era nulo, então, não era possível inicializar/alterar o campo 'chave' da struct do item
    return(false);
}

/* 
A função "item_get_dados", cujo retorno é do tipo ponteiro void (void *), tem o papel de acessar o campo 'dado' dentro da struct de um
item recebido como parâmetro: 
01) Caso o item seja nulo, ou seja, não tenha ocorrido corretamente a alocação dinâmica, retorna NULL
02) Caso o item não seja nulo, ou seja, tenha ocorrido corretamente a alocação dinâmica, a função retorna o ponteiro para o 'dado' do item
recebido.
Complexidade: O(1)
*/
void *item_get_dados (ITEM *item){
    // Verifica se o item existe.
    if(item != NULL){
        // Retorna o campo 'dado', da struct ITEM.
        return(item->dado);
    }
    // Se o item não existe, retorna NULL.
    return(NULL);
}

