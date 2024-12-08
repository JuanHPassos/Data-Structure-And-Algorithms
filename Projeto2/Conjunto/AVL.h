#ifndef AVL_H
    #define AVL_H
    
    #include "stdbool.h"
    #define max(a,b) ((a>b) ? a : b)

    typedef struct avl_ AVL;

    AVL *avl_criar(void);
    void avl_apagar(AVL **avl);
    bool avl_inserir(AVL *avl, int valor);
    bool avl_remover(AVL *avl, int valor);
    bool avl_buscar(AVL *avl, int valor);
    void avl_imprimir(AVL *avl);
    void avl_copiar(AVL *avl_destino, AVL *avl_origem);
    void avl_interseccao(AVL *avl_intersec, AVL *avl_1, AVL *avl_2);
    

#endif