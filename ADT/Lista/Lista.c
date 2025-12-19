#include "Lista.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct no_ NO;

struct no_
{
    ITEM *item;
    // Lista duplamente encadeada.
    NO *proximo;
    NO *anterior;
};


struct lista_{
    // Lista circular duplamente encadeada.
    NO *cabeca;
    int tamanho; // Tamanho lista.
    bool ordenada; // 1 simboliza ordenada.
}; 

void lista_inserir_ordenada(LISTA *lista, NO *novo_no);

LISTA *lista_criar(bool ordenada)
{
    LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
    NO *cabeca = (NO*) malloc(sizeof(NO));
    
    if(lista != NULL && cabeca != NULL)
    {
        // Cabeca aponta para o inicio da lista.
        // Se o inicio for igual ao cabeca, lista vazia.
        cabeca->proximo = cabeca;
        lista->cabeca = cabeca;
        lista->cabeca->item = NULL;
        // Fim da lista é o anterior ao cabeça.
        lista->cabeca->anterior = cabeca;
        lista->tamanho = 0;
        lista->ordenada = ordenada;
    }
    
    return lista;
}

// Busca melhor inserção dada condição da lista.
bool lista_inserir(LISTA *lista, ITEM *item)
{
    // Verificar existência do item e da lista.
    if(lista != NULL && item != NULL)
    {
        // Verificar se a lista está cheia(acabou memória)
        NO *novo_no = (NO*) malloc(sizeof(NO));
        if(novo_no != NULL)
        {        
            // Guardar informação(item) no nó.
            novo_no->item = item;
            
            if(lista->ordenada == 1)
                lista_inserir_ordenada(lista, novo_no);
            else
            {
                novo_no->anterior = lista->cabeca->anterior;
                novo_no->proximo = lista->cabeca;
                novo_no->anterior->proximo = novo_no;
                novo_no->proximo->anterior = novo_no;
            }
            
            lista->tamanho++;
            
            return true;
        }
        // Novo-no nula significa que memória está cheia.
    }
    // Não há como inserir em uma lista nula
    // E nem inserir um item nulo.
    return false;
}


// Inseri um elemento em uma lista ordenada(ord. não estável).
void lista_inserir_ordenada(LISTA *lista, NO *novo_no)
{
    // Chave a ser procurada.
    int chave = item_get_chave(novo_no->item);
    // Guardar item procurado no nó cabeça.
    lista->cabeca->item = novo_no->item;
    // Variável para encontrar posição de inserção.
    NO *busca = lista->cabeca->proximo;
    
    // Procurar nó maior ou igual a chave ou o nó cabeça.
    while(chave > item_get_chave(busca->item))
        busca = busca->proximo;

    // Novo nó vira antecessor ao nó busca.
    novo_no->anterior = busca->anterior;
    novo_no->proximo = busca;
    novo_no->anterior->proximo = novo_no;
    novo_no->proximo->anterior = novo_no;

    // Nó cabeça volta a ter item nulo.
    lista->cabeca->item = NULL;

}

void lista_apagar(LISTA **lista)
{
    if(*lista != NULL)
    {
        // Enquanto o único elementoda lista não for o nó cabeça.
        while((*lista)->cabeca != (*lista)->cabeca->proximo)
        {    
            // Atualiza lista sem o no do inicio(que sera apagado).
            NO *apaga_no = (*lista)->cabeca->proximo;
            (*lista)->cabeca->proximo = apaga_no->proximo;

            // Apaga nó, itens e os dados.
            void *dado = item_get_dados(apaga_no->item);
            if(dado != NULL)
            {
                free(dado);
                dado = NULL;
            }
            item_apagar(&(apaga_no->item));
            apaga_no->proximo = NULL;
            apaga_no->anterior = NULL;
            free(apaga_no);
            apaga_no = NULL;

            // Atualiza tamanho da lista.
            (*lista)->tamanho--;
        }

        // Apagar nó cabeça e estrutura de controle da lista.
        (*lista)->cabeca->anterior = NULL;
        (*lista)->cabeca->proximo = NULL;
        free((*lista)->cabeca);
        (*lista)->cabeca = NULL;
        free(*lista);
        *lista = NULL;
    }
}

// Retorna nulo caso item não seja encontrado.
ITEM *lista_remover(LISTA *lista, int chave)
{
    ITEM *retorno = NULL;
    if(!lista_vazia(lista))
    {
        // Nó cabeca garante um elemento igual na lista.
        lista->cabeca->item = item_criar(chave, NULL);
        // Variável para percorrer a lista, procurando chave.
        NO *buscar_no = lista->cabeca->proximo;
        // Busca difere entre ordenada e não ordenada.
        if(lista->ordenada == 1)
        {
            // Procura até achar um elemento maior ou igual.
            while(chave > item_get_chave(buscar_no->item))
                buscar_no = buscar_no->proximo;
        }
        else
        {
            // Procura até achar umn elemento igual.
            while(chave != item_get_chave(buscar_no->item))
                buscar_no = buscar_no->proximo;
        }
        
        // Nó a ser removido não pode ser o cabeca, nem chave diferente.
        if(buscar_no != lista->cabeca && 
            item_get_chave(buscar_no->item) == chave)
        {
            // Garantir conexão da lista.
            NO *anterior = buscar_no->anterior;
            NO *proximo = buscar_no->proximo;

            anterior->proximo = proximo;
            proximo->anterior = anterior;

            // Desvincular nó a ser removido da lista.
            buscar_no->proximo = NULL;
            buscar_no->anterior = NULL;

            // Guardar item a ser retornado.
            retorno = buscar_no->item;
            
            // Apagar nó.
            free(buscar_no);
            buscar_no = NULL;

            // Atualizar tamanho da lista.
            lista->tamanho--;    
        }

        // Tornar item da cabeca nula.
        item_apagar(&(lista->cabeca->item));
        lista->cabeca->item = NULL;
    }
    // Retorna nulo caso lista vazia ou item não encontrado.
    return retorno;
}

// Retorna item buscado(ou nulo caso não seja encontrado).
ITEM *lista_busca(LISTA *lista, int chave)
{
    if(!lista_vazia(lista))
    {
        lista->cabeca->item = item_criar(chave, NULL);

        // buscar_no começa do início da lista.
        NO *buscar_no = lista->cabeca->proximo;
        if(lista->ordenada == 1)
            // Procura até achar um elemento maior ou igual.
            while(chave > item_get_chave(buscar_no->item))
                buscar_no = buscar_no->proximo;
        else
            // Procura até achar um elemento igual.
            while(chave != item_get_chave(buscar_no->item))
                buscar_no = buscar_no->proximo;
        
        // Tornar item da cabeca nula.
        item_apagar(&(lista->cabeca->item));
        lista->cabeca->item = NULL;
        
        if(item_get_chave(buscar_no->item) == chave)    
            return buscar_no->item; // Retornar item buscado.
    }
    // Retorna nulo se lista não existi ou está vazia.
    return NULL;
}

// Retorna -1 caso lista não exista.
int lista_tamanho(LISTA *lista)
{
    if(lista != NULL) 
        return lista->tamanho;
    
    return -1; // Simboliza erro.
}

// Retorna verdadeiro para lista nula.
bool lista_vazia(LISTA *lista)
{
    if(lista != NULL)
        return (lista->cabeca->proximo == NULL);
    
    // Evita que o usuário manipule uma lista que não existe.
    return true; 
}

// Retorna verdadeiro caso lista não existe.
bool lista_cheia(LISTA *lista)
{
    if(lista != NULL)
    {
        NO *verifica_memoria = (NO*) malloc(sizeof(NO));
        if(verifica_memoria != NULL) 
        {
            free(verifica_memoria); 
            verifica_memoria = NULL; // Boa prática
            // Se alocou, ainda há memória disponível.
            return false;
        }
        
    }
    // Não há o que fazer um uma lista cheia, retorna-se true.
    // Evita que o usuário manipule uma lista que não existe.
    return true; 
}

// Imprimi lista separada por espaços, e \n no final.
void lista_imprimir(LISTA *lista)
{
    if(lista != NULL)
    {
        NO *imprimir_no = lista->cabeca->proximo;

        while(imprimir_no->item != NULL)
        {
            printf("%d ", item_get_chave(imprimir_no->item));
            imprimir_no = imprimir_no->proximo;
        }
        printf("\n");
    }
}