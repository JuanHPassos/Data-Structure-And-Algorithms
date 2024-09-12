# Pilhas(TAD):

## Conteudo
  1.Conceitos Introdutórios
  2.Implementação Sequencial
  3.Implementação Encadeada
  4.Aplicações com Pilha

**- O que são pilhas? Para o que servem?**
- Empilhamento de dados(ITENS), e desempilha pelo ultimo colocado.
Servem para auxiliar problemas praticos em computação. Exemplos:
Botão de back do navegador web.

- Controle de chamadas de procedimentos:
chamada de função formam uma pilha, na qual são empilhados os endereços
de retorno e os parametros, ou seja, a memoria stack funciona como uma pilha.

### Definição: 
  São estruturas de dados nas quais as inserções e remoções são realizadas na mesma extremidade da estrutura, chamada topo.(Last-in/First-Out -> "Lifo").

### Exemplo
**Algoritmo: decimal -> binario**
Pilha funciona, pois obtem dado em uma ordem e a resposta esta na ordem inversa.

**- Organização vs alocação de memória**
`Alocação Estatica:` reserva memoria em tempo de compilação.
`Alocação Dinamica:` em tempo de execução.

`Sequencial:` contiguos.
`Encadeado:` são definidos por ponteiros.

1. Sequencial e estatica: Uso de arrays.
2. Encadeada e estática: Array simulando Mem. Princ.
3. Sequencial e dinamica: Alocação dinamica de Array.
4. Encadeada e dinamica: Uso de ponteiros.

**Obs: Não usa-se o 1 e 2, pois é necessario ponteiro para criar um TAD.**

## Operações principais:
-Empilhar dados(P,x): insere o elemento x no topo de P.
-Desempilhar dados(P): remove o elemento do topo de P, e retorna esse elemento.

### Auxiliares:
-Criar(P): Cria uma pilha vazia.
-Apagar(P): apaga a pilha P da memoria.
-Topo(P): retorna o elemento do topo de P, sem remover.
-Tamanho(P): retorna o numero de elementos em P.
-Vazia(P): indica se a pilha P está vazia.
-Cheia(P): indica se a pilha P está cheia(útil para implementações sequenciais).

## Implementação sequencial
Cria-se um vetor dinamicamente de determinado tamanho, e uma variavel topo, a qual guarda
o ultimo espaço livre da pilha. Se topo maior que tamanho, a pilha esta cheia.(topo == tamanho+1)
Desempilhar -> topo-1, pois topo é usado como a variavel que pode empilhar, entao para desempilhar e sempre topo-1. 

## Interface
```c
PILHA *pilha_criar(void);
void pilha_apagar(PILHA **pilha); //Passado por referencia para desalocar dentro da função.
bool pilha_vazia(PILHA *pilha);
bool pilha_cheia(PILHA *pilha);
int pilha_tamanho(PILHA *pilha);
ITEM *pilha_topo(PILHA *pilha);
bool pilha_empilhar(PILHA *pilha, ITEM *item);
ITEM *pilha_desempilhar(PILHA *pilha);

void pilha_print(PILHA *p);
void pilha_inverter(PILHA *p);
```

## Implementação da interface:
```c
#include "item.h"
#include <stdbool.h>
typedef struct pilha PILHA;
#define TAM 100 //Cliente precisa saber o tamanho da pilha

struct pilha{
    ITEM *item[TAM];//Item é um vetor de ponteiros para itens(TAD's)
    int tamanho; //Topo da pilha
};
...
//Programa cliente(cliente.c)
#include "pilha.h"
...
PILHA *p;
...

Exemplo Função:
PILHA *pilha_criar(void){
    PILHA *pilha;
    pilha = (PILHA*) malloc(sizeof(PILHA));//Cria vetor de ponteiros para item de tamanho 100.
    if(pilha != NULL){
        pilha->tamanho = 0;//Pilha vazia
    }    
    return (pilha);
}

bool pilha_vazia(PILHA *pilha){
    if(pilha != NULL)
        return (pilha->tamanho == 0);
    return false;
}

bool pilha_cheia(PILHA *pilha){
    if(pilha != NULL)
        return (pilha->tamanho == TAM);
    return false;
}

int pilha_tamanho(PILHA *pilha, ITEM *item){
    if(pilha != NULL){
        return pilha->tamanho;
    }
    return (-1);
}

bool pilha_empilhar(PILHA *pilha, ITEM *item){
    //Não verifica-se se o item existe, pois isso é responsabilidade do clinete.(A pilha empilha).
    if(!pilha_cheia(pilha)){
        pilha->item[pilha->tamanho] = item;
        pilha->tamanho++;
        return(true);
    }
    return(false);
}


ITEM *pilha_desempilhar(PILHA *pilha){
    //É necessario a variavel auxiliar, para "pilha->item[p->tamanho] = NULL;" essa linha existir.
    ITEM *topo = NULL;
    if(!pilha_vazia(pilha)){
        topo = pilha->item[(pilha->tamanho)-1];
        pilha->tamanho--;
        pilha->item[p->tamanho] = NULL;
    }
    return topo;
}
```

## Pilhas encadeadas

Cria-se nós que são ligados por meio de ponteiros do tipo nó, formando um encadeamento/sequencia, nao necessitando que esses nós estejam continuos na memoria. É necessario um inicio(ponteiro), que aponta para o primeiro nó, e a partir dele, percorre-se a sequencia.

### Nó
```c
typedef struct NO_ no;
struct no_{
    ITEM *item;

    no* anterior;
};
Pilha encadeada:
tepydef struct pilha_ PILHA;
struct pilha_{
    no* topo;
    int tamanho;
};
```

Cria-se a pilha com a struct pilha. Agora para empilhar, cria-se um nó, que ira receber o item passado como parametro(o que vai ser empilhado), alem disso, o anterior recebe o topo e o topo recebe a auxiliar.

### Exemplo de função com pilha encadeada
```c
void pilha_apagar(PILHA **pilha){
    if(*pilha != NULL){
        while((*pilha)->tamanho){
            NO* aux = (*pilha)->topo;
            (*pilha)->topo = aux->anterior;
            free(aux->item);
            aux->item = NULL;
            aux->anterior = NULL;
            free(aux);
            aux = NULL;
            (*pilha)->tamanho--;
        }
        free(*pilha);
        *pilha = NULL;
    }
}
```
