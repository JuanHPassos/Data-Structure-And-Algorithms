#include "Conjunto.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  /*0 -> AVL, 1 -> Rubro negra*/
  unsigned char tipo;
  scanf("%hhu", &tipo); 

  // Criar conjuntos.
  CONJUNTO *A = conjunto_criar(tipo);
  CONJUNTO *B = conjunto_criar(tipo);

  // Tamanho conjunto a e b.
  int tamanho_a, tamanho_b;
  scanf("%d %d", &tamanho_a, &tamanho_b);

  for(int i = 0; i < tamanho_a; i++)
  {
    // Elemento a ser inserido no conjunto.
    int elemento;
    scanf("%d", &elemento);
    conjunto_inserir(A, elemento);
  }

  for(int i = 0; i < tamanho_b; i++)
  {
    // Elemento a ser inserido no conjunto.
    int elemento;
    scanf("%d", &elemento);
    conjunto_inserir(B, elemento);
  }

  int operacao;
  scanf("%d", &operacao);

  switch(operacao){
    case 1: 
      int elemento_pertence;
      scanf("%d", &elemento_pertence);
      if(conjunto_pertence(A, elemento_pertence))
        printf("Pertence");
      else
        printf("Nao pertence");
      break;
    case 2: 
      // C é o conjunto união de A e B.
      CONJUNTO *C_uniao = conjunto_uniao(A, B);
      conjunto_imprimir(C_uniao);
      conjunto_apagar(&C_uniao);
      break;
    
    case 3: 
      // C é o conjunto união de A e B.
      CONJUNTO *C_intersec = conjunto_interseccao(A, B);
      conjunto_imprimir(C_intersec);
      conjunto_apagar(&C_intersec);
      break;
    case 4: 
      // Elemento a ser removido de A.
      int elemento_remover;
      scanf("%d", &elemento_remover);
      conjunto_remover(A, elemento_remover);
      break;   
  }

  conjunto_apagar(&A);
  conjunto_apagar(&B);
    
  return 0;
}
/*
 0
 5 
 3
 1 2 3 4 5
 7 3 8
 1
 2
*/
