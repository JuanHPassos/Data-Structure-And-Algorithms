#include "item.h"
#include"ABB.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct no_ NO;

struct no_
{
    ITEM *item;
    // Filhos esquerdo e direito.
    NO *esq;
    NO *dir;
};

struct abb_
{
    NO *raiz;
    int tamanho;
};

// Modularização
NO *abb_inserir_no(NO *raiz, NO *no, bool *inserido);
ITEM *abb_busca_no(NO *raiz, int chave);
NO *abb_remover_no(NO *raiz, int chave, ITEM **item);
void abb_imprimir_no(NO *raiz);
void abb_apagar_no(NO *raiz);
NO *pegar_sucessor(NO *raiz);

// Criar árvore binária, retorna nulo caso falhe.
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

// Retorna falso caso abb nula ou memoria cheia.
bool abb_inserir(ABB *abb, ITEM *item)
{
    bool inserido = false; // Verifica inserção.
    if(abb != NULL && item != NULL)
    {
        NO *novo_no = (NO*) malloc(sizeof(NO));
        if(novo_no != NULL)
        {
            // Inicializa-se novo nó.
            novo_no->item = item;
            // Nó inserido é folha.
            novo_no->esq = NULL;
            novo_no->dir = NULL;
            
            // Função recursiva para inserir nó, retorna raiz.
            abb->raiz = abb_inserir_no(abb->raiz, novo_no, &inserido);

            // Atualizar tamanho caso elemento tenha sido inserido.
            if(inserido == true)
                abb->tamanho++;

            return inserido;
        }
        // Se novo_no nulo, memória cheia.
    }
    // Não se insere em uma árvore nula.
    return inserido;
}

// Retorna raiz.
NO *abb_inserir_no(NO *raiz, NO *folha, bool *inserido)
{
    // Se raiz nula, achou lugar de inserção.
    if(raiz == NULL)
    {
        raiz = folha;
        *inserido = true; // Nó inserido.
    }
    // Sendo chave procurada menor que a atual, percorre-se a esquerda.
    // Caso seja maior, percorre-se o caminho da direita.
    else if (item_get_chave(folha->item) < item_get_chave(raiz->item))
        raiz->esq = abb_inserir_no(raiz->esq, folha, inserido);
    else if(item_get_chave(folha->item) > item_get_chave(raiz->item))
        raiz->dir = abb_inserir_no(raiz->dir, folha, inserido);
    
    return raiz;
}

// Retorna nulo caso item não esteja na árvore.
ITEM *abb_busca(ABB *abb, int chave)
{
    ITEM *item = NULL;
    if(abb != NULL)
        item = abb_busca_no(abb->raiz, chave);

    return item;
}

// Retorna nulo caso não encontre o item.
ITEM *abb_busca_no(NO *raiz, int chave)
{
    if(raiz != NULL)
    {
        if(chave < item_get_chave(raiz->item))
            // Propaga resultado.
            return abb_busca_no(raiz->esq, chave);
        else if(chave > item_get_chave(raiz->item))
            // Propaga resultado.
            return abb_busca_no(raiz->dir, chave);
        else
            // Item encontrado.
            return raiz->item;
    }
    // Item não está na árvore.
    return NULL;
}

// Retorna nulo caso item não esteja na árvore.
ITEM *abb_remover(ABB *abb, int chave)
{
    // Retorna item ao usuário.
    ITEM *item = NULL;

    if(abb != NULL)
    {
        // Remover nó com chave passado no parametro.
        abb->raiz = abb_remover_no(abb->raiz, chave, &item);
        // Se houve remoção, atualiza-se o tamanho da árvore.
        if(item != NULL)
            abb->tamanho--;
    }
    // Retorna nulo caso chave não esteja na árvore.
    return item;
}

NO *abb_remover_no(NO *raiz, int chave, ITEM **item)
{
    // Se encontrou nulo, chave não está na árvore.
    if(raiz == NULL)
        return NULL;

    // Se chave menor que nó atual, percorre-se esquerda.
    if(chave < item_get_chave(raiz->item))
        raiz->esq = abb_remover_no(raiz->esq, chave, item);
    // Se chave maior que nó atual, percorre-se direita.
    else if(chave > item_get_chave(raiz->item))
        raiz->dir = abb_remover_no(raiz->dir, chave, item);
    else
    {
        // Caso o elemento ainda não tenha sido removido.
        if(*item == NULL)
            *item = raiz->item;

        // Caso não exista filho esquerdo.
        // Incluso caso que raiz é folha.
        if(raiz->esq == NULL)
        {
            // Filho direito assumirá lugar do pai.
            NO *filho_direito = raiz->dir;
            free(raiz);
            raiz = filho_direito;
        }
        // Caso filho direito nulo e esquerdo não nulo.
        else if(raiz->dir == NULL)
        {
            // Filho esquerdo assume lugar do pai.
            NO *filho_esquerdo = raiz->esq;
            free(raiz);
            raiz = filho_esquerdo;
        }
        // Caso exista os dois filhos.
        else
        {
            // Pega-se nó com chave sucessora ao atual.
            NO *sucessor = pegar_sucessor(raiz);       
            raiz->item = sucessor->item;
            // Problema reduzida a remover uma folha da sub-árvore.
            raiz->dir = abb_remover_no(raiz->dir, item_get_chave(sucessor->item), item);
        }
    }

    return raiz;
} 

// Retorna folha(sucessor do nó de dois filhos)
NO *pegar_sucessor(NO *raiz)
{
    NO *folha = raiz->dir;
    // Sucessor é o menor elemento
    // da sub-árvore da direita.
    while(folha->esq != NULL)
        folha = folha->esq;
    
    return folha;
} 

// Apaga árvore, itens e dados.
void abb_apagar(ABB **abb)
{
    if(*abb != NULL)
    {
        abb_apagar_no((*abb)->raiz);
        free(*abb);
        *abb = NULL;
    }
}

// Apaga árvore em pós-ordem.
void abb_apagar_no(NO *raiz)
{
    if(raiz != NULL)
    {
        abb_apagar_no(raiz->esq);
        abb_apagar_no(raiz->dir);
        // Apagar dado, itens e nó.
        void *dado = item_get_dados(raiz->item);
        if(dado != NULL)
        {
            free(dado);
            dado = NULL;
        }
        
        if(raiz->item != NULL)
        {
            free(raiz->item);
            raiz->item = NULL;
        }
        
        free(raiz);
        raiz = NULL;
    }
}



// Imprime árvore em ordem(crescente)
void abb_imprimir(ABB *abb)
{
    if(abb != NULL)
        abb_imprimir_no(abb->raiz);
}

// Imprime recursivamente uma árvore binária.
void abb_imprimir_no(NO *raiz)
{
    if(raiz != NULL)
    {
        abb_imprimir_no(raiz->esq);
        printf("%d ", item_get_chave(raiz->item));
        abb_imprimir_no(raiz->dir);
    }
}

