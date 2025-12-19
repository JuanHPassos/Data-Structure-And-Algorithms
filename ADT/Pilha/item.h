#ifndef ITEM_H
	#define ITEM_H
	
	#include <stdbool.h>

	typedef struct item_ ITEM;

	// Responsabilidade de apagar os dados é do usuário.

	ITEM *item_criar (int chave, void *dado);
	bool item_apagar (ITEM **item);
	int item_get_chave (ITEM *item);
	bool item_set_chave (ITEM *item, int chave);
	void *item_get_dados (ITEM *item);
	void item_set_dados (ITEM *item, void *dado);

#endif
