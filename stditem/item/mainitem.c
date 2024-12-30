#include"item.h"

#include<stdio.h>
#include<stdlib.h>

int **cria_vetor_ints(int tamanho);
ITEM **cria_itens(int tamanho, int **vet_int);
void teste_gets_item(ITEM ***vet_item, int tamanho);
void teste_apagar_item(ITEM ***vet_item,int tamanho);
void teste_set_item(int tamanho, ITEM ***vet_item, int ***vet_int);

int main(void)
{
    int tamanho;

    scanf("%d", &tamanho);

    int **vet_int = cria_vetor_ints(tamanho);

    ITEM **vet_item = cria_itens(tamanho, vet_int);

    teste_gets_item(&vet_item, tamanho);

    teste_set_item(tamanho, &vet_item, &vet_int);

    teste_gets_item(&vet_item, tamanho);

    teste_apagar_item(&vet_item, tamanho);

    free(vet_int);
    vet_int = NULL;

    return 0;
}

int **cria_vetor_ints(int tamanho)
{
    int **vet_int = (int**) malloc(tamanho*sizeof(int*));

    for(int i = 0; i < tamanho; i++)
    {
        vet_int[i] = (int*) malloc(sizeof(int));
        vet_int[i][0] = i;
    }

    return vet_int;
}

ITEM **cria_itens(int tamanho, int **vet_int)
{
    ITEM **vet_item = (ITEM**) malloc(tamanho*sizeof(ITEM*));

    for(int i = 0; i < tamanho; i++)
    {
        vet_item[i] = item_criar(i, vet_int[i]);
    }
    return vet_item;
}

void teste_gets_item(ITEM ***vet_item, int tamanho)
{
    for(int i = 0; i < tamanho; i++)
    {
        int *dado = item_get_dados((*vet_item)[i]);
        printf("Chave: %d, Dado[0]: %d.\n", item_get_chave((*vet_item)[i]), dado[0]);
    }
    printf("\n");
}

void teste_apagar_item(ITEM ***vet_item,int tamanho)
{
    for(int i = 0; i < tamanho; i++)
    {
        int *dado = item_get_dados((*vet_item)[i]);
        free(dado); // Se dado for nulo, houve erro no TAD item.
        dado = NULL;
        item_apagar(&((*vet_item)[i]));
    }
    free(*vet_item);
    *vet_item = NULL;
}

void teste_set_item(int tamanho, ITEM ***vet_item, int ***vet_int)
{
    // Inverti valores.
    for(int i = 0; i < tamanho; i++)
    {
        item_set_chave((*vet_item)[i], ((tamanho - 1) - i));
        item_set_dados((*vet_item)[i], (*vet_int)[(tamanho - 1) - i]);
    }

}
