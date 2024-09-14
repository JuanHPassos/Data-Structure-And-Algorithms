#ifndef FILA_H
    #define FILA_H

    #include "item.h"

    #define TAM_MAX 100

    typedef struct fila_ FILA;

    FILA* fila_criar();
    bool fila_cheia(FILA *fila);
    bool fila_vazia(FILA *fila);
    bool fila_inserir(FILA *fila, ITEM *item); 
    ITEM *fila_remover(FILA *fila);
    int fila_tamanho(FILA *fila);
    ITEM *fila_frente(FILA *fila);
    void fila_apagar(FILA **fila);

#endif