#ifndef ITEM_H
	#define ITEM_H
	#include <stdbool.h>

	/* ESTE É O TAD ITEM */

	/* TYPEDEF utilizado para representar o tipo 'struct item_' apenas por 'ITEM' */
	typedef struct item_ ITEM;

	/* A função "item_criar", cujo retorno tem tipo ITEM*, tem o papel de criar o item, com os parâmetros recebidos, alocando a sua memória
	dinamicamente: */
	ITEM *item_criar (int chave, void *comp);

	/* A função "item_apagar", cujo retorno é do tipo booleano, tem o papel de liberar a memória alocada do item, a partir do duplo ponteiro que
	 é recebido como parâmetro */
	bool item_apagar (ITEM **item);

	/* A função "item_get_chave", cujo retorno é do tipo inteiro, tem o papel de acessar o campo da 'chave' dentro da struct de um item recebido
	como parâmetro */
	int item_get_chave (ITEM *item);

	/* A função "item_set_chave", cujo retorno é do tipo booleano, tem o papel de inicializar/alterar o campo 'chave' da struct do item recebido
	item por uma outra 'chave', que também é recebida como parâmetro da função */
	bool item_set_chave (ITEM *item, int chave);

	/* A função "item_get_dados", cujo retorno é do tipo ponteiro void (void *), tem o papel de acessar o campo 'dado' dentro da struct de um
	item recebido como parâmetro: */
	void *item_get_dados (ITEM *item);

#endif
