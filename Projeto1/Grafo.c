#include "Grafo.h"
#include "Lista.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct no_ NO;

struct no_{
   NO *proximo;
   char chave;
   int peso;
};

/*Estrutura de controle*/
struct grafo_{
   NO *inicio;
   NO *fim;
   int tamanho;
};
// Struct usada para achar menor caminho.
typedef struct resposta_{
    int menor_distancia;
    char *caminho;
    char origem;
    char tamanho;
}CAMINHO;
// Modularizao
void encontrar_caminho(GRAFO **distancia, LISTA *lista, char index, CAMINHO *path);

GRAFO *grafo_criar(){
   GRAFO *grafo = (GRAFO*) malloc(sizeof(GRAFO));
   
   if(grafo != NULL){
      grafo->inicio = NULL;   
      grafo->fim = NULL;
      grafo->tamanho = 0; 
   }

   return(grafo);
}

bool grafo_inserir(GRAFO *grafo,char chave, int peso){
   if(!grafo_cheia(grafo)){
      NO *no = (NO*) malloc(sizeof(NO));
      no->chave = chave;
      no->peso = peso;
      no->proximo = NULL;

      if(grafo->inicio == NULL){
         grafo->inicio = no;
         grafo->fim = no;
      }
      else{
         grafo->fim->proximo = no;
         grafo->fim = no;   
      }
      grafo->tamanho++;
      
      return true;
   }
   return false;
}

bool grafo_apagar(GRAFO **grafo){
   if(!grafo_vazia(*grafo)){
      while((*grafo)->inicio != NULL){
         // Tirar no do grafo, deixando-a encadeada.
         NO *no_apagado = (*grafo)->inicio;
         (*grafo)->inicio = (*grafo)->inicio->proximo;
         
         // Apagar no.
         no_apagado->proximo = NULL; 
         free(no_apagado); no_apagado = NULL;
      }
      (*grafo)->fim = NULL;
      free(*grafo); *grafo = NULL; 
      return true;
   }
   return false;
}

int grafo_busca(GRAFO *grafo, char chave){
   if(!grafo_vazia(grafo)){
      NO *busca = grafo->inicio;
      while(busca != NULL){
         if(chave == busca->chave) return(busca->peso);
         busca = busca->proximo;
      }
   }
   return(-1); // Não há ligação
}

int grafo_tamanho(GRAFO *grafo){
   if(grafo != NULL){
      return(grafo->tamanho);
   }
   return(-1);
}

bool grafo_vazia(GRAFO *grafo){
   if(grafo != NULL){
      return(grafo->inicio == NULL);
   }
   return true;
}

bool grafo_cheia(GRAFO *grafo){
   if(grafo != NULL){
      NO *no = (NO*) malloc(sizeof(NO));

      if(no == NULL) return(true);
   
      free(no); no = NULL;
      return(false);
   }
   return(true);
}

void grafo_imprimir(GRAFO *grafo){
   if(!grafo_vazia(grafo)){
      NO *imprimi = grafo->inicio;
      while(imprimi != NULL){
         printf("%d\n", imprimi->chave);
         imprimi = imprimi->proximo;
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
        if(grafo_busca(distancia[(int)index], path->origem) == -1) return; 
        // Vetor que guardará esse caminho temporario.    
        char *caminho = (char*) malloc(((path->tamanho) + 2) * sizeof(char)); 
        // Guarda o caminho formado no vetor.
        caminho[0] = path->origem;
        for(int i = 0; i < path->tamanho; i++){
           caminho[i+1] = lista_get_chave(lista, i); // lista->chave[i]
        } 
        caminho[(path->tamanho) + 1] = path->origem;
        // Percorrer o caminho, se existir, somando as distancias.
        int dist = 0;
        for(int i = 1; i <= (path->tamanho) + 1; i++){
            // Variavel com objetivo de chamar a função de busca apenas 1 vez.
            int temp_dist = grafo_busca(distancia[(int)caminho[i-1]], caminho[i]);
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
        encontrar_caminho(distancia, lista, index + 1, path);
        lista_remover(lista, index + 1);
    }
}
