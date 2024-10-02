#include<stdio.h>
#include<stdlib.h>

#include "Lista.h"

typedef struct resposta_{
    int menor_distancia;
    char *caminho;
    char origem;
    char tamanho;
}CAMINHO;

struct lista_{
    char ini;
    char fim; // Ultimo elemento igual a fim-1.
    int tamanho;
    bool ordenada; // Ordenada se = 1. Não ordenada se = 0.
    char chave[TAM_MAX];
}; 

// Modulariazação das funções
int lista_busca_sequencial(LISTA *lista, char chave);
int lista_busca_ordenada(LISTA *lista,char chave);
bool lista_inserir_fim(LISTA *lista, char chave);
bool lista_inserir_posicao(LISTA *lista, char x, char chave);
void encontrar_caminho(GRAFO **distancia, LISTA *lista, char index, CAMINHO *path);

LISTA *lista_criar(bool ordenada){
    LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
    if(lista != NULL){
        lista->ini = 0;
        lista->fim = 0;
        lista->ordenada = ordenada;
        lista->tamanho = 0;
    }
}

bool lista_inserir(LISTA *lista, char chave){
    if(!lista_cheia(lista)){
        if(!(lista->ordenada)){
            return(lista_inserir_fim(lista, chave));
        }
        else{
            char x = lista_busca_ordenada(lista, chave);
            return (lista_inserir_posicao(lista, x, chave));
        }
        return true;
    }
    return false;
}

bool lista_inserir_fim(LISTA *lista, char chave){
    lista->chave[lista->fim] = chave;
    lista->tamanho++; lista->fim++;
    return true;
}


bool lista_inserir_posicao(LISTA *lista, char x, char chave){
    for (int i = lista->fim; i > x; i--){
        lista->chave[i] = lista->chave[i - 1];
    }
    lista->chave[x] = chave;
    lista->tamanho++; lista->fim++;

    return true; 
}

bool lista_apagar(LISTA **lista){
    if(!lista_vazia(*lista)){
        free(*lista); *lista = NULL;
        
        return(true);
    }
    return(false);
}

bool lista_remover(LISTA *lista, char chave){
    if(!lista_vazia(lista)){
        int posicao = -1;
        if(lista->ordenada){
            posicao = lista_busca_ordenada(lista, chave);
        }
        else{
            posicao = lista_busca_sequencial(lista, chave);
        }

        if(posicao == -1) return(false);

        lista->chave[posicao] = -1;
        
        for(int i = posicao; i < (lista->fim) - 1; i++){
            lista->chave[i] = lista->chave[i+1];
        }

        lista->fim--;
        lista->tamanho--;

        return true;
        
    }
    return false;
}

int lista_busca_ordenada(LISTA *lista,char chave){
    int l = lista->ini, r = (lista->fim) - 1;
    if(r == -1) return 0;
    while(l < r){
        int media = (l+r)/2;
        if(chave <= lista->chave[media]){
            r = media;
        }
        else{
            l = media + 1;
        }
    } 

    if(lista->chave[l] >= chave){
        return (l);
    }
    else return(lista->fim);
}

int lista_busca_sequencial(LISTA *lista, char chave){
    for(int i = lista->ini; i < lista->fim; i++){
        if(chave == lista->chave[i]){
            return i;
        }
    }
    return(-1); // Não existe posição menos 1, logo simboliza que nao achou.
}

int lista_busca(LISTA *lista, char chave){
    if(!lista_vazia(lista)){
        if(lista->ordenada)
            return(lista->chave[(lista_busca_ordenada(lista, chave))]);
        else
            return(lista->chave[lista_busca_sequencial(lista, chave)]);
    }
    else return -1;
}

int lista_tamanho(LISTA *lista){
    if(lista != NULL){
        return(lista->tamanho);
    }
    return(-1);
}

bool lista_vazia(LISTA *lista){
    if(lista != NULL){
        return(lista->tamanho == 0);
    }
    return(true);
}

bool lista_cheia(LISTA *lista){
    if(lista != NULL){
        return(lista->tamanho == TAM_MAX);
    }
    return(true);
}

void lista_imprimir(LISTA *lista){
    if(!lista_vazia(lista)){
        int index = lista->ini;
        while(index != lista->fim){
            printf("%d", lista->chave[index]);
            index++;
        }
    }
}

void menor_caminho(GRAFO **distancia, char origem,char tamanho){
    if(distancia == NULL) return;
    
    // Struct criada para economizar memoria a cada chamada recursiva e guardar o valor da menor distancia e do melhor caminho a ser feito 
    CAMINHO *path = (CAMINHO*) malloc(sizeof(CAMINHO));
    path->origem = origem;
    path->tamanho = tamanho;
    path->menor_distancia = INFINITO;
    // Lista na qual será feita a permutação das palavras
    LISTA *lista = lista_criar(0);
    
    encontrar_caminho(distancia, lista, 0, path);
    // Imprime cidade de origem, caminho e a distancia.
    printf("%d\n", origem+1);
    printf("%d ", path->caminho[tamanho + 1]+1);
    for(int i = tamanho; i >= 0; i--){
        printf("- %d ", path->caminho[i]+1);
    }
    printf("\n%d", path->menor_distancia);

    lista_apagar(&lista);
    free(path->caminho);
    path->caminho = NULL;
    free(path);
    path = NULL;

    return;
}

void encontrar_caminho(GRAFO **distancia, LISTA *lista, char index, CAMINHO *path){
   if(index == path->origem) index++;
   
   if(lista_tamanho(lista) == 0) lista_inserir(lista, index);
   
   // Possivel permutação
   if(lista_tamanho(lista) == path->tamanho){
        // Se não há caminho com a origem, não é um caminho valido.
        if(grafo_peso(distancia[index], path->origem) == -1) return; 
        // Vetor que guardará esse caminho temporario.    
        char *caminho = (char*) malloc(((path->tamanho) + 2) * sizeof(char)); 
        // Guarda o caminho formado no vetor.
        caminho[0] = path->origem;
        for(int i = 0; i < path->tamanho; i++){
           caminho[i+1] = lista->chave[i];  
        } 
        caminho[(path->tamanho) + 1] = path->origem;
        // Percorrer o caminho, se existir, somando as distancias.
        int dist = 0;
        for(int i = 1; i <= (path->tamanho) + 1; i++){
            // Variavel com objetivo de chamar a função de busca apenas 1 vez.
            int temp_dist = grafo_peso(distancia[caminho[i-1]], caminho[i]);
            // Se não existir caminho, não é um resposta válida.
            if(temp_dist == -1){
                free(caminho); 
                caminho = NULL; 
                return;
            }

            dist += temp_dist;
        }
        // Caso esse caminho, tenho distancia menor, salva-se ele.
        if(dist < path->menor_distancia){
            path->menor_distancia = dist;

            if(path->caminho != NULL)
                free(path->caminho);
            
            path->caminho = caminho; 
        }

        return;
   }
   
   // Não permuta-se a origem, tendo em vista que estara no inicio da palavra.
    if(index + 1 == path->origem) index++;

    // Inseri a proxima cidade em todas as posições possiveis, ate formar todas as permutações.
    for(int i = 0; i <= lista_tamanho(lista); i++){
        lista_inserir_posicao(lista, i, index + 1);
        encontrar_caminho(distancia, lista, index+1, path);
        lista_remover(lista, index+1);
    }
}

