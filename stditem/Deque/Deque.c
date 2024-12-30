#include "Deque.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct no_ NO;

struct no_
{
    NO* proximo;
    NO* anterior;
    ITEM *item;
};

struct deque_
{
    // Permite inserção no fim e início.
    NO *inicio;
    NO *fim;
    int tamanho;
};

// Cria um deque, retorna nulo caso erro na alocação.
DEQUE* deque_criar()
{
    DEQUE *deque = (DEQUE*) malloc(sizeof(DEQUE));
    // Se a memória foi alocada, inicializa-se os campos.
    if(deque != NULL)
    {
        deque->tamanho = 0;
        deque->inicio = NULL;
        deque->fim = NULL;
    }
    return deque;
}

// Apaga deque, itens e dados. 
void deque_apagar(DEQUE** deque)
{
    if(*deque != NULL)
    {
        // Esvaziar deque apagando os itens e dados.
        while((*deque)->inicio != NULL)
        {
            // Receber item do início e apagá-lo.
            ITEM *item = deque_remover_inicio(*deque);
            void *dado = item_get_dados(item);
            if(dado != NULL)
            {
                free(dado);
                dado = NULL;
            }

            item_apagar(&item);
            
        }
        free(*deque); 
        *deque = NULL;
    }
}

// Inseri no inicio do deque, retorna falso caso deque cheia ou nula.
bool deque_inserir_inicio(DEQUE* deque, ITEM* item)
{
    if(deque != NULL)
    {
        NO* novo_inicio = (NO*) malloc(sizeof(NO));
        
        if(novo_inicio != NULL)
        {
            novo_inicio->proximo = deque->inicio;

            if(deque->inicio == NULL)
            {
                deque->inicio = novo_inicio; //Deque vazia, define-se inicio.
                deque->fim = novo_inicio; // Se deque vazia(fim == inicio).
            }
            else 
                deque->inicio->anterior = novo_inicio; // Mantém ligação do deque.
            
            // Define novo início.
            deque->inicio = novo_inicio;
            
            // Não há nó anteior ao início.
            novo_inicio->anterior = NULL;
            
            deque->tamanho++;

            // Guarda item passado como parâmetro.
            deque->inicio->item = item;
        
            return true;
        }
        // Se novo_inicio for nulo, deque está cheia.
    }

    // Não há como inserir se deque nula.
    return false;
}

bool deque_inserir_fim(DEQUE* deque, ITEM* item)
{
    if(deque != NULL)
    {
        NO* novo_fim = (NO*) malloc(sizeof(NO));

        if(novo_fim != NULL)
        {
            // Após inserir no fim, fim é antecesor desse novo elemento.
            novo_fim->anterior = deque->fim;

            // Se deque for vazio.
            if(deque->inicio == NULL)
            {
                deque->fim = novo_fim; // Define-se fim.
                deque->inicio = novo_fim; // Inicio é igual ao fim.
            }
            else 
                deque->fim->proximo = novo_fim; // Mantém ligação do deque.

            // Define-se novo fim.
            deque->fim = novo_fim;

            // Não há sucessor ao fim.
            novo_fim->proximo = NULL;

            deque->tamanho++; 
            // Guardar item passado como parâmetro.
            deque->fim->item = item;

            return true;
        }
        // Se novo_fim for nulo, deque está cheia.
    }
    // Não há como inserir se deque nula.

    return false;
}

// Função que retorna item removido do início.
ITEM* deque_remover_inicio(DEQUE* deque)
{
    if(!deque_vazia(deque))
    {
        // Guardar nó a ser removido.
        NO *inicio = deque->inicio;
        // Guardar item a ser retornado.
        ITEM *item = inicio->item;

        // Atualiza-se o início da fila.
        deque->inicio = deque->inicio->proximo;
        
        // Caso ainda existe início(deque não vazio).
        // Garante que não há antecessor ao início.
        if(deque->inicio != NULL)
            deque->inicio->anterior = NULL;
        else
            deque->fim = NULL; 

        // Desaloco nó do antigo início
        inicio->proximo = NULL;
        free(inicio); 
        inicio = NULL;

        deque->tamanho--;
        
        return item;
    }
    // Se deque vazia, não há remoção, retorna-se nulo.
    return (NULL);
}

// Função que retorna item removido do fim.
ITEM* deque_remover_fim(DEQUE* deque)
{
    if(!deque_vazia(deque))
    {
        // Guardar nó a ser removido.
        NO *fim = deque->fim;
        // Guardar item a ser retornado.
        ITEM *item = fim->item;

        // Voltar fim para o penultimo da deque.
        deque->fim = deque->fim->anterior;
        
        // Apagar nó fim.
        fim->anterior = NULL;
        free(fim); 
        fim = NULL;
        
        // Se deque não for vazia, não há sucessor ao fim
        if(deque->fim != NULL)
            deque->fim->proximo = NULL;
        else
            deque->inicio = NULL; // Fila vazia, ajustar início.
        
        deque->tamanho--;
            
        return item;
    }
    return NULL;
}

// Retorna primeiro elemento do deque(ou nulo caso não exista)
ITEM* deque_primeiro(DEQUE* deque)
{
    if(deque != NULL) 
        return deque->inicio->item;
    
    return NULL;
}

// Retorna o último elemento do deque(ou nulo caso não exista)
ITEM* deque_ultimo(DEQUE* deque)
{
    if(deque != NULL) 
        return deque->fim->item;

    return NULL;
}

// Retorna -1 caso deque não exista
int deque_tamanho(DEQUE* deque)
{
    if(deque != NULL) 
        return deque->tamanho;

    return -1;
}

// Retorna verdadeiro se deque for nulo.
bool deque_vazia(DEQUE* deque){
    if(deque != NULL) 
        return (deque->inicio == NULL);
    
    return true;
}

// Retorna verdadeiro para deque nulo ou cheio.
bool deque_cheia(DEQUE* deque){
    if(deque != NULL)
    {
        NO *novo_no = (NO*) malloc(sizeof(NO));
        if(novo_no != NULL)
        {
            free(novo_no);
            novo_no = NULL;

            return (false);
        }
        // Se novo_no for nulo, memória está cheia.
    }
    // Retorna verdeiro se deque nulo,
    // pois impede ações com o deque.
    return(true);
}

// Imprimi deque separados por espaço.
void deque_imprimir(DEQUE *deque)
{
    if(!deque_vazia(deque))
    {
        // Variável para percorrer deque.
        NO *index = deque->inicio;
        while(index != NULL)
        {
            printf("%d ", item_get_chave(index->item));
            index = index->proximo;
        }
        printf("\n");
    }
}

