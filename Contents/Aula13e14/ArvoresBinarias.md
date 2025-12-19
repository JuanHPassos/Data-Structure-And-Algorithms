# Árvores Binárias

## Conteudo

- Conceitos
- Implementação
- Percurso
- Operações

## Definição

Uma Árvore Binária(AB)T é um conjunto finito de elementos, denominados nós ou vértices, tal que:
1. Se T = $\emptyset$, árvore é dita vazia.
2. T contém um nó especial r, chamado raiz de T, e os demais nós podem ser subdivididos em dois sub-conjutos distintos $T_e$ e $T_d$, os quais também são árvores binárias(possivelmente vazias)
    - $T_e$ e $T_d$ são denominados sub-árvores esquerda e árvore direita de T, respectivamente.

## Porque Árvore Binária é importante?

Bom, dada uma lista encadeada, que nos proporciona uma melhor controle de memória, tem como problema a função de busca, pois diferente da sequencial, não é possível fazer uma busca binária. Assim, para resolver esse problema, existe a árvore binária que busca resolver esse problema de busca em uma implementação encadeada.

### Árvore Estritamente Binária
- Possui nós com 0(nenhum) ou 2(dois) filhos.
    - Nós interiores(Não folhas) têm 2 filhos.

### Árvore Binária Completa Cheia(ABCC)
- É uma Árvore Estritamente Binária
- Todos os seus nós-folha estão no mesmo nível.
- Obs: número de nós = $2^(d+1) - 1$

## Problemas(ABCC)
- Necessidade de manter os níveis cheios/completos

## Árvore Binária Completa(ABC)
- Se a **profundidade da árvore** é d, então cada nó folha está no nível d-1 ou no nível de d.
- O nível d-1 está totalmente preenchido.
- Os nós folha no nível d estão todos mais á esquerda possível.

## Árvore Binária Perfeitamente Balanceada
- Para cada nó, o número de nós de suas sub-árvores esquerda e direita difere em, no máximo, 1.

## Árvore Binária Balanceada
- Para cada nó, as alturas de suas sub-árvores diferem de, no máximo 1.
- Obs: toda perfeitamente balanceada é balanceada.

Anotações: 
Toda árvore completa é balanceada, porém nem toda árvore balanceada é completa.

## Percursos
- Percorrer AB, significa visistar cada nó uma unica vez.
  - Visita(ação em um nó):
    - Mostrar seu valor se for igual a i, sendo i inteiro.
    - Modificar valor do nó.
    - ...
  
Um percurso gera uma sequencia linear de nós, e podemos então falar de nó predecessor ou sucessor de um nó, segundo um dado percurso. Não existe um percurso único para árvores (binárias ou não): diferentes percursos podem ser realizados dependendo da aplicação.

### Percursos básicos

- pré-ordem:
    - visita raiz.
    - percorre a subárvore a esquerda em pré-ordem.
    - percorre a subárvore a direita em pré-ordem.
- em-ordem:
    - percorre a sub-árvore a esquerda em-ordem.
    - visita a raiz.
    - percorre a sub-árvore a direita em-ordem.
- pós-ordem:
    - percorre a sub-árvore a esquerda pós-ordem.
    - percorre a sub-árvore a direita pós-ordem.
    - visita a raiz.

