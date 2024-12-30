#include "item.h"

#include<stdio.h>
#include<stdlib.h>

struct item_
{
    int chave;
    // Guarda um ponteiro de algum tipo.
    // Ocorra cast do ponteiro void.
    void *dado;
};

// Cria um item(tipo abstrato de dado)
ITEM *item_criar (int chave, void *dado)
{
    ITEM *item = (ITEM*) malloc(sizeof(ITEM));
    // Caso haja memória, inicializa-se os campos.
    if(item != NULL)
    {
        item->chave = chave;
        item->dado = dado;
    }
    // Retorna nulo caso não haja memória.
    return item;
}

// Apaga um item, retorna se foi possível apagar o item.
bool item_apagar (ITEM **item){
    // Caso o item exista.
    if((*item) != NULL)
    {
        // Apaga-se o dado que o item guarda(caso exista).
        // if((*item)->dado != NULL)
        // {
        //     free((*item)->dado);
        //     (*item)->dado = NULL;
        // }

        // Apaga o item.
        free(*item);
        *item = NULL;
        return true;
    }
    return false;
}

// Retorna a chave presente no item.	
int item_get_chave (ITEM *item)
{
    if(item != NULL)
    {
        return item->chave;
    }
    // Se o item não existir, não se pode retornar valor simbolico
    // pois pode ser interpretado como a chave do item
    // assim opta-se por encerrar o programa.
    exit(1);
}

// Trocar chave de um item.
bool item_set_chave (ITEM *item, int chave)
{
    if(item != NULL)
    {
        // Troca-se a chave pelo parâmetro.
        item->chave = chave;
        return true;
    }
    return false;
}

// Acesso ao ponteiro guardado no item.
// Retorna nulo caso item não exista.
void *item_get_dados (ITEM *item)
{
    if(item != NULL)
    {
        // Sofre cast ao tipo desejado ao ser atribuido.
        return item->dado;
    }
    return NULL;
}

// Atualiza dado do item com o que foi passado como parametro.
void item_set_dados (ITEM *item, void *dado)
{
    if(item != NULL)
    {
        // Implementação apagando dados.
        // if(item->dado != NULL)
        //     free(item->dado);

        // Atualiza dado do item.
        item->dado = dado;
    }
}