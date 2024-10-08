#include<stdio.h>
#include<stdlib.h>

#include "Lista.h"

struct lista_{
    char ini;
    char fim; // Ultimo elemento igual a fim-1.
    int tamanho;
    bool ordenada; // Ordenada se = 1. Não ordenada se = 0.
    char chave[TAM_MAX];
}; 

// Modulariazação das funções
int lista_busca_sequencial(LISTA *lista, char chave);
int lista_busca_ordenada(LISTA *lista,char chave);
bool lista_inserir_fim(LISTA *lista, char chave);
bool lista_inserir_posicao(LISTA *lista, char x, char chave);

LISTA *lista_criar(bool ordenada){
    LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
    if(lista != NULL){
        lista->ini = 0;
        lista->fim = 0;
        lista->ordenada = ordenada;
        lista->tamanho = 0;
    }
}

bool lista_inserir(LISTA *lista, char chave){
    if(!lista_cheia(lista)){
        if(lista->ordenada){
            return(lista_inserir_fim(lista, chave));
        }
        else{
            char x = lista_busca_ordenada(lista, chave);
            return (lista_inserir_posicao(lista, x, chave));
        }
        return true;
    }
    return false;
}

bool lista_inserir_fim(LISTA *lista, char chave){
    lista->chave[lista->fim] = chave;
    lista->tamanho++; lista->fim++;
    return true;
}


bool lista_inserir_posicao(LISTA *lista, char x, char chave){
    for (int i = lista->fim; i > x; i--){
        lista->chave[i] = lista->chave[i - 1];
    }
    lista->chave[x] = chave;
    lista->tamanho++; lista->fim++;

    return true; 
}

bool lista_apagar(LISTA **lista){
    if(!lista_vazia(*lista)){
        free(*lista); *lista = NULL;
        
        return(true);
    }
    return(false);
}

bool lista_remover(LISTA *lista, char chave){
    if(!lista_vazia(lista)){
        int posicao = -1;
        if(lista->ordenada){
            posicao = lista_busca_ordenada(lista, chave);
        }
        else{
            posicao = lista_busca_sequencial(lista, chave);
        }

        if(posicao == -1) return(false);
        
        for(int i = posicao; i < (lista->fim) - 1; i++){
            lista->chave[i] = lista->chave[i+1];
        }

        lista->fim--;
        lista->tamanho--;

        return true;
        
    }
    return false;
}

int lista_busca_ordenada(LISTA *lista,char chave){
    int l = lista->ini, r = (lista->fim) - 1;
    if(r == -1) return 0;
    while(l < r){
        int media = (l+r)/2;
        if(chave <= lista->chave[media]){
            r = media;
        }
        else{
            l = media + 1;
        }
    } 

    if(lista->chave[l] >= chave){
        return (l);
    }
    else return(lista->fim);
}

int lista_busca_sequencial(LISTA *lista, char chave){
    for(int i = lista->ini; i < lista->fim; i++){
        if(chave == lista->chave[i]){
            return i;
        }
    }
    return(-1); // Não existe posição menos 1, logo simboliza que nao achou.
}

int lista_busca(LISTA *lista, char chave){
    if(!lista_vazia(lista)){
        if(lista->ordenada)
            return(lista->chave[(lista_busca_ordenada(lista, chave))]);
        else
            return(lista->chave[lista_busca_sequencial(lista, chave)]);
    }
    else return -1;
}

int lista_tamanho(LISTA *lista){
    if(lista != NULL){
        return(lista->tamanho);
    }
    return(-1);
}

bool lista_vazia(LISTA *lista){
    if(lista != NULL){
        return(lista->tamanho == 0);
    }
    return(true);
}

bool lista_cheia(LISTA *lista){
    if(lista != NULL){
        return(lista->tamanho == TAM_MAX);
    }
    return(true);
}

void lista_imprimir(LISTA *lista){
    if(!lista_vazia(lista)){
        int index = lista->ini;
        printf("Lista: ");
        while(index != lista->fim){
            printf("%d ", lista->chave[index]);
            index++;
        }
        printf("\n");
    }
}

char lista_get_chave(LISTA *lista,int i){
    if(lista != NULL){
        return(lista->chave[i]);
    }
    printf("Lista nao existe.");
    exit(1);
}

