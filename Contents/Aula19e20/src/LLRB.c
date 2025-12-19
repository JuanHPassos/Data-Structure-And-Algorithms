#include "LLRB.h"

#include<stdlib.h>
#include<stdio.h>

typedef struct no_ NO;

struct no_
{
    ITEM *item;
    NO *esq;
    NO* dir;
    int cor; // Preto = 0. Vermelho = 1.
};

struct llrb_
{
    NO *raiz;
    int tamanho;
};

// Modularização
void llrb_inverter(NO *raiz);
NO *rot_dir(NO *A);
NO *rot_esq(NO *B);

LLRB *llrb_criar(void)
{
    LLRB *llrb = (LLRB*) malloc(sizeof(LLRB));
    if(llrb != NULL)
    {
        llrb->raiz = NULL;
        llrb->tamanho = 0;
    }
}

// Função que garante que um nó não terá duas ligações vermelhas.
void llrb_inverter(NO *raiz)
{
    // Inverte cores.
    raiz->cor = !(raiz->cor);
    raiz->esq->cor = !(raiz->esq->cor);
    raiz->dir->cor = !(raiz->dir->cor);
}

// Rotação direita em uma llrb
NO *rot_dir(NO *A)
{
    NO *B = A->esq;

    A->esq = B->dir;
    B->dir = A;

    B->cor = A->cor;
    A->cor = 1; // Aresta que causou desbalanceamento(vermelha).

    return B;
}

// Rotação esquerda em uma llrb
NO *rot_esq(NO *B)
{
    NO *C = B->dir;
    // Rotação esquerda.
    B->dir = C->esq; 
    C->esq = B;
    // Ajuste cores.
    C->cor = B->cor;
    B->cor = 1; // Vermelha.

    return C;
}