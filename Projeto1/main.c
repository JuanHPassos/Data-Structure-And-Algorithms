#include "Deque.h"

#include<stdio.h>
#include<stdlib.h>

int **alocar_matriz(int linha, int coluna);

int main(){
    // Numero de nos, começo da viagem, e ligações entre os nos.
    int cidades, origem, ligacoes;
     // Matriz que guarda o peso dos nos(distancias das cidades).
    int **distancia;

    scanf("%d %d %d", &cidades, &origem, &ligacoes);
    origem--; // Base zero.

    distancia = alocar_matriz(cidades, cidades);

    // Estabelece ligações entre os nos.
    for(int i = 0; i< ligacoes; i++){
        int cidade_a, cidade_b, percurso;
        scanf("%d %d %d", &cidade_a, &cidade_b, &percurso);
        cidade_a--; cidade_b--; // Base 0.
        distancia[cidade_a][cidade_b] = percurso;
        distancia[cidade_b][cidade_a] = percurso;
    }

    // Struct definida no .h para retornar a resposta, com a menor distancia e o caminho.
    PATH menor_caminho;
    menor_caminho.distancia = INFINITO; // Elemento neutro da operação mínimo.
    // Deque que servira de auxilio para gerar todas as permutações.
    DEQUE *permutacao = deque_criar(); 
    // Função que gera todos os caminhos possiveis e retorna o menor.
    caminho(permutacao, 0, origem, distancia, cidades, &menor_caminho);

    printf("%d %s\n", menor_caminho.distancia, menor_caminho.caminho);

    free(menor_caminho.caminho); menor_caminho.caminho = NULL;

}

int **alocar_matriz(int linha, int coluna){
    int **matriz;

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

