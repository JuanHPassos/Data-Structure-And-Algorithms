#include "Deque.h"

#include<stdio.h>
#include<stdlib.h>

int **alocar_matriz(int linha, int coluna);

int main(){
    int cidades, origem, ligacoes;
     
    int **distancia;

    distancia = alocar_matriz(cidades, cidades);

    scanf("%d %d %d", &cidades, &origem, &ligacoes);

    for(int i = 0; i< ligacoes; i++){
        int cidade_a, cidade_b, percurso;
        scanf("%d %d %d", &cidade_a, &cidade_b, &percurso);
        distancia[cidade_a][cidade_b] = percurso;
    }

    PATH menor_caminho;
    menor_caminho.distancia = INFINITO;

    DEQUE *permutacao = deque_criar(); 

    caminho(permutacao, 1, origem, distancia, cidades, &menor_caminho);

    printf("%d %s\n", menor_caminho.distancia, menor_caminho.caminho);

    free(menor_caminho.caminho); menor_caminho.caminho = NULL;

}

int **alocar_matriz(int linha, int coluna){
    int **matriz;
    
    //Ajustando o valor para incluir a posição n.
    linha++; coluna++;

    matriz = (int **) malloc(linha * sizeof(int*));

    matriz[0] = (int*)malloc(linha * coluna * sizeof(int));

    for(int i = 1; i < linha; i++){
        matriz[i] = matriz[0] + coluna * i;
    }

    for(int i = 0; i<linha; i++){
        for(int j = 0; j<coluna; j++){
            matriz[i][j] = 0;
        }
    }

    return matriz;
}

