#include "Lista.h"
#include "Grafo.h"

#include<stdio.h>
#include<stdlib.h>

int main(){
    // Numero de nos, começo da viagem, e ligações entre os nos.
    int cidades, origem, ligacoes;

    scanf("%d %d %d", &cidades, &origem, &ligacoes);
    origem--; // Base zero.

    // Lista que guarda o peso dos nos(distancias das cidades).
    GRAFO **distancia = alocar_vetor_grafo(cidades);

    // Vetor de listas que guarda as ligacoes com as cidades.
    for(int i = 0; i < ligacoes; i++){
        int cidade_a, cidade_b, percurso;
        scanf("%d %d %d", &cidade_a, &cidade_b, &percurso);
        cidade_a--; cidade_b--; // Base 0.
        grafo_inserir(distancia[cidade_a], cidade_b, percurso);
        grafo_inserir(distancia[cidade_b], cidade_a, percurso);
    }
    
    menor_caminho(distancia, origem, cidades-1);
    
    // Desalocação de memoria
    for(int i = 0; i < cidades; i++){
        grafo_apagar(&distancia[i]);
    }
    free(distancia);
    distancia = NULL;

    return 0;
}

