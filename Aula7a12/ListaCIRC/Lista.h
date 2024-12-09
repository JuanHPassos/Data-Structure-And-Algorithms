#ifndef LISTA_H
    #define LISTA_H
 
    #define ORDENADA 0  /*0 = lista não ordenada; 1 = lista ordenada*/

    #include<stdbool.h>

    typedef struct lista_ LISTA; 

    LISTA *lista_criar(bool ordenada);
    bool lista_inserir(LISTA *lista, int chave);
    bool lista_apagar(LISTA **lista);
    int lista_remover(LISTA *lista, int chave);
    int lista_busca(LISTA *lista, int chave);
    int lista_tamanho(LISTA *lista);
    bool lista_vazia(LISTA *lista);
    bool lista_cheia(LISTA *lista);
    void lista_imprimir(LISTA *lista);

#endif