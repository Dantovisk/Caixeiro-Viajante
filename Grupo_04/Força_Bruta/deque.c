#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

/* Declaração do tipo DEQUE, uma estrutura de dados que permite a manipulação das extremidades.
 * *itens[MAX_TAMANHO]: Um vetor de ponteiros para 'ITEM', que armazena os elementos do deque. O tamanho máximo do vetor é definido pela
constante 'MAX_TAMANHO' declarada na interface.
 * tamanho: um inteiro que indica o número de itens armazenados no deque, valor que se atualiza conforme itens são inseridos ou removidos.
 * inicio: um inteiro que representa o índice do primeiro elemento no deque.
 * fim: um inteiro que representa o índice (a posição) do próximo espaço disponível, após o último elemento do deque.*/
typedef struct deque_{
    ITEM *itens[MAX_TAMANHO];
    int tamanho;
    int inicio;
    int fim;
} DEQUE;

/* A função "deque_criar" tem o papel de criar a estrutura de um deque, alocando a sua memória dinamicamente e
inicializando os campos da struct DEQUE.
 * Em caso de erro na alocação de memória, apenas retorna NULL sem mudar os campos da struct.
 * Em caso de sucesso na alocação de memória, os campos 'tamanho', 'inicio' e 'fim' são inicializados como 0, para que se possa futuramente
operar com o vetor de itens 'ITEM* itens[MAX_TAMANHO]'. Assim, retorna-se um ponteiro para este deque.
 * Complexidade: O(1). */
DEQUE* deque_criar(){
    DEQUE *deque = NULL;
    deque = (DEQUE *) malloc(sizeof(DEQUE));

    // Verifica se a alocação foi bem sucedido.
    if(deque != NULL){
        deque->tamanho = 0;
        deque->inicio = 0;
        deque->fim = 0;
    }

    return deque;
}

/* A função "deque_apagar", recebe o endereço de um deque e libera a memória alocada de cada item da estrutura e, por fim,
libera o espaço alocado para a estrutura do deque.
 * Caso o deque recebido seja nulo, ou seja, não tenha ocorrido corretamente a alocação dinâmica, nenhuma operação é realizada.
 * Caso o deque não seja nulo, ou seja, tenha ocorrido corretamente a alocação dinâmica, são liberados os itens e depois a estrutura em si.
 * Complexidade: O(n). O while precisa fazer a operação de remoção do item e liberação de memória N vezes. */
void deque_apagar(DEQUE** deque){
    if(*deque != NULL){
        ITEM *it; // Declaração de um item auxiliar usado para apagar os itens do DEQUE.

        // O while continua até que não haja mais itens dentro do vetor.
        while(!deque_vazia(*deque)){
            it = deque_remover_fim(*deque);
            item_apagar(&it);
            it = NULL;
        }

        // Liberação da memória da estrutura.
        free(*deque);
        *deque = NULL;
    }

    return;
}

/* A função "deque_inserir_inicio" recebe um deque e um item, tendo o objetivo de inserir um item no início do deque, retornando se a operação
foi bem sucedida ou não.
 * A fim de que a complexidade se matenha O(1), optou-se por utilizar um deque de característica circular, para que seja poupada a realização de 
deslocamentos desnecessários. Então, para se inserir um item no início, é preciso realizar uma operação com o resto de MAX_TAMANHO, considerando 
que ao fazer deque->inicio-1, pode-se acabar chegando a um índice negativo.
 * Caso o deque não exista ou esteja cheio (ambas as verificações feitas na função "deque_cheia"), retorna-se FALSO, indicando que não foi inserido
o item no deque.
 * Caso essas condições não se apliquem, o deque existe e há espaço nele, portanto, o item é inserido no início do deque, seguindo a lógica dele ser
circular, assim retornando VERDADEIRO.
 * Complexidade: O(1). */
bool deque_inserir_inicio(DEQUE* deque, ITEM* item){
    // Verificação se deque existe e não está cheio.
    if(!deque_cheia(deque)){
        // Atualização da variável início, para a posição anterior, antes de fazer a inserção:
        deque->inicio = (deque->inicio - 1 + MAX_TAMANHO) % MAX_TAMANHO; // Operação modular do deque circular de decrementar um índice.
        deque->itens[deque->inicio] = item;
        deque->tamanho++; // Como se adicionou um item, o tamanho deve ser incrementado.

        return true;
    }
    return false;
}

/* A função "deque_inserir_fim" recebe um deque e um item, tendo o objetivo de inserir um item no fim do deque, retornando se a operação
foi bem sucedida ou não.
 * A fim de que a complexidade se matenha O(1), optou-se por utilizar um deque de característica circular, para que seja poupada a realização de deslocamentos
desnecessários. Então, para se inserir um item no fim, é preciso realizar uma operação com o resto de MAX_TAMANHO, considerando que ao fazer 
deque->fim + 1, pode-se acabar chegando a um índice maior do que MAX_TAMANHO.
 * Caso o deque não exista ou esteja cheio (ambas as verificações feitas na função "deque_cheia"), retorna-se FALSO, indicando que não foi inserido
o item no deque.
 * Caso essas condições não se apliquem, o deque existe e há espaço nele, portanto, o item é inserido no fim do deque, seguindo a lógica dele ser
circular, assim retornando VERDADEIRO.
 * Complexidade: O(1). */
bool deque_inserir_fim(DEQUE* deque, ITEM* item){
    // Verificação se deque existe e não está cheio.
    if(!deque_cheia(deque)){
        // É efetivamente inserido o item na posição fim (Lembrando que deque->fim é a próxima posição disponível do deque, não o último elemento).
        deque->itens[deque->fim] = item;
        deque->fim = (deque->fim + 1) % MAX_TAMANHO; // Operação modular do deque circular de incrementar o índice.
        deque->tamanho++; // Como se adicionou um item, o tamanho deve ser incrementado.

        return true;
    }
    return false;
}

/* A função "deque_remover_inicio", recebe um deque e retira o item que estava localizado em seu início, retornando-o. 
 * A fim de que a complexidade se matenha O(1), optou-se por utilizar um deque de característica circular, para que seja poupada a realização
de deslocamentos desnecessários. Então, para se retirar o item, é preciso realizar uma operação com o resto de MAX_TAMANHO, considerando que ao fazer 
deque->inicio + 1, pode-se acabar chegando a um índice maior do que MAX_TAMANHO.
 * Caso o deque não exista ou esteja vazio (ambas as verificações feitas na função "deque_vazia"), retorna-se NULL, indicando que não foi retirado item
algum do começo do deque.
 * Caso essas condições não se apliquem, o deque existe e há pelo menos algum item nele, portanto, o item que está em seu início é retornado, seguindo a
lógica dele ser circular, assim retornando 'it'.
 * Complexidade: O(1).  */
ITEM* deque_remover_inicio(DEQUE* deque){
    // Verificação se deque existe e não está vazio.
    if(!deque_vazia(deque)){
        // A variável do tipo ITEM recebe o item que se encontra na posição inicial do deque.
        ITEM *it = deque->itens[deque->inicio];
        deque->inicio = (deque->inicio + 1) % MAX_TAMANHO; // Operação modular do deque circular de incrementar o índice.
        deque->tamanho--; // Como se retirou um item, o tamanho deve ser decrementado.
        return it;
    }
    return NULL;
}

/* A função "deque_remover_fim", recebe um deque e retira o item que estava localizado em seu fim, retornando-o.
 * A fim de que a complexidade se matenha O(1), optou-se por utilizar um deque de característica circular, para que seja poupada a realização
de deslocamentos desnecessários. Então, para se retirar o item, é preciso realizar uma operação com o resto de MAX_TAMANHO, considerando que ao fazer 
deque->fim-1, pode-se acabar chegando a um índice negativo.
 * Caso o deque não exista ou esteja vazio (ambas as verificações feitas na função "deque_vazia"), retorna-se NULL, indicando que não foi retirado item
algum do fim do deque.
 * Caso essas condições não se apliquem, o deque existe e há pelo menos algum item nele, portanto, o item que está em seu fim é retornado, seguindo a
lógica dele ser circular, assim retornando 'it'.
 * Complexidade: O(1) */
ITEM* deque_remover_fim(DEQUE* deque){
    // Verificação se deque existe e não está vazio.
    if(!deque_vazia(deque)){
        deque->fim = (deque->fim - 1 + MAX_TAMANHO) % MAX_TAMANHO; // Operação modular do deque circular de decrementar um índice.
        ITEM *it = deque->itens[deque->fim];
        deque->tamanho--; // Como se retirou um item, o tamanho deve ser decrementado.
        return it;
    }
    return NULL;
}

/* A função "deque_primeiro", recebe um deque e mostra o item que está localizado em seu início, retornando-o.
 * A fim de que a complexidade se matenha O(1), optou-se por utilizar um deque de característica circular, para que seja poupada a realização de deslocamentos
desnecessários. Então, para se mostrar esse item, é preciso realizar uma operação com o resto de MAX_TAMANHO, para garantir que ele esteja no intervalo entre
0 e MAX_TAMANHO-1.
 * Caso o deque não exista ou esteja vazio (ambas as verificações feitas na função "deque_vazia"), retorna-se NULL, indicando que não foi possível mostrar
o item da posição inicial do deque.
 * Caso essas condições não se apliquem, o deque existe e há pelo menos algum item nele, portanto, o item que está em seu início é retornado, seguindo a
lógica dele ser circular, assim retornando 'it', sem removê-lo do deque.
 * Complexidade: O(1). */
ITEM* deque_primeiro(DEQUE* deque){
    // Verificação se deque existe e não está vazio.
    if(!deque_vazia(deque)){
        ITEM *it = deque->itens[deque->inicio]; 
        return it;
    }
    return NULL;
}

/* A função "deque_ultimo", recebe um deque e mostra o item que está localizado em seu fim, retornando-o.
 * A fim de que a complexidade se matenha O(1), optou-se por utilizar um deque de característica circular, para que seja poupada a realização de deslocamentos
desnecessários. Então, para se mostrar esse item, é preciso realizar uma operação com o resto de MAX_TAMANHO, para garantir que ele esteja no intervalo entre
0 e MAX_TAMANHO-1.
 * Caso o deque não exista ou esteja vazio (ambas as verificações feitas na função "deque_vazia"), retorna-se NULL, indicando que não foi possível mostrar
o item da posição do fim do deque.
 * Caso essas condições não se apliquem, o deque existe e há pelo menos algum item nele, portanto, o item que está em seu final é retornado, seguindo a
lógica dele ser circular, assim retornando 'it', sem removê-lo do deque.
 * Complexidade: O(1). */
ITEM* deque_ultimo(DEQUE* deque){
    // Verificação se deque existe e não está vazio.
    if(!deque_vazia(deque)){
        // Operação modular de decremento, já que o deque->fim é uma posição à frente do primeiro elemento.
        ITEM *it = deque->itens[(deque->fim - 1 + MAX_TAMANHO) % MAX_TAMANHO];
        return it;
    }
    return NULL;
}

/* A função "deque_contar" recebe um deque e retornar o seu tamanho (a quantidade de elementos).
 * Caso o deque não exista, retorna-se uma constante ERRO (-1), sabendo que o tamanho não pode ser negativo.
 * Caso ele exista, é retornado o campo da struct DEQUE, deque->tamanho, indicando a quantidade de elementos dentro dele.
 * Complexidade: O(1). */
int deque_contar(DEQUE* deque){
    // Verificação se o deque existe.
    if(deque != NULL) {
        return deque->tamanho;
    }
    return ERRO;
}

/* A função "deque_vazia" recebe um deque e retorna se o deque é vazio ou não.
 * Caso o deque não exista, retorna-se VERDADEIRO.
 * Caso ele exista, é retornado VERDADEIRO, caso seu tamanho seja igual a 0 (não há elementos) e FALSO, caso contrário.
 * Complexidade: O(1). */
bool deque_vazia(DEQUE* deque){
    // Verificação se o deque existe.
    if(deque != NULL) {
        return deque->tamanho == 0;
    }
    return true;
}

/* A função "deque_cheia" recebe um deque e retorna se o deque está cheio ou não.
 * Caso o deque não exista, retorna-se VERDADEIRO.
 * Caso ele exista, é retornado VERDADEIRO, caso seu tamanho seja igual a MAX_TAMANHO (não há como colocar mais elementos) e FALSO, caso contrário.
 * Complexidade: O(1). */
bool deque_cheia(DEQUE* deque){
    // Verificação se o deque existe.
    if(deque != NULL) {
        return deque->tamanho == MAX_TAMANHO;
    }
    return true;
}

// FUNÇÃO USADA SOMENTE PARA DEBUG
// /* A função "deque_printar", recebe um deque e printa a chave de todos os seus itens.
//  * Caso o deque não exista, não printa nada, apenas retorna.
//  * Caso o deque exista, por meio de um laço de repetição 'for', faz-se a impressão de todos os conteúdos dos itens, começando do início
//  e percorrendo circulamento o deque levando em consideração o seu tamanho (quantidade de elementos).
//  * Complexidade: O(n) */
// void deque_printar(DEQUE *deque){
//     if(deque != NULL){
//         int i = deque->inicio;
//         for(int j = 0; j < deque->tamanho; j++){
//             printf("%d", item_get_chave(deque->itens[i]));
//             i = (i + 1) % MAX_TAMANHO;
//         }
//         printf("\n");
//     }
    
//     return;
// }

/* A função "deque_copiar" recebe um deque de origem e um deque de destino e copia o conteúdo da origem para o destino.
 * A ideia é passar os itens do deque de origem para o de destino, sem perder o de origem, com as funções já existentes no 
TAD 'deque.h' e no TAD 'item.h', sejam elas: "deque_vazia", "deque_criar","deque_remover_inicio", "item_apagar", "deque_inserir_fim", 
"deque_apagar". Para tanto, fez-se o uso de um deque temporário, que armazena temporariamente os itens do deque de origem.
 * Complexidade: O(n). Existem 3 operações que são O(n), afinal, demandar fazer operações por todo o deque. */
void deque_copiar(DEQUE* origem, DEQUE* destino) {
    // Verifica-se se os deques são válidos.
    if (!origem || !destino) {
        return;
    }

    // A partir do deque de destino, recebido como parâmetro, vai-se apagando/limpando todo o seu conteúdo, até que fique vazio. COMPLEXIDADE = O(n)
    while(!deque_vazia(destino)){
        ITEM *item = deque_remover_inicio(destino); // Recebe cada item do deque, removendo cada um pelo início
        item_apagar(&item); // Apaga cada um dos itens que estavam dentro do deque de destino
    }
 
    DEQUE* temp = deque_criar(); // Cria um deque temporário para receber as cópias dos itens do deque de origem.
    ITEM* item; // Item auxiliar para ajudar na cópia.

    // A partir do deque de origem, recebido como parâmetro, vai-se apagando/limpando todo o seu conteúdo, até que fique vazio. COMPLEXIDADE = O(n).
    while (!deque_vazia(origem)) {
        item = deque_remover_inicio(origem); // É recebido o item que estava localizado na posição inicial dentro do deque de origem.

        // É criado um novo item, cópia do item que foi retirado da posição inicial do deque.
        ITEM* novoItem = item_criar(item_get_chave(item), item_get_dados(item));
        deque_inserir_fim(destino, novoItem); // Insere-se no fim do deque de destino 'novoItem', cópia do item do deque de origem.
        deque_inserir_fim(temp, item); // Armazena temporariamente no deque auxiliar o item que estava e foi removido da posição inicial do deque.
    }

    // A partir do deque temporário, vai-se apagando/limpando todo o seu conteúdo, até que fique vazio. COMPLEXIDADE = O(n).
    while (!deque_vazia(temp)) {
        item = deque_remover_inicio(temp);
        deque_inserir_fim(origem, item); 
    }
    // Finalizado a função, tem-se de volta o deque de destino, com os mesmos valores do original.

    deque_apagar(&temp);

    return;
}


