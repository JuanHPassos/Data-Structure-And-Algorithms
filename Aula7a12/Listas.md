# Listas

- Lista linear é uma sequencia de componentes do mesmo tipo.(Linear porque há um único caminho)

*Propriedade estrutural*: posição relativa. `(xi < xi+1)`
- Possui proximo e anterior.

As operações mais frequentes em listas são a busca(para poder inserir no meio), a inclusão e a remoção de um determinado elemento.
Lista podem ser ordenadas e a sua implementação depende do uso, podendo ser sequencial ou encadeado.

- Lista sequencial é um array de ponteiros para item.

- Listas simplesmente encadeadas, consistem em lista formada por nós com apenas ponteiros para o proximo.

## Listas Lineares Dinâmicas Duplamente Encadeadas

- Lista em que cada nó possui dois ponteiros, tanto para o proximo quanto para o anterior.
Utilizado quando é necessário navegar em dois sentidos, um exemplo é a playlist(com respectiva resprodução) de músicas, indo para o próximos e anterior. Beneficiado é a aplicação.
Manipulação da lista é mais complexa(possui mais um ponteiro), porém algumas operações são beneficiadas.

## Listas Encadeadas com Nó Cabeça

- Funciona em Listas Encadeadas a operação mais complexa é a remoção de um elemento dado uma chave.

- Pois o algoritmo precisa apontar para o item anterior ao que será removido, o que no caso da remoção do primeiro elemento, configura uma exceção que precisa ser tratada à parte.

- Uma solução que simplifica a implementação é substituir o ponteiro para início por um nó cabeça.

- Um nó cabeça é um nó normal da lista, mas esse é sempre o primeiro nó e a informação armazenada não tem valor.

No cabeça esta presenta durante todo o código, e auxilia na otimização da função de remover, diminuindo em uma comparação.

## Lista Encadeadas Circulares

Essa implementação consiste fazer o ultimo elemento, ao invés de apontar para nulo, apontar para o inicio. Portanto, nessa implementação nao é necessário ponteiro para inicio, tendo em vista que o inicio é definido por fim->proximo.

Essa implementação consiste em otimizar a função de busca, pois em uma implementação comum, faz-se 2 comparações por nó, verifca-se se ele é o fim da lista ou se é o item buscado. Resultando em 2n comparações.

Adiciona-se um nó sentinela, no qual é inserido a chave de busca. Assim busca-se apenas pela chave, pois quando ela encontrar, duas opções são possíveis, ou o no sentinela foi encontrado, ou foi encontrado o no da lista que possui essa chave, ressaltando que se inicia a busca no sentinela->próximo. Dessa forma, são realizadas apenas n comparações.

## Lista Encadeadas Ordenadas

- Não precisa de ponteiro de fim, porque a inserção será em qualquer posição da lista. O emprego do nó cabeça facilita a implementação uma vez que vamos buscar a posição anterior à inserção, e no caso de ser o menor item da lista, isso não representará uma exceção.

- Além disso, a busca pode ser melhorada, buscando um item igual, se for maior, nao achamos, pois todos depois desse maior, são maiores que ele.
