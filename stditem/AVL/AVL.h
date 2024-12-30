#ifndef AVL_H
    #define AVL_H
    
    #include "stdbool.h"
    #include "item.h"
    #define max(a,b) ((a>b) ? a : b)

    typedef struct avl_ AVL;

    AVL *avl_criar(void);
    void avl_apagar(AVL **avl);
    bool avl_inserir(AVL *avl, ITEM *item);
    ITEM *avl_remover(AVL *avl, int chave);
    ITEM *avl_buscar(AVL *avl, int chave);
    void avl_imprimir(AVL *avl);

#endif