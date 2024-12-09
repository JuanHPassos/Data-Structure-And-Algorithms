#include<stdio.h>
#include<stdlib.h>

#include "Lista.h"

int main(void){
    LISTA *lista = lista_criar(1);

    lista_inserir(lista, item_criar(13, NULL));
    lista_inserir(lista, item_criar(2, NULL));
    lista_inserir(lista, item_criar(5, NULL));
    lista_inserir(lista, item_criar(6, NULL));
    lista_inserir(lista, item_criar(3, NULL));
    lista_inserir(lista, item_criar(4, NULL));
    lista_remover(lista, 5);
    lista_imprimir(lista);
    lista_remover(lista, 6);
    lista_imprimir(lista);
    lista_remover(lista, 1293);
    lista_imprimir(lista);
    lista_remover(lista, 2);
    lista_imprimir(lista);
    lista_remover(lista, 13);
    lista_imprimir(lista);
    lista_apagar(&lista);

    return 0;
}