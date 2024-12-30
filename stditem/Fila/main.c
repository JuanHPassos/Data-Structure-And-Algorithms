#include"Fila.h"

#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    FILA *fila = fila_criar();

    fila_inserir(fila, item_criar(1, NULL));
    fila_inserir(fila, item_criar(2, NULL));
    fila_inserir(fila, item_criar(3, NULL));
    fila_inserir(fila, item_criar(4, NULL));
    fila_inserir(fila, item_criar(5, NULL));
    fila_inserir(fila, item_criar(6, NULL));
    fila_imprimir(fila);
    fila_inverter(fila);
    fila_imprimir(fila);
    fila_remover(fila);
    fila_remover(fila);
    fila_remover(fila);
    fila_remover(fila);
    fila_inverter(fila);
    fila_imprimir(fila);

    fila_apagar(&fila);

    return 0;
}