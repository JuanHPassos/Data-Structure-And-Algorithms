#ifndef ABB_H
    #define ABB_H

    #include "item.h"

    typedef struct abb_ ABB;

    ABB *abb_criar(void);
    bool abb_inserir(ABB *abb, ITEM *item);
    ITEM *abb_busca(ABB *abb, int chave);
    ITEM *abb_remover(ABB *abb, int chave);
    void abb_imprimir(ABB *abb);
    void abb_apagar(ABB **abb);

#endif