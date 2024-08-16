# TADs Ponto e Círculo
Sejam as interfaces dos `TADs` Ponto e Circulo como definido abaixo. Desenvolva a
implementação dos `TADs` e um programa cliente (main.c) que use os dois `TADs.` O
programa cliente deve, pela ordem:
 1. Criar um ponto p e um círculo r definidos pelo usuário (stdin);
 2. Imprimir as coordenadas do ponto;
 3. Imprimir as coordenadas do ponto central do círculo e o de seu raio;
 4. Apagar o ponto e apagar o círculo.
```c
 //(ponto.h)
 #ifndef PONTO_H
 #define PONTO_H
 typedef struct ponto_ PONTO; 
  PONTO *ponto_criar (float x, float y);
  void ponto_apagar (PONTO **p);
  bool ponto_set (PONTO *p, float x, float y);
  float ponto_get_x (PONTO *p);
  float ponto_get_y (PONTO *p);
  void ponto_print (PONTO *p); 
#endif
```
```c
//(circulo.h)
 #ifndef CIRCULO_H
 #define CIRCULO_H
 #include “ponto.h”
 typedef struct circulo_ CIRCULO; 
 CIRCULO *circulo_criar (PONTO *p, float raio);
 bool circulo_set_ponto (CIRCULO *c, PONTO *p);
 bool circulo_set_raio (CIRCULO *c, int raio);
 PONTO *circulo_get_ponto (CIRCULO *c);
 int circulo_get_raio (CIRCULO *c);
 void circulo_apagar (CIRCULO **circulo);
 #endif
```

| **Exemplo de Entrada** | **Exemplo de Saída**                             |
|------------------------|--------------------------------------------------|
| 5                      | Ponto: (5.0, 2.0)                                |
| 2                      | Circulo: Centro (4.0, 2.0), Raio = 7.0           |
| 4                      |                                                  |
| 2                      |                                                  |
| 7                      |                                                  |

## **Observações:**
 • O exercício deve ser desenvolvido individualmente por cada aluno, sendo este responsável por decidir as
 melhores opções de implementação.

 • Somente as bibliotecas stdio.h, stdlib.h e stdbool.h podem ser utilizadas.
