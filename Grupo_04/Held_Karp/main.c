#include <stdio.h>   // Biblioteca padrão de entrada e saída
#include <stdlib.h>  // Biblioteca padrão para alocação dinâmica de memória
#include "deque.h"   // Inclui funções para manipulação de deques
#include "lista.h"   // Inclui funções para manipulação de listas de adjacência

// Define um valor constante, como se fosse um "infinito" para inicialização de distâncias
#define INF 100000007  

// Função principal para resolver o problema do Caixeiro Viajante
void caixeiro(int n, LISTA *adj[25], int inicio) {

    // --- ALOCAÇÃO DE MEMÓRIA ---

    // Alocação de memória para a tabela DP (n+1) x (2^n)
    int **dp = (int**)malloc(sizeof(int*)*(n+1));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc(sizeof(int) * (1 << n));  
    }

    // Aloca memória para os deques que armazenarão os caminhos
    DEQUE ***paths = (DEQUE***)malloc(sizeof(DEQUE**) * (n+1));

    // O laço 'for' percorre cada uma das linhas do vetor de ponteiros duplos para DEQUE criado
    for (int i = 0; i <= n; i++) {
        paths[i] = (DEQUE**)malloc(sizeof(DEQUE*) * (1 << n));  
    }

    // --- INICIALIZAÇÃO DE TODAS AS MÁSCARAS E DEQUES ---   

    // Itera sobre todas as combinações de cidades
    for (int bm = 1; bm < (1 << n); bm++) {  

        // Itera sobre as 'n' cidades
        for (int i = 1; i <= n; i++) {

            // Inicializa todas as distâncias como infinito
            dp[i][bm] = INF;  

            // Cria um deque vazio para armazenar o caminho
            paths[i][bm] = deque_criar();  
        }
    }

    // A distância para chegar à cidade 1 quando apenas ela foi visitada é 0
    dp[1][1] = 0;
    
    // Cria um item representando a cidade 1 e o insere no deque correspondente
    ITEM* item_inicial = item_criar(1, NULL); 

    // Insere no deque correspondente à cidade 1 e bitmask 1
    deque_inserir_fim(paths[1][1], item_inicial); 

    // --- ITERA SOBRE TODAS AS COMBINAÇÕES POSSÍVEIS DE CIDADES VISITADAS (BITMASK) (2^N)*(N^2) ---

    // Itera sobre todas as máscaras
    for (int bm = 1; bm < (1 << n); bm++) {  

        // Itera sobre as cidades atuais como destino
        for (int i = 1; i <= n; i++) {  

            // Verifica se a cidade i foi visitada na bitmask, se sim, pula
            if (!((1 << (i - 1)) & bm)) continue; 

            // Se o caminho para a cidade i com essa bitmask for infinito, pula
            if (dp[i][bm] >= INF) continue;  

            // Itera sobre as possíveis cidades vizinhas da cidade i
            for (int j = 1; j <= n; j++) {

                // A variável 'it' do tipo ITEM recebe o item da lista de adjacência da cidade i, na posição j
                ITEM *it = lista_item(adj[i], j);  

                // Se não houver conexão, continua para o próximo vizinho
                if (it == NULL) continue;  

                // A variável 'k' recebe a chave (cidade) do item
                int k = item_get_chave(it);  

                // A variável 'w' recebe o peso (distância) entre as cidades
                int w = *((int*)item_get_dados(it));  

                // Cria a máscara para a cidade k
                int mask = (1 << (k - 1));  

                // Verifica se a cidade k ainda não foi visitada na bitmask atual
                if (!(mask & bm)) {  

                    // Se o novo caminho for mais curto
                    if (dp[k][bm | mask] > dp[i][bm] + w) {  

                        // Atualiza a distância mínima para a cidade k
                        dp[k][bm | mask] = dp[i][bm] + w; 

                        // Copia o caminho atual para o novo caminho
                        deque_copiar(paths[i][bm], paths[k][bm | mask]); 
                        
                        // Adiciona a cidade k ao caminho, criando um novo item para a cidade k
                        ITEM* novo_item = item_criar(k, NULL); 

                        // E o inserindo (a cidade k) no deque
                        deque_inserir_fim(paths[k][bm | mask], novo_item);  
                    }
                }
            }
        }
    }

    // Inicializa a resposta com infinito
    int resp = INF;  

    // Inicializa a cidade final como 2, pois sempre começamos em 1
    int minInd = 2;  

    // --- ITERA PARA ENCONTRAR A MENOR DISTÂNCIA PARA COMPLETAR O CICLO E VOLTAR À CIDADE 1 ---

    // Itera sobre as cidades
    for (int i = 2; i <= n; i++) {  

        // Itera sobre os vizinhos de cada cidade
        for (int j = 1; j <= n; j++) {  

            // A variável 'it' recebe o endereço do item da lista de adjacência na posição j
            ITEM *it = lista_item(adj[i], j);  
            
            // Se não houver conexão, continua
            if (it == NULL) continue; 

            // A variável inteira 'k' recebe (cidade) do vizinho
            int k = item_get_chave(it);  
            // A variável inteira 'w' recebe o peso (distância) entre as cidades
            int w = *((int*)item_get_dados(it));  

            // Só interessa o caminho que volta para a cidade 1
            if (k != 1) continue;  
            
            // Se um caminho menor é encontrado
            if (resp > dp[i][(1 << n) - 1] + w) {  

                // Atualiza a menor distância
                resp = dp[i][(1 << n) - 1] + w;  

                // Atualiza a cidade final do caminho
                minInd = i;  
            }
        }
    }

    // Verifica se encontramos um caminho válido (menor que infinito)
    if (resp >= INF) {

        // Se 'resp' ainda for igual ou maior que a constante INF, imprime "IMPOSSIVEL"
        printf("IMPOSSIVEL!");

        // Retorna porque não é possível traçar o caminho
        return;
    }

    // --- IMPRESSÃO DO MENOR TRAJETO E DAS CIDADES --- 

    // Se chegou aqui, significa que foi encontrado um caminho válido, então, a menor distância encontrada é impressa
    printf("Cidade Inicial: %d\n", inicio);  
    printf("Distancia minima: %d\n", resp);  

    // A variável 'resultado' do tipo DEQUE * recebe o endereço do deque de menor caminho
    DEQUE* resultado = paths[minInd][(1 << n) - 1];

    // A variável 'tam' recebe a quantidade de elementos do deque 'resultado'
    int tam = deque_contar(resultado);  

    // Ajusta o deque para garantir que o caminho comece na cidade de início, considerando que o deque é circular
    while (item_get_chave(deque_primeiro(resultado)) != inicio) {

        // Remove o item do início do deque
        ITEM* item = deque_remover_inicio(resultado); 

        // Insere o item no final, efetivamente fazendo um "shift" 
        deque_inserir_fim(resultado, item);  
    }

    // Imprime a cidade de início
    printf("%d", inicio);  

    // Itera sobre a quantidade de elementos do deque para imprimir o caminho, imprim
    for (int i = 0; i < tam; i++) {  

        // Remove o item do final do deque
        ITEM* item = deque_remover_fim(resultado);  

        // Imprime a cidade
        printf("->%d", item_get_chave(item));  

        // Depois de impressa a cidade, apaga o item para liberar memória
        item_apagar(&item);  
    }

    // Nova linha após o caminho impresso
    printf("\n");  

    // --- LIBERA A MEMÓRIA DOS DEQUES ---

    // Itera sobre todas as máscaras
    for (int bm = 1; bm < (1 << n); bm++) {  
        // Itera sobre todas as cidades
        for (int i = 1; i <= n; i++) {  
            // Apaga o deque correspondente
            deque_apagar(&paths[i][bm]);  
        }
    }

    // --- LIBERA A MEMÓRIA ALOCADA PARA DP E V ---

    // Itera sobre a quantidade de cidades
    for (int i = 0; i <= n; i++) {

        free(dp[i]);  
        free(paths[i]);  
    }

    free(dp);  
    free(paths);  
}

/* ESSE PROGRAMA COMPORTA ENTRADAS DE 2<=N<=19 */
int main() {

    int n, inputs, inicio;

    // Declaração da LISTA adjacência
    LISTA *adj[25];

    scanf("%d %d %d", &n, &inicio, &inputs);

    // Em cada uma das linhas de 'adj[i]' criando listas ordenadas.
    for(int i=0; i<=n; i++) adj[i] = lista_criar(true);

    // Faz 'inputs' iterações para realizar a leitura das informações
    for (int i = 0; i < inputs; i++) {
        // Declaração das variáveis 'a':cidade1, 'b':cidade2 e 'c':distanciaentreelas.
        int a, b, c;
        // Faz a leitura dos valores de 'a', 'b' e 'c'.
        scanf("%d %d %d", &a, &b, &c);
        // Alocação da memória para a variável 'c' (distância) que ficará armazenada em dado para adj[a].
        int *p1 = (int*)malloc(sizeof(int));
        // Alocação da memória para a variável 'c' (distância) que ficará armazenada em dado para adj[b].
        int *p2 = (int*)malloc(sizeof(int));
        // Faz ambos os conteúdos dos ponteiros serem o valor de 'c' (distância)
        *p1 = c;
        *p2 = c;

        // São criados dois novos itens: it1 com a cidade2 e a distância c, it2 com a cidade1 e a distância c
        ITEM *it1 = item_criar(b, p1), *it2 = item_criar(a, p2);
        // Insere-se na lista de adjacência, na posição refente a cidade1, it1(que tem a cidade2 e a distância
        // como dados)
        lista_inserir(adj[a], it1);
        // Insere-se na lista de adjacência, na posição refente a cidade2, it2(que tem a cidade1 e a distância
        // como dados)
        lista_inserir(adj[b], it2);
    }

    // A função caixeiro é chamada, a fim de resolver, calculando a menor distância entre as cidades
    caixeiro(n, adj, inicio);

    // É liberara a memória de todas as linhas da LISTA de adjascências.
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
Cidade Inicial: 2
Distancia minima: 20
2->3->4->1->2
*/
