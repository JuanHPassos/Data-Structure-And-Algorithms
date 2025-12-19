#ifndef LLRB_H
    #define LLRB_H

    #include <stdbool.h>
    #include <stdlib.h>

    typedef struct llrb_ LLRB;
    typedef struct no_ NO;

    LLRB *llrb_criar();
    bool llrb_inserir(LLRB *arvore, int dado);
    bool llrb_remover(LLRB *arvore, int chave);
    NO *llrb_busca(LLRB *arvore, int chave);
    void llrb_imprimir(LLRB *arvore);
    void llrb_apagar(LLRB **arvore);
    int no_get_dado(NO *no);
    bool pertence (LLRB *arvore, int chave);
    LLRB *uniao (LLRB *arv1, LLRB *arv2);
    LLRB *intersecao (LLRB *arv1, LLRB *arv2);
    void llrb_copiar(LLRB *llrb_destino, LLRB *llrb_origem);
    

#endif