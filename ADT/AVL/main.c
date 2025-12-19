#include "AVL.h"

#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    AVL *avl = avl_criar();

    avl_inserir(avl, item_criar(30,NULL));
    avl_inserir(avl, item_criar(45,NULL));
    avl_inserir(avl, item_criar(15,NULL));
    avl_inserir(avl, item_criar(41,NULL));
    avl_inserir(avl, item_criar(56,NULL));
    avl_inserir(avl, item_criar(35,NULL));
    avl_inserir(avl, item_criar(43,NULL));
    avl_inserir(avl, item_criar(50,NULL));
    avl_inserir(avl, item_criar(49,NULL));
    avl_inserir(avl, item_criar(60,NULL));
    avl_inserir(avl, item_criar(65,NULL));

    ITEM *item1 = avl_remover(avl, 45);
    ITEM *item2 = avl_remover(avl, 41);

    avl_imprimir(avl);

    printf("\n Itens: %d %d", item_get_chave(item1), item_get_chave(item2));

    avl_apagar(&avl);
}