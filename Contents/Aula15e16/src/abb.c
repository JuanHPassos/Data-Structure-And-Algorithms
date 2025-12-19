#include "item.h"
#include"abb.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct no_ NO;

struct no_
{
    ITEM *item;
    NO *esq;
    NO *dir;
};

struct abb
{
    NO* raiz;
    int tamanho;
};

// Modularização do código
NO *abb_inserir_no(NO *raiz, NO *no);
ITEM *abb_busca_no(NO *raiz, int chave);
NO *abb_remover_no(NO *raiz, int chave, bool *removido);
NO *pegar_sucessor(NO *raiz);
int abb_perfeitamente_balanceada_no(NO *raiz);
void abb_imprimir_no(NO* raiz);
void abb_apagar_arvore_no(NO **raiz);

ABB *abb_criar (void)
{
    ABB *abb = (ABB*) malloc(sizeof(ABB));
    if(abb != NULL)
    {
        abb->raiz = NULL;
        abb->tamanho = 0;
    }
    return abb;
}

void abb_imprimir (ABB *T)
{
    if(T != NULL)
    {
        printf("Árvore binária: \n");
        abb_imprimir_no(T->raiz);
        printf("\n");
    }
}

// Impressão da árvore em ordem.
void abb_imprimir_no(NO* raiz)
{
    if(raiz != NULL)
    {
        abb_imprimir_no(raiz->esq);
        printf("%d ", item_get_chave(raiz->item));
        abb_imprimir_no(raiz->dir);
    }
}

// Chama função recursiva que apaga arvore binaria.
void abb_apagar_arvore(ABB **T)
{
    if(*T != NULL)
    {
        abb_apagar_arvore_no(&((*T)->raiz));  
        free(*T);
        *T = NULL;  
    }
    return;
}

// Apaga uma árvore em pos-ordem, desalocando memoria.
void abb_apagar_arvore_no(NO **raiz)
{
    if(*raiz != NULL)
    {
        // Percorre a árvore em pos-ordem.
        abb_apagar_arvore_no(&((*raiz)->esq));
        abb_apagar_arvore_no(&((*raiz)->dir));
        // Desalocação de memória.
        item_apagar(&((*raiz)->item));
        free(*raiz);
        *raiz = NULL;
    }
}

// Função para inserir em uma árvore binária.
bool abb_inserir(ABB *abb, ITEM *item)
{
    if(abb != NULL)
    {
        NO *novo_no = (NO*) malloc(sizeof(NO));
        if(novo_no != NULL)
        {
            novo_no->item = item;
            novo_no->esq = NULL;
            novo_no->dir = NULL;
            abb->raiz = abb_inserir_no(abb->raiz, novo_no);
            abb->tamanho++;

            return true;
        }
    }
    return false;
}

NO *abb_inserir_no(NO *raiz, NO *no)
{
    if(raiz == NULL)
    {
        raiz = no;
    }

    else if( item_get_chave(no->item) < item_get_chave(raiz->item) )
        raiz->esq = abb_inserir_no(raiz->esq, no);
    else if( item_get_chave(no->item) > item_get_chave(raiz->item) )
        raiz->dir = abb_inserir_no(raiz->dir, no);
    else
    {
        // Se já houver a chave, mantém-se a antiga.
        item_apagar(&(no->item));
        free(no);
    }
    
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

bool abb_remover(ABB *abb, int chave)
{
    // Controle da remoção.
    bool removido = false;
    // Se árvore existir.
    if(abb != NULL)
    {
        // Remover nó com chave passado no parametro.
        abb->raiz = abb_remover_no(abb->raiz, chave, &removido);
        // Se houve remoção, atualiza-se o tamanho da árvore.
        if(removido)
            abb->tamanho--;
    }
    return removido;
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
            raiz->dir = abb_remover_no(raiz->dir, item_get_chave(sucessor->item), removido);
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

bool abb_vazia(ABB *T)
{
    if(T != NULL)
    {
        return (T->raiz == NULL); 
    }
    return true;
}
// Retorna 0 para verdadeiro e 1 para falso.
bool abb_perfeitamente_balanceada(ABB *T)
{
    if(T != NULL)
    {
        // Se retornar -1, não é perfeitamente balanceada.
        int perf_balan = abb_perfeitamente_balanceada_no(T->raiz);
        // Retorna 1 que simboliza falso, e 0 verdadeiro.
        if(perf_balan == -1)
            return 1;
        else
            return 0;
    }
    return 0;
}

int abb_perfeitamente_balanceada_no(NO *raiz)
{
    // Se não há nó, a quantidade equivale a 0.
    if(raiz != NULL)
    {
        // Calcula os nós da esquerda.
        int esq = abb_perfeitamente_balanceada_no(raiz->esq);
        // Se árvore estiver desbalanceada, se propaga o resultado.
        if(esq == -1) return -1;

        // Calcula os nós da direita.
        int dir = abb_perfeitamente_balanceada_no(raiz->dir);
        // Se árvore estiver desbalanceada, se propaga o resultado.
        if(dir == -1) return -1;

        // Se diferença dos nós nas sub-árvores for maior que 1, está desbalanceada.
        if(abs(esq - dir) > 1) return -1;

        // Quantidade de nós dessa árvore:
        // Nós da sub-árvore da esquerda.
        // Nós da sub-árvore da direita. 
        // + o nó atual.
        return (esq + dir) + 1; 
    }
    return 0;
}