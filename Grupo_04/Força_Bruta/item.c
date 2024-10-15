#include <stdio.h>
#include <stdlib.h>
#include "item.h"

/* Declaração da estrutura item, que serve para generalizar o tipo de dado das estruturas de dado a partir do ponteiro void.
 * chave: Um inteiro que representa a chave do item.
 * dado: Um ponteiro genérico que contém os dados associados ao item. */
typedef struct item_{
    int chave;
    void *dado;
} DADO;

/* A função "item_criar" tem o papel de criar a estrutura de um item, alocando a sua memória dinamicamente e
inicializando os campos da struct ITEM.
 * Em caso de erro na alocação de memória, apenas retorna NULL sem mudar os campos da struct.
 * Em caso de sucesso na alocação de memória, a partir dos parâmetros da função, a chave e o dado recebidos são colocados dentro do item 
criado e a função retorna um ponteiro para este item 
 * Complexidade: O(1) */
ITEM *item_criar (int chave, void *comp){
    ITEM *item = NULL;
    item = (ITEM *) malloc(sizeof(ITEM));
    
    if(item != NULL){
        item->chave = chave;
        item->dado = comp;
    }

    return(item);
}

/* A função "item_apagar", recebe o endereço de um item e libera a memória alocada de cada item da estrutura e, por fim,
libera o espaço alocado para a estrutura do item.
 * Caso o item seja nulo, ou seja, não tenha ocorrido corretamente a alocação dinâmica, o retorno é FALSO
 * Caso o item não seja nulo, ou seja, tenha ocorrido corretamente a alocação dinâmica, o retorno é VERDADEIRO
 * Complexidade: O(1) */
bool item_apagar (ITEM **item){
    if(*item != NULL){

        // Se o dado do item for diferente de nulo, libera-se sua memória
        if((*item)->dado != NULL){
            free((*item)->dado);
            (*item)->dado = NULL;
        }

        // Libera-se a memória
        free(*item);
        *item = NULL;
        return(true);
    }
    return(false);
}

/* A função "item_get_chave" recebe um item e retorna sua chave. 
 * Caso o item seja nulo, ou seja, não tenha ocorrido corretamente a alocação dinâmica, o programa se encerra, pois se está querendo 
acessar o campo de um item que não foi alocado devidamente.
 * Caso o item não seja nulo, ou seja, tenha ocorrido corretamente a alocação dinâmica, a função retorna a 'chave' do item recebido.
Complexidade: O(1) */
int item_get_chave (ITEM *item){
    // Verificação se o item não é nulo
    if(item != NULL) {
        return(item->chave);
    }

    exit(1);
}

/* A função "item_set_chave" recebe um item e um inteiro chave, alterando a chave atual do item para a nova e retornando se a operação
foi bem sucedida.
 * Caso o item seja nulo, ou seja, não tenha ocorrido corretamente a alocação dinâmica, o retorno é FALSO
 * Caso o item não seja nulo, ou seja, tenha ocorrido corretamente a alocação dinâmica, a chave é alterada e o retorno é VERDADEIRO
 * Complexidade: O(1). */
bool item_set_chave (ITEM *item, int chave){
    // Verificação se o item não é nulo
    if(item != NULL){
        item->chave = chave;
        return(true);
    }
    return(false);
}

/* A função "item_get_chave" recebe um item e retorna sua chave. 
 * Caso o item seja nulo, ou seja, não tenha ocorrido corretamente a alocação dinâmica, retorna NULL
 * Caso o item não seja nulo, ou seja, tenha ocorrido corretamente a alocação dinâmica, a função retorna o ponteiro para o 'dado' 
do item recebido.
 * Complexidade: O(1) */
void *item_get_dados (ITEM *item){
    // Verifica se o item existe.
    if(item != NULL){
        return(item->dado);
    }
    return(NULL);
}

