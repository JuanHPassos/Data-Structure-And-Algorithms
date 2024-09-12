#include "Pilha.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct no_ {
    ITEM *item;
    NO* anterior;
}NO;

struct pilha{
    NO* topo;
    int tamanho;
};

PILHA* pilha_criar(void){
    PILHA *pilha;
    pilha = (PILHA*) malloc(sizeof(PILHA));
    if(pilha != NULL){
        pilha->tamanho = 0;
        pilha->topo = NULL; //Boa prática
    }
    return pilha;
}

void pilha_apagar(PILHA** pilha){
    NO *aux = NULL;
    if((*pilha != NULL) && !pilha_vazia(*pilha)){
        while((*pilha)->tamanho != 0){
            aux = (*pilha)->topo;
            //Novo topo é o nó anterior.
            (*pilha)->topo = (*pilha)->topo->anterior;
            //Apaga-se o conteúdo do nó do antigo topo.
            item_apagar(&aux->item);
            //Corta-se a ligação do topo antigo com o novo.
            aux->anterior = NULL;
            (*pilha)->tamanho--;
            free(aux); aux = NULL;
        }
    }
    free(*pilha);
    *pilha = NULL;
}
bool pilha_vazia(PILHA* pilha){
    if(pilha != NULL){
        return (pilha->tamanho == 0);
    }
    return true;
}
bool pilha_cheia(PILHA* pilha){
    if(pilha != NULL){
        NO* novo = (NO*) malloc(sizeof(NO));
        if(novo == NULL) return true;
        free(novo); novo = NULL;
        return false;
    }
    return false;
}
int pilha_tamanho(PILHA* pilha){
    return (pilha != NULL ? pilha->tamanho: -1);
}

ITEM* pilha_topo(PILHA* pilha){
    if(pilha != NULL && (!pilha_vazia(pilha))){
        return (pilha->topo->item);
    }
    return NULL;
}

bool pilha_empilhar(PILHA* pilha, ITEM* item){
    NO* novo_no = (NO*) malloc(sizeof(NO));
    //Verificar se há memória e se a pilha existe.
    if(novo_no != NULL && !pilha_cheia(pilha)){
        novo_no->item = item;
        novo_no->anterior = pilha->topo;
        pilha->topo = novo_no;
        pilha->tamanho++;
        return true;//Não há free, pois a memoria precisa continuar alocada.
    }
    return false;
}
  
ITEM* pilha_desempilhar(PILHA* pilha){
    if(!pilha_vazia(pilha)){
        ITEM *item = pilha->topo->item;
        NO *aux = pilha->topo;
        pilha->topo = pilha->topo->anterior;
        aux->anterior = NULL;
        free(aux); aux = NULL;
        pilha->tamanho--;
        return item;
    }
    return NULL;
}
void pilha_print(PILHA* p){
    if(p != NULL){
        NO *aux = p->topo;
        while(aux != NULL){
            printf("%c", aux->item);
            aux = aux->anterior;
        }
        aux = NULL;
    }
}
  