/* Suponha que temos n cidades numeradas de 0 a n − 1 e interligadas por estradas de mão única,
As ligações entre as cidades são representadas por uma matriz A definida da seguinte forma: A[x][y]
 vale 1 se existe estrada da cidade x para a cidade y e vale 0 em caso contrário.  A distância de uma cidade o a uma cidade x é o menor número de estradas que é preciso percorrer para ir
 de o a x. O problema que queremos resolver é o seguinte: determinar a distância de uma dada cidade o a
 cada uma das outras cidades da rede. As distâncias são armazenadas em um vetor d de tal modo que d[x]
 seja a distância de o a x. Se for impossível chegar de o a x, podemos dizer que d[x] vale ∞. Usamos
 ainda −1 para representar ∞ uma vez que nenhuma distância “real” pode ter valor −1.*/

#include"Fila.h"

#include<stdio.h>
#include<stdlib.h>

int **alocar_matriz(int linha, int coluna);
//Funcao que encontra menor distancia para todos os vertices a partir da origem.
void bfs(int **adj, int *dist, int origem, int n){
  // Parametros: matriz adjacencia, vetor de distancias, origem, e a quantidade de nos.
    int vis[n]; // Vetor visistador.
    for(int i = 0; i < n; i++) vis[i] = 0; // Nenhuma cidade foi visistada.
    FILA *fila = fila_criar();
    fila_inserir(fila, item_criar(origem, NULL)); // Adiciona-se origem a fila.
    vis[origem] = 1; // Visita origem.
    dist[origem] = 0; // Distancia da origem para ela mesma é 0.
    // Visita-se todas as cidades que da para chegar partindo da origem.
    while(!fila_vazia(fila)){
        ITEM *item = fila_remover(fila); 
        int no = item_get_chave(item);
        item_apagar(&item);
        // Passa-se por todos os nos adjacentes.
        for(int i = 0; i < n; i++){
            // Se for adjacente e nao tiver visitado.
            if(adj[no][i] == 1 && vis[i] == 0){
                vis[i] = 1; // Visita-o.
                dist[i] = dist[no] + 1; // Sua distancia é da onde veio(pai) + 1.
                fila_inserir(fila, item_criar(i, NULL)); // Parte-se para esse no(filho).
            }
        }
    }
}

int main(){
    int n, origem; // n = tamanho.
    scanf("%d %d", &n, &origem);

    int **adj = alocar_matriz(n, n);
    int *dist = (int*) malloc(n*sizeof(int));

    for(int i = 0; i < n; i++){
        dist[i] = -1; // inicializa dist, como -1(simboliza infinito).
        for(int j = 0; j < n; j++){
            scanf("%d", &adj[i][j]);
        }
    }

    bfs(adj, dist, origem, n);

    printf("Distâncias em relação a %d: \n", origem);
    for(int i = 0; i < n; i++){
        printf("%d ", dist[i]);
    }

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

    return matriz;
}
