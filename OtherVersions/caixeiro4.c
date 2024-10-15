#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
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

int calculaDistancia(int c1, int c2, LISTA **adj){
    ITEM *it = lista_item(adj[c1 - 1], c2 - 1);
    if(it != NULL)
        return *(int *) item_get_dados(it);

    return -1;
}

void calculaCaminho(DEQUE *aux, CAMINHO *local, CAMINHO *global, LISTA **adj, int c_inicio){
    int tam = deque_contar(aux);
    for(int i = 0; i < tam; i++){
        int n;
        if(!deque_vazia(local->deque))
            n = calculaDistancia(item_get_chave(deque_primeiro(aux)), item_get_chave(deque_ultimo(local->deque)), adj);
        else    
            n = calculaDistancia(item_get_chave(deque_primeiro(aux)), c_inicio, adj);

        if(n == -1)
            return;
        local->distancia += n;

        deque_inserir_fim(local->deque, deque_remover_inicio(aux));

        if(tam == 1){
            int m = calculaDistancia(c_inicio, item_get_chave(deque_ultimo(local->deque)), adj);
            if(m == -1)
                return;
            local->distancia += m;

            if(local->distancia < global->distancia || global->distancia == 0){
                // printf("oi %d\n", global->distancia);
                // deque_printar(global->deque);
                global->distancia = local->distancia;
                // printf("oi %d\n", global->distancia);
                copiar_deque(local->deque, global->deque);
                // deque_printar(local->deque);
            }

           local->distancia -= m;
        } else
            calculaCaminho(aux, local, global, adj, c_inicio);

        deque_inserir_fim(aux, deque_remover_fim(local->deque));

        local->distancia -= n;
    }

    return;
}

int main(void){
    int n, c_inicio, arestas;
    scanf("%d", &n);
    scanf("%d", &c_inicio);
    scanf("%d", &arestas);

    LISTA **adj = (LISTA **) malloc(sizeof(LISTA *) * n);
    for(int i = 0; i < n; i++)
        adj[i] = lista_criar(true);

    int c1, c2;
    for(int i = 0; i < arestas; i++){
        int *dist1 = (int *) malloc(sizeof(int));
        scanf("%d %d %d", &c1, &c2, dist1);
        int *dist2 = (int *) malloc(sizeof(int));
        *dist2 = *dist1;
        lista_inserir(adj[c1-1], item_criar(c2-1, dist1));
        lista_inserir(adj[c2-1], item_criar(c1-1, dist2));
    }

    CAMINHO *global = (CAMINHO *) malloc(sizeof(CAMINHO));
    global->deque = deque_criar();
    global->distancia = 0;

    CAMINHO *local = (CAMINHO *) malloc(sizeof(CAMINHO));
    local->deque = deque_criar();
    local->distancia = 0;

    DEQUE *aux = deque_criar();
    for(int i = 0; i < n; i++){
        if(i == c_inicio-1)
            continue;
        deque_inserir_fim(aux, item_criar(i+1, NULL));
    }
    // deque_printar(aux);
    Timer timer;
    start_timer(&timer);
    calculaCaminho(aux, local, global, adj, c_inicio);
    printf("%lf\n", stop_timer(&timer));

    //

    printf("-------------------------------------\n");
    printf("Origem: %d\n", c_inicio);
    printf("Distância: %d\n", global->distancia);
    printf("-------------------------------------\n");
    printf("+ Caminho\n");
    printf("%d - ", c_inicio);

    ITEM *it;
    while(deque_contar(global->deque) != 0){
        it = deque_remover_inicio(global->deque);
        printf("%d - ", item_get_chave(it));
        item_apagar(&it);
    }

    printf("%d\n", c_inicio);
    printf("-------------------------------------\n");
    

    //
    deque_apagar(&(global->deque));
    deque_apagar(&(local->deque));
    deque_apagar(&aux);

    free(local);
    local = NULL;
    free(global);
    global = NULL;

    for(int i = 0; i < n; i++){
        lista_apagar(&adj[i]);
    }

    free(adj);
    adj = NULL;

    return 0;
}