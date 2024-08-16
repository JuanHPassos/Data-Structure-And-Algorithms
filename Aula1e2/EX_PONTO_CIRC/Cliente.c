#include "ponto.h"
#include "circulo.h"
#include<stdio.h>

int main(void){
    PONTO *p;
    CIRCULO *r;

    float x, y, raio;
    scanf("%f %f", &x, &y);
    p = ponto_criar(x,y);
    scanf("%f %f %f", &x, &y, &raio);
    r = circulo_criar(ponto_criar(x,y), raio);
    printf("Ponto: "); 
    ponto_print(p);
    printf("\nCirculo: Centro "); 
    ponto_print(circulo_get_ponto(r));
    printf(", Raio = %.1f", circulo_get_raio(r));
    ponto_apagar(&p);
    circulo_apagar(&r);

    return 0;
}