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
    // 1 é falso. 0 é verdadeiro.
    if(ab_checar_busca(arvore_binaria))
    {
        printf("NÃO!"); 
    }else{
        printf("É DE BUSCA SIM!");
    }

    ab_apagar_arvore(&arvore_binaria);

    return 0;

}