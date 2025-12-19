#ifndef LISTA_H
#define LISTA_H

#define LISTA_TAM_MAX 12

#include <stdbool.h>

typedef struct lista_ LISTA;

LISTA *lista_criar(int capacidade, bool ordenada);
bool lista_apagar(LISTA **lista);

bool lista_inserir(LISTA *lista, char chave);
bool lista_inserir_posicao(LISTA *lista, int n, char chave);

char lista_obter_posicao(LISTA *lista, int n);

bool lista_remover(LISTA *lista, char chave);

char lista_busca(LISTA *lista, char chave);
int lista_tamanho(LISTA *lista);

bool lista_vazia(LISTA *lista);
bool lista_cheia(LISTA *lista);

void lista_imprimir(LISTA *lista);

#endif
