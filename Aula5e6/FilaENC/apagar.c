/*
Apague uma fila de maneira recursiva com no maximo 8 bytes por chamada.
*/

#include"fila.h"

#include<stdio.h>
#include<stdlib.h>

#ifndef _STRUCTS_

    #define _STRUCTS_

    typedef struct no_ {
        ITEM* item;
        struct no_* proximo;
    }noObj;

    typedef noObj NO;

    typedef struct fila_ {
        NO* inicio;
        NO* fim;
        int tamanho;
    }filaObj;

    typedef filaObj FILA;

#endif

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


