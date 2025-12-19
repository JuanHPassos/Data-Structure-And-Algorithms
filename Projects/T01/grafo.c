#include "grafo.h"
#include "lista.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct no_ NO;

struct no_ {
    NO *proximo;
    char chave;
    int peso;
};

struct grafo_ {
    NO *inicio;
    NO *fim;
    int tamanho;
};

GRAFO *grafo_criar(void)
{
    GRAFO *grafo = (GRAFO *)malloc(sizeof(GRAFO));

    if (grafo != NULL) {
        grafo->inicio = NULL;
        grafo->fim = NULL;
        grafo->tamanho = 0;
    }

    return (grafo);
}

bool grafo_inserir(GRAFO *grafo, char chave, int peso)
{
    NO *no = (NO *)malloc(sizeof(NO));
    no->chave = chave;
    no->peso = peso;
    no->proximo = NULL;

    if (grafo->inicio == NULL) {
        grafo->inicio = no;
        grafo->fim = no;
    } else {
        grafo->fim->proximo = no;
        grafo->fim = no;
    }

    grafo->tamanho++;

    return true;
}

bool grafo_apagar(GRAFO **grafo)
{
    if (grafo_vazio(*grafo))
        return false;

    while ((*grafo)->inicio != NULL) {
        // Tirar nó do grafo, preservando o encadeamento
        NO *no_apagado = (*grafo)->inicio;
        (*grafo)->inicio = (*grafo)->inicio->proximo;

        // Apagar nó
        no_apagado->proximo = NULL;
        free(no_apagado);
        no_apagado = NULL;
    }

    (*grafo)->fim = NULL;

    free(*grafo);
    *grafo = NULL;

    return true;
}

int grafo_peso(GRAFO *grafo, char chave)
{
    if (!grafo_vazio(grafo)) {
        for (NO *busca = grafo->inicio; busca != NULL; busca = busca->proximo) {
            if (chave == busca->chave) {
                return (busca->peso);
            }
        }
    }

    return (-1); // Não há ligação
}

int grafo_tamanho(GRAFO *grafo)
{
    if (grafo == NULL)
        return (-1);

    return (grafo->tamanho);
}

bool grafo_vazio(GRAFO *grafo)
{
    if (grafo == NULL)
        return true;

    return (grafo->inicio == NULL);
}

void grafo_imprimir(GRAFO *grafo)
{
    if (grafo_vazio(grafo))
        return;

    for (NO *no = grafo->inicio; no != NULL; no = no->proximo)
        printf("%d\n", no->chave);
}

typedef struct caminho_ {
    int menor_distancia;
    char *caminho;
    char origem;
    char tamanho;
} CAMINHO;

static void encontrar_caminho(
    GRAFO **distancia, LISTA *lista, char index, CAMINHO *caminho);

void menor_caminho(GRAFO **distancia, char origem, char tamanho)
{
    if (distancia == NULL)
        return;

    // Guarda o valor da menor distância até agora e o caminho correspondente
    CAMINHO *caminho = (CAMINHO *)malloc(sizeof(CAMINHO));
    caminho->caminho = NULL;
    caminho->origem = origem;
    caminho->tamanho = tamanho - 1;
    caminho->menor_distancia = INFINITO;

    // Lista na qual será feita a permutação das cidades
    LISTA *lista = lista_criar(tamanho, false);

    encontrar_caminho(distancia, lista, 0, caminho);

    // Imprime cidade de origem, caminho e a distância.
    printf("%d\n", origem + 1);
    printf("%d", caminho->caminho[tamanho] + 1);

    for (int i = tamanho - 1; i >= 0; i--) {
        printf(" - %d", caminho->caminho[i] + 1);
    }

    printf("\n%d\n", caminho->menor_distancia);

    lista_apagar(&lista);

    free(caminho->caminho);
    caminho->caminho = NULL;

    free(caminho);
    caminho = NULL;

    return;
}

static void encontrar_caminho(
    GRAFO **distancia, LISTA *lista, char cidade, CAMINHO *caminho)
{
    if (cidade == caminho->origem)
        cidade++;

    if (lista_tamanho(lista) == 0)
        lista_inserir(lista, cidade);

    // Possivel permutação
    if (lista_tamanho(lista) == caminho->tamanho) {
        // Se não há caminho com a origem, não é um caminho válido.
        if (grafo_peso(distancia[cidade], caminho->origem) == -1)
            return;

        // Vetor que guardará esse caminho temporário.
        char *caminho_str = (char *)malloc((caminho->tamanho + 2) * sizeof(char));

        // Guarda o caminho formado no vetor.
        caminho_str[0] = caminho->origem;

        for (int i = 0; i < caminho->tamanho; i++)
            caminho_str[i + 1] = lista_obter_posicao(lista, i);

        caminho_str[caminho->tamanho + 1] = caminho->origem;

        // Percorrer o caminho, se existir, somando as distancias.
        int dist = 0;

        for (int i = 1; i <= (caminho->tamanho) + 1; i++) {
            // Variável com objetivo de chamar a função de busca apenas 1 vez.
            int temp_dist = grafo_peso(distancia[caminho_str[i - 1]], caminho_str[i]);

            // Se não existir caminho, não é uma resposta válida.
            if (temp_dist == -1) {
                free(caminho_str);
                caminho_str = NULL;

                return;
            }

            dist += temp_dist;
        }

        // O caminho será salvo caso tenha distância menor que o atual
        if (dist < caminho->menor_distancia) {
            caminho->menor_distancia = dist;

            if (caminho->caminho != NULL)
                free(caminho->caminho);

            caminho->caminho = caminho_str;
        } else {
            free(caminho_str);
        }

        return;
    }

    // Não permuta-se a origem, tendo em vista que estará sempre no início.
    if (cidade + 1 == caminho->origem)
        cidade++;

    // Insere a próxima cidade em todas as posições possíveis,
    // recursivamente, até obter todas as permutações.
    for (int i = 0; i <= lista_tamanho(lista); i++) {
        lista_inserir_posicao(lista, i, cidade + 1);
        encontrar_caminho(distancia, lista, cidade + 1, caminho);
        lista_remover(lista, cidade + 1);
    }
}
