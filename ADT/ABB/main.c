#include "ABB.h"

#include<stdio.h>
#include<stdlib.h>

int main()
{
    ABB *abb = abb_criar();

    abb_inserir(abb, item_criar(1, NULL));
    abb_inserir(abb, item_criar(2, NULL));
    abb_inserir(abb, item_criar(3, NULL));
    abb_inserir(abb, item_criar(4, NULL));
    abb_inserir(abb, item_criar(5, NULL));
    abb_inserir(abb, item_criar(6, NULL));
    abb_inserir(abb, item_criar(6, NULL));
    abb_inserir(abb, item_criar(7, NULL));
    abb_inserir(abb, item_criar(8, NULL));
    abb_inserir(abb, item_criar(9, NULL));
    abb_remover(abb, 3);
    abb_remover(abb, 4);
    abb_remover(abb, 5);
    abb_remover(abb, 6);
    abb_remover(abb, 3);
    abb_remover(abb, 10);
    abb_imprimir(abb);
    abb_apagar(&abb);

    return 0;

}