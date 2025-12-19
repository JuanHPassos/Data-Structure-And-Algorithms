#ifndef CONJUNTO_H
    #define CONJUNTO_H
    
    #include<stdbool.h>

    #define AVL_ 0
    #define LLRB_ 1

    typedef struct conjunto_ CONJUNTO;

    CONJUNTO *conjunto_criar(unsigned char tipo);
    void conjunto_apagar(CONJUNTO **conjunto);
    bool conjunto_inserir(CONJUNTO *conjunto, int chave);
    bool conjunto_remover(CONJUNTO *conjunto, int chave);
    void conjunto_imprimir(CONJUNTO *conjunto);
    bool conjunto_pertence(CONJUNTO *conjunto, int chave);
    CONJUNTO *conjunto_uniao(CONJUNTO *conjunto1, CONJUNTO *conjunto2);
    CONJUNTO *conjunto_interseccao(CONJUNTO *conjunto1, CONJUNTO *conjunto2);

#endif