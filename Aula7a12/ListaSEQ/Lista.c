#include<stdio.h>
#include<stdlib.h>

#include "Lista.h"

struct lista_{
    int ini;
    int fim; // Ultimo elemento igual a fim-1.
    int tamanho;
    bool ordenada; // Ordenada se = 1. Não ordenada se = 0.
    ITEM *itens[TAM_MAX];
}; 

// Modulariazação das funções
int lista_busca_sequencial(LISTA *lista, int chave);
int lista_busca_ordenada(LISTA *lista,int chave);
bool lista_inserir_fim(LISTA *lista, ITEM *item);
bool lista_inserir_posicao(LISTA *lista, int x, ITEM *item);

LISTA *lista_criar(bool ordenada){
    LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
    if(lista != NULL){
        lista->ini = 0;
        lista->fim = 0;
        lista->ordenada = ordenada;
        lista->tamanho = 0;
    }
}

bool lista_inserir(LISTA *lista, ITEM *item){
    if(!lista_cheia(lista)){
        if(!(lista->ordenada)){
            return(lista_inserir_fim(lista, item));
        }
        else{
            int x = lista_busca_ordenada(lista, item_get_chave(item));
            if(x == -1) x = lista->fim;
            return (lista_inserir_posicao(lista, x, item));
        }
        return true;
    }
    return false;
}

bool lista_inserir_fim(LISTA *lista, ITEM *item){
    lista->itens[lista->fim] = item;
    lista->tamanho++; lista->fim++;
    return true;
}


bool lista_inserir_posicao(LISTA *lista, int x, ITEM *item){
    for (int i = lista->fim; i > x; i--){
        lista->itens[i] = lista->itens[i - 1];
    }
    lista->itens[x] = item;
    lista->tamanho++; lista->fim++;

    return true; 
}

bool lista_apagar(LISTA **lista){
    if(!lista_vazia(*lista)){
        int index = (*lista)->ini;
        while(index != (*lista)->fim){
            item_apagar(&((*lista)->itens[index]));
            index++;
            (*lista)->tamanho--;
        }
        free(*lista); *lista = NULL;
        
        return(true);
    }
    return(false);
}

ITEM *lista_remover(LISTA *lista, int chave){
    if(!lista_vazia(lista)){
        int posicao = -1;
        if(lista->ordenada){
            posicao = lista_busca_ordenada(lista, chave);
        }
        else{
            posicao = lista_busca_sequencial(lista, chave);
        }

        if(posicao == -1) return NULL;

        ITEM *retorno = lista->itens[posicao];
        lista->itens[posicao] = NULL;
        
        for(int i = posicao; i < (lista->fim) - 1; i++){
            lista->itens[i] = lista->itens[i+1];
        }

        lista->fim--;
        lista->tamanho--;

        return(retorno);
        
    }
    return(NULL);
}

int lista_busca_ordenada(LISTA *lista,int chave){
    int l = lista->ini, r = (lista->fim) - 1;
    
    if(r == -1) return 0; // Se lista vazia, insere no inicio.
    
    while(l < r){
        int media = (l+r)/2;
        if(chave <= item_get_chave(lista->itens[media])){
            r = media;
        }
        else{
            l = media + 1;
        }
    } 

    if(item_get_chave(lista->itens[l]) >= chave){
        return (l);
    }
    else return(-1); // Não achou esse item.
}

int lista_busca_sequencial(LISTA *lista, int chave){
    for(int i = lista->fim; i < lista->fim; i++){
        if(chave == item_get_chave(lista->itens[i])){
            return i;
        }
    }
    return(-1); // Não existe posição menos 1, logo simboliza que nao achou.
}

ITEM *lista_busca(LISTA *lista, int chave){
    int x = -1;
    if(!lista_vazia(lista)){
        if(lista->ordenada)
            x = lista_busca_ordenada(lista, chave);
        else
            x = lista_busca_sequencial(lista, chave);
    }
     // Função de busca binaria, retorna maior cas nao ache igual.
    if(x == -1 || item_get_chave(lista->itens[x]) != chave) return NULL;
    else return(lista->itens[x]);
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
        while(index != lista->fim){
            printf("%d", item_get_chave(lista->itens[index]));
            index++;
        }
    }
}
