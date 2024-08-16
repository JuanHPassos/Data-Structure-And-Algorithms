# Exercício de Programação: Verificação de Ponto em Circunferência

## Descrição do Exercício

O exercício consiste em utilizar o programa fornecido (`main.c`) e os TADs `Ponto` e `Círculo` desenvolvidos no exercício 1 para determinar se, dado um ponto, ele está **dentro**, **fora** ou **no raio** de uma circunferência.

### Função `distancia`

Deve ser desenvolvida uma função `float distancia(PONTO *pa, PONTO *pb);` que, dado dois pontos, retorna a distância entre eles. Essa distância será usada na `main` para decidir a posição relativa do ponto em relação à circunferência.

A função `distancia()` pode ser implementada em qualquer um dos TADs, mas é necessário justificar a escolha.

### Justificativa para a Implementação da Função `distancia()`

A função `distancia()` faz mais sentido ser implementada no TAD `Ponto`, uma vez que o cálculo da distância é uma operação diretamente relacionada à manipulação de pontos. Implementá-la no TAD `Ponto` mantém o princípio de coesão, agrupando as operações que fazem sentido para esse tipo de dado.

### Entrada e Saída

- **Entrada:**
  - Primeira linha: `x y raio` da circunferência
  - Segunda linha: `n` quantidade de casos de teste
  - `n` linhas seguintes: `x y` do ponto

- **Restrições:**
  - `x`, `y`: números de ponto flutuante
  - `raio`: número de ponto flutuante não negativo
  - `n`: valor inteiro não negativo

| **Exemplo de Entrada** | **Exemplo de Saída** |
|------------------------|----------------------|
| 0 0 1                  | fora                 |
| 3                      | no raio              |
| 0 -3                   | dentro               |
| 1 0                    |                      |
| 0.1 0                  |                      |


### Observações

- O exercício deve ser desenvolvido individualmente por cada aluno, que será responsável por decidir as melhores opções de implementação.
- Somente as bibliotecas `stdio.h`, `stdlib.h`, `stdbool.h` e `math.h` podem ser utilizadas.

### Dica

Caso apareça um erro parecido com "undefined reference to `pow`", acrescente no `Makefile` na tag `all`:

```makefile
all: -lm

