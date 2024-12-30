#include"Pilha.h"

#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    PILHA *pilha = pilha_criar();

    pilha_empilhar(pilha, item_criar(1, NULL));
    pilha_empilhar(pilha, item_criar(2, NULL));
    pilha_empilhar(pilha, item_criar(3, NULL));
    pilha_empilhar(pilha, item_criar(4, NULL));
    pilha_empilhar(pilha, item_criar(5, NULL));
    pilha_empilhar(pilha, item_criar(6, NULL));
    pilha_empilhar(pilha, item_criar(7, NULL));
    pilha_imprimir(pilha);
    pilha_inverter(&pilha);
    pilha_imprimir(pilha);
    for(int i = 0; i < 7; i++)
    {
        ITEM *item = pilha_desempilhar(pilha);
        if(item != NULL)
        {
            printf("Chave: %d\n", item_get_chave(item));
            item_apagar(&item);
        }
    }
    pilha_apagar(&pilha);
    
    return 0;
}