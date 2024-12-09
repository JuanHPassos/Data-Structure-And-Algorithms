#include "Lista.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct no_ NO;

struct no_{
    ITEM *item;
    NO *proximo;
    NO *anterior;
};


struct lista_{
    NO *inicio;
    NO *fim;
    int tamanho; // Tamanho lista.
    bool ordenada;
}; 

bool lista_inserir_ordenada(LISTA *lista, ITEM *item);
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
// Implementar
bool lista_inserir_ordenada(LISTA *lista, ITEM *item){
    NO *novo_no = (NO*) malloc(sizeof(NO));
    novo_no->item = item;
    int chave = item_get_chave(item);
    if(chave < item_get_chave(lista->inicio->item)){
        novo_no->proximo = lista->inicio;
        lista->inicio->anterior = novo_no;
        lista->inicio = novo_no;
        lista->inicio->anterior = NULL;
    }
    else if(item_get_chave(lista->fim->item) < chave){
        novo_no->anterior = lista->fim;
        lista->fim->proximo = novo_no;
        lista->fim = novo_no;
        lista->fim->proximo = NULL;
    }
    else{
        NO *busca = lista->inicio;
        while(busca != NULL){
            if(chave < item_get_chave(busca->item)) break;
            busca = busca->proximo;
        }
        busca->anterior->proximo = novo_no;
        novo_no->anterior = busca->anterior;
        busca->anterior = novo_no;
        novo_no->proximo = busca;
    }
}
// Inseri ao fim da lista quando nao esta ordenada.
bool lista_inserir_fim(LISTA *lista, ITEM *item){
    NO *novo_fim = (NO*) malloc(sizeof(NO));
    novo_fim->item = item;

    lista->fim->proximo = novo_fim;
    novo_fim->anterior = lista->fim;

    lista->fim = novo_fim;
    novo_fim->proximo = NULL;
    return(true);
}
// Busca melhor inserção dada condição da lista.
bool lista_inserir(LISTA *lista, ITEM *item){
    if(!lista_cheia(lista)){
        if(lista->tamanho == 0){
            NO *inicio = (NO*) malloc(sizeof(NO));
            // Controle sobre os ponteiros do nó.
            inicio->anterior = NULL;
            inicio->proximo = NULL;
            // Garantir ligação.
            lista->inicio = inicio;
            lista->fim = inicio;
            // Guardar informação no nó.
            inicio->item = item;
        }
        else if(lista->ordenada){
            lista_inserir_ordenada(lista, item);
        }
        else{
            lista_inserir_fim(lista,item);
        }
        
        lista->tamanho++;
        return(true);
    }
    return(false);
}

bool lista_apagar(LISTA **lista){
    while(!lista_vazia(*lista)){
        // Atualiza lista sem o no do inicio(que sera apagado).
        NO *apaga_no = (*lista)->inicio;
        (*lista)->inicio = apaga_no->proximo;
        // Apaga no e item.
        item_apagar(&(apaga_no->item));
        apaga_no->proximo = NULL;
        apaga_no->anterior = NULL;
        free(apaga_no);
        apaga_no = NULL;
        // Atualiza tamanho da lista.
        (*lista)->tamanho--;
    }
    if(*lista != NULL){
        (*lista)->fim = NULL;
        free(*lista);
        *lista = NULL;
        return(true);
    }
    return(false);
}

// Remova da lista em tres casos(inicio, meio, fim).
ITEM *lista_remover(LISTA *lista, int chave){
    ITEM *retorno = NULL;
    if(!lista_vazia(lista)){
        if(chave == item_get_chave(lista->inicio->item)){
            NO *remove_inicio = lista->inicio;
            retorno = remove_inicio->item;

            lista->inicio = lista->inicio->proximo;
            // Seta o ponteiro anterior do primeiro no para NULL, caso contrario a lista esta vazia, entao ajusta-se o ponteiro fim para NULL tambem.
            if(lista->inicio != NULL)
                lista->inicio->anterior = NULL;
            else
                lista->fim = NULL;
            
            lista->tamanho--;

            remove_inicio->proximo = NULL;
            free(remove_inicio);
            remove_inicio = NULL;
            
        }
        else if(chave == item_get_chave(lista->fim->item)){
            NO *remove_fim = lista->fim;
            retorno = remove_fim->item;

            lista->fim = lista->fim->anterior;
            // Caso em que a lista acaba ja foi checado anteriormente.
            lista->fim->proximo = NULL;
            lista->tamanho--;

            remove_fim->anterior = NULL;
            free(remove_fim);
            remove_fim = NULL;
        }
        else{
            // Note que se chegar nesse caso, item buscado nao é as pontas.
            NO *remove_meio = lista->inicio;
            while(remove_meio->proximo != NULL){
                if(chave == item_get_chave(remove_meio->proximo->item)) break;
                remove_meio = remove_meio->proximo;
            }
            // Caso em que não há esse elemento no deque.
            if(remove_meio->proximo == NULL) return(NULL);
            // Guarda no a ser removido
            NO *no_removido = remove_meio->proximo;
            // Pula o no a ser removido, garantindo ligação da lista.
            remove_meio->proximo = no_removido->proximo;
            no_removido->proximo->anterior = no_removido->anterior; 
            // Salvar informação e remover o no.
            retorno = no_removido->item;
            no_removido->anterior = NULL;
            no_removido->proximo = NULL;
            free(no_removido);
            no_removido = NULL;
            // Atualizar tamanho da lista.
            lista->tamanho--;
        }
    }
    return(retorno);
}

ITEM *lista_busca(LISTA *lista, int chave){
    if(!lista_vazia(lista)){
        NO *busca = lista->inicio;
        while(busca != NULL){
            if(chave == item_get_chave(busca->item)) break;
            busca = busca->proximo;
        }

        if(busca != NULL) return(busca->item);
    }
    return(NULL);
}

int lista_tamanho(LISTA *lista){
    if(lista != NULL) return(lista->tamanho);
    return(-1); // Simboliza erro.
}

bool lista_vazia(LISTA *lista){
    if(lista != NULL){
        return (lista->tamanho == 0);
    }
    return(true); // Simboliza que usuário nao pode prosseguir.
}

bool lista_cheia(LISTA *lista){
    if(lista != NULL){
        NO *teste_memoria = (NO*) malloc(sizeof(NO));
        if(teste_memoria == NULL) return(true);
        free(teste_memoria); 
        teste_memoria = NULL; // Boa prática

        return(false);
    }
    return(true); // Simboliza que o usuario não pode prosseguir no seu objetivo.
}

void lista_imprimir(LISTA *lista){
    if(lista != NULL){
        NO *imprimi = lista->inicio;
        printf("Lista: ");
        while(imprimi != NULL){
            printf("%d ", item_get_chave(imprimi->item));
            imprimi = imprimi->proximo;
        }
        printf("\n");
    }
}