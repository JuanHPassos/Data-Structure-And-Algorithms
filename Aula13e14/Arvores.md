# Árvores

## Introdução

- `Estrutura de listas`: organização linear dos dados, onde sua propriedade básica é a relação sequencial mantida entre seus elementos.
- `Estrutura de árvores`: organização dos dados de forma não-linear mantendo um relacionamento hierárquico entre seus elementos.

### Exemplos

Representação baseada na relação hierárquica entre os elementos:
1. Árvores genealógicas(Pais, filhos, netos...)
2. Organização de um livro(Livro, cap, seções...)
3. Representação da estrtura organizacional de uma instituição.(USP, Departamentos, Professores)

Obeerve que para extrair informações específicas de uma determinada ramificação da árvore não é necessário o percurso por toda a estrutura de informação, uma vez que o relacionamento entre os dados nos permite uma consulta seletiva em regiões específicas das árvore.
- *Uni a vantagem da implementação encadeada com busca binária(árvores binárias)*
  
## Definição

Uma árvore enraizada T é um conjunto finito de elementos denominados *nós* ou vértices tais que:
- T = $\emptyset$, a árvore é dita vazia.
- T = {r} U {$T_1$} U {$T_2$} U {$T_3$} U ... U{$T_n$}

Um nó especial da árvore, r, é chamado de *raiz* da árvore. Os restantes constituem um único conjunto vazio ou são dividos em n $\geq$ 1 conjuntos disjuntos não vazios, $T_1$, $T_2$, $T_3$, ... ,$T_n$, as *subárvores* de r, cada qual por sua vez uma árvore. Assim, para denotar uma árvore T usamos:
T = {$T_1$, $T_2$, $T_3$, ..., $T_n$}, com r a raiz da árvore e $T_v$ a subárvore T com raiz em v. *Note que a definição apresentada é recursiva!*

## Representação

A estrutura de árvore pode ser representada graficamente de diversas maneiras, dentre elas temos:
- Conjunto aninhados
- Indentação
- Grafos(mais utilizada)

## Terminologias

Considerando a árvore Tc, Tc = {D, {E,{F}},{G,{H,{I}},{J,{K},{L}},{M}}}, e a definição dada de árvores anteriormentes vejamos algumas terminologias básicas.
- O *grau de um nó* é o número de sub-árvores relacionadas àquele nó. Por exemplo: em Tc o grau do nó D é 2, de G é 3 e dos nós K, L, I, F e M é 0.
- Nós com grau igual a zero não possuem sub-árvores, portanto são chamados *nós folhas ou terminais*.
- Se cada nó de uma árvore possui um grau máximo e todos os nós possuem o mesmo grau máximo, podemos definir este grau como o *grau da árvore*.

Para identificar os nós na estrutura, usamos denominações da relação hierárquica existente em uma árvore genealógica.
- Cada raiz $R_i$ da sub-árvore $T_i$ é chamada *filho* de R. O termo *neto* é usado de forma análoga.
- O nó raiz r da árvore T é o *pai* de todas as raízes $r_i$ das sub-árvores $T_i$. O termo *avô* é definido de forma análoga.
- Duas raízes $r_i$ e $r_j$ das sub-árvores $T_i$ e $T_j$ de T são ditas *irmãs*.

Outras definições importantes são obtidas a partir da distância de um nó em relação aos outros nós da árvore.
- *Caminho*: sequência não vazia de nós P = {$r_1$, $r_2$, ...,$r_k$}, onde o i-ésimo nó $r_i$ da sequência é pai de $r_{i+1}$.(Conjuntos dos nós pai-filho)
- *Comprimento*: tomando a definição de caminho, o comprimento de um caminho P é igual a k-1.(Quantidade de arestas)

- *Altura de um nó*: a altura de um nó $r_i$ é o comprimento do `caminho mais longo` do nó $r_i$ a uma folha.(folhas têm algura 0).
- *Altura de uma árvore*: é igual a altura da raiz de r e T.(Comprimento entre raiz e folha mais longe)
- *Profundidade*: a profundidade de um nó $r_i$ de uma árvore T é o comprimento do `único caminho` em T entre a raiz r e o nó $r_i$.
- *Nível*: um conjunto de nós com a mesma profundidade é denominado nível da árvore.(raiz possui nivel zero).
*DICA: Altura = Folha. Profundidade = Raiz.*

- *Ascendência e descendência*: considerando dois nós $r_i$ e $r_j$, o nó $r_i$ é um ancestral de $r_j$ se existe um caminho em T de $r_i$ e $r_j$, tal que, o comprimento de P entre $r_i$ e $r_j$ seja diferente de 0.(De forma análoga se define descendente de um nó)








