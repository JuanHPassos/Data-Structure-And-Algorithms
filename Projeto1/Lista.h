#ifndef LISTA_H
    #define LISTA_H
 
    #define ORDENADA 0  /*0 = lista não ordenada; 1 = lista ordenada*/
    #define TAM_MAX 13
    #define INFINITO 100000000

    #include<stdbool.h>

    typedef struct lista_ LISTA; 

    LISTA *lista_criar(bool ordenada);
    bool lista_inserir(LISTA *lista, char chave);
    bool lista_apagar(LISTA **lista);
    bool lista_remover(LISTA *lista, char chave);
    int lista_busca(LISTA *lista, char chave);
    int lista_tamanho(LISTA *lista);
    bool lista_vazia(LISTA *lista);
    bool lista_cheia(LISTA *lista);
    void lista_imprimir(LISTA *lista);
    char lista_get_chave(LISTA *lista,int i);
    bool lista_inserir_posicao(LISTA *lista, char x, char chave);
#endif
