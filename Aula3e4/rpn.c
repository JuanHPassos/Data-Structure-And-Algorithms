#include "Pilha.h"

#include<stdio.h>
#include<stdlib.h>

float rpn(char *sequencia){
    if(sequencia != NULL){
        PILHA *pilha = pilha_criar();
        while(*sequencia != '\0'){
            if(*sequencia >= '0' && *sequencia <= '9'){
                //Atualiza o ponteiro para uma nova região da memória.
                float *numero = (float*) malloc(sizeof(float));
                
                *numero = (float) *sequencia-'0'; 
                
                pilha_empilhar(pilha, item_criar(0,numero));
            }
            else{
                //Recebe-se os topos da pilha e seus respectivos numeros.
                ITEM *topo1 = pilha_desempilhar(pilha); 
                ITEM *topo2 = pilha_desempilhar(pilha);
                float *resultado = (float*) malloc(sizeof(float));
                float operando1 = *(float*)item_get_dados(topo1);
                float operando2 = *(float*)item_get_dados(topo2);

                switch (*sequencia){
                    // "48/" é igual a 8/4.
                    case '+': *resultado = operando2 + operando1; break;
                    case '-': *resultado = operando2 - operando1; break;
                    case '*': *resultado = operando2 * operando1; break;
                    case '/': *resultado = operando2 / operando1; break;
                }
                
                pilha_empilhar(pilha, item_criar(0, resultado));
                item_apagar(&topo1);
                item_apagar(&topo2);

            }
            sequencia++;
        }   

        ITEM *ultimo_elemento = pilha_desempilhar(pilha);
        float resposta = *((float*)item_get_dados(ultimo_elemento));
        item_apagar(&ultimo_elemento);
        pilha_apagar(&pilha);

        return resposta;
    
    }
    exit(1);
}