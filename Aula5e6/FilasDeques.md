# Fila
- Identico as filas do mundo real, o primeiro a chegar é o primeiro a sair.

## O que é?
- É uma estrutura para armazenar um conjunto de elementos, que funciona da seguinte forma.
- Novos elementos = fim da fila.
- Tirar apenas o primeiro elemento.

## Para que serve?
Modelar situações em que é preciso armazenar um conjunto de elementos, no qual o primeiro a entrar, deve ser o primeiro a sair.

## Operações principais
- `fila_criar()`: cria uma fila F vazia.

- `fila_inserir(F,x)`: insere o elemento x no final da fila F.
(true se foi bem sucedido, false caso contrario).

- `fila_remover(F)`: remove o primeiro elemento de F, e retorna ele.
(NULL caso nao seja possivel devolver).

`fila_frente(F)`: retorna o primeiro elemento da fila(sem remove-lo).

`fila_tamanho(F)`: retorna numero de elementos da fila.

`fila_vazia(F)`: verifica se existe e se tam == 0.

`fila_cheia(F)`: verifica se existe e se tem espaço.

## Implementação sequencial

Filas sequencias serão criadas de forma circular para quando tirar um elemento da frente, nao perca-se a posição
do inicio do vetor. Dessa forma tem-se um referencia para o inicio(remoção) e fim(inserção), alem do total de elementos.

## Implementação dinâmica

Filas encadeadas(dinamicas) são implementadas com um no, o qual terá um item e um ponteiro para o proximo da fila.

# Deque 
É uma junção de pilha com fila, podendo fazer inserções tanto no fim quanto no inicio, e remoções tanto no fim como no inicio.

## Implementação sequencial

Nota-se que na implementação sequencial, sera implementada de forma circular, para que não se perca espaços dos vetores após as remoções, sem a necessidade de um bit shift após cada remoção.


## Implementação dinâmica

Deques encadeados(dinamicos) são implementadas com um no(struct), o qual terá um item e um ponteiro para o proximo e anterior do deque.
