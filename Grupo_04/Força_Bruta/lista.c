#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* Declaração da lista sequencial ordenada, uma estrutura que mantém seu conteúdo sempre ordenado ao inserir:
 * *itens[TAM_MAX]: Um vetor de ponteiros para 'ITEM', que armazena os elementos do lista. O tamanho máximo do vetor é definido pela
constante 'TAM_MAX'.
 * inicio: um inteiro que representa o índice do primeiro elemento no lista.
 * fim: um inteiro que representa o índice (a posição) do próximo espaço disponível, após o último elemento do lista.
 * tamanho: um inteiro que indica o número de itens armazenados no lista, valor que se atualiza conforme itens são inseridos ou removidos. */
typedef struct lista_{
    ITEM *itens[TAM_MAX];
    int inicio;
    int fim; // O PRÓXIMO ÍNDICE DISPONÍVEL
    int tamanho; // QNTD DE ELEMENTOS DO VETOR DE ITENS
} LISTA;

/* A função "lista_criar" tem o papel de criar a estrutura de uma lista, alocando a sua memória dinamicamente e
inicializando os campos da struct LISTA.
 * Em caso de erro na alocação de memória, apenas retorna NULL sem mudar os campos da struct.
 * Em caso de sucesso na alocação de memória, os campos 'tamanho', 'inicio' e 'fim' são inicializados como 0, para que se possa futuramente
operar com o vetor de itens 'ITEM* itens[MAX_TAMANHO]'. Assim, retorna-se um ponteiro para esta lista.
 * Complexidade: O(1). */
LISTA *lista_criar(void){
    LISTA *l = NULL;
    l = (LISTA *) malloc(sizeof(LISTA));

    // Verifica se a alocação foi bem sucedido.
    if(l != NULL){
        l->inicio = 0;
        l->fim = 0;
        l->tamanho = 0;
    }
    return l;
}

/* A função "lista_apagar", recebe o endereço de um lista e libera a memória alocada de cada item da estrutura e, por fim,
libera o espaço alocado para a estrutura do lista.
 * Caso o lista recebido seja nulo, ou seja, não tenha ocorrido corretamente a alocação dinâmica, nenhuma operação é realizada.
 * Caso o lista não seja nulo, ou seja, tenha ocorrido corretamente a alocação dinâmica, são liberados os itens e depois a estrutura em si.
 * Complexidade: O(n). O while precisa fazer a operação de remoção do item e liberação de memória N vezes. */
void lista_apagar(LISTA **lista) {
    if (lista == NULL || *lista == NULL)
        return;

    ITEM *it; // Declaração de um item auxiliar usado para apagar os itens do DEQUE.

    // O while continua até que não haja mais itens dentro do vetor.
    while(!lista_vazia(*lista)) {
        it = lista_remover(*lista, (*lista)->fim - 1);
        item_apagar(&it);
    }

    // Liberação da memória da estrutura.
    free(*lista);
    *lista = NULL;
    return;
}

/* A função "lista_busca" recebe uma lista e um valo (val) tendo como objetivo achar um item dentro da lista de chave igual a val.
 * É usado como função auxiliar da inserção e remoção, não sendo passada na interface.
 * Utiliza busca binária iterativa como modelo de busca, reduzindo o tamanho do raio de busca pela metade a cada iteração.
 * Retorna 'meio', caso ache um item com o mesmo valor
 * Retorna 'inf', o limite inferior da lista depois de realizada a busca, quando ele ultrapassar o limite superior 'sup'.
 * Complexidade: O(log n).*/
int lista_busca(LISTA *lista, int val){
    // Declara e inicializa a variável 'inf' como o limite inferior inicial da busca, isto é, o início da lista
    int inf = lista->inicio;
    // Declara e inicializa a variável 'sup' como o limite superior inicial da busca, isto é, o fim da lista
    int sup = lista->fim;
    int meio;

    // Inicia-se um laço while que só terá fim quando o limite inferior ultrapassar o limite superior
    while (inf < sup) {
        // A variável, a cada iteração do while, recebe o novo meio da busca, gerado pela média aritmética dos limites
        meio = (inf + sup) / 2;

        // Verifica-se, primeiramente, se o termo que ficou no meio tem o valor que se está buscando, retornando 'meio', caso sim.
        if (item_get_chave(lista->itens[meio]) == val) 
            return meio;

        // Caso contrário, é necessário verificar se o valor buscado é menor que o do termo central. Caso sim, o espaço de busca é reduzido
        // à metade, ao tornar o índice do meio o novo limite superior da busca
        else if (item_get_chave(lista->itens[meio]) > val)
            sup = meio;

        // Caso contrário, é notório que se está no caso em que o valor buscado é maior que o do termo central. Então, o espaço de busca é
        // reduzido à metade, ao tornar o índice do meio+1 o novo limite inferior da busca.
        else
            inf = meio + 1;
    }
    return inf;
}

/* A função "lista_inserir_posição" recebe uma lista, um valor de posição (pos) e um item, efetuando a inserção do item na lista da posição. 
 * A quantidade de deslocamentos a ser realizada é descrita por lista->fim - pos + 1.
 * Caso a lista não exista, esteja cheia ou a posição esteja fora dos limites da lista, retorna-se FALSO, indicando que não foi possível inserir na
posição.
 * Caso contrário, a lista existe, não está cheia e há algum espaço vago, é retornado VERDADEIRO após fazer a inserção na posição e os
deslocamentos necessários.
 * Complexidade: 0(n). No pior caso, a inserção acontece na primeira posição, sendo necessário deslocar todos os elementos. */
bool lista_inserir_posicao(LISTA *lista, int pos, ITEM *item){
    // Verifica se a lista existe e não está cheia e, a posição está dentro do limite da lista (0 a lista->fim são as únicas possíveis opções de inserção)
    if(!lista_cheia(lista) && pos >= 0 && pos <= lista->fim){
        // Faz o shit dos itens para liberar a posição que se deseja inserir.
        for(int i = lista->fim; i > pos; i--)                                                                                                                                                                                  
            lista->itens[i] = lista->itens[i-1];                                                                                                                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                 
        lista->itens[pos] = item; // A inserção acontece na posição ideal, mantendo a lista ainda ordenada                                                                                                                                                                                                          
        lista->fim++; // Como foi inserido um item, lista->fim é incrementada                                                                                                                                                                                                  
        lista->tamanho++; // Como foi inserido um item, lista->tamanho é incrementada                                                                                                                                                                                                         
        return true;                                                                                                                                                                                                                          
    }
    return false;                                                                                                                                                                                                                             
}                                                                                                                                                                                                                           

/* A função "lista_inserir" recebe uma lista e um item que se deseja inserir na lista ordenada.
 * Serve de interface para o usuário, chama as funções auxiliares "lista_busca" e "lista_inserir_posicao".
 * Complexidade: : T(n) = log n + n --> O(n) */                                                                                                                                                                                                                                  
bool lista_inserir(LISTA *lista, ITEM *item){                                                                                                                                                                                                                                                                                                                                                                                               
    int x = lista_busca(lista, item_get_chave(item));                                                                                                                                                                            
    return(lista_inserir_posicao(lista, x, item));                                                                                                                                                                                                                                                                                                                                                                                                                                         
}        

/* A função "lista_remover" recebe uma lista e um valor da posição do item que se deseja remover.
 * Como se trata de uma lista sequencial, é necessário fazer deslocamentos para fechar o espaço do item retirado, 
retomando para que a lista fique contínua. A quantidade de deslocamentos a ser realizada é descrita por lista->fim-1-pos.
 * Caso a lista não exista ou esteja vazia (verificações de "lista_vazia"), ou se a posição de remoção não estiver nos
limites da lista, é retornado NULL.
 * Caso contrário, a lista existe, há algum item nela e a posição está adequada, o item é retirado, os delocamentos são
feitos para mantê-la organizada, então, o item 'it' pode ser retornado.
 * Complexidade: O(n). No pior caso, a remoção acontece na primeira posição, de modo que é necessário deslocar todos os elementos */
ITEM *lista_remover(LISTA *lista, int pos){
    // Verificação se a lista não existe ou está vazia ou se a posição de remoção não está nos limites da lista
    if (lista_vazia(lista) || pos < 0 || pos > lista->fim) {
        return NULL;
    }

    ITEM *it = lista->itens[pos]; // ITEM it recebe o item que se deseja remover para posterior return.

    // Faz o shit dos itens para preencher a posição do item removido.
    for (int j = pos; j < lista->fim - 1; j++) {                                                                                                                      
        lista->itens[j] = lista->itens[j + 1];
    }
    
    lista->fim--; // Como um item foi retirado, lista->fim é decrementado.
    lista->tamanho--; // Como um item foi retirado, lista->tamanho (a quantidade de elementos) é decrementado.

    return it;
}

/* A função "lista_item" recebe uma lista e uma chave, retornando ao usuário o item da lista com essa determinada chave.
 * Usa a lógica de busca binária iterativa.
 * Caso a lista não exista ou o item procurado não existe na lista, é retornado NULL.
 * Caso contrário a lista existe e foi encontrado o item, retornando-o.
 * Complexidade: O(log n). */
ITEM *lista_item(LISTA *lista, int chave) {
    // Declara e inicializa a variável 'inf' como o limite inferior inicial da busca, isto é, o início da lista
    int inf = lista->inicio;
    // Declara e inicializa a variável 'sup' como o limite superior inicial da busca, isto é, o fim da lista
    int sup = lista->fim;
    int meio;

    // Inicia-se um laço while que só terá fim quando o limite inferior ultrapassar o limite superior
    while (inf < sup) {
        // A variável, a cada iteração do while, recebe o novo meio da busca, gerado pela média aritmética dos limites
        meio = (inf + sup) / 2;

        // Verifica-se, primeiramente, se o termo que ficou no meio tem o valor que se está buscando, retornando 'meio', caso sim.
        if (item_get_chave(lista->itens[meio]) == chave) 
            return lista->itens[meio];

        // Caso contrário, é necessário verificar se o valor buscado é menor que o do termo central. Caso sim, o espaço de busca é reduzido
        // à metade, ao tornar o índice do meio o novo limite superior da busca
        else if (item_get_chave(lista->itens[meio]) > chave)
            sup = meio;

        // Caso contrário, é notório que se está no caso em que o valor buscado é maior que o do termo central. Então, o espaço de busca é
        // reduzido à metade, ao tornar o índice do meio+1 o novo limite inferior da busca.
        else
            inf = meio + 1;
    }
    return NULL;
}


/* A função "lista_tamanho" recebe uma lista e retorna o seu tamanho (a quantidade de elementos) dentro da lista em questão.
 * Caso a lista não exista, retorna-se uma constante ERRO (-1), sabendo que o tamanho não pode ser negativo.
 * Caso ela exista, é retornado o campo da struct LISTA, lista->tamanho, indicando a quantidade de elementos dentro dela.
 * Complexidade: O(1). */
int lista_tamanho(LISTA *lista) {
    // Verificação se a lista existe.
    if(lista != NULL) {
        return(lista->tamanho);
    }
    return ERRO;
}

/* A função "lista_vazia" recebe um lista e retorna se o lista é vazio ou não.
 * Caso o lista não exista, retorna-se VERDADEIRO.
 * Caso ele exista, é retornado VERDADEIRO, caso seu tamanho seja igual a 0 (não há elementos) e FALSO, caso contrário.
 * Complexidade: O(1). */
bool lista_vazia(LISTA *lista){         
    // Verificação se a lista existe.                                                                                                                                                                                                      
    if(lista != NULL) {                                                                                                                                                                                                               
        return (lista->tamanho == 0);       
    }
    return true;                                                                                                                                                                                                                              
}                                                                                                                                                                                                                                             

/* A função "lista_cheia" recebe um lista e retorna se o lista está cheio ou não.
 * Caso o lista não exista, retorna-se VERDADEIRO.
 * Caso ele exista, é retornado VERDADEIRO, caso seu tamanho seja igual a MAX_TAMANHO (não há como colocar mais elementos) e FALSO, caso contrário.
 * Complexidade: O(1). */                                                                                                                                                                                                                     
bool lista_cheia(LISTA *lista){    
    // Verificação se a lista existe.                                                                                                                                                                                                           
    if(lista != NULL) {                                                                                                                                                                                                                         
        return (lista->tamanho >= TAM_MAX);                                                                                                                                                                                                     
    }                                                                                                                                                                                                         
    return true;                                                                                                                                                                                                                              
} 

