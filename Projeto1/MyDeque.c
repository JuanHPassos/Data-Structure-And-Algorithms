#include<stdio.h>
#include <stdlib.h>
#include "Deque.h"
#include "item.h"

typedef ITEM* Item;

typedef struct node_ {
  struct node_* proximo;
  struct node_* anterior;
  Item item;
}nodeObj;

typedef nodeObj* Node;

typedef struct deque_ {
  int tamanho;
  Node inicio;
  Node fim; 
}dequeObj;

typedef dequeObj* Deque;

Node node_criar() {
  Node node = malloc(sizeof(nodeObj));
  
  node->proximo = node->anterior = NULL;
  node->item = NULL;

  return node;
}
void node_apagar(Node* nodep) {
  Node node = *nodep;
  if (node == NULL) return;

  item_apagar(&node->item);
  free(node);
  node = NULL; 
}

Deque deque_criar() {
  Deque deque = malloc(sizeof(dequeObj));

  deque->tamanho = 0;
  deque->fim = deque->inicio = NULL;

  return deque;
}

void deque_apagar(Deque* dequep){
  Deque deque = *dequep;
  
  while(true){
    Node node = deque->inicio;
    if (node == NULL) break;
    deque->inicio = node->proximo;
    node_apagar(&node);
  }

  free(deque);
  deque = NULL;
}


bool deque_inserir_inicio(DEQUE* deque, ITEM* item) {
  if(deque == NULL) return false;
  if(deque_cheia(deque)) return false;

  Node node = node_criar();
  node->item = item;

  if (deque_vazia(deque)) {
    deque->fim = node;
  }
  else {
  deque->inicio->anterior = node;
  }

  node->proximo = deque->inicio;
  deque->inicio = node;

  deque->tamanho+=1;
  return true;
}

bool deque_inserir_fim(DEQUE* deque, ITEM* item) {
  if(deque == NULL) return false;
  if(deque_cheia(deque)) return false;

  Node node = node_criar();
  node->item = item;

  if (deque_vazia(deque)) {
    deque->inicio = node;
  }
  else {
    deque->fim->proximo = node;
  }

  node->anterior = deque->fim;
  deque->fim = node;

  deque->tamanho+=1;
  return true;
}

ITEM* deque_remover_inicio(DEQUE* deque) {
  if(deque == NULL) return NULL;
  if(deque_vazia(deque)) return NULL;

  if(deque->tamanho == 1) {
    deque->fim = NULL;
  }
  
  else {
    deque->inicio->proximo->anterior = NULL;
  }
  
  Node removidoNode = deque->inicio;
  Item removidoItem = removidoNode->item;

  deque->inicio = deque->inicio->proximo;

  free(removidoNode);

  deque->tamanho-=1;
  return removidoItem;
}

ITEM* deque_remover_fim(DEQUE* deque) {
  if(deque == NULL) return NULL;
  if(deque_vazia(deque)) return NULL;

  if(deque->tamanho == 1) {
    deque->inicio = NULL;
  }

  else {
    deque->fim->anterior->proximo = NULL;
  }

  Node removidoNode = deque->fim;
  Item removidoItem = removidoNode->item;

  deque->fim = deque->fim->anterior;

  free(removidoNode);

  deque->tamanho-=1;
  return removidoItem;
}


ITEM* deque_primeiro(DEQUE* deque) {
  if (deque == NULL) return NULL;
  if (deque_vazia(deque)) return NULL;
  return deque->inicio->item;
}

ITEM* deque_ultimo(DEQUE* deque) {
  if (deque == NULL) return NULL;
  if (deque_vazia(deque)) return NULL;
  return deque->fim->item;
}

int deque_contar(DEQUE* deque) {
  if (deque == NULL) return ERRO;
  return deque->tamanho;
}

bool deque_vazia(DEQUE* deque) {
  if(deque == NULL) return true;
  else return deque->tamanho == 0;
}
bool deque_cheia(DEQUE* deque) {
  if(deque == NULL) return true;
  else return deque->tamanho >= MAX_TAMANHO;
}
// Função que gera todas as permutações dos nos, e retorna a palavra que representa o menor caminho, junto com a menor distancia.
void caminho(DEQUE *deque, int index, int origem, int **m, int n,PATH *resp){
    // Não permuta-se a origem, tendo em vista que estara no inicio da palavra.
    if(index == origem) index++;

    // Se o deque estiver vazio, inicia-se.
    if(deque_contar(deque) == 0) deque_inserir_inicio(deque, item_criar(index, NULL));
    
    printf("%d", index);
    // Caso caminho tenha visitado todas as cidades, é um possivel resposta.
    if(deque_contar(deque) == n-1){   
      printf("/");     
        // Se nao for possivel voltar a origem, não é um caminho possível.
        if(m[index][origem] == 0){ 
          printf("oi");
          return;
        }
        
        char *path = (char*) malloc((n+1)*sizeof(char)); // Variavel de auxilio, armazena caminho feito.
        path[0] = origem + '0';
        Node nodeObj = deque->inicio;
        int cidade = 1; // Index do vetor que armazena o caminho.
        int distancia = 0; 
        // Enquanto nao percorrer todo o caminho.
        while(nodeObj != NULL){
          // Guarda cidade atual.
          path[cidade] = item_get_chave(nodeObj->item) + '0';
          
          // Se nao houver caminho possivel, distancia será 0, logo, não é uma solução possivel.
          if(m[path[cidade-1]-'0'][path[cidade]-'0'] == 0){
            free(path); path = NULL;
            return;
          }  
          else{
            // Caso contrario, percorre-se esse caminho.
            distancia += m[path[cidade-1]-'0'][path[cidade]-'0'];
          } 
          // Avança para proxima cidade.
          cidade++;
          nodeObj = nodeObj->proximo;
        }
        // Retorna a origem.
        distancia += m[path[cidade-1]-'0'][origem];
        
        // Caso novo caminho seja menor.
        if(distancia < (resp->distancia)){
          resp->distancia = distancia;
          
          if(resp->caminho != NULL) free(resp->caminho);
          
          resp->caminho = path;
        }    
        // Caso contrario, descarta-se essa opção.
        else{
          free(path); 
          path = NULL;
        }
    }
   
     // Não permuta-se a origem, tendo em vista que estara no inicio da palavra.
    if(index+1 == origem) index++;

    //Gerar todas as permutações.
    deque_inserir_fim(deque, item_criar(index+1, NULL));
    caminho(deque, index+1, origem, m, n, resp);
    ITEM *item = deque_remover_fim(deque);
    item_apagar(&item);

    deque_inserir_inicio(deque, item_criar(index+1, NULL));
    caminho(deque, index+1, origem, m, n, resp);
    item = deque_remover_inicio(deque);
    item_apagar(&item);
  
}

