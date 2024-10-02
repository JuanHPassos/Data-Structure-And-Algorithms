#ifndef GRAFO_H
    #define GRAFO_H
 
    #define ORDENADA 0  /*0 = GRAFO não ordenada; 1 = GRAFO ordenada*/
    #define TAM_MAX 13
    #define INFINITO 100000000

    #include<stdbool.h>

    typedef struct grafo_ GRAFO; 

    GRAFO *grafo_criar();
    bool grafo_inserir(GRAFO *grafo,char chave, int peso);
    bool grafo_apagar(GRAFO **grafo);
    int grafo_peso(GRAFO *grafo, char chave);
    int grafo_tamanho(GRAFO *grafo);
    bool grafo_vazia(GRAFO *grafo);
    bool grafo_cheia(GRAFO *grafo);
    void grafo_imprimir(GRAFO *grafo);

#endif