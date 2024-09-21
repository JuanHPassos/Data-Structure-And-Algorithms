#include"Deque.h"

#include<stdio.h>
#include<stdlib.h>

struct deque_{
    ITEM *vet_item[MAX_TAMANHO];
    int inicio;
    int fim;
    int tam; // Tamanho
};

DEQUE* deque_criar(){
    DEQUE *deque = (DEQUE*) malloc(sizeof(DEQUE));
    if(deque != NULL){
        deque->inicio = 0;
        deque->fim = 1;
        deque->tam = 0;
    }
    return(deque);
}

void deque_apagar(DEQUE** deque){
    if(*deque != NULL){
        free(*deque);
        *deque = NULL;
    }
}

bool deque_inserir_inicio(DEQUE* deque, ITEM* item){
    if(!deque_cheia(deque)){
        deque->vet_item[deque->inicio] = item;
        
        deque->inicio--;

        if(deque->inicio < 0) deque->inicio = MAX_TAMANHO - 1;

        deque->tam++;

        return(true);
    }
    return(false);
}

bool deque_inserir_fim(DEQUE* deque, ITEM* item){
    if(!deque_cheia(deque)){
        deque->vet_item[deque->fim] = item;

        deque->fim = (deque->fim + 1)%12;

        deque->tam++;

        return(true);
    }
    return(false);
}

ITEM* deque_remover_inicio(DEQUE* deque){
    if(!deque_vazia(deque)){
        ITEM* item = NULL;
        
        deque->inicio = (deque->inicio + 1)%12;

        item = deque->vet_item[deque->inicio];

        deque->vet_item[deque->inicio] = NULL;

        deque->tam--;

        return(item);
    }
    return(NULL);
}

ITEM* deque_remover_fim(DEQUE* deque){
    if(!deque_vazia(deque)){
        ITEM *item = NULL;

        deque->fim--; 

        if(deque->fim < 0) deque->fim = MAX_TAMANHO - 1;

        item = deque->vet_item[deque->fim];

        deque->vet_item[deque->fim] = NULL;

        deque->tam--;

        return(item);
    }
    return(NULL);
}

ITEM* deque_primeiro(DEQUE* deque){
    if(!deque_vazia(deque)){
        int primeiro = deque->inicio;
        
        primeiro = (primeiro + 1)%12;
        
        return(deque->vet_item[primeiro]);
    }
    return(NULL);
}

ITEM* deque_ultimo(DEQUE* deque){
    if(!deque_vazia(deque)){
        int ultimo = deque->fim;

        if(ultimo == 0) ultimo = MAX_TAMANHO - 1;

        return(deque->vet_item[ultimo]);
    }
    return(NULL);
}

int deque_contar(DEQUE* deque){
    if(deque != NULL){
        return(deque->tam);
    }
    return(ERRO);
}

bool deque_vazia(DEQUE* deque){
    if(deque != NULL){
        return(deque->tam == 0);
    }
    return(true);
}

bool deque_cheia(DEQUE* deque){
    if(deque != NULL){
        return(deque->tam == MAX_TAMANHO);
    }
    return(true);
}
