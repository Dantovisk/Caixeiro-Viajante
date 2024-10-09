#include <stdio.h>
#include <stdlib.h>
#include "deque.h"
#include "lista.h"
#include "item.h"

#define INF 100000007

// Calcularemos como se a cidade inicial fosse a 1, pois isso não altera o resultado do caixeiro.
// Depois de calcularmos podemos deslocar a ordem do trajeto como desejado.

void caixeiro(int n, LISTA *adj[25], int inicio){

    int **dp = (int**)malloc(sizeof(int*) *(n+1));
    for(int i=0; i<=n; i++){
        dp[i] = (int*)malloc(sizeof(int) * (1<<n));
    }

    DEQUE ***v = (DEQUE***)malloc(sizeof(DEQUE**) * (n+1));
    for(int i=0; i<=n; i++){
        v[i] = (DEQUE**)malloc(sizeof(DEQUE*) * (1<<n));
    }

    // Inicializando as máscaras e os deques
    for (int bm = 1; bm < (1 << n); bm++) {
        for (int i = 1; i <= n; i++) {
            dp[i][bm] = INF;
            v[i][bm] = deque_criar();
        }
    }
    dp[1][1] = 0;
    ITEM* item_inicial = item_criar(1, NULL);
    deque_inserir_fim(v[1][1], item_inicial);


    for (int bm = 1; bm < (1 << n); bm++) { // Iterando por todas as máscaras
        for (int i = 1; i <= n; i++) {      // Iterando pelas ultimas cidades
            // Verifica se a cidade i já foi visitada na bitmask bm, se não for
            // então o caminho é inválido
            if (!((1 << (i - 1)) & bm)) continue;

            //verifica se o caminho existe (é diferente de infinito)
            if (dp[i][bm] >= INF) continue;
            
            for (int j = 1; j<=n; j++) {
                ITEM *it = lista_item(adj[i], j);
                if(it == NULL) continue;

                int k = item_get_chave(it);
                int w = *((int*)item_get_dados(it));

                int mask = (1 << (k - 1));
                if (!(mask & bm)) {
                    if (dp[k][bm | mask] > dp[i][bm] + w) {
                        dp[k][bm | mask] = dp[i][bm] + w;

                        copiar_deque(v[i][bm], v[k][bm | mask]);

                        // Adiciona o novo ponto k
                        ITEM* novo_item = item_criar(k, NULL);
                        deque_inserir_fim(v[k][bm | mask], novo_item);
                    }
                }
            }
        }
    }

    int resp = INF;
    int minInd = 2;

    // como calculamos o trajeto sem contar o caminho da cidade final até a cidade 1, precisamos somar esse
    // Valor nos resultados.
    // O fato de não termos calculado isso acima faz com que precisemos calcular apenas metade das iterações


    for (int i = 2; i <= n; i++) {
        for (int j = 1; j<=n; j++) {
            ITEM *it = lista_item(adj[i], j);
            if(it == NULL) continue;
            int k = item_get_chave(it);
            int w = *((int*)item_get_dados(it));

            if(k!= 1) continue;

            if (resp > dp[i][(1 << n) - 1] + w) {
                resp = dp[i][(1 << n) - 1] + w;
                minInd = i;
            }
        }
    }

    //significa q nao achou
    if(resp >= INF) {
        printf("IMPOSSIVEL!");
        return;
    }

    printf("%d\n", resp);

    DEQUE* resultado = v[minInd][(1 << n) - 1];
    
    int tam = deque_contar(resultado);

    //shift na deque para garantir que o trajeto começe na cidade de origem
    while(item_get_chave(deque_primeiro(resultado)) != inicio){
        ITEM* item = deque_remover_inicio(resultado);
        deque_inserir_fim(resultado, item);
    }

   printf("%d", inicio);
    for (int i = 0; i < tam; i++) {
        //remover do fim pois o array está invertido
        ITEM* item = deque_remover_fim(resultado);
        printf("->%d", item_get_chave(item));
        item_apagar(&item);
    }
    printf("\n");

    // Libera a memória dos deques
    for (int bm = 1; bm < (1 << n); bm++) {
        for (int i = 1; i <= n; i++) {
            deque_apagar(&v[i][bm]);
        }
    }

    for(int i=0; i<=n; i++){
        free(dp[i]);
        free(v[i]);
    }
    free(dp);
    free(v);

}

int main() {//esse programa comporta entradas de até n<=19
    int n, inputs, inicio;
    LISTA *adj[25];

    scanf("%d %d %d", &n, &inicio, &inputs);

    for(int i=0; i<=n; i++) adj[i] = lista_criar(true);

    for (int i = 0; i < inputs; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        int *p1 = (int*)malloc(sizeof(int));
        int *p2 = (int*)malloc(sizeof(int));
        *p1 = c;
        *p2 = c;
        ITEM *it1 = item_criar(b, p1), *it2 = item_criar(a, p2);
        lista_inserir(adj[a], it1);
        lista_inserir(adj[b], it2);
        //lista_inserir_node(adj[a], c, b);
        //lista_inserir_node(adj[b], c, a);
    }

    caixeiro(n, adj, inicio);

    for(int i=0; i<=n; i++) lista_apagar(&adj[i]);

    return 0;
}

/*
Entrada:
4
2
6
1 2 2
1 3 6
1 4 8
2 3 3
2 4 5
3 4 7

Saida:
20
2->3->4->1->2
*/
