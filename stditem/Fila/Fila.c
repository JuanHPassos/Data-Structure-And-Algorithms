#include "Fila.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct _no NO;

struct _no
{
    NO* proximo;
    ITEM *item;
};

struct fila_
{
    // Ponteiro para frente e fim da fila.
    NO* frente; // Aponta para o nó mais antigo da estrutura.
    NO* fim; // Aponta para o ultimo nó inserido.
    int tamanho;
};

// Função cria fila, retorna nulo como erro ao alocar.
FILA* fila_criar(void)
{
    FILA *fila = (FILA*) malloc(sizeof(FILA));
    // Caso fila tenha sido alcoada, inicializa-se os campos.
    if(fila != NULL)
    {
        // Inicialmente, não há fim nem frente.
        fila->frente = NULL;
        fila->fim = fila->frente;
        fila->tamanho = 0;
    }
    return fila;
}
    
// Retorna verdadeiro caso memória cheia ou fila nula.
bool fila_cheia(FILA *fila)
{
    if(fila != NULL)
    {
        // Fila está cheia somente se a memória encheu.
        NO* verificar_memoria = (NO*) malloc(sizeof(NO));
        // Caso ocorra alocação dinâmica.
        if(verificar_memoria != NULL)
        {
            // A memória não está cheia.
            // Desalocar memória usada para verificar.
            free(verificar_memoria); 
            verificar_memoria = NULL;
            return false;
        }
        // Se memoria cheia, não houve alocação, retorna true no final.
    }
    // Se não existir fila, retorna-se verdadeiro.
    // Tal opção evita erros, pois fila cheia evita ações com a fila.  
    return true;
}

// Retorna verdadeiro para fila vazia ou nula.
bool fila_vazia(FILA *fila)
{
    // Fila está vazia se não há itens na frente.
    if(fila != NULL)
        return (fila->frente == NULL);

    // Dado que a fila não existi, ela está vazia.
    return true;
}

// Retorna falso caso item nulo, fila nula ou fila cheia.
bool fila_inserir(FILA *fila, ITEM *item)
{
    if(fila != NULL && item != NULL)
    {
        NO *novo_fim = (NO*) malloc(sizeof(NO));

        if(novo_fim != NULL)
        {    
            // Se fila vazia(define-se o inicio).
            if(fila->frente == NULL)
                fila->frente = novo_fim;  
            else 
                fila->fim->proximo = novo_fim; // Garante ligação da fila.
            
            // Inicializa nó
            novo_fim->item = item; 
            novo_fim->proximo = NULL;

            // Define novo fim da fila.
            fila->fim = novo_fim;

            fila->tamanho++;
            // Retorna nulo caso ocorra inserção
            return true;
        }
        // Se novo_fim for nulo, a memória está cheia.
    }
    // Caso de item ou fila nula.
    return false;
} 

// Remove frente da fila, retorna nulo caso contrário.
ITEM *fila_remover(FILA *fila)
{
    if(!fila_vazia(fila))
    {
        // Guardar frente a ser retirada.
        NO *frente = fila->frente;
        ITEM *item = frente->item;

        // Atualizar frente e tamanho da fila.
        fila->frente = fila->frente->proximo;
        fila->tamanho--;
        
        // Desalocação da antiga frente da fila.
        frente->proximo = NULL;
        free(frente); 
        frente = NULL;
        
        // Se fila ficou vazia, ajustar fim para nulo.
        if(fila->frente == NULL)
            fila->fim = NULL;
        
        // Retorna item da frente.
        return item;
    }
    // Retorna nulo em caso de fila vazia ou nula.
    return NULL;
}

// Retorna -1 caso fila não exista.
int fila_tamanho(FILA *fila)
{
    if(fila != NULL)
        return (fila->tamanho);

    // Simboliza fila nula.
    return (-1);
}
    
// Retorna item da frente da fila.(nulo caso não exista)
ITEM *fila_frente(FILA *fila)
{
    if(fila != NULL) 
        return (fila->frente->item);
    
    return NULL;
}

void fila_apagar(FILA **fila)
{
    // Se fila existir.
    if(*fila != NULL)
    {
        // Esvazia-se a fila apagando os seus dados e itens.
        while((*fila)->frente != NULL)
        {
            ITEM *frente = fila_remover(*fila);

            // Apagar dados do item.
            void *dado = item_get_dados(frente);
            if(dado != NULL)
            {
                free(dado);
                dado = NULL;
            }

            //Apaga-se o conteúdo do nó(item) do antiga frente.
            item_apagar(&(frente));
        }

        // Apagar estrutura de controle da fila.
        free(*fila); 
        *fila = NULL;
    }
}

// Inverte fila recursivamente
void fila_inverter_no(NO *no)
{
    // Encontra penúltimo da fila.
    if(no->proximo->proximo != NULL) 
        fila_inverter_no(no->proximo);
    // Inverte os ponteiros
    no->proximo->proximo = no;
    no->proximo = NULL;
}

// Retorna falso caso a fila não existir.
bool fila_inverter(FILA *fila)
{
    if(fila != NULL && fila->tamanho > 1)
    {
        // Função recursiva que inverterá os ponteiros.
        fila_inverter_no(fila->frente);
        // Antiga frente será novo fim e vice-versa.
        NO *aux = fila->frente;
        fila->frente = fila->fim;
        fila->fim = aux; 
        return true;
    }
    return false;
}

void fila_imprimir(FILA *fila)
{
    if(fila != NULL && fila->frente != NULL)
    {
        // Variável auxiliar imprimir fila.
        NO *elemento = fila->frente;

        // Percorre fila imprimindo valores.
        while(elemento != NULL)
        {
            printf("%d ", item_get_chave(elemento->item));
            elemento = elemento->proximo;
        }
        printf("\n");
    }
}

/*
Maneira eficiente de apagar a pilha, visando memoria.

void apagar_no(NO **no){
    if((*no)->proximo != NULL)
        apagar_no(&(*no)->proximo);
    
    free((*no)->item); (*no)->item = NULL; 
    free(*no); *no = NULL;  
    
    return;  
}

void fila_apagar(FILA **f){
    if(!fila_vazia(*f) && (*f) != NULL){
        apagar_no(&(*f)->inicio);
        
        free(*f); *f = NULL;
    }
    return;
}
*/

