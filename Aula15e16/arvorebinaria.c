#include "arvorebinaria.h"

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct no_ NO;

struct no_
{
    ITEM *item;
    NO *esq;
    NO *dir;
};

struct arv_bin
{
    NO *raiz;
    int profundidade;
};

// Modularização
void inserir (NO *raiz, NO *no, int lado, int chave);
void imprimir(NO *raiz);
void apagar_arvore(NO **raiz);
int estritamente_binaria(NO *raiz);
int checar_busca(NO *raiz);

AB *ab_criar(void)
{
    AB *arvorebinaria = (AB*) malloc(sizeof(AB));
    if(arvorebinaria != NULL)
    {
        arvorebinaria->raiz = NULL;
        arvorebinaria->profundidade = -1; // Não existe nenhum nó(existe a árvore).
    }
    return(arvorebinaria);
}

bool ab_inserir (AB *T, ITEM *item, int lado, int chave)
// Arvore binária, item a ser inserido, lado do filho, chave é o pai.
{
    if(T != NULL)
    {
        NO *novo_no = (NO*) malloc(sizeof(NO));
        if(novo_no != NULL)
        {
            novo_no->item = item;
            novo_no->esq = NULL;
            novo_no->dir = NULL;
        }
        if(T->raiz == NULL)
        {
            // Sobrescrever caso já exista.
            if(T->raiz != NULL)
            {
                novo_no->esq = T->raiz->esq;
                novo_no->dir = T->raiz->dir;
                T->raiz->esq = NULL;
                T->raiz->dir = NULL;
                free(T->raiz);
            }
            T->raiz = novo_no;
        }
        else inserir (T->raiz, novo_no, lado, chave);
    }
}
// Implementação pre-ordem
void inserir (NO *raiz, NO *no, int lado, int chave)
{
    if(raiz != NULL)
    {
        if(item_get_chave(raiz->item) == chave)
        {
            // Verifica em qual filho será inserido.
            if(lado == FILHO_ESQ)
            {
                // Sobrescrever caso já exista.
                if(raiz->esq != NULL)
                {
                    no->esq = raiz->esq->esq;
                    no->dir = raiz->esq->dir;
                    raiz->esq->esq = NULL;
                    raiz->esq->dir = NULL;
                    free(raiz->esq);
                }
                raiz->esq = no;
            }else{
                // Sobrescrever caso já exista.
                if(raiz->dir != NULL)
                {
                    no->esq = raiz->dir->esq;
                    no->dir = raiz->dir->dir;
                    raiz->dir->esq = NULL;
                    raiz->dir->dir = NULL;
                    free(raiz->dir);
                }
                raiz->dir = no;
            }
            return;
        }
        // Caso não tenha encontrado o pai, continua a busca.
        inserir(raiz->esq, no, lado, chave);
        inserir(raiz->dir, no, lado, chave);
    }
}
// Chama função que imprimir recursivamente uma arvore de busca binaria
void ab_imprimir (AB *T)
{
    if(T != NULL)
    {
        printf("Arvore Binaria em pre-ordem: \n");
        imprimir(T->raiz);
        printf("\n");
    }
}
// Imprimi uma arvore de forma pre-ordem.
void imprimir(NO *raiz)
{
    if(raiz != NULL)
    {
        printf("%d ", item_get_chave(raiz->item));
        imprimir(raiz->esq);
        imprimir(raiz->dir);
    }
}

// Chama função recursiva que apaga arvore binaria.
void ab_apagar_arvore(AB **T)
{
    if(*T != NULL)
    {
        apagar_arvore(&((*T)->raiz));  
        free(*T);
        *T = NULL;  
    }
    return;
}
// Apaga uma árvore em pos-ordem, desalocando memoria.
void apagar_arvore(NO **raiz)
{
    if(*raiz != NULL)
    {
        // Percorre a árvore em pos-ordem.
        apagar_arvore(&((*raiz)->esq));
        apagar_arvore(&((*raiz)->dir));
        // Desalocação de memória.
        item_apagar(&((*raiz)->item));
        free(*raiz);
        *raiz = NULL;
    }
}

// Retorna 1 se nao for, e 0 se for.
int ab_estritamente_binaria (AB *T)
{
    int boleano = 1;
    if(T != NULL)
    {
        boleano = estritamente_binaria(T->raiz);
    }
    return boleano;
}

// Verifica se todos osnós possuem apenas 0 ou 2 filhos(de forma pre-ordenada).
int estritamente_binaria(NO *raiz)
{
    if (raiz != NULL)
    {
        int filhos = 0;
        if (raiz->esq != NULL) filhos++;
        if (raiz->dir != NULL) filhos++;

        // Se o nó tem apenas um filho, retorna 1 (não é estritamente binária)
        if (filhos == 1) return 1;

        // Verifica recursivamente se as subárvores esquerda e direita são estritamente binárias
        if (estritamente_binaria(raiz->esq) || estritamente_binaria(raiz->dir))
            return 1; // Retorna falso.
    }

    return 0; // Retorna 0 para o caso base onde a árvore é vazia
}

// Checar se árvore passado como parâmetro é binária de busca(ABB).
int ab_checar_busca (AB *T)
{
    int booleano = 1;
    if(T != NULL)
    {
        booleano = checar_busca(T->raiz);
    }

    return booleano;
}

// Função recursiva para percorrer árvore.
int checar_busca(NO *raiz)
{
    // Caso exista o nó.
    if(raiz != NULL)
    {
        // Checar filho esquerdo.
        if(raiz->esq != NULL)
        {
            // Se filho esquerdo for maior que o pai, não é ABB.
            if(item_get_chave(raiz->item) < item_get_chave(raiz->esq->item))
            {
                return 1; // Retorna falso.
            }
        }

        // Checar filho direito.
        if(raiz->dir != NULL)
        {
            // Se filho direito for menor que o pai, não é ABB.
            if(item_get_chave(raiz->item) > item_get_chave(raiz->dir->item))
            {
                return 1; // Retorna falso.
            }
        }
        // Se vier algum um, é falso, entra no if e retorna 1.
        if(checar_busca(raiz->esq) || checar_busca(raiz->dir))
        {
            return 1; // Retorna falso.
        }     
    }
    return 0; // Retorna 1 para o caso base onde a árvore é vazia    
}



