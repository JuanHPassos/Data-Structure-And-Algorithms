#include "Grafo.h"

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

int grafo_peso(GRAFO *grafo, char chave){
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