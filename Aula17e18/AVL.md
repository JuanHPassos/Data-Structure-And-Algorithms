# Árvores AVL

## Introdução

- Árvore AVL 
    - ABB na qual as alturas das duas sub-árvores de todo nó nunca diferem em mais de 1.
    - Fator de Balanceamento de nó: a altura de sua sub-árvore esquerda menos a altura da sub-árvore direita,
    difere de no máximo 1.

### O que causa desbalanceamento?

Inserção em nós que ja possuem um desbalanceamento, como filhos de um nó que possui fator de balanceamento 1 ou -1.

# Técnicas de rotação(balanceia a árvore)

## Rotação Simples

### Rotação direita

- Ocorre quando há um **desbalanceamento à esquerda**.
  - O desbalanceamento à esquerda em uma árvore AVL ocorre quando o fator de balanceamento de um nó se torna maior que 1, indicando que a subárvore esquerda cresceu desproporcionalmente em relação à subárvore direita. O fator de balanceamento de um nó é calculado como a altura da subárvore esquerda menos a altura da subárvore direita. Se FB(𝑛)>1, o desbalanceamento está à esquerda. Esse problema normalmente surge após inserções ou remoções na subárvore esquerda do nó.
- O "nó mais jovem desbalanceado" em uma árvore AVL é o nó mais próximo da folha (em direção à raiz) que se torna desbalanceado após uma operação de inserção ou remoção. Esse nó é o primeiro a apresentar um fator de balanceamento fora do intervalo [-1,1] ao recalcular as alturas da árvore. Ele é crucial no processo de balanceamento, pois é a partir dele que as rotações (simples ou duplas) são aplicadas para restaurar o equilíbrio da árvore.
- O nó mais jovem desbalanceado (A) se torna o filho direito de seu filho esquerdo (B), enquanto o filho direito de B é realocado como o filho esquerdo de A. Essa operação reduz a altura da subárvore esquerda e aumenta a da subárvore direita de B, restaurando o equilíbrio e garantindo a propriedade de busca binária da árvore.

### Rotação esquerda

Análoga a rotação direita, com as seguintes mudanças.

- Ocorre **desbalanceamento à direita**.
- O nó mais jovem desbalanceado (A) se torna o filho esquerdo de seu filho direito (B), enquanto o filho esquerdo de B é realocado como o filho direito de A. Essa operação reduz a altura da subárvore direita e aumenta a da subárvore esquerda de B, restaurando o equilíbrio e garantindo a propriedade de busca binária da árvore.

## Rotação dupla

Uma rotação dupla ocorre em uma árvore AVL quando uma simples rotação (à direita ou à esquerda) não é suficiente para corrigir um desbalanceamento causado por inserções ou remoções. Isso acontece nos seguintes casos:

1. Rotação dupla à direita (esquerda-direita): 
Ocorre quando um nó apresenta desbalanceamento à esquerda (FB(n)>1), mas a inserção ou remoção ocorreu na subárvore direita de seu filho esquerdo.
2. Rotação dupla à esquerda (direita-esquerda): 
Ocorre quando um nó apresenta desbalanceamento à direita (FB(n)<−1), mas a inserção ou remoção ocorreu na subárvore esquerda de seu filho direito.

A rotação dupla combina duas rotações simples consecutivas: primeiro uma rotação na subárvore interna (esquerda ou direita) e, em seguida, uma rotação na raiz do nó desbalanceado, corrigindo o fator de balanceamento da árvore. 

Obs: fatores de balanceamento(A e B) com sinais diferentes, equivale a rotação dupla.

## Inserção em AVL's

- Utilizando as rotinas de rotação pode-se definir um algoritmo de inserção em árvores AVL.
- A maioria das implementações guardam o fator de balanceamento, porém guardar a altura dos nós facilita.
- A inserção é feita em dois passos:
  - O primeiro é uma inserção em ABBs.
  - O segundo é o rebalanceamento, se necessário.
Algoritmo de Inserção
 - A primeira etapa é definir uma inserção em ABB e atualizar as alturas dos nós.

Na volta da inserção o balanceamento é verificado, se a árvore estiver desbalanceada, aplicar as rotações necessárias.
O desbalaceamento pode ser verificado: 
- Com base na altura das sub-árvores cada nó armazena sua altura, assim, calcula-se o FB.
- Ou com base no fator de balanceamento cada nó armazena seu FB.
  
Se FB = -2 as rotações podem ser:
  - Esquerda
  - Direita/Esquerda
Se FB do filho direito (B) é negativo: rotação Esquerda, caso contrário rotação Direita/Esquerda.
Se FB = 2 as rotações podem ser:
  - Direita
  - Esquerda/Direita
Se FB do filho esquerdo (B) é positivo, rotação Direita, caso contrário rotação Esquerda/Direita.

## Remoção em AVL's

Utilizando as rotinas de rotação pode-se definir um algoritmo de remoção em árvores AVL.
A remoção é feita em dois passos:
  - O primeiro é uma remoção em ABB's.
    - Existem 3 casos possíveis: o nó a ser removido possui grau 0, 1 ou 2.
  - O segundo é o rebalanceamento, se necessário.


