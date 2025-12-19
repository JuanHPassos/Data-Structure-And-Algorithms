#ifndef GRAFO_H
#define GRAFO_H

#define GRAFO_TAM_MAX 12

#include <stdbool.h>

#define INFINITO 1000000

typedef struct grafo_ GRAFO;

void menor_caminho(GRAFO **distancia, char origem, char tamanho);

GRAFO *grafo_criar(void);
bool grafo_apagar(GRAFO **grafo);

bool grafo_inserir(GRAFO *grafo, char chave, int peso);

int grafo_peso(GRAFO *grafo, char chave);

int grafo_tamanho(GRAFO *grafo);
bool grafo_vazio(GRAFO *grafo);
void grafo_imprimir(GRAFO *grafo);

#endif
