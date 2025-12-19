#include "Fila.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct _no NO;

struct _no{
    NO* proximo;
    ITEM *item;
};

struct fila_{
    NO* frente;
    NO* fim;
    int tamanho;
};

FILA* fila_criar(){
    FILA *fila = (FILA*) malloc(sizeof(FILA));
    if(fila != NULL){
        fila->frente = NULL;
        fila->fim = fila->frente;
        fila->tamanho = 0;
    }
    return (fila);
}
    
bool fila_cheia(FILA *fila){
    if(fila != NULL){
        NO *novo_fim = (NO*) malloc(sizeof(NO));
        
        if(novo_fim == NULL) return false;
        
        free(novo_fim);
        
        novo_fim = NULL;
    }
    return true;
}

bool fila_vazia(FILA *fila){
    if(fila != NULL){
        return (fila->tamanho == 0);
    }
    return true;
}

bool fila_inserir(FILA *fila, ITEM *item){
    if(!fila_cheia(fila)){
        NO *novo_fim = (NO*) malloc(sizeof(NO));

        if(fila->frente == NULL) fila->frente = novo_fim; // Se fila vazia(define-se o inicio).
        else fila->fim->proximo = novo_fim; // Define o novo fim.
        
        novo_fim->item = item; novo_fim->proximo = NULL;

        fila->fim = novo_fim;

        fila->tamanho++;

        return (true);
    }
    return(false);
} 

ITEM *fila_remover(FILA *fila){
    if(!fila_vazia(fila)){
        NO *frente = fila->frente;
        ITEM *item = frente->item;

        fila->frente = fila->frente->proximo;
        fila->tamanho--;
        
        frente->proximo = NULL;
        free(frente); frente = NULL;
        
        if(fila_vazia(fila))
            fila->fim = NULL;
        
        return (item);
    }
    return NULL;
}

int fila_tamanho(FILA *fila){
    if(fila != NULL){
        return (fila->tamanho);
    }
    return (-1);
}
    
ITEM *fila_frente(FILA *fila){
    if(fila != NULL) return (fila->frente);
    return NULL;
}

void fila_apagar(FILA **fila){
    if(*fila != NULL){
        while(!fila_vazia(*fila)){
            ITEM *frente = fila_remover(*fila);
            // Remover linha, caso desalocar item seja responsabilidade do cliente.
            free(frente); frente = NULL;
        }
        free(*fila); 
        *fila = NULL;
    }
}

/*
Maneira eficiente de apagar a pilha, visando memoria.

void apagar_no(NO **no){
    if((*no)->proximo != NULL)
        apagar_no(&(*no)->proximo);
    
    free((*no)->item); (*no)->item = NULL; 
    free(*no); *no = NULL;  
    
    return;  
}

void fila_apagar(FILA **f){
    if(!fila_vazia(*f) && (*f) != NULL){
        apagar_no(&(*f)->inicio);
        
        free(*f); *f = NULL;
    }
    return;
}
*/

bool fila_inverter(FILA *fila){
    if(fila != NULL){
        inverte(fila->frente);
        NO *aux = fila->frente;
        fila->frente = fila->fim;
        fila->fim = aux; 
        return true;
    }
    return false;
}

void inverte(NO *no){
    if(no->proximo->proximo != NULL) inverte(no->proximo);

    no->proximo->proximo = no;
    no->proximo = NULL;
}
