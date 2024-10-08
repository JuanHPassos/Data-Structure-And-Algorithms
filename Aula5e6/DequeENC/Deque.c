#include "Deque.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct no_ NO;

struct no_{
    NO* proximo;
    NO* anterior;
    ITEM *item;
};

struct deque_{
    NO *inicio;
    NO *fim;
    int tamanho;
};

DEQUE* deque_criar(){
    DEQUE *deque = (DEQUE*) malloc(sizeof(DEQUE));
    if(deque != NULL){
        deque->tamanho = 0;
        deque->inicio = NULL;
        deque->fim = NULL;
    }
    return (deque);
}

void deque_apagar(DEQUE** deque){
    while(!deque_vazia(*deque)){
        ITEM *item = deque_remover_inicio(*deque); // Responsabilidade desenvolvedor.
        item_apagar(&item); item = NULL; // documente caso contrario.
    }
    if(*deque != NULL) free(*deque); 
    *deque = NULL;
}

bool deque_inserir_inicio(DEQUE* deque, ITEM* item){
    if(!deque_cheia(deque)){
        NO* novo_inicio = (NO*) malloc(sizeof(NO));
        
        novo_inicio->proximo = deque->inicio;

        if(deque->inicio == NULL){
            deque->inicio = novo_inicio; //Deque vazia, define-se inicio.
            deque->fim = novo_inicio; // Se deque vazia(fim == inicio).
        }
        else deque->inicio->anterior = novo_inicio; // Define o novo fim.
        
        deque->inicio = novo_inicio;
        
        novo_inicio->anterior = NULL;
        
        deque->tamanho++;

        deque->inicio->item = item;

        return(true);
    }
    return (false);
}

bool deque_inserir_fim(DEQUE* deque, ITEM* item){
    if(!deque_cheia(deque)){
        NO* novo_fim = (NO*) malloc(sizeof(NO));

        novo_fim->anterior = deque->fim;

        if(deque->inicio == NULL){
            deque->fim = novo_fim; // Se deque vazia(define-se o fim).
            deque->inicio = novo_fim; //Inicio é igual ao fim.
        }
        else deque->fim->proximo = novo_fim; // Define o novo fim.

        deque->fim = novo_fim;

        novo_fim->proximo = NULL;

        deque->tamanho++;

        deque->fim->item = item;

        return(true);
    }
    return(false);
}

ITEM* deque_remover_inicio(DEQUE* deque){
    if(!deque_vazia(deque)){
        NO *inicio = deque->inicio;
        ITEM *item = inicio->item;

        deque->inicio = deque->inicio->proximo;
        
        if(deque->inicio != NULL)
            deque->inicio->anterior = NULL;
        
        deque->tamanho--;

        inicio->proximo = NULL;
        free(inicio); inicio = NULL;

        if(deque_vazia(deque))
            deque->fim = NULL;
        
        return(item);
    }
    return (NULL);
}

ITEM* deque_remover_fim(DEQUE* deque){
    if(!deque_vazia(deque)){
        NO *fim = deque->fim;
        ITEM *item = fim->item;

        deque->fim = deque->fim->anterior;
        
        if(deque->fim != NULL)
            deque->fim->proximo = NULL;
        
        deque->tamanho--;

        fim->anterior = NULL;
        free(fim); fim = NULL;
        
        if(deque_vazia(deque))
            deque->inicio = NULL;

        return(item);
    }
    return(NULL);
}

ITEM* deque_primeiro(DEQUE* deque){
    if(deque != NULL) return(deque->inicio->item);
    return (NULL);
}

ITEM* deque_ultimo(DEQUE* deque){
    if(deque != NULL) return (deque->fim->item);
    return(NULL);
}

int deque_contar(DEQUE* deque){
    if(deque != NULL) return(deque->tamanho);
    return (-1);
}

bool deque_vazia(DEQUE* deque){
    if(deque != NULL) return(deque->tamanho == 0);
    return true;
}
bool deque_cheia(DEQUE* deque){
    if(deque != NULL){
        NO *novo_no = (NO*) malloc(sizeof(NO));
        if(novo_no == NULL) return(true);
        
        free(novo_no);
        novo_no = NULL;
    
        return (false);
    }
    return(true);
}


void deque_imprimir(DEQUE *deque){
    if(!deque_vazia(deque)){
        NO *index = deque->inicio;
        printf("Deque: ");
        while(index != NULL){
            printf("%d ", item_get_chave(index->item));
            index = index->proximo;
        }
        printf("\n");
    }
}

