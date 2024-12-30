# Árvores rubro-negras
- Balancear árvore binária de busca
- Left-leaning Red-Black Trees

### Porque rubro-negra?
Arestas são coloridas:
- Vermelhas
- Pretas

### Regras (caracterização de desbalanceamento)
1. Aresta vermelha sempre vai para o filho esquerdo
2. Todo nó possui, no máximo, uma aresta vermelha
3. Balanceamento negro perfeito
   - Todo filho nulo está à mesma distância da raiz - distância negra
       - Considerando apenas as arestas negras 

A árvore pende para a esquerda e no pior caso tem 2log(n)

# Funções principais:

## Inserção
- Igual à ABB
- Porém, todo nó possui aresta incidente **vermelha!**

A cor da aresta que chega no nó, está no nó de destino.
Toda inserção, é com uma aresta vermelha.

# Exemplo
```
        30
    20      40
10

Inserir 45:
        30
    20      40
10              45

Viola regra de ser aresta vermelha na direita, solução é rotacionar para esquerda:
        30
    20      40
10       45

```

**Existem 3 casos de inserção:**

### Inserção em nó com incidência vermelha:
```
    b
a

Inserir c:
    b   
a       c

Aresta de "b" com "a" já era vermelha e "b" com "c" é vermelho:
1º se um nó tem duas arestas vermelha, inverte as cores
A aresta que chega em "b", ficou vermelha eo resto preta.

```

### 2º caso:
```
    c
b

Inserir "a":
        c
    b
a

Cor de "b" e "a" são vermelhas, e cor de "c" preta, porém ao aplicar rotação direita:
    b   
a       c   

"c" fica vermelha e "a" vermelha, porém "b" fica preta, agora realizamos o primeiro caso(inversão).

````

3º Caso("a" vermelho, "c" preto):
```
    c   
a

Inserir b:
    c
a
  b

"b" fica vermelho a direita, logo rotação esquerda:
        c
    a
b
Caímos no segundo caso, rotação direita e inverte.
    a
b        c

"a" preto, "b" vermelho e "c" vermelho.

OBS:Por definição a raiz é negra, setar sempre para negra.
```

A inserção é igual a ABB, mas no final devemos fazer as operações nessa ordem.
A ordem das operações é:
1. Rotação Esquerda.
2. Rotação Direita.
3. Rotação Inverter.

## Remoção

Remoção sempre de um nó com aresta vermelha(pois não causa desbalanceamento)
 - Aplicar conceitos de remoção de ABB no caso de nó não folha
   - Substituição de chave não altera formato/propriedades da árvore
 - Propagar aresta vermelha da raiz até a folha se necessário:
   - Se busca pela esquerda: moveRedLeft
   - Se busca pela direita: moveRedRight
 - Na volta da recursão: operações inverte, rotação direita e esquerda para corrigir violações.

Ou seja, devemos arrumar a árvore para o nó a ser removido ser um nó folha com uma aresta vermelha no final da árvore e após remover devemos reajustar a árvore novamente.

### MoveRedLeft
Exemplo de árvore:
```
        H
    T       T
T        T

Caso caminho a ser tomado for esquerda, verificar:
Se aresta esquerda for negra e aresta esquerda esquerda for negra:
    Se a aresta direita->esquerda for negra
        Inverta(H)
    Senão
        Inverta(H)
        Rotação direita(H->dir)
                H
            T       T
        T               T
        Rotação esquerda(H)
                    T
                H       T
            T               
        T    
        Inverte(T nova raiz)
                    T(nova raiz)
                H       T
            T               
        T
Senão
    apenas prosseguir.

Após isso o valor foi encontrado, e é necessário rearrumar a árvore.
Com as mesmas operações de inserção.
```
