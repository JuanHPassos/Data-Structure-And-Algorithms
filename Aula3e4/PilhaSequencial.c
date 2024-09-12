#include "Pilha.h"

#include<stdio.h>
#include<stdlib.h>

struct pilha{
    ITEM *item[TAM];
    /*Remete numericamente ao tamanho, e como posição do vetor ao ultimo espaço livre*/
    int tamanho;
};

PILHA* pilha_criar(void){
    PILHA *pilha;
    pilha = (PILHA*) malloc(sizeof(PILHA));
    if(pilha != NULL){
        pilha->tamanho = 0;  //Pilha vazia.
    }
    return pilha;
}

/*A função pilha apagar tem como objetivo apagar a pilha, e somente ela, tendo em vista que caso
o cliente tenha alocado os itens, a responsabilidade de desaloca-los é dele. Pois nesse arquivo.c apenas pilhas são alocadas dinamicamente. Logo, apenas elas são desalocadas. Dessa forma, o cliente possui total
responsabilida sobre os dados que alocou.*/
void pilha_apagar(PILHA** pilha){
    if(*pilha != NULL){
        free(*pilha);
        *pilha = NULL; //Boa prática.
    }
    return;
}

bool pilha_vazia(PILHA* pilha){
    if(pilha != NULL){
        return (pilha->tamanho == 0);
    }
    return false;
}

bool pilha_cheia(PILHA* pilha){
    if(pilha != NULL){
        /*150 tamanho maximo da pilha definido no ponto arquivo.h.*/
        return (pilha->tamanho == 150);
    }
    return false;
}

int pilha_tamanho(PILHA* pilha){
    if(pilha != NULL){
        return pilha->tamanho;
    }
    return -1; //Mensagem de erro.
}

ITEM* pilha_topo(PILHA* pilha){
    return pilha->item[pilha->tamanho-1];  //Tamanho-1 corresponde ao ultimo elemento do topo.
}

bool pilha_empilhar(PILHA* pilha, ITEM* item){
    if(!pilha_cheia(pilha)){
        pilha->item[pilha->tamanho] = item;
        pilha->tamanho++;
        return true;
    }
    return false;
}

ITEM* pilha_desempilhar(PILHA* pilha){
    ITEM *topo = NULL;  //Inicialize ponteiros.
    if(!pilha_vazia(pilha)){
        pilha->tamanho--;
        topo = pilha->item[pilha->tamanho];
        pilha->item[pilha->tamanho] = NULL;
    }
    return topo;
}

void pilha_print(PILHA* p){
    for(int i = 0; i<p->tamanho; i++){
        printf("%c", p->item[i]);
    }
}
