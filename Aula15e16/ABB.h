#ifndef ABB_H
    #define ABB_H

    #include "item.h"

    typedef struct abb_ ABB;

    bool ABB_inserir(ABB *abb, ITEM *item);
    ITEM *ABB_busca(ABB *abb, int chave);
    ITEM *ABB_remover(ABB *abb, int chave);
    


#endif