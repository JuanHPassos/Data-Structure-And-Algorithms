#include "item.h"
#include"ABB.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct no_ NO;

struct no_
{
    ITEM *item;
    NO *esq;
    NO *dir;
};

struct abb_
{
    NO* raiz;
    int tamanho;
};

// Modularização
NO *abb_inserir_no(NO *raiz, NO *no, bool *inserido);

NO *cria_no(ITEM *item)
{
    NO *no = (NO*) malloc(sizeof(NO));
    if(no != NULL)
    {
        no->dir = NULL;
        no->esq = NULL;
        no->item = item;
    }
    return no;
}

ABB *abb_criar(void)
{
    ABB *abb = (ABB*) malloc(sizeof(ABB));
    // Caso haja memória, inicia-se os campos da ABB.
    if(abb != NULL)
    {
        abb->raiz = NULL;
        abb->tamanho = 0;
    }
    return abb;
}

// Função para inserir em uma árvore binária.
bool abb_inserir(ABB *abb, ITEM *item)
{
    bool inserido = false; // Verifica inserção.
    if(abb != NULL)
    {
        NO *novo_no = (NO*) malloc(sizeof(NO));
        if(novo_no != NULL)
        {
            novo_no->item = item;
            novo_no->esq = NULL;
            novo_no->item = NULL;
            abb->raiz = abb_inserir_no(abb->raiz, novo_no, &inserido);
            if(inserido)
                abb->tamanho++;

            return inserido;
        }
    }
    return inserido;
}

NO *abb_inserir_no(NO *raiz, NO *no, bool *inserido)
{
    if(raiz == NULL)
    {
        raiz = no;
        *inserido = true; // Nó inserido.
    }
    else if( item_get_chave(no->item) < item_get_chave(raiz->item) )
        raiz->esq = inserir(raiz->esq, no);
    else if( item_get_chave(no->item) > item_get_chave(raiz->item) )
        raiz->dir = inserir(raiz->dir, no);
    
    return raiz;
}

ITEM *abb_busca(ABB *abb, int chave)
{
    ITEM *item = NULL;
    if(abb != NULL)
    {
        item = abb_busca_no(abb->raiz, chave);
    }
    return item;
}

ITEM *abb_busca_no(NO *raiz, int chave)
{
    if(raiz != NULL){
        if(item_get_chave(raiz->item) == chave)
            return raiz->item;
        else
        {
            if(chave < item_get_chave(raiz->item))
                return abb_busca_no(raiz->esq, chave);
            else if(chave < item_get_chave(raiz->item))
                return abb_busca_no(raiz->dir, chave);
            else
                return raiz->item;
        }
    }

    return NULL;
}

ITEM *abb_remover(ABB *abb, int chave)
{
    // Se árvore existir.
    if(abb != NULL)
    {
        bool removido = false;
        // Remover nó com chave passado no parametro.
        abb->raiz = abb_remover_no(abb->raiz, chave, removido);
        // Se houve remoção, atualiza-se o tamanho da árvore.
        if(removido)
            abb->tamanho--;
    }
}

NO *abb_remover_no(NO *raiz, int chave, bool *removido)
{
    if(raiz->item == NULL)
        return NULL;

    if(chave < item_get_chave(raiz->item))
        raiz->esq = abb_remover_no(raiz->esq, chave, removido);
    else if(chave > item_get_chave(raiz->item))
        raiz->dir = abb_remover_no(raiz->dir, chave, removido);
    else
    {
        // Chave existe e será removida.
        *removido = true;
        
        if(raiz->esq == NULL)
        {
            NO *temp = raiz->dir;
            free(raiz);
            raiz = NULL;
            return temp;
        }
        else if(raiz->dir == NULL)
        {
            NO *temp = raiz->esq;
            free(raiz);
            raiz = NULL;
            return temp;
        }
        else
        {
            NO *sucessor = pegar_sucessor(raiz);
            item_apagar(&(raiz->item));                
            raiz->item = sucessor->item;
            raiz->dir = abb_remover_no(raiz->dir, sucessor->item, removido);
        }
    }

    return raiz;
} 

NO *pegar_sucessor(NO *raiz)
{
    NO *no = raiz->dir;
    if(no != NULL)
        while(no->esq != NULL)
        {
            no = no->esq;
        }
    
    return no;
} 