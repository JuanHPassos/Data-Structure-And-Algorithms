#include "arvorebinaria.h"

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int tamanho_arvore;

    scanf("%d", &tamanho_arvore);

    AB *arvore_binaria = ab_criar();

    for(int i = 0; i < tamanho_arvore; i++)
    {
        int valor, lado, pai;
        scanf("%d %d %d", &valor, &lado, &pai);
        ITEM *item = item_criar(valor, NULL);
        ab_inserir(arvore_binaria, item, lado, pai);
    }

    if(ab_estritamente_binaria(arvore_binaria))
    {
        printf("É ESTRITAMENTE SIM!");
    }else{
        printf("NÃO!");
    }

    ab_apagar_arvore(&arvore_binaria);

    return 0;

}