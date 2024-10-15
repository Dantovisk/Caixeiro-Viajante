#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

/*
A 'struct deque_', por meio do typedef feito no TAD "Deque.h", passa a ser do tipo 'DEQUE'. Um deque permite a inserção e remoção de itens
tanto no início quanto no final. 
A estrutura possui os seguintes campos:
01) *itens[MAX_TAMANHO]: Um vetor de ponteiros para 'ITEM', armazenando os elementos do deque.
02) tamanho: indica o número de itens armazenados no deque.
03) inicio: índice do primeiro elemento.
04) fim: índice da próxima posição disponível após o último elemento.
*/
struct deque_{
    ITEM *itens[MAX_TAMANHO];
    int tamanho;
    int inicio;
    int fim;
};

/*
Cria a estrutura de um deque, alocando memória e inicializando os campos 'tamanho', 'inicio' e 'fim' como 0.
Em caso de erro de alocação, retorna NULL.
Complexidade: O(1).
*/
DEQUE* deque_criar(){
    // Declaração da variável ponteiro para deque e inicialização dela como NULL.
    DEQUE *deque = NULL;
    // Alocação da memória a partir da função da <stdlib.h> malloc().
    deque = (DEQUE *) malloc(sizeof(DEQUE));

    // Se a memória para deque for corretamente alocada, são inicializadas as variáveis que vão operar o vetor de itens, sejam elas os campos
    // da struct: tamanho, inicio, fim. Todos inicializadas como 0.
    if(deque != NULL){
        // O deque começa vazio, seu tamanho recebe 0.
        deque->tamanho = 0;
        // O índice inicial, quando o deque está vazio, é 0.
        deque->inicio = 0;
        // O índice final, quando o deque está vazio, é 0.
        deque->fim = 0;
    }
    // Possíveis retornos: NULL(Falha na alocação) ou DEQUE* (Sucesso na alocação).
    return deque;
}

/* 
A função "deque_apagar", cujo retorno é do tipo void, a partir do duplo ponteiro que é recebido como parâmetro, tem o papel de liberar a memória
alocada de cada item do vetor de itens, e somente depois, liberar o espaço alocado para a estrutura do deque.
01) Caso o deque recebido seja nulo, ou seja, não tenha ocorrido corretamente a alocação dinâmica, nenhuma operação é realizada.
02) Caso o deque não seja nulo, ou seja, tenha ocorrido corretamente a alocação dinâmica, são liberados os itens e depois a estrutura em si.
Complexidade: O(N).
O while precisa fazer a operação de remoção do item e liberação de memória N vezes.
*/
void deque_apagar(DEQUE** deque){
    // Verificação se o deque é nulo/existe.
    if(*deque != NULL){
        // Declaração da variável it, um ponteiro para item que vai receber os itens a serem apagados.
        ITEM *it;
        // O while continua até que não haja mais itens dentro do vetor.
        while(!deque_vazia(*deque)){
            // A variável recebe o endereço do último elemento do vetor e libera o seu espaço.
            it = deque_remover_fim(*deque);
            // Libera-se a memória do item.
            item_apagar(&it);
            // Como boa prática, faz-se o ponteiro item receber nulo, a fim de não ser possível acessar mais a região de memória liberada.
            it = NULL;
        }
        // Depois de liberada a memória de cada item, a memória da estrutura pode ser liberada.
        free(*deque);
        // Como boa prática, faz-se o ponteiro para deque receber nulo, a fim de não ser possível acessar mais a região de memória liberada.
        *deque = NULL;
    }
    // Apenas retorna, sem devolver nada.
    return;
}

/*
Insere um item no início do deque, ajustando os índices circularmente para evitar deslocamentos.
Se o deque estiver cheio ou não existir, retorna FALSO.
Complexidade: O(1).
*/
bool deque_inserir_inicio(DEQUE* deque, ITEM* item){
    // Verificação se deque existe e não está cheio.
    if(!deque_cheia(deque)){
        // Atualização da variável início, para a posição anterior, antes de fazer a inserção:
        // Como o deque é circular, é utilizado o operador % com o MAX_TAMANHO, para corrigir o caso em que deque->inicio seja 0 e o índice ficasse
        // negativo. Assim, é somado MAX_TAMANHO e o verdadeiro indíce passa a ser o resto da divisão por MAX_TAMANHO, mantendo o valo entre 0 e
        // MAX_TAMANHO-1.
        deque->inicio = (deque->inicio - 1 + MAX_TAMANHO) % MAX_TAMANHO;
        // É efetivamente inserido o item na posição início, com o indíce já atualizado.
        deque->itens[deque->inicio] = item;
        // Como se adicionou um item, o tamanho deve ser incrementado.
        deque->tamanho++;
        // Retorna VERDADEIRO, indicando que o item foi inserido no início do deque com sucesso.
        return true;
    }
    // Retorna FALSO, indicando que não foi possível inserir no início, afinal, ou o deque não existe ou o deque está cheio.
    return false;
}

/* 
A função "deque_inserir_fim", cujo retorno é do tipo booleano, tem a objetivo de inserir um item, recebido como parâmetro, no fim do deque. A fim de
que a complexidade se matenha O(1), optou-se por utilizar um deque de característica circular, para que seja poupada a realização de deslocamentos
desnecessários. Então, para se inserir um item no fim, é preciso realizar uma operação com o resto de MAX_TAMANHO, considerando que ao fazer 
deque->fim + 1, pode-se acabar chegando a um índice maior do que MAX_TAMANHO.
01) Caso o deque não exista ou esteja cheio (ambas as verificações feitas na função "deque_cheia"), retorna-se FALSO, indicando que não foi inserido
o item no deque.
02) Caso essas condições não se apliquem, o deque existe e há espaço nele, portanto, o item é inserido no fim do deque, seguindo a lógica dele ser
circular, assim retornando VERDADEIRO.
Complexidade: O(1).
*/
bool deque_inserir_fim(DEQUE* deque, ITEM* item){
    // Verificação se deque existe e não está cheio.
    if(!deque_cheia(deque)){
        // É efetivamente inserido o item na posição fim (Lembrando que deque->fim é a próxima posição disponível do deque, não o último elemento).
        deque->itens[deque->fim] = item;
        // Atualização da variável deque->fim, para a posição posterior, logo depois de fazer a inserção:
        // Como o deque é circular, é utilizado o operador % com o MAX_TAMANHO, para corrigir o caso em que deque->fim+1 ultrapassa MAX_TAMANHO. Para
        // corrigir isso, basta que se opere com o resto da divisão por MAX_TAMANHO.
        deque->fim = (deque->fim + 1) % MAX_TAMANHO;
        // Como se adicionou um item, o tamanho deve ser incrementado.
        deque->tamanho++;
        // Retorna VERDADEIRO, indicando que o item foi inserido no fim do deque com sucesso.
        return true;
    }
    // Retorna FALSO, indicando que não foi possível inserir no fim, afinal, ou o deque não existe ou o deque está cheio.
    return false;
}

/*
Remove e retorna o item do início do deque, ajustando os índices circularmente.
Se o deque estiver vazio ou não existir, retorna NULL.
Complexidade: O(1).
*/
ITEM* deque_remover_inicio(DEQUE* deque){
    if(!deque_vazia(deque)){
        ITEM *it = deque->itens[deque->inicio];
        deque->inicio = (deque->inicio + 1) % MAX_TAMANHO;
        deque->tamanho--;
        // Retorna o ponteiro para o item que estava na posição inicial do deque, a remoção foi bem sucedida.
        return it;
    }
    // Retorna NULL, a remoção não foi bem sucedida.
    return NULL;
}

/*
Remove e retorna o item do fim do deque, ajustando os índices circularmente.
Se o deque estiver vazio ou não existir, retorna NULL.
Complexidade: O(1)
*/
ITEM* deque_remover_fim(DEQUE* deque){
    // Verificação se deque existe e não está vazio.
    if(!deque_vazia(deque)){
        // Atualização da variável deque->fim, antes da remoção (Lembrando que deque->fim é a próxima posição disponível do deque, não o último elemento).
        // Como o deque é circular, é utilizado o operador % com o MAX_TAMANHO, para corrigir o caso em que deque->fim seja 0 e o índice ficasse negativo.
        // Assim, é somado MAX_TAMANHO e o verdadeiro indíce passa a ser o resto da divisão por MAX_TAMANHO, mantendo o valor entre 0 e MAX_TAMANHO-1.
        deque->fim = (deque->fim - 1 + MAX_TAMANHO) % MAX_TAMANHO;
        // A variável do tipo ITEM recebe o item que se encontra na posição final do deque.
        ITEM *it = deque->itens[deque->fim];
        // Como se retirou um item, o tamanho deve ser decrementado.
        deque->tamanho--;
        // Retorna o ponteiro para o item que estava na posição final do deque, a remoção foi bem sucedida.
        return it;
    }
    // Retorna NULL, a remoção não foi bem sucedida.
    return NULL;
}

/*
Retorna o item do início do deque sem removê-lo.
Se o deque estiver vazio ou não existir, retorna NULL.
Complexidade: O(1).
*/
ITEM* deque_primeiro(DEQUE* deque){
    // Verificação se deque existe e não está vazio.
    if(!deque_vazia(deque)){
        // A variável do tipo ITEM recebe o item que se encontra na posição inicial do deque, o índice segue a lógica do deque circular, limitando entre 0
        // e MAX_TAMANHO-1.
        ITEM *it = deque->itens[deque->inicio % MAX_TAMANHO];
        // Retorna o ponteiro para o item que está na posição inicial do deque, sem remoção.
        return it;
    }
    // Retorna NULL, não há deque ou o deque está vazio, não foi possível mostrar o primeiro item.
    return NULL;
}

/*
Retorna o item do fim do deque sem removê-lo.
Se o deque estiver vazio ou não existir, retorna NULL.
Complexidade: O(1).
*/
ITEM* deque_ultimo(DEQUE* deque){
    if(!deque_vazia(deque)){
        // A variável do tipo ITEM recebe o item que se encontra na posição final do deque, o índice segue a lógica do deque circular, limitando entre 0
        // e MAX_TAMANHO-1.
        ITEM *it = deque->itens[(deque->fim - 1 + MAX_TAMANHO) % MAX_TAMANHO];
         // Retorna o ponteiro para o item que estava na posição final do deque, sem remoção.
        return it;
    }
    // Retorna NULL, não há deque ou o deque está vazio, não foi possível mostrar o último item.
    return NULL;
}

/* 
A função "deque_contar", cujo o retorno é do tipo inteiro, é responsável por retornar o tamanho (a quantidade de elementos) dentro do deque em questão.
01) Caso o deque não exista, retorna-se uma constante ERRO.
02) Caso ele exista, é retornado o campo da struct DEQUE, deque->tamanho, indicando a quantidade de elementos dentro dele.
Complexidade: O(1).
*/
int deque_contar(DEQUE* deque){
    // Verificação se o deque existe.
    if(deque != NULL) {
        // Retorna o campo da struct DEQUE, deque->tamanho, indicando a quantidade de elementos existentes no deque.
        return deque->tamanho;
    }
    // Retorna um ERRO (-1), sabendo que o tamanho não pode ser negativo.
    return ERRO;
}

/*
A função "deque_vazia", cujo o retorno é do tipo booleano, é responsável por retornar se é VERDADE OU FALSO que o tamanho do deque, armazenado no campo
da struct DEQUE, é 0.
01) Caso o deque não exista, retorna-se VERDADEIRO.
02) Caso ele exista, é retornado:
 * VERDADEIRO: se não há elementos no deque, isto é, seu tamanho é 0.
 * FALSO: se há pelo menos um elemento no deque, isto é, seu tamanho não é 0.
Complexidade: O(1).
*/
bool deque_vazia(DEQUE* deque){
    // Verificação se o deque existe.
    if(deque != NULL) {
        // Retorna o valor booleano da comparação de deque->tamanho com 0: VERDADEIRO, se deque->tamanho = 0, do contrário, FALSO.
        return deque->tamanho == 0;
    }
    // Retorna VERDADEIRO por padrão quando o deque não existe.
    return true;
}

/*
A função "deque_cheia", cujo o retorno é do tipo booleano, é responsável por retornar se é VERDADE OU FALSO que o tamanho do deque, armazenado no campo
da struct DEQUE, é o mesmo valor que MAX_TAMANHO.
01) Caso o deque não exista, retorna-se VERDADEIRO.
02) Caso ele exista, é retornado:
 * VERDADEIRO: se o campo da struct DEQUE, deque->tamanho, atingiu o limite do tamanho do vetor (MAX_TAMANHO), configurando um deque cheio.
 * FALSO:  se o campo da struct DEQUE, deque->tamanho, ainda não atingiu o limite do tamanho do vetor (MAX_TAMANHO), configurando um deque que ainda há
posições vagas.
Complexidade: O(1).
*/
bool deque_cheia(DEQUE* deque){
    // Verificação se o deque existe.
    if(deque != NULL) {
        // Retorna o valor booleano da comparação de deque->tamanho com MAX_TAMANHO: VERDADEIRO, se deque->tamanho = MAX_TAMANHO, do contrário, FALSO.
        return deque->tamanho == MAX_TAMANHO;
    }
    // Retorna VERDADEIRO por padrão quando o deque não existe.
    return true;
}


/* 
A função "deque_copiar", cujo retorno é do tipo void, recebe como parâmetros, um deque de origem e um deque de destino: a ideia é passar os itens do deque
de origem para o de destino, sem perder o de origem, com as funções já existentes no TAD 'deque.h' e no TAD 'item.h', sejam elas: "deque_vazia", "deque_criar",
"deque_remover_inicio", "item_apagar", "deque_inserir_fim", "deque_apagar". Para tanto, fez-se o uso de um deque temporário, que armazena temporariamente os
itens do deque de origem.
Complexidade: O(N).
Existem 3 operações que são O(N), afinal, demandar fazer operações por todo o deque.
*/
void deque_copiar(DEQUE* origem, DEQUE* destino) {
    // Verifica-se se os deques são válidos.
    if (!origem || !destino) {
        // Caso não sejam válidos, já retorna.
        return;
    }

    // A partir do deque de destino, recebido como parâmetro, vai-se apagando/limpando todo o seu conteúdo, até que fique vazio. COMPLEXIDADE = O(N)
    while(!deque_vazia(destino)){
        // Recebe cada item do deque, removendo cada um pelo início
        ITEM *item = deque_remover_inicio(destino);
        // Apaga cada um dos itens que estavam dentro do deque de destino
        item_apagar(&item);
    }
    // Finalizado o while, tem-se um deque de destino vazio, sem itens.

    // Cria um deque temporário para receber as cópias dos itens do deque de origem. 
    DEQUE* temp = deque_criar();
    // Declaração da variável 'item', um ponteiro para ITEM
    ITEM* item;

    // A partir do deque de origem, recebido como parâmetro, vai-se apagando/limpando todo o seu conteúdo, até que fique vazio. COMPLEXIDADE = O(N).
    while (!deque_vazia(origem)) {
        // A variável item recebe o endereço do item que estava localizado na posição inicial dentro do deque de origem.
        item = deque_remover_inicio(origem);
        // É criado um novo item, cópia do item que foi retirado da posição inicial do deque.
        ITEM* novoItem = item_criar(item_get_chave(item), item_get_dados(item));
        // Insere-se no fim do deque de destino 'novoItem', cópia do item do deque de origem.
        deque_inserir_fim(destino, novoItem); 
        // Armazena temporariamente no deque auxiliar o item que estava e foi removido da posição inicial do deque.
        deque_inserir_fim(temp, item);     
    }
    // Finalizado o while, tem-se um deque temporário e um deque de destino com cópias dos itens do deque de origem.

    // A partir do deque temporário, vai-se apagando/limpando todo o seu conteúdo, até que fique vazio. COMPLEXIDADE = O(N).
    while (!deque_vazia(temp)) {
        // A variável item recebe o endereço do item que estava localizado na posição inicial dentro do deque de origem.
        item = deque_remover_inicio(temp);
        // Insere-se no fim do deque de origem, o respectivo item que ali estava inicialmente, voltando ao deque original.
        deque_inserir_fim(origem, item); 
    }
    // Finalizado o while, tem-se de volta o deque de destino, com os mesmos valores do original.
    
    // Libera o deque temporário
    deque_apagar(&temp);
}