#include "Pilha.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct no_ NO;

struct no_ 
{
    ITEM *item;
    NO* anterior;
};

struct pilha
{
    NO* topo;
    int tamanho;
};

// Criar pilha encadeada que guarda um item(chave + ponteiro).
PILHA* pilha_criar(void)
{
    PILHA *pilha = (PILHA*) malloc(sizeof(PILHA));
    // Caso tenha memória, inicializa-se pilha.
    if(pilha != NULL)
    {
        pilha->tamanho = 0; // Pilha inicia vazia.
        pilha->topo = NULL; //Boa prática.
    }
    return pilha;
}

// Apaga os dados, itens, e pilha.
void pilha_apagar(PILHA** pilha)
{
    NO *aux = NULL;
    if(*pilha != NULL)
    {
        // Enquanto a pilha não for vazia.
        while((*pilha)->topo != NULL)
        {
            // Variável que guarda o topo a ser removido.
            aux = (*pilha)->topo;

            //Novo topo é o nó anterior ao atual.
            (*pilha)->topo = (*pilha)->topo->anterior;

            // Apagar dados do item.
            void *dado = item_get_dados(aux->item);
            if(dado != NULL)
            {
                free(dado);
                dado = NULL;
            }

            //Apaga-se o conteúdo do nó(item) do antigo topo.
            item_apagar(&(aux->item));

            //Corta-se a ligação do topo antigo com o novo.
            aux->anterior = NULL;
            
            // Desalocação de memória.
            free(aux); aux = NULL;
            (*pilha)->tamanho--;
        }
    }
    
    // Desalocação da estrutura de controle da pilha.
    free(*pilha);
    *pilha = NULL;
}

// Retorna verdadeiro para pilha vazia ou nula.
bool pilha_vazia(PILHA* pilha)
{
    if(pilha != NULL)
        return (pilha->topo == NULL); // Se topo nulo, pilha vazia.

    // Se não houver pilha, ela está vazia.
    return true;
}

// Retorna verdadeiro para pilha cheia ou nula.
bool pilha_cheia(PILHA* pilha)
{
    if(pilha != NULL)
    {
        // Pilha está cheia somente se a memória encheu.
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
    // Se não existir pilha, retorna-se verdadeiro.
    // Tal opção evita erros, pois pilha cheia evita ações com a pilha.  
    return true;
}

// Retorna -1 caso pilha não exista.
int pilha_tamanho(PILHA* pilha)
{
    return (pilha != NULL ? pilha->tamanho : -1);
}

// Verifica o topo da pilha retornando o item.
// Retorna nulo se a pilha não existir.
ITEM* pilha_topo(PILHA* pilha)
{
    // Se a pilha existir e não for vazia.
    if(pilha != NULL && pilha->topo != NULL)
    {
        // Retorna o item do topo.
        return (pilha->topo->item);
    }
    return NULL;
}

// Retorna falso caso memória cheia ou pilha/item nulos.
bool pilha_empilhar(PILHA* pilha, ITEM* item)
{
    // Caso pilha e itens existam.
    if(pilha != NULL && item != NULL)
    {
        NO* novo_no = (NO*) malloc(sizeof(NO));
        // E se a memória não estiver cheia.
        // Empilha-se o novo nó.
        if(novo_no != NULL)
        {
            novo_no->item = item;
            // Novo no aponta para o topo atual.
            novo_no->anterior = pilha->topo;
            // Atualiza-se o topo da pilha.
            pilha->topo = novo_no;
            pilha->tamanho++; // Incremento tamanho.

            return true;
        }
        // Se novo_no for nulo, a memória está cheia.
    }
    // Não se empilha em uma pilha nulo, ou um item nulo.
    return false;
}
  
// Retorna item do topo da pilha(retorna nulo caso não exista pilha).
ITEM* pilha_desempilhar(PILHA* pilha)
{
    if(!pilha_vazia(pilha))
    {
        // Guarda item do topo para ser retornado.
        ITEM *item = pilha->topo->item;
        // Guarda nó a ser removido.
        NO *aux = pilha->topo;
        // Atualiza o topo.
        pilha->topo = pilha->topo->anterior;

        // Desalocação do nó atual.
        aux->anterior = NULL;
        free(aux); 
        aux = NULL;
        
        // Atualização do tamanho.
        pilha->tamanho--;

        return item;
    }
    // Retorna nulo caso não exista pilha.
    return NULL;
}

// As chave são impressas do topo à base.
void pilha_imprimir(PILHA* pilha)
{
    if(pilha != NULL)
    {
        // Variável auxiliar imprimir pilha.
        NO *elemento = pilha->topo;

        // Percorre pilha imprimindo valores.
        while(elemento != NULL)
        {
            printf("%d ", item_get_chave(elemento->item));
            elemento = elemento->anterior;
        }
        printf("\n");
    }
}

void pilha_inverter(PILHA **pilha) 
{
    // Verificar se a pilha existe e se possui elementos para ser invertida.
    if (*pilha == NULL || (*pilha)->tamanho <= 1)
        return;

    // Criação de pilha auxiliar para inversão
    PILHA *pilha_auxiliar = pilha_criar();

    // Transferir elementos da pilha original para a pilha auxiliar
    while ((*pilha)->topo != NULL) 
        pilha_empilhar(pilha_auxiliar, pilha_desempilhar(*pilha));

    // Desalocar pilha antiga.
    free(*pilha);
    
    // Substituir a pilha original pela pilha auxiliar invertida
    *pilha = pilha_auxiliar;
}

/*
// Inverte pilha de forma recursiva.
void pilha_inverter_no(NO *no)
{
    // Percorrer pilha até penultimo nó.
    if(no->anterior->anterior != NULL)
        inverte(no->anterior);    

    // Volta a recursão atualizando os ponteiros.
    no->anterior->anterior = no;
    no->anterior = NULL;
}

// Inverte pilha de forma recursiva.
void pilha_inverter(PILHA *pilha)
{
    if(!pilha_vazia(pilha))
    {
        // Se pilha possuir tamanho 1, sua inversa é ela mesma.
        if(pilha->tamanho > 1)
        {
            // Novo topo será o último nó da pilha.
            NO *novo_topo = pilha->topo;
            // Percorrer pilha e guardar esse ultimo nó.
            while(novo_topo->anterior != NULL) 
                novo_topo = novo_topo->anterior;
            // Inverter pilha.
            pilha_inverter_no(pilha->topo);
            // Dada a pilha invertida, apenas atualiza-se o topo.
            pilha->topo = novo_topo;
        }
    }
}
*/

