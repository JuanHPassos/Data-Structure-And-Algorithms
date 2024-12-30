#ifndef _PILHA_H
  #define _PILHA_H

  #include "item.h"
  #include <stdbool.h>

  typedef struct pilha PILHA;

  // Apagar item é responsabilidade do usuário.

  PILHA* pilha_criar(void);
  
  /*A função pilha apagar, apaga o item para o usuário e os dados nela contido,
  dessa forma, é recomendado que causo o usuário queira manter esse dados,
  esvazie a pilha primeiro e depois chame a pilha apagar.*/
  void pilha_apagar(PILHA** pilha);
  
  bool pilha_vazia(PILHA* pilha);
  bool pilha_cheia(PILHA* pilha);
  int pilha_tamanho(PILHA* pilha);
  ITEM* pilha_topo(PILHA* pilha);
  bool pilha_empilhar(PILHA* pilha, ITEM* item);
  ITEM* pilha_desempilhar(PILHA* pilha);
  void pilha_imprimir(PILHA* pilha);
  void pilha_inverter(PILHA **pilha);
  
#endif 
