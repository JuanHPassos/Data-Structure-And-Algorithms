#ifndef LLRB_H
    #define LLRB_H
    
    #include "item.h"
    #define max(a,b) ((a>b) ? a : b)

    typedef struct llrb_ LLRB;

    LLRB *llrb_criar(void);
    void llrb_apagar(LLRB **llrb);
    bool llrb_inserir(LLRB *llrb, ITEM *item);


#endif