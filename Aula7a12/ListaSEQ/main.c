#include"Lista.h"

#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;
    LISTA *lista = lista_criar(1); 
    scanf("%d", &n);

    for(int i = 0; i<n; i++){
        int numero;
        scanf("%d", &numero);
        lista_inserir(lista, item_criar(numero, NULL));
    }

    lista_imprimir(lista);

    // lista_apagar(&lista);

    return 0;
}