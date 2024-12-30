#ifndef FILA_H
    #define FILA_H

    #include "item.h"

    #define TAM_MAX 100

    typedef struct fila_ FILA;

    FILA* fila_criar(void);
    bool fila_cheia(FILA *fila);
    bool fila_vazia(FILA *fila);
    bool fila_inserir(FILA *fila, ITEM *item); 
    ITEM *fila_remover(FILA *fila);
    int fila_tamanho(FILA *fila);
    ITEM *fila_frente(FILA *fila);
    void fila_imprimir(FILA *fila);
    bool fila_inverter(FILA *fila);

    /*A função pilha apagar, apaga o item para o usuário e os dados nela contido,
    dessa forma, é recomendado que causo o usuário queira manter esse dados,
    esvazie a pilha primeiro e depois chame a pilha apagar.*/
    void fila_apagar(FILA **fila);

#endif