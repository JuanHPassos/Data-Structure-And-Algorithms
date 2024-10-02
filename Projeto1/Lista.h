#ifndef LISTA_H
    #define LISTA_H
 
    #define ORDENADA 0  /*0 = lista não ordenada; 1 = lista ordenada*/
    #define TAM_MAX 13
    #define INFINITO 100000000

    #include "Grafo.h"
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
    void menor_caminho(GRAFO **distancia, char origem, char tamanho);
#endif