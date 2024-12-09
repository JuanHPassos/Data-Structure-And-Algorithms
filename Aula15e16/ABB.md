# ABB (Árvore Binária de Busca)

Possui seguuintes propriedades:

- Seja S = {$s_i$, ... , $s_n$} o conjunto de chaves dos nós da árvore T.
  - Esse conjunto de chaves satifaz $s_i$ < ... < $s_n$
  - A cada nó $v_j$ $\in$ T está associada uma chave distinta $s_j$ $\in$ s, que pode ser consultada por r($v_j$) = $s_j$

- Dado um nó v de T:
  - Se $v_i$ pertence a sub-árvore esquerda de v, então r($v_i$) < r(v) 
  - Se $v_i$ pertence a sub-árvore direita de v, então r($v_i$) > r(v) 

## Definições

- Um percurso `em-ordem` em uma ABB resulta na sequência de valores em ordem crescente.
- Bom, se invertemos as propriedades supracitadas(direita - menor e esquerda - maior), obtém-se valores em ordem decrescente.

- **Objetivo**: buscar elementos(pode sofrer inserções e remoções).
O tempo de busca é estimado pelo número de comparações de chaves. As ABB constituem a alternativa que combina as vantagens das listas sequenciais e encadeadas: são encadeada(cresce e diminui sobre demanda) e permitem busca binária $O(log n)$

## Funções

### Inserção

- Procurar "local" para inserir o novo nó, começando a procura a partir do nó-raiz.
- Se um ponteiro( filho esquerdo/direito de um nó-raiz) nulo é atingido, coloque o novo nó como sendo filho do nó-raiz.
- Para cada nó-raiz de uma sub-árvore:
  - Se a chave for menor que o nó atual, percorre-se o filho da esquerda.
  - Se a chave for maior que o nó atual, percorre-se o filho da direita.

## Busca
Começa pela raiz, caso o nó pesquisado seja nulo, retorne nulo. Caso a chave pesquisada seja encontrada, retorne o item do nó pesquisado.
Para cada nó-raiz de uma sub-árvore compare:
Se o valor da chave for menor, continue pela sub-árvore esquerda, caso contrário, continue pela direita.

## Remoção

Casos de remoção:
    - Caso 1: o nó é folha.
      - Retirar sem problema.
    - Caso 2: o nó possui uma sub-árvore.
      - O nó da sub-árvore ocupa o lugar do nó retirado.
    - Caso 3: o nó possui duas sub-árvores.
      - Qualquer um dos nós podem ocupar o mesmo lugar.


   