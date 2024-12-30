#ifndef LLRB_H
    #define LLRB_H

    #include <stdbool.h>
    #include "item.h"

    typedef struct llrb_ LLRB;

    LLRB *llrb_criar();
    bool llrb_inserir(LLRB *llrb, ITEM *item);
    ITEM *llrb_remover(LLRB *llrb, int chave);
    ITEM *llrb_buscar (LLRB *llrb, int chave); 
    void llrb_imprimir(LLRB *llrb);
    void llrb_apagar(LLRB **llrb);

#endif