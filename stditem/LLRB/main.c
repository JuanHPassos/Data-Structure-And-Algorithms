#include "LLRB.h"

#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    LLRB *llrb = llrb_criar();

    llrb_inserir(llrb, item_criar(6, NULL));
    llrb_inserir(llrb, item_criar(3, NULL));
    llrb_inserir(llrb, item_criar(8, NULL));
    llrb_inserir(llrb, item_criar(2, NULL));
    llrb_inserir(llrb, item_criar(5, NULL));
    llrb_inserir(llrb, item_criar(7, NULL));
    ITEM *busca = llrb_buscar(llrb, 7);
    if(busca != NULL)
        printf("Chave: %d", item_get_chave(busca));

    printf("\n");
    llrb_imprimir(llrb);
    printf("\n");
    
    ITEM *apagar = llrb_remover(llrb, 3);
    void *dado = item_get_dados(apagar);
    if(dado != NULL)
    {
        free(dado);
        dado = NULL;
    }
    item_apagar(&apagar);

    llrb_imprimir(llrb);
}