#include "Lista.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct no_ NO;

struct no_{
   NO *proximo;
   ITEM *item;
};

/*Estrutura de controle*/
struct lista_{
   NO *inicio;
   NO *fim;
   int tamanho;
   bool ordenada;
};

//Modularização funções
bool lista_inserir_ordernado(LISTA *lista, ITEM *item);
bool lista_inserir_fim(LISTA *lista, ITEM *item);


LISTA *lista_criar(bool ordenada){
   LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
   
   if(lista != NULL){
      lista->inicio = NULL;   
      lista->fim = NULL;
      lista->tamanho = 0;
      lista->ordenada = ordenada;   
   }

   return(lista);
}

bool lista_inserir(LISTA *lista, ITEM *item){
   if(!lista_cheia(lista)){
      if(lista->ordenada){
         lista_inserir_ordernado(lista, item);
      }
      else{
         lista_inserir_fim(lista, item);
      }
      return true;
   }  
   return false; 

}
bool lista_inserir_ordernado(LISTA *lista, ITEM *item){
   NO *no = (NO*) malloc(sizeof(NO));
   
   no->item = item;

   if(lista->inicio == NULL){
      lista->inicio = no; 
      lista->fim = no; 
      no->proximo = NULL;
   }
   else{
      int chave = item_get_chave(item);
      if(chave <= item_get_chave(lista->inicio->item)){
         no->proximo = lista->inicio;
         lista->inicio = no;
      }
      else if(item_get_chave(lista->fim->item) <= chave){
         lista->fim->proximo = no;
         lista->fim = no;
      }
      else{
         NO *busca = lista->inicio;

         while(chave > item_get_chave(busca->proximo->item)){
         busca = busca->proximo;
         }
         
         no->proximo = busca->proximo;
         busca->proximo = no;
      
      }   
   }

   lista->tamanho++;
   return true;
}

bool lista_inserir_fim(LISTA *lista, ITEM *item){
   NO *no = (NO*) malloc(sizeof(NO));

   no->item = item;
   no->proximo = NULL;

   if(lista->inicio == NULL){
      lista->inicio = no;
      lista->fim = no;
   }
   else{
      lista->fim->proximo = no;
      lista->fim = no;   
   }
   lista->tamanho++;
   
   return true;
}

bool lista_apagar(LISTA **lista){
   if(!lista_vazia(*lista)){
      while((*lista)->inicio != NULL){
         // Tirar no da lista, deixando-a encadeada.
         NO *no_apagado = (*lista)->inicio;
         (*lista)->inicio = (*lista)->inicio->proximo;
         
         // Apagar no com o item.
         no_apagado->proximo = NULL; 
         item_apagar(&(no_apagado->item));
         free(no_apagado); no_apagado = NULL;
      }
      (*lista)->fim = NULL;
      free(*lista); *lista = NULL;
      
   }
}

ITEM *lista_remover(LISTA *lista, int chave){
   NO *remover_no = NULL;
   ITEM *item = NULL;
   if(!lista_vazia(lista)){
      if(chave == item_get_chave(lista->inicio->item)){ 
         remover_no = lista->inicio;
         lista->inicio = lista->inicio->proximo;
      }
      else{
         NO *busca = lista->inicio;

         while(busca->proximo != NULL){
            if(chave == item_get_chave(busca->proximo->item)) break;
            busca = busca->proximo;
         }

         //Se o no procurado(busca->proximo) for null, não há o no com a chave buscada.
         if(busca->proximo == NULL) return NULL;

         //busca->proximo é o no a ser removido.
         remover_no = busca->proximo;

         // Se o no a ser removido, for o ultimo da lista, arruma-se o ponteiro fim.
         if(remover_no->proximo == NULL){
            lista->fim = busca;
         }

         //Garante a ligação da lista.
         busca->proximo = busca->proximo->proximo;

      }

      //Remoção do no, e retorno do item.
      remover_no->proximo = NULL;
      item = remover_no->item;
      free(remover_no);
      remover_no = NULL; // Boa prática.
      lista->tamanho--;

   }

   return (item);
}

ITEM *lista_busca(LISTA *lista, int chave){
   if(!lista_vazia(lista)){
      NO *busca = lista->inicio;
      while(busca != NULL){
         if(chave == item_get_chave(busca->item)) return(busca->item);
         busca = busca->proximo;
      }
   }
   return(NULL);
}

int lista_tamanho(LISTA *lista){
   if(lista != NULL){
      return(lista->tamanho);
   }
   return(-1);
}

bool lista_vazia(LISTA *lista){
   if(lista != NULL){
      return(lista->inicio == NULL);
   }
   return true;
}

bool lista_cheia(LISTA *lista){
   if(lista != NULL){
      NO *no = (NO*) malloc(sizeof(NO));

      if(no == NULL) return(true);
   
      free(no); no = NULL;
      return(false);
   }
   return(true);
}

void lista_imprimir(LISTA *lista){
   if(!lista_vazia(lista)){
      NO *imprimi = lista->inicio;
      while(imprimi != NULL){
         printf("%d\n", item_get_chave(imprimi->item));
         imprimi = imprimi->proximo;
      }
   }
}