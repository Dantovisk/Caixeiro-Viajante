#include <stdio.h>
#include <stdlib.h>
#include "Deque.h"

void permuta(DEQUE *aux, DEQUE *d){
    if(deque_contar(aux) == 1){
        deque_inserir_fim(d, deque_remover_inicio(aux));
        deque_printar(d);
        printf("\n");
        deque_inserir_fim(aux, deque_remover_fim(d));
        return;
    }

    int tam = deque_contar(aux);
    for(int i = 0; i < tam; i++){
        deque_inserir_fim(d, deque_remover_inicio(aux));
        permuta(aux, d);
        deque_inserir_fim(aux, deque_remover_fim(d));
    }

    return;
}

int main(void){
    DEQUE *d = deque_criar();
    DEQUE *aux = deque_criar();

    for(int i=0; i < 3; i++){
        deque_inserir_fim(aux, item_criar('A'+i, NULL));
    }

    // deque_printar(aux);

    permuta(aux, d);
}
