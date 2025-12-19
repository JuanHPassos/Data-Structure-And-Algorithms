#include "Pilha.h"

#include<stdio.h>
#include<stdlib.h>

bool balanceada(char *sequencia){
    PILHA *pilha;
    pilha = pilha_criar();
    if(pilha == NULL){
        exit(1);
    }
    while(*sequencia != '\0'){
        if(*sequencia == '('){
            pilha_empilhar(pilha, item_criar(')', NULL)); 
        }
        else if(*sequencia == '{'){
            pilha_empilhar(pilha, item_criar('}', NULL)); 
        }
        else if(*sequencia == '['){
            pilha_empilhar(pilha, item_criar(']', NULL)); 
        }
        else{
            if(!pilha_vazia(pilha) && *sequencia == item_get_chave(pilha_topo(pilha))){
                pilha_desempilhar(pilha);
            }
            else return false;
        }
        sequencia++;
    }
    return pilha_vazia(pilha);
}