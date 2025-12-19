#include "grafo.h"

#include <stdio.h>
#include <stdlib.h>

GRAFO **alocar_vetor_grafo(int n);

int main(void)
{
    // Número de nós, começo da viagem, e ligações entre os nós.
    int cidades, origem, ligacoes;

    scanf("%d %d %d", &cidades, &origem, &ligacoes);

    // Contaremos a partir do zero
    origem--;

    // Lista que guarda o peso dos nós (distâncias entre as cidades)
    GRAFO **distancia = alocar_vetor_grafo(cidades);

    // Vetor de listas que guarda as ligacões entre as cidades.
    for (int i = 0; i < ligacoes; i++) {
        int cidade_a, cidade_b, percurso;
        scanf("%d %d %d", &cidade_a, &cidade_b, &percurso);

        cidade_a--;
        cidade_b--;

        grafo_inserir(distancia[cidade_a], cidade_b, percurso);
        grafo_inserir(distancia[cidade_b], cidade_a, percurso);
    }

    menor_caminho(distancia, origem, cidades);

    for (int i = 0; i < cidades; i++) {
        grafo_apagar(&distancia[i]);
    }

    free(distancia);
    distancia = NULL;

    return 0;
}

GRAFO **alocar_vetor_grafo(int n)
{
    GRAFO **vet_grafo = (GRAFO **)malloc(n * sizeof(GRAFO *));

    if (vet_grafo == NULL)
        return NULL;

    for (int i = 0; i < n; i++)
        vet_grafo[i] = grafo_criar();

    return vet_grafo;
}
