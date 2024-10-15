#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Deque.h"
#include "lista.h"
#include <time.h>

typedef struct {
    clock_t start;
    clock_t end;
} Timer;

void start_timer(Timer *timer) {
    timer->start = clock();
}

double stop_timer(Timer *timer) {
    timer->end = clock();
    return ((double) (timer->end - timer->start)) / CLOCKS_PER_SEC;
}

typedef struct{
    DEQUE *deque;
    int distancia;
} CAMINHO;

void calculaCaminho(DEQUE *aux, CAMINHO *local, CAMINHO *global, int **adj){
    int tam = deque_contar(aux);
    for(int i = 0; i < tam; i++){
        if(!deque_vazia(local->deque)) local->distancia += adj[item_get_chave(deque_ultimo(local->deque))-1][item_get_chave(deque_ultimo(aux))-1];

        deque_inserir_fim(local->deque, deque_remover_inicio(aux));

        if(tam == 1){
            local->distancia += adj[item_get_chave(deque_ultimo(local->deque))-1][item_get_chave(deque_primeiro(local->deque))-1];

            if(local->distancia < global->distancia || global->distancia == 0){
                global->distancia = local->distancia;
                copiar_deque(local->deque, global->deque);
            }

           local->distancia -= adj[item_get_chave(deque_ultimo(local->deque))-1][item_get_chave(deque_primeiro(local->deque))-1];
        } else
            calculaCaminho(aux, local, global, adj);

        deque_inserir_fim(aux, deque_remover_fim(local->deque));

        if(!deque_vazia(local->deque)) local->distancia -= adj[item_get_chave(deque_ultimo(local->deque))-1][item_get_chave(deque_ultimo(aux))-1];
    }

    return;
}

int main(void){
    int n;
    scanf("%d", &n);
    int tot = (n * (n - 1)) / 2;

    int **adj = (int **) malloc(sizeof(int *) * n);
    adj[0] = (int *) malloc(sizeof(int) * n * n);

    for(int i = 1; i < n; i++)
        adj[i] = adj[0] + i * n;

    for(int i = 0; i < tot; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        adj[a-1][b-1] = c;
        adj[b-1][a-1] = c;
    }

    CAMINHO *global = (CAMINHO *) malloc(sizeof(CAMINHO));
    global->deque = deque_criar();
    global->distancia = 0;

    CAMINHO *local = (CAMINHO *) malloc(sizeof(CAMINHO));
    local->deque = deque_criar();
    local->distancia = 0;

    DEQUE *aux = deque_criar();
    for(int i = 0; i < n; i++){
        deque_inserir_fim(aux, item_criar(i+1, NULL));
    }
    
    calculaCaminho(aux, local, global, adj);

    //

    printf("-------------------------------------\n");
    ITEM *it = deque_primeiro(global->deque);
    printf("Origem: %d\n", item_get_chave(it));
    printf("Distância: %d\n", global->distancia);
    printf("-------------------------------------\n");
    printf("+ Caminho\n");
    while(deque_contar(global->deque) != 0){
        printf("%d - ", item_get_chave(deque_remover_inicio(global->deque)));
    }
    printf("%d \n", item_get_chave(it));
    printf("-------------------------------------\n");
    

    //
    deque_apagar(&(global->deque));
    deque_apagar(&(local->deque));
    deque_apagar(&aux);
    free(local);
    free(global);
    free(adj[0]);
    free(adj);

    return 0;
}