#include "Lista.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct no_ NO;

struct no_{
    NO *proximo;
    int chave;
};

struct lista_{
    NO *cabeca;
    NO *fim;
    int tamanho;  
    bool ordenada;  
};

// Modularização
bool lista_inserir_ordenada(LISTA *lista,int chave);
bool lista_inserir_fim(lista, chave);

LISTA *lista_criar(bool ordenada){
    LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
    if(lista != NULL){
        NO *cabeca = (NO*) malloc(sizeof(NO));
        
        cabeca->proximo = cabeca;
        lista->cabeca = cabeca;
        lista->fim = NULL;
        cabeca->chave = -1;
        lista->tamanho = 0;
        lista->ordenada = ordenada;
    }
    return lista;
}

bool lista_inserir(LISTA *lista, int chave){
    if(!lista_cheia(lista)){
        lista->cabeca->chave = chave;
        if(lista->ordenada){
            lista_inserir_ordenada(lista, chave);
        }
        else{
            lista_inserir_fim(lista, chave);
        }
        lista->cabeca->chave = -1;
        lista->tamanho++;

        return true;
    }
    return false;
}

bool lista_inserir_ordenada(LISTA *lista,int chave){
    NO *busca = lista->cabeca;

    NO *no = (NO*) malloc(sizeof(NO));
    no->chave = chave;

    while(busca->proximo->chave <= chave){
        busca = busca->proximo;
    }

    no->proximo = busca->proximo;
    busca->proximo = no;

    // Se o no inserido for o ultimo, ou seja, aponta para o no cabeca, ele e o fim.
    if(no->proximo == lista->cabeca)
        lista->fim = no;

    busca = NULL;
    no = NULL;

    return true;
}

bool lista_inserir_fim(LISTA *lista,int chave){
    NO *no = (NO*) malloc(sizeof(NO));
    no->chave = chave;

    no->proximo = lista->cabeca;
    lista->fim->proximo = no;
    lista->fim = no;

    return true;
}

bool lista_apagar(LISTA **lista);

bool lista_remover(LISTA *lista, int chave){
    if(!lista_vazia(lista)){
        lista->cabeca->chave = chave;
        if(lista->ordenada){
            lista_remover_ordenada(lista, chave);
        }
        else{
            lista_remover_chave(lista, chave);
        }
        lista->cabeca->chave = -1;
        lista->tamanho--;

        return true;
    }
    return false;
}

bool lista_remover_ordenada(LISTA *lista,int chave){
    NO *busca = lista->cabeca;
    
    while(busca->proximo->chave <= chave){
        busca = busca->proximo;
    }

    if(busca->proximo->chave != chave){
        busca = NULL;
        return true;
    }
    NO *remove = busca->proximo;    
    busca->proximo = remove->proximo;

    if(remove->proximo == lista->cabeca)
        lista->fim = busca;


    busca = NULL;

    return true;
}

bool lista_remover_chave(lista, chave){

}

int lista_busca(LISTA *lista, int chave);
int lista_tamanho(LISTA *lista);
bool lista_vazia(LISTA *lista);
bool lista_cheia(LISTA *lista);
void lista_imprimir(LISTA *lista);
