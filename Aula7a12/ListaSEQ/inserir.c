#include"lista.h"

#include<stdio.h>
#include<stdlib.h>

#ifndef STRUCTS_

    #define STRUCTS_

    struct lista_{ 

        ITEM *lista[TAM_MAX];

        int inicio; // pos do primeiro item

        int fim; // pos do próximo espaço vazio

        int tamanho;

    };

#endif


bool lista_inserir_posicao(LISTA *lista, int x, ITEM *item);
int lista_busca_ordenada(LISTA *lista,int chave);

bool lista_inserir(LISTA *lista, ITEM *item){
    if(lista != NULL && !(lista->tamanho == TAM_MAX)){
        int x = lista_busca_ordenada(lista, item_get_chave(item));
        return (lista_inserir_posicao(lista, x, item));
    }
    return false;
}

bool lista_inserir_posicao(LISTA *lista, int x, ITEM *item){
    for (int i = lista->fim; i > x; i--){
        lista->lista[i] = lista->lista[i - 1];
    }
    lista->lista[x] = item;
    lista->tamanho++; lista->fim++;

    return true; 
}

int lista_busca_ordenada(LISTA *lista,int chave){
    int l = lista->inicio, r = (lista->fim) - 1;
    if(r == -1) return 0;
    while(l < r){
        int media = (l+r)/2;
        if(chave <= item_get_chave(lista->lista[media])){
            r = media;
        }
        else{
            l = media + 1;
        }
    } 

    if(item_get_chave(lista->lista[l]) >= chave){
        return (l);
    }
    else return(lista->fim);
}



