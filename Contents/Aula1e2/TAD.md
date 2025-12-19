# Tipos abstratos de dados (TAD)

## Tipo de Dado
Método para tentar interpretar o conteúdo da memória do computador, define a quantidade de bytes e como se interpreta a sequência de bits.

### Tipos de Dados:
- **Básicos:** `int`, `char`, `double` ...
- **Abstrato:** Permite implementações diferentes.
  - Exemplo: Pilha pode ser implementada em um vetor ou de maneira encadeada. Ou seja, faz a mesma coisa, porém é implementada de maneira diferente, por isso é abstrato (seguindo um padrão).

## TAD (Tipo Abstrato de Dado)
Conjunto de valores e sequência de operações, que servem como modelo para definir e representar um tipo de dado estruturado. É usado para encapsular tipos de dados (ex: racional formado por dois inteiros), permitindo a encapsulação dos dados. Isso é importante para o cliente, pois ele não precisa se importar com a implementação.

- **Exemplo:** A preocupação de tempo e espaço é do desenvolvedor do TAD, que pode atualizar de maneira mais eficiente, sem precisar modificar o código.
- O TAD permite o ocultamento das informações que são limitadas às operações definidas pelo desenvolvedor, portanto, os dados são protegidos (controle do desenvolvedor).

## Implementação de Tipo de Dado Abstrato para Número Racional (2/7)
Desenvolver um tipo de dado novo como uma biblioteca para ser usado por outras pessoas (`arquivo.h`). O TAD fornece operações para aplicar em cima de um dado e é usado para criar um dado e organizá-los. O dado é definido no arquivo de implementação (esconde-se do usuário detalhes de implementação).

### Vantagens do TAD
- **Organização dos dados e controle:** Protege os dados dos usuários, que só podem acessar os dados por meio das operações.
  - *Exemplo:* Só pode usar racional da maneira que o desenvolvedor define (padronização).
- Atualizações na biblioteca podem ser feitas desde que não se mude a interface, assim não é necessário mudar o código.

### Resumo das Vantagens do TAD:
- **Reúso:** Permite compartilhamento para outros códigos e outras pessoas.
- **Manutenção:** Possibilidade de melhorar a eficiência sem precisar mexer no código.
- **Correção**
- **Independência de representação**

## Implementação
É necessário dois módulos:
1. **Módulo de definição do TAD (`arquivo.c`).** Não é visível para os clientes, é passado por um objeto para ser usado.
2. **Interface (`arquivo.h`).** Possui os protótipos das funções, é visível para os clientes.
   - Serve para guardar o `typedef` e os protótipos das funções, garantindo que o cliente não tenha acesso ao código fonte.

## Código do Cliente
A variável deve ser criada como ponteiro para saber a quantidade de memória a ser reservada, pois o código do cliente não tem acesso ao módulo de definição, não sabendo assim o tamanho da `struct`. Por isso, usar ponteiro, pois sempre são reservados 8 bytes.

Todo TAD possui dados, e só pode ter acesso aos dados por meio das funções definidas.

## Abstração ITEM
Serve para que, independentemente do tipo de dado que o cliente escolher, ele possa usar a função criada pelo desenvolvedor, sem a necessidade de alteração do código. O código do cliente usa o tipo de dado abstrato passando o dado que ele quer usar. Com esse item abstrato, a estrutura de dado utiliza ele com a estrutura que o cliente escolher, dessa forma, não há necessidade de alterar o código fonte.

- Deve-se passar o `cliente.c` e o `item.c` para o compilador:
  ```bash
  gcc cliente.c item.c -Wall -std=c99 -o cli
  ```
## Detalhes escopo do TAD(no arquivo.h)
```c
#ifndef ITEM_H 
/*(se nao foi definido, defina) pois o ITEM_H estara em mais arquivos, entao quando o compilador chegar nesse arquivo, ele ja pode ter sido incluido*/
    #define ITEM_H
    /*("_H" é uma conveção, assim como o nome do TAD em maiusculo)*/

    #include<stdbool.h>

    typedef struct item_ ITEM;

    ITEM *item_criar (int chave, void *comp);
/*(ITEM é formado por uma chave é o identificador do ITEM,
 e o seu dados que no codigo fonte do ITEM é um ponteiro void que é definido no codigo do cliente)*/
    bool item_apagar (ITEM **item);
    bool item_get_chave (ITEM *item);
    bool item_set_chave (ITEM *item, int chave);
    bool *item_get_dados (ITEM *item);
    /*Observação: convenção das funções do TAD. Primeiro é escrito o nome do TAD e após isso o que a função faz.*/
#endif

```
