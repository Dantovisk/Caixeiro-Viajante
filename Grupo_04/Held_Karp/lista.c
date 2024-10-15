#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
/* 
A 'struct lista_', por meio do typedef feito no TAD "lista.h", passa a ser do tipo 'LISTA'. Um lista permite a inserção e remoção de itens
em qualquer posição.
A estrutura possui quatro campos:
01) *itens[TAM_MAX]: Um vetor de ponteiros para 'ITEM', que armazena os elementos do lista. O tamanho máximo do vetor é definido pela
constante 'TAM_MAX'.
02) inicio: um inteiro que representa o índice do primeiro elemento no lista.
03) fim: um inteiro que representa o índice (a posição) do próximo espaço disponível, após o último elemento do lista.
04) tamanho: um inteiro que indica o número de itens armazenados no lista, valor que se atualiza conforme itens são inseridos ou removidos. 
*/
struct lista_{
    ITEM *itens[TAM_MAX];
    int inicio;
    int fim; // O PRÓXIMO ÍNDICE DISPONÍVEL
    int tamanho; // QNTD DE ELEMENTOS DO VETOR DE ITENS
    bool ordenada;
};

/* 
A função "lista_criar", cujo retorno tem tipo LISTA *, tem o papel de criar a estrutura de uma lista, alocando a sua memória dinamicamente e
inicializando os campos 'tamanho' como 0 (A lista, quando criada, está vazia) e, 'inicio' e 'fim' também como 0 (O índice de começo e fim do
lista que acabou de ser criado e está vazia é 0), além de definir conforme o parâmetro recebido 'ordenada', se ela será ou não ordenada:
01) Em caso de erro na alocação de memória, apenas retorna NULL sem mudar os campos da struct.
02) Em caso de sucesso na alocação de memória, os campos 'tamanho', 'inicio' e 'fim' são inicializados como 0, para que se possa futuramente
operar com o vetor de itens 'ITEM* itens[TAM_MAX]'. Assim, retorna-se um ponteiro para este lista.
Complexidade: O(1).
*/
LISTA *lista_criar(bool ordenada){
    // Declaração da variável ponteiro para lista e inicialização dela como NULL.
    LISTA *l = NULL;
     // Alocação da memória a partir da função da <stdlib.h> malloc().
    l = (LISTA *) malloc(sizeof(LISTA));
    // Se a memória para lista for corretamente alocada, são inicializadas as variáveis que vão operar o vetor de itens, sejam elas os campos
    // da struct: tamanho, inicio, fim. Todos inicializadas como 0. Além disso, recebe-se 'ordenada' e seu valor booleano vai no campo da struct
    // 'l->ordenada'.
    if(l != NULL){
        // O índice inicial, quando a lista está vazia, é 0.
        l->inicio = 0;
        // O índice final, quando a lista está vazia, é 0.
        l->fim = 0;
        // a lista começa vazia, seu tamanho recebe 0.
        l->tamanho = 0;
        // A lista recebe o valor booleano se está ou não ordenada, ficando aqui armazenada essa informação.
        l->ordenada = ordenada;
    }
    // Possíveis retornos: NULL(Falha na alocação) ou LISTA* (Sucesso na alocação).
    return l;
}

/*
A função "lista_busca", cujo retorno é do tipo inteiro, é responsável por realizar uma busca binária em uma lista ordenada do valor 'val', 
recebido como parâmetro, entre os itens da lista. Como a cada iteração do while, reduz-se o espaço de busca à metade, esse se torna um
algoritmo extremamente eficaz em efetuar uma busca ordenada (log n).
01) Retorna 'meio', caso ache um item com o mesmo valor
02) Retorna 'inf', o limite inferior da lista depois de realizada a busca, quando ele ultrapassar o limite superior 'sup'.
Coplexidade: O(LOG N).
*/
int lista_busca(LISTA *lista, int val){
    // Declara e inicializa a variável 'inf' como o limite inferior inicial da busca, isto é, o início da lista
    int inf = lista->inicio;
    // Declara e inicializa a variável 'sup' como o limite superior inicial da busca, isto é, o fim da lista
    int sup = lista->fim;
    // Declara a variável 'meio'
    int meio;
    // Verifica se a lista está vazia, se sim, retorna o índice do lista->fim(0).
    if(lista_vazia(lista)) {
        return lista->fim;
    }

    // Inicia-se um laço while que só terá fim quando o limite inferior ultrapassar o limite superior
    while (inf < sup) {
        // A variável, a cada iteração do while, recebe o novo meio da busca, gerado pela média aritmética dos limites
        meio = (inf + sup) / 2;
        // Verifica-se, primeiramente, se o termo que ficou no meio tem o valor que se está buscando, retornando 'meio', caso sim.
        if (item_get_chave(lista->itens[meio]) == val) {
            return meio;
        }
        // Caso contrário, é necessário verificar se o valor buscado é menor que o do termo central. Caso sim, o espaço de busca é reduzido
        // à metade, ao tornar o índice do meio o novo limite superior da busca
        else if (item_get_chave(lista->itens[meio]) > val) {
            sup = meio;
        }
        // Caso contrário, é notório que se está no caso em que o valor buscado é maior que o do termo central. Então, o espaço de busca é
        // reduzido à metade, ao tornar o índice do meio+1 o novo limite inferior da busca.
        else {
            inf = meio + 1;
        }
    }
    // Quanto o limite inferior ultrapassar o limite posterior significa que aquela deve ser a posição do item buscado na lista.
    return inf;
}

/*
A função "lista_inserir_posição", cujo retorno é do tipo booleano, tem objetivo de, a partir dos parâmetros recebidos (LISTA *lista: A LISTA
EM QUE OCORRERÁ A INSERÇÃO, ITEM *item: O ITEM QUE SE DESEJA INSERIR, int pos: A POSIÇÃO IDEAL DE INSERÇÃO), efetuar a inserção de um item
na lista e mantê-la ordenada. Como se trata de uma lista sequencial, para mantê-la ordenada após uma inserção, é necessário fazer deslocamentos
para abrir um espaço para inserção. A quantidade de deslocamentos a ser realizada é descrita por lista->fim - pos.
01) Caso a lista não exista, esteja cheia ou a posição esteja fora dos limites da lista, retorna-se FALSO, indicando que não foi possível inserir na
posição.
02) Caso contrário, a lista existe, não está cheia e há algum espaço vago, é retornado VERDADEIRO após fazer a inserção na posição ideal e os
deslocamentos necessários.
Complexidade: 0(N)
No pior caso, a inserção acontece na primeira posição, sendo necessário deslocar todos os elementos.
*/
bool lista_inserir_posicao(LISTA *lista, int pos, ITEM *item){
    // Verifica se a lista existe e não está cheia e, a posição está dentro do limite da lista (0 a lista->fim são as únicas possíveis opções de inserção)
    if(!lista_cheia(lista) && pos >= 0 && pos <= lista->fim){
        // Percorre o vetor, de trás para frente, da posição final até a que se deseja inserir, fazendo os deslocamentos    
        for(int i = lista->fim; i > pos; i--){                                                                          
            // A posição que está à frente numericamente, recebe o item anterior                                                                                                                      
            lista->itens[i] = lista->itens[i-1];                                                                                                                                                                                              
        }                                                                       
        // Terminado o laço 'for', tem-se livre a posição de inserção para assim fazê-la                                                                                                                                                              

        // A inserção acontece na posição ideal, mantendo a lista ainda ordenada                                                                                                                                                      
        lista->itens[pos] = item;                                               
        // Como foi inserido um item, lista->fim é incrementada                                                                                                                                                              
        lista->fim++;                                          
        // Como foi inserido um item, lista->tamanho é incrementada                                                                                                                                                                               
        lista->tamanho++;                                          
        // É retornado VERDADEIRO, indicando que houve efetivamente a inserção                                                                                                                                                                           
        return true;                                                                                                                                                                                                                          
    }                                                                                                                                                                                                                                         
    // É retornado FALSO, indicando que a inserção não pôde ser bem sucedida
    return false;                                                                                                                                                                                                                             
}              

/*
A função "lista_inserir_fim", cujo retorno é do tipo booleano, é responsável por, a partir dos parâmetros recebidos (LISTA *lista: A LISTA
EM QUE OCORRERÁ A INSERÇÃO, ITEM *it: O ITEM QUE SE DESEJA INSERIR), efetuar a inserção de um item no final da lista por padrão, o que é
recompensado em desempenho, não precisa fazer deslocamentos, mas assim, não se preocupa com ordenação.
01) Caso a lista esteja cheia ou nem sequer exista(ambas verificações feitas na função "lista_cheia"), retorna-se FALSO, indicando que não
foi possível realizar a inserção.
02) Se isso não se aplicar, a lista existe e há espaços vagos, desse modo, o item é inserido e retorna-se TRUE, indicando o sucesso. 
Complexidade: 0(1)
*/
bool lista_inserir_fim (LISTA *lista, ITEM *it) {
    // Verificação se a lista existe e não está cheia.
    if(!lista_cheia(lista)){
        // Inserção na posição final (Lembrando que lista->fim é a próxima posição vaga, não o último elemento)
        lista->itens[lista->fim] = it;
        // Como foi adicionado um item, lista->fim é incrementado.
        lista->fim++;
        // Como foi adicionado um item, lista->tamanho é incrementado.
        lista->tamanho++;
        // Retorna VERDADEIRO, indicando que o item foi inserido no fim da lista com sucesso.
        return(true);
    }
    // Retorna FALSO, indicando que não foi possível inserir no fim, afinal, ou o lista não existe ou o lista está cheio.
    return(false);
}                                                                                                                                                                                                                               

/*
A função "lista_inserir", cujo retorno é do tipo booleano, é responsável por, a partir dos parâmetros recebidos (LISTA *lista: A LISTA
EM QUE OCORRERÁ A INSERÇÃO, ITEM *item: O ITEM QUE SE DESEJA INSERIR), efetuar a inserção de um item. Para tanto, ela chama as funções
auxiliares "lista_busca"+"lista_inserir_posicao" e "lista_inserir_fim", conforme se a lista deve ser ordenada ou não. 
01) A lista é ordenada, logo, utiliza-se a lógica das funções "lista_busca" e "lista_inserir_posicao" combinadas para inserir adequadamente.
02) A lista não é ordenada, logo, basta inserir no fim com a função "lista_inserir_fim"
Complexidade: 
* ORDENADA: T(N) = LOG N + N --> O(N)
* NÃO ORDENADA: O(1)
*/                                                                                                                                                                                                                                  
bool lista_inserir(LISTA *lista, ITEM *item){      
    // Verifica se se trata de uma lista ordenada ou não com base no campo da struct LISTA, lista->ordenada                                                                                                                                                                                           
    if(lista->ordenada){              
        // A variável 'x' recebe o inteiro que indica a posição ideal de inserção.                                                                                                                                                                                                               
        int x = lista_busca(lista, item_get_chave(item));
        // A variável 'x' é passada como parâmetro para a inserção ocorrer na posição ideal para item, mantendo ordenada a lista
        // Como "lista_inserir_posicao" retorna um booleano, se foi ou não possível inserir, já é dado o return desse valor.                                                                                                                                                                                     
        return(lista_inserir_posicao(lista, x, item));                                                                                                                                                                                        
    }     
    // Caso a lista não seja ordenada, para manter a complexidade O(1), insere-se no fim.                                                                                                                                                                                                                                    
    // Como "lista_inserir_fim" retorna um booleano, se foi ou não possível inserir no fim, já é dado o return desse valor.                                                                                                                                                                                                                                            
    return(lista_inserir_fim(lista, item));                                                                                                                                                                                                                                                                                                                                                                          
}        

/*
A função "lista_remover", cujo retorno é do tipo ITEM *, é responsável por, a partir dos parâmetros recebidos (LISTA 
*lista: A LISTA EM QUE OCORRERÁ A REMOÇÃO, int pos: A POSIÇÃO DE QUE SE DESEJA REMOVER), efetuar, dada uma posição, 
a remoção do item ali localizado. Como se trata de uma lista sequencial, para mantê-la organizada após uma remoção, é
necessário fazer deslocamentos para fechar o espaço do item retirado, retomando para que a lista fique contínua. A
quantidade de deslocamentos a ser realizada é descrita por lista->fim-1-pos.
01) Caso a lista não exista ou esteja vazia (verificações de "lista_vazia"), ou se a posição de remoção não estiver nos
limites da lista, é retornado NULL.
02) Caso contrário, a lista existe, há algum item nela e a posição está adequada, o item é retirado, os delocamentos são
feitos para mantê-la organizada, então, o item 'it' pode ser retornado.
Complexidade: O(N)
No pior caso, a remoção acontece na primeira posição, de modo que é necessário deslocar todos os elementos
*/
ITEM *lista_remover(LISTA *lista, int pos){
    // Verificação se a lista não existe ou está vazia ou se a posição de remoção não está nos limites da lista
    if (lista_vazia(lista) || pos<0 || pos > lista->fim) {
        // É retornado NULL, mostrando que não foi possível remover.
        return NULL;
    }
    // A variável 'it' passa a apontar para o item da posição desejada.
    ITEM *it = lista->itens[pos];
    // Percorre o vetor da posição em que se removeu até o o último elemento (lista->fim-1), fazendo os deslocamentos
    for (int j = pos; j < lista->fim - 1; j++) {
        // O item na posição 'j' recebe o valor do próximo item 'j+1'.                                                                                                                      
        lista->itens[j] = lista->itens[j + 1];
    }
    // Terminado o laço 'for', agora o vetor se encontra organizado novamente.
    
    // Como um item foi retirado, lista->fim é decrementado.
    lista->fim--;
    // Como um item foi retirado, lista->tamanho (a quantidade de elementos) é decrementado.
    lista->tamanho--;

    // O item que foi retirado da lista é retornado ao usuário.
    return it;
}

/*
A função "lista_item", cujo retorno é do tipo ITEM *, tem a função de retornar ao usuário o item da lista com uma
determinada chave, recebida como parâmetro da função.
01) Caso a lista não exista ou o item procurado não existe na lista, é retornado NULL.
02) Caso contrário a lista existe e foi encontrado, a partir da função "lista_busca" (Tem que ter retornado 'meio')
e a comparação se a chave é a mesma, o respectivo item é retornado, mas não é removido da lista.
Complexidade: O(LOG N).
*/
ITEM *lista_item(LISTA *lista, int chave) {
    // Verificação se a lista existe
    if(lista != NULL) {
        // A função "lista_busca" (O(LOG N)) é chamada para encontrar a posição do item com chave dada na lista ordenada
        int i = lista_busca(lista, chave);
        // Caso de "lista_busca" retornar o fim da lista, indicativo de que o item não existe
        if(i >= lista->fim) {
            // Retorna NULL, mostrando que o item não existe
            return NULL;
        }
        // Verificação para ver se a posição retornada pelo "lista_busca" é de um item com a mesma chave(Retornou 'meio')
        if(chave != item_get_chave(lista->itens[i]) ) {
            // Retorna NULL, mostrando que não há um item com aquela chave na lista.
            return NULL;
        }
        // O item com a chave almejada é retornado.
        return (lista->itens[i]);
    }
    // Retorna NULL se a lista não existe
    return NULL;
}

/* 
A função "lista_tamanho", cujo o retorno é do tipo inteiro, é responsável por retornar o tamanho (a quantidade de elementos) dentro da lista em questão.
01) Caso a lista não exista, retorna-se uma constante ERRO.
02) Caso ela exista, é retornado o campo da struct LISTA, lista->tamanho, indicando a quantidade de elementos dentro dela.
Complexidade: O(1).
*/
int lista_tamanho(LISTA *lista) {
    // Verificação se a lista existe.
    if(lista != NULL) {
        // Retorna o campo da da struct LISTA, lista->tamanho, indicando a quantidade de elementos existentes nela.
        return(lista->tamanho);
    }
    // Retorna um ERRO (-1), sabendo que o tamanho não pode ser negativo.
    return ERRO;
}

/*
A função "lista_vazia", cujo o retorno é do tipo booleano, é responsável por retornar se é VERDADE OU FALSO que o tamanho da lista, armazenado no campo
da struct LISTA, é 0.
01) Caso a lista não exista, retorna-se VERDADEIRO.
02) Caso ele exista, é retornado:
 * VERDADEIRO: se não há elementos na lista, isto é, seu tamanho é 0.
 * FALSO: se há pelo menos um elemento na lista, isto é, seu tamanho não é 0.
Complexidade: O(1).
*/
bool lista_vazia(LISTA *lista){         
    // Verificação se a lista existe.                                                                                                                                                                                                      
    if(lista != NULL) {               
        // Retorna o valor booleano da comparação de lista->tamanho com 0: VERDADEIRO, se lista->tamanho = 0, do contrário, FALSO.                                                                                                                                                                                                   
        return (lista->tamanho == 0);       
    }                                                                                                                                                                                                    
    // Retorna VERDADEIRO por padrão quando a lista não existe.                                                                                                                                                                                                                                   
    return true;                                                                                                                                                                                                                              
}                                                                                                                                                                                                                                             

/*
A função "lista_cheia", cujo o retorno é do tipo booleano, é responsável por retornar se é VERDADE OU FALSO que o tamanho da lista, armazenado no campo
da struct LISTA, é o mesmo valor ou maior que TAM_MAX.
01) Caso a lista não exista, retorna-se VERDADEIRO.
02) Caso ele exista, é retornado:
 * VERDADEIRO: se o campo da struct LISTA, lista->tamanho, atingiu ou ultrapassou o limite do tamanho do vetor (TAM_MAX), configurando um lista cheio.
 * FALSO:  se o campo da struct LISTA, lista->tamanho, ainda não atingiu o limite do tamanho do vetor (TAM_MAX), configurando um lista que ainda há
posições vagas.
Complexidade: O(1).
*/                                                                                                                                                                                                                               
bool lista_cheia(LISTA *lista){    
    // Verificação se a lista existe.                                                                                                                                                                                                           
    if(lista != NULL) {                            
        // Retorna o valor booleano da comparação de lista->tamanho com TAM_MAX: VERDADEIRO, se lista->tamanho >= TAM_MAX, do contrário, FALSO.                                                                                                                                                                                             
        return (lista->tamanho >= TAM_MAX);                                                                                                                                                                                                     
    }                  
    // Retorna VERDADEIRO por padrão quando a lista não existe.                                                                                                                                                                                                           
    return true;                                                                                                                                                                                                                              
}  

/* 
A função "lista_apagar", cujo retorno é do tipo void, a partir do duplo ponteiro que é recebido como parâmetro, tem o papel de liberar a memória
alocada de cada item do vetor de itens, e somente depois, liberar o espaço alocado para a estrutura da lista.
01) Caso a lista recebida seja nulo, ou seja, não tenha ocorrido corretamente a alocação dinâmica, nenhuma operação é realizada.
02) Caso a lista não seja nula, ou seja, tenha ocorrido corretamente a alocação dinâmica, são liberados os itens e depois a estrutura em si.
Complexidade: O(N).
O for precisa fazer a operação de receber o item e a liberação de sua memória N vezes.
*/
void lista_apagar(LISTA **lista) {
    // Verificação se a lista é nulo/existe.
    if (lista == NULL || *lista == NULL) {
        // Retorna, sem fazer nenhuma operação
        return;
    }
    // O for percorre toda a lista, da posição de início até o último elemento, localizado em lista->fim-1
    for (int i = (*lista)->inicio; i < (*lista)->fim; i++) {
        // A variável 'it', do tipo ITEM *, passa a apontar para o endereço do item de cada iteração
        ITEM *it = (*lista)->itens[(*lista)->inicio + i];
        // Apaga cada um dos itens que estavam dentro da lista, liberando a sua memória
        item_apagar(&it);
    }
    // Depois de liberada a memória de cada item, a memória da estrutura pode ser liberada.
    free(*lista);
    // Como boa prática, faz-se o ponteiro para lista receber nulo, a fim de não ser possível acessar mais a região de memória liberada.
    *lista = NULL;
    // Apenas retorna, sem devolver nada.
    return;
}

