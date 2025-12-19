#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

struct lista_ {
    int tamanho;
    bool ordenada;
    char elementos[LISTA_TAM_MAX];
};

static char lista_busca_sequencial(LISTA *lista, char chave);
static char lista_busca_ordenada(LISTA *lista, char chave);

static bool lista_inserir_fim(LISTA *lista, char chave);

bool lista_inserir_posicao(LISTA *lista, int n, char chave);

LISTA *lista_criar(int capacidade, bool ordenada)
{
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA) + capacidade * sizeof(char));

    if (lista != NULL) {
        lista->tamanho = 0;
        lista->ordenada = ordenada;
    }

    return lista;
}

bool lista_inserir(LISTA *lista, char chave)
{
    if (lista_cheia(lista))
        return false;

    if (!lista->ordenada) {
        return lista_inserir_fim(lista, chave);
    } else {
        char x = lista_busca_ordenada(lista, chave);
        return lista_inserir_posicao(lista, x, chave);
    }
}

static bool lista_inserir_fim(LISTA *lista, char chave)
{
    if (!lista || lista->ordenada)
        return false;

    lista->elementos[lista->tamanho] = chave;
    lista->tamanho++;

    return true;
}

bool lista_inserir_posicao(LISTA *lista, int n, char chave)
{
    if (!lista || lista->ordenada)
        return false;

    for (int i = lista->tamanho; i > n; i--)
        lista->elementos[i] = lista->elementos[i - 1];

    lista->elementos[n] = chave;
    lista->tamanho++;

    return true;
}

char lista_obter_posicao(LISTA *lista, int n)
{
    if (!lista)
        return -1;

    return lista->elementos[n];
}

bool lista_apagar(LISTA **lista)
{
    if (!lista)
        return false;

    free(*lista);
    *lista = NULL;

    return (true);
}

bool lista_remover(LISTA *lista, char chave)
{
    if (lista_vazia(lista))
        return false;

    int posicao;

    if (lista->ordenada) {
        posicao = lista_busca_ordenada(lista, chave);
    } else {
        posicao = lista_busca_sequencial(lista, chave);
    }

    if (posicao == -1)
        return false;

    for (int i = posicao; i < lista->tamanho - 1; i++)
        lista->elementos[i] = lista->elementos[i + 1];

    lista->tamanho--;

    return true;
}

static char lista_busca_ordenada(LISTA *lista, char chave)
{
    int l = 0, r = lista->tamanho - 1;

    if (r == -1)
        return 0;

    while (l < r) {
        int media = (l + r) / 2;

        if (chave <= lista->elementos[media]) {
            r = media;
        } else {
            l = media + 1;
        }
    }

    if (lista->elementos[l] >= chave) {
        return l;
    } else
        return lista->tamanho;
}

static char lista_busca_sequencial(LISTA *lista, char chave)
{
    for (int i = 0; i < lista->tamanho; i++) {
        if (chave == lista->elementos[i]) {
            return i;
        }
    }

    return (-1); // Não existe posição menos 1, logo simboliza que nao achou.
}

char lista_busca(LISTA *lista, char chave)
{
    if (lista_vazia(lista))
        return -1;

    if (lista->ordenada)
        return lista->elementos[lista_busca_ordenada(lista, chave)];
    else
        return lista->elementos[lista_busca_sequencial(lista, chave)];
}

int lista_tamanho(LISTA *lista)
{
    if (lista == NULL)
        return -1;

    return lista->tamanho;
}

bool lista_vazia(LISTA *lista)
{
    if (lista == NULL)
        return true;

    return lista->tamanho == 0;
}

bool lista_cheia(LISTA *lista)
{
    if (lista == NULL)
        return true;

    return lista->tamanho == LISTA_TAM_MAX;
}

void lista_imprimir(LISTA *lista)
{
    if (!lista_vazia(lista)) {
        for (int i = 0; i != lista->tamanho; i++) {
            printf("%d", lista->elementos[i]);

            if (i != lista->tamanho - 1)
                printf(" ");
        }

        printf("\n");
    }
}
