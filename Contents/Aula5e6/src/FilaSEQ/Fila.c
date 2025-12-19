#include "Fila.h"

#include<stdio.h>
#include<stdlib.h>

struct fila_{
    ITEM *fila[TAM_MAX];// Vetor de ponteiros para item.  
    int ini;
    int fim;
    int tam;// Tamanho.
};

FILA* fila_criar(void){
    FILA *fila = (FILA*) malloc(sizeof(FILA));
    if(fila != NULL){
        fila->ini = 0;
        fila->fim = 0;
        fila->tam = 0;
    }
    return (fila);
}

bool fila_cheia(FILA *fila){
    if(fila != NULL){
        return (fila->tam == TAM_MAX);
    }
    return (true);
}

bool fila_vazia(FILA *fila){
    if(fila != NULL){
        return (fila->tam == 0);
    }
    return (true);
}

bool fila_inserir(FILA *fila, ITEM *item){
    if(!fila_cheia(fila)){
        
        fila->fila[fila->fim] = item;    
        
        fila->tam++;
        
        fila->fim = (++(fila->fim))%TAM_MAX;
        
        return (true);
    }
    
    return (false);
}

ITEM *fila_remover(FILA *fila){
    if(!fila_vazia(fila)){
        ITEM *frente = fila->fila[fila->ini];

        fila->fila[fila->ini] = NULL;
        
        fila->tam--;

        fila->ini = (++(fila->ini))%TAM_MAX;

        return (frente);
    }
    return (NULL);
}

int fila_tamanho(FILA *fila){
    if(fila != NULL){
        return (fila->tam);
    }
    return (-1); // ERRO
}

ITEM *fila_frente(FILA *fila){
    if(fila != NULL){
        return (fila->fila[fila->ini]);
    }
    return (NULL);
}
/*Implementação na qual desalocar o item é responsabilidade do usuário*/
void fila_apagar(FILA **fila){
    if(*fila != NULL){
        free(*fila);
        *fila = NULL;
    }
}
/*Implementação na qual o desenvolvedor desaloca o item para o usuario
void fila_apagar(FILA **fila){
    if(*fila != NULL){
        while(!fila_vazia(*fila)){
            ITEM* frente = fila_remover(*fila);
            free(frente);
            frente = NULL;
        }
        free(*fila);
        *fila = NULL;
    }
}
*/
