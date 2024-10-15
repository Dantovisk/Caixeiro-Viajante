/* Grupo 4 - SCC0202 - Algoritmos e Estruturas de Dados I - Projeto 1
 * Pedro Henrique de Sousa Prestes	  15507819
 * Dante Brito Lourenço	   	          15447326
 * João Gabriel Pieroli da Silva	  15678578
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "deque.h"
#include "lista.h"
#include <time.h>

/* ESTRUTURA TIMER: é utilizada para verificar o tempo de execução do código 
 * A função "start_timer" é responsável por setar o tempo em que o programa iniciou, no campo da struct Timer (clock_t start), iniciando o temporizador e
armazenando o tempo atual na variável 'start'. 
 * A função "stop_timer" é responsável por interromper o temporizador e armazenar o tempo atual logo que o programa foi concluído
na variável 'end', que faz parte do campo da struct Timer (clock_t end). Desse modo, é feito o cálculo da variação e conversão disso para segundos. */
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

/* A estrutura CAMINHO armazena as informações de um dado caminho, guardando a ordem das cidades e a distância do trajeto.
A estrutura possui dois campos:
 * DEQUE *deque: uma estrutura de deque para armazenar a ordem/sequência das cidades do trajeto.
 * int distancia: um inteiro que guarda a distância do trajeto em questão. */
typedef struct{
    DEQUE *deque;
    int distancia;
} CAMINHO;

/* A função "calculaDistancia" recebe duas cidades (ints) c1 e c2 e acessa a lista de adjacência de uma delas (c1) e procurando um item 
a partir da chave do valor de c2, retornando o dado do item que corresponde à distância entre ambas. Caso não haja conexão entre as duas cidades, 
retorna -1 indicando falha no cálculo de distância. 
 * COMPLEXIDADE: O(log n) */
int calculaDistancia(int c1, int c2, LISTA **adj){
    ITEM *it = lista_item(adj[c1 - 1], c2 - 1);
    if(it != NULL)
        return *(int *) item_get_dados(it);

    return -1;
}

/* A função "caixeiroSolver" é a responsável por resolver o problema em si do caixeiro viajante:
 * Recebe um deque auxiliar (aux) com itens que representam a sequência de cidades que vão ser permutadas. O CAMINHO local armazena o trajeto e a
distância de cada uma das possibilidades possíveis de rota, já o CAMINHO global sempre vai armazenar o melhor CAMINHO calculado até àquele momento, sendo
responsável por armazenar a menor rota após o término da função. O vetor de LISTAS adj representa as listas de adjacência de cada uma das cidades e o int
c_inicio é a cidade de origem e destino da rota, já que ela tem posição fixa e por isso não é permutada com as outras.
 * Não há retorno, mas as informações mais importantes serão mantidas dentro do CAMINHO global.
 * COMPLEXIDADE: O((n-1)! * log n). */
void caixeiroSolver(DEQUE *aux, CAMINHO *local, CAMINHO *global, LISTA **adj, int c_inicio){
    int tam = deque_contar(aux); 
    int dist; // Variável que armazenará a distância entre duas cidades em uma dada iteração.

    /* Caso o auxiliar esteja vazio, indicando que um caminho completo foi calculado e representando o caso base da recursão, ele é
    copiado para o caminho global se ele for o menor caminho calculado até o momento. */
    if(tam == 0){
        // Calcula a distância entre a última cidade permutada e a cidade de início, completando o ciclo.
        dist = calculaDistancia(c_inicio, item_get_chave(deque_ultimo(local->deque)), adj);

        // Desconsidera o caminho caso não existe a ligação final.
        if(dist == -1)
            return;

        local->distancia += dist;

        // Se a distância local for menor que a global (menor até o momento) ou é o primeiro caminho calculado, ela é copiada para ser a nova menor.
        if(local->distancia < global->distancia || global->distancia == 0){
            global->distancia = local->distancia;
            deque_copiar(local->deque, global->deque);
        }

        local->distancia -= dist;

        return;
    }

    // O tamanho do auxiliar indica as permutações seguintes, já que ele diminui a cada chamada da função (fatorial). 
    for(int i = 0; i < tam; i++){
        // No caso de ser a primeira cidade a ser inserida, ela é ligada com a c_inicio, se não for o caso, ela é ligada com a próxima a ser adicionada.
        if(!deque_vazia(local->deque))
            dist = calculaDistancia(item_get_chave(deque_primeiro(aux)), item_get_chave(deque_ultimo(local->deque)), adj);
        else    
            dist = calculaDistancia(item_get_chave(deque_primeiro(aux)), c_inicio, adj);
        
        // Desconsidera o caminho caso não exista tal ligação, tentando outra cidade.
        if(dist == -1){
            deque_inserir_fim(aux, deque_remover_inicio(aux));    
            continue;
        }

        /* A distância é somada e a cidade é adicionada ao caminho local. A cidade é removida e sua distância subtraída durante 
        "a volta" para o cálculo de outra possibilidade. */
        local->distancia += dist;

        deque_inserir_fim(local->deque, deque_remover_inicio(aux));
        caixeiroSolver(aux, local, global, adj, c_inicio);
        deque_inserir_fim(aux, deque_remover_fim(local->deque));

        local->distancia -= dist;
    }

    return;
}

/* A função "entrada_de_dados", cujo retorno é do tipo LISTA **, tem o objetivo de receber todos os dados fornecidos pelo usuário, 
'n_cidades' (Número de cidades), 'c_inicio' (Cidade de início), 'arestas (indica quantas arestas existem), retornando o vetor de listas 
de adjacência que armazena todas as distâncias entre as cidades. 
 * COMPLEXIDADE: O(n^2) */
LISTA **entrada_de_dados(int *n_cidades, int *c_inicio) {
    int arestas;
    scanf("%d", n_cidades);
    scanf("%d", c_inicio);
    scanf("%d", &arestas);

    // Alocação do vetor de listas e criação de uma lista de adjacência para cada cidade.
    LISTA **adj = (LISTA **) malloc(sizeof(LISTA *) * (*n_cidades));
    for(int i = 0; i < (*n_cidades); i++) {
        adj[i] = lista_criar();
    }

    /* Leitura de todas as arestas (cidade1 - cidade2 - distância)
     * Variáveis 'c1' e 'c2' armazenam a cidade;
     * Distâncias são armazenadas em ponteiros dinâmicos para serem usadas como dados nos itens; */
    int c1, c2;
    for(int i = 0; i < arestas; i++){
        int *dist1 = (int *) malloc(sizeof(int));

        scanf("%d %d %d", &c1, &c2, dist1);

        // Copia o conteúdo do ponteiro dist1 para dist2, para criação de itens diferentes nas listas.
        int *dist2 = (int *) malloc(sizeof(int));
        *dist2 = *dist1;

        // Cria o item, com a distância recebida, na posição respectiva posição destinada da cidade 1 com a cidade 2
        lista_inserir(adj[c1-1], item_criar(c2-1, dist1));
        // Cria o item, com a distância recebida, na posição respectiva posição destinada da cidade 2 com a cidade 1 (O caminho inverso também deve ser o mesmo)
        lista_inserir(adj[c2-1], item_criar(c1-1, dist2));
    }

    return adj; // Retorna o vetor de listas.
}

/* A função "caminho_criar" tem o objetivo de criar uma struct CAMINHO, alocando memória para ela e para seu campo, caminho->deque,
inicializando a distância como 0.
 * Se a alocação correr bem, aloca memória também para o deque, campo da struct CAMINHO, e inicializa a distância como 0.
 * Complexidade: O(1). */
CAMINHO *caminho_criar() {
    // É alocada a memória da struct CAMINHO em si
    CAMINHO *caminho = (CAMINHO *) malloc(sizeof(CAMINHO));

    // Verifica se a alocação deu certo
    if(caminho == NULL) {
        printf("Erro na alocação de caminho");
        exit(1);
    }

    // É alocada a memória do deque que fica dentro da struct CAMINHO.
    caminho->deque = deque_criar();

    // O campo caminho->distancia, da struct CAMINHO, é inicializado como 0
    caminho->distancia = 0;

    return caminho;
}


int main(void){
    int n_cidades, c_inicio; // Número de cidades e cidade de início.

    /* A função auxiliar "entrada_de_dados" é chamada para cuidar de todas as entradas de dados fornecidos pelo usuário,
    retornando a matriz LISTA de adjacência que representa as conexões entre as cidades e suas distâncias. */
    LISTA **adj = entrada_de_dados(&n_cidades, &c_inicio);
    
    /* Inicialização:
     * CAMINHO de caráter global, que armazenará o menor caminho encontrado pelo algoritmo;
     * CAMINHO de caráter local, usado para testar diferentes combinações de cidades durante o cálculo do caminho. */
    CAMINHO *global = caminho_criar();
    CAMINHO *local = caminho_criar();

    // Criação de um deque auxiliar para armazenar as cidades que ainda precisam ser visitadas pelo caixeiro, lidando com as permutações.
    DEQUE *aux = deque_criar();

    /* Preenchimento do deque auxiliar com o número de todas as cidades a serem visitadas (exceto a cidade de início), pois apresenta posição fixa
    e não precisa ser permutada.
     * COMPLEXIDADE: O(N) */
    for(int i = 0; i < n_cidades; i++){
        // A cidade inicial, fornecida pelo usuário, deve ser ignorada, pois o caixeiro parte dela e retorna a ela.
        if(i == c_inicio - 1) {
            // Se a cidade atual for a cidade de início, passa para a próxima iteração.
            continue;
        }
        // As outras cidades (excluindo a cidade inicial) são inseridas no final do deque.
        deque_inserir_fim(aux, item_criar(i + 1, NULL));
    }

    // Declaração da struct Timer, que será usada para medir o tempo gasto pelo algoritmo ao calcular o caminho mínimo.
    Timer timer;
    start_timer(&timer);

    /* Chama a função "caixeiroSolver" para resolver o problema do caixeiro viajante, encontrando o menor caminho possível
    que percorre todas as cidades e retorna à cidade inicial. */
    caixeiroSolver(aux, local, global, adj, c_inicio);

    // Após o cálculo, para o temporizador e imprime o tempo total gasto para resolver o problema.
    printf("%lf\n", stop_timer(&timer));

    /* Imprime as informações referentes à composição e resolução do problema, caso ele tenha achado pelo menos um caminho. 
     * Caso contrário, printa que a resolução é impossível. */
    if(global->distancia == 0){
        printf("-------------------------------------\n");
        printf("A resolução é impossível\n");
        printf("-------------------------------------\n");
    } else{
        printf("-------------------------------------\n");
        printf("Origem: %d\n", c_inicio);
        printf("Distância: %d\n", global->distancia);
        printf("-------------------------------------\n");
        printf("+ Caminho\n");
        printf("%d - ", c_inicio);
        
        /* O laço 'while' percorre todos os itens do deque global (que contém o menor caminho encontrado) e os imprime com o
        auxílio da variável ITEM *it. 
         * COMPLEXIDADE: O(N) */
        ITEM *it;  // Imprime a cidade inicial para depois imprimir o restante da rota
        while(deque_contar(global->deque) != 0){
            it = deque_remover_inicio(global->deque);
            printf("%d - ", item_get_chave(it));
            item_apagar(&it); // Não há mais utilidade para os itens que representam cidades após a impressão do resultado.
        }

        printf("%d\n", c_inicio); // Imprime a cidade inicial novamente, indicando o fechamento do ciclo.
        printf("-------------------------------------\n");
    }

    // Libera a memória das estruturas criadas ao longo do código
    deque_apagar(&(global->deque));
    deque_apagar(&(local->deque));
    deque_apagar(&aux);

    free(local);
    local = NULL;
    free(global);
    global = NULL;
    
    // Libera a memória da lista de adjacências (cada linha do vetor de listas representa uma cidade e suas conexões).
    for(int i = 0; i < n_cidades; i++){
        lista_apagar(&adj[i]);
    }

    free(adj);
    adj = NULL;

    return 0;
}
