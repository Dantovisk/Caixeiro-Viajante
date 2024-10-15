#include <stdio.h>
#include <stdlib.h>
#include "Deque.h"

typedef struct deque_{
    ITEM *itens[MAX_TAMANHO];
    int tamanho;
    int inicio;
    int fim;
} DEQUE;

DEQUE* deque_criar(){
    DEQUE *deque = (DEQUE *) malloc(sizeof(DEQUE));

    if(deque != NULL){
        deque->tamanho = 0;
        deque->inicio = 0;
        deque->fim = 0;
    }

    return deque;
}

void deque_apagar(DEQUE** deque){
    if(*deque != NULL){
        ITEM *it;
        while(!deque_vazia(*deque)){
            it = deque_remover_fim(*deque);
            item_apagar(&it);
        }
            
        free(*deque);
        *deque = NULL;
    }

    return;
}

bool deque_inserir_inicio(DEQUE* deque, ITEM* item){
    if(!deque_cheia(deque)){
        deque->inicio = (deque->inicio - 1 + MAX_TAMANHO) % MAX_TAMANHO;
        deque->itens[deque->inicio] = item;
        deque->tamanho++;
        return true;
    }

    return false;
}

bool deque_inserir_fim(DEQUE* deque, ITEM* item){
    if(!deque_cheia(deque)){
        deque->itens[deque->fim] = item;
        deque->fim = (deque->fim + 1) % MAX_TAMANHO;
        deque->tamanho++;
        return true;
    }

    return false;
}

ITEM* deque_remover_inicio(DEQUE* deque){
    if(!deque_vazia(deque)){
        ITEM *it = deque->itens[deque->inicio];
        deque->inicio = (deque->inicio + 1) % MAX_TAMANHO;
        deque->tamanho--;
        
        return it;
    }

    return NULL;
}

ITEM* deque_remover_fim(DEQUE* deque){
    if(!deque_vazia(deque)){
        deque->fim = (deque->fim - 1 + MAX_TAMANHO) % MAX_TAMANHO;
        ITEM *it = deque->itens[deque->fim];
        deque->tamanho--;

        return it;
    }

    return NULL;
}

ITEM* deque_primeiro(DEQUE* deque){
    if(!deque_vazia(deque)){
        ITEM *it = deque->itens[deque->inicio % MAX_TAMANHO];
        return it;
    }
    return NULL;
}

ITEM* deque_ultimo(DEQUE* deque){
    if(!deque_vazia(deque)){
        ITEM *it = deque->itens[(deque->fim - 1 + MAX_TAMANHO) % MAX_TAMANHO];
        return it;
    }
    return NULL;
}

int deque_contar(DEQUE* deque){
    if(deque != NULL)
        return deque->tamanho;

    return ERRO;
}

bool deque_vazia(DEQUE* deque){
    if(deque != NULL)
        return deque->tamanho == 0;

    return true;
}

bool deque_cheia(DEQUE* deque){
    if(deque != NULL)
        return deque->tamanho == MAX_TAMANHO;

    return true;
}

void deque_printar(DEQUE *deque){
    if(deque != NULL){
        int i = deque->inicio;
        for(int j = 0; j < deque->tamanho; j++){
            printf("%d", item_get_chave(deque->itens[i]));
            i = (i + 1) % MAX_TAMANHO;
        }
        printf("\n");
    }
    
    return;
}

// Função para copiar os elementos de um deque para outro
void copiar_deque(DEQUE* origem, DEQUE* destino) {
    // Verificar se os deques são válidos
    if (!origem || !destino) {
        return;
    }

    while(!deque_vazia(destino)){
        ITEM *item = deque_remover_inicio(destino);
        item_apagar(&item);
    }

    // Cria uma cópia temporária para iterar sobre o deque sem removê-los
    DEQUE* temp = deque_criar();
    ITEM* item;

    // Itera sobre o deque original e copia os itens para o deque destino
    while (!deque_vazia(origem)) {
        item = deque_remover_inicio(origem);
        ITEM* novoItem = item_criar(item_get_chave(item), item_get_dados(item));
        deque_inserir_fim(destino, novoItem);  // Insere no deque destino
        deque_inserir_fim(temp, item);     // Armazena temporariamente no deque auxiliar
    }

    // Restaurar o deque original
    while (!deque_vazia(temp)) {
        item = deque_remover_inicio(temp);
        deque_inserir_fim(origem, item);   // Insere de volta no deque original
    }

    // Libera o deque temporário
    deque_apagar(&temp);

    return;
}
