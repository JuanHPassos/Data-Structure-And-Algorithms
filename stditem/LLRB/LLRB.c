#include "LLRB.h"

#include <stdlib.h>
#include <stdio.h>
#include "item.h"


#define VERMELHO 1
#define PRETO 0

typedef struct no_ NO;
struct no_ 
{
    ITEM *item;
    // Filhos esquerdo (esq) e direito (dir).
    NO *esq;
    NO *dir; 
    // Cor da aresta incidente.
    int cor;
};

struct llrb_ 
{
    NO *raiz;
    int tamanho;
};

// Modularização:
// Similares para as ABB's
void llrb_apagar_no (NO **raiz);
NO *llrb_inserir_no (NO *raiz, ITEM *item, bool *inserido);
NO *llrb_remover_no(NO *raiz, int chave, ITEM **item);
ITEM *llrb_buscar_no (NO *raiz, int chave); 
// Funções de balanceamento
NO *rot_dir(NO *raiz);
NO *rot_esq(NO *raiz);
void inverte (NO *raiz);
NO *MoveRedLeft (NO *raiz);
NO *MoveRedRight (NO *raiz);
// Auxiliares para implementação
NO *pegarSuccessor (NO *raiz);
int vermelho (NO *raiz);

// Função auxiliar utilizada no balanceamento da árvore,
// inverte as cores das restas incidadentes do nó alvo e dos seus filhos.
void inverte (NO *raiz) 
{
    // Verifica-se a existencia do nó, se existe inverte a cor de sua aresta incidente.
    if(raiz != NULL)
        raiz->cor = !raiz->cor;
    if(raiz->esq != NULL)
        raiz->esq->cor = !raiz->esq->cor;
    if(raiz->dir != NULL)
        raiz->dir->cor = !raiz->dir->cor;
}

// Função auxiliar de rotação direita para o balanceamento.
NO *rot_dir (NO *raiz) 
{
    // "no" aponta para o filho esquerdo de "raiz".
    NO *no = raiz->esq;
    // Filho direito de "no" vira filho esquerdo de "raiz".
    raiz->esq = no->dir;
    // "raiz" vira filho direito de "no".
    no->dir = raiz;
    
    // Atualiza as cores das arestas incidentes em "no" e "raiz".
    no->cor = raiz->cor;
    raiz->cor = VERMELHO;

    // Retorna "no" como nova raiz.
    return no;
}

// Função auxiliar de rotação esquerda para o balanceamento
NO *rot_esq (NO *raiz) 
{
    // "no" aponta para o filho direito de "raiz".
    NO *no = raiz->dir;
    // Filho esquerdo de "no" vira filho direito de "raiz".
    raiz->dir = no->esq;
    // "raiz" vira filho esquerdo de "no".
    no->esq = raiz;

    // Atualiza as cores das arestas incidentes em "no" e "raiz".
    no->cor = raiz->cor;
    raiz->cor = VERMELHO;

    // Retorna "no" como nova raiz.
    return no;
}

// Verifica a cor da aresta incidente
int vermelho (NO *raiz) 
{   
    if (raiz != NULL) 
        return (raiz->cor == VERMELHO);

    // Se nulo, aresta preta por definição.
    return PRETO;
}


// Busca nó de menor valor na sub-árvore.
NO* pegarSuccessor(NO *raiz) 
{
    // Avança para sub-arvore com itemes maiores que a raiz.
    NO *sucessor = raiz->dir; 
    // Busca-se item sucessor da raiz.
    if(sucessor != NULL)
        // Sucessor é o nó na sub-árvore mais a esquerda possível.
        while(sucessor->esq != NULL)
            sucessor = sucessor->esq;

    return sucessor;
}

// Funções principais gerais

// Cria uma estrutura de Árvore Binária Rubro-Negra pendente para a esquerda (LLRBT);
LLRB *llrb_criar () 
{
    // Aloca dinamicamente uma árvore nova.
    LLRB *llrb = (LLRB*)malloc(sizeof(LLRB));
    // Se a alocação foi bem sucedida, inicializam-se os campos.
    if (llrb != NULL) 
    {
        llrb->tamanho = 0;
        llrb->raiz = NULL;
    }
    // Retorna nulo caso alocação mal sucedida.
    return llrb;
}

// Apagar a árvore em pós-ordem.
void llrb_apagar_no (NO **raiz) 
{
    if(*raiz != NULL) {
        // Percorre em pós-ordem.
        llrb_apagar_no(&(*raiz)->dir);
        llrb_apagar_no(&(*raiz)->esq);

        // Caso item exista.
        if((*raiz)->item != NULL)
        {    
            // Apagar item e dados.
            void *dado = item_get_dados((*raiz)->item);
            if(dado != NULL)
            {
                free(dado);
                dado = NULL;
            }
            item_apagar(&((*raiz)->item));
        }
        // Apagar nó.
        free(*raiz); 
        *raiz = NULL;
    }
}

// Apagar a árvore.
void llrb_apagar (LLRB **llrb) 
{
    if (*llrb != NULL)
    {
        // Apaga todos os nós e os aponta para nulo.
        llrb_apagar_no(&(*llrb)->raiz);
        // Apagar estrutura de controle.
        free(*llrb); 
        *llrb = NULL;
    }
}

// Funçõs que inserem um nó na árvore
NO *llrb_inserir_no (NO *raiz, ITEM *item, bool *inserido) 
{
    // Se o nó atual é nulo, logo estamos inserindo uma folha no seu respectivo lugar
    if (raiz == NULL) 
    {    
        NO *folha = (NO*) malloc(sizeof(NO));
        
        if(folha != NULL)
        {
            folha->esq = NULL;
            folha->dir = NULL;
            folha->cor = VERMELHO;
            folha->item = item;
            // Garante o incremento correto do tamanho da árvore.
            *inserido = true; 
        }   
        
        return folha;
    }

    // Se o elemento é menor que o atual insere-se na sub-árvore à esquerda
    if (item_get_chave(item) < item_get_chave(raiz->item))     
        raiz->esq = llrb_inserir_no(raiz->esq, item, inserido); 
    // Se o elemento é maior que o atual insere-se na sub-árvore à direita
    else if (item_get_chave(item) > item_get_chave(raiz->item))
        raiz->dir = llrb_inserir_no(raiz->dir, item, inserido); 

    // Operações necessárias para o manter o balanceamento

    // Se o filho direito tem aresta incidente vermelha e a esquerda preto é necessário um rotação à esquerda, pois a aresta vermelha não pode estar à direita.
    if (vermelho(raiz->dir) && !vermelho(raiz->esq))  
        raiz = rot_esq(raiz);
    // Se há duas arestas esquerdas vermelhas seguidas faz-se uma rotação direita
    // Se esquerda for preta, sai e não executa esquerda esquerda(caso seja nula).
    if (vermelho(raiz->esq) && vermelho(raiz->esq->esq)) 
        raiz = rot_dir(raiz);
    // Se o nó possui dois filhos com arestas vermelhas inverte-se as cores das arestas
    if (vermelho(raiz->esq) && vermelho(raiz->dir)) 
        inverte(raiz);

    // Retorna a raiz após a inserção e os devidos balanceamentos.
    return raiz;
}

// Retorna falso caso arvore nula ou elemento ja presente.
bool llrb_inserir(LLRB *llrb, ITEM *item) 
{
    bool inserido = false;
    if (llrb != NULL) 
    {
        llrb->raiz = llrb_inserir_no(llrb->raiz, item, &inserido);
        llrb->raiz->cor = PRETO; // Atualiza a cor da nova raiz.
        
        if (inserido == true)
            llrb->tamanho++;
    }
    // Retorna nulo caso árvore nula, cheia ou elemento já presente.
    return inserido;
}

// Retorna item buscado, nulo caso não esteja na árvore.
ITEM *llrb_buscar_no (NO *raiz, int chave) 
{
    // Percorreu árvore e não encontrou elemento buscado.
    if (raiz == NULL) 
        return NULL;
    
    // Elemento existe na árvore.
    if(chave == item_get_chave(raiz->item))
        return raiz->item;

    // Se a chave do nó atual for menor, deve-se pegar o caminho da esquerda.
    if(chave < item_get_chave(raiz->item))
        return llrb_buscar_no(raiz->esq, chave); // Propaga resultado 
    else
        // Pegar caminho da direita caso seja maior.
        return llrb_buscar_no(raiz->dir, chave); // Propaga resultado
}

// Retorna nulo caso árvore não exista ou item não esteja na arvore.
ITEM *llrb_buscar (LLRB *llrb, int chave) 
{
    // Verifica se a árvore existe.
    if (llrb != NULL) 
        // Retorna item buscado(nulo caso não esteja na árvore).
        return llrb_buscar_no(llrb->raiz, chave);

    // Retorna nulo se a árvore não existe.
    return NULL;
}

// Imprimi: (chave[cor](sub-arv-esq)(sub-arv-dir))
void llrb_imprimir_no (NO *raiz) 
{
    printf("(");
    if(raiz != NULL) 
    {
        printf("%d[%d] ", item_get_chave(raiz->item), raiz->cor);
        llrb_imprimir_no(raiz->esq);
        llrb_imprimir_no(raiz->dir);
    }
    printf(")");
}

// Imprime elementos em ordem separados por espaço.
void llrb_imprimir (LLRB *llrb) 
{
    if (llrb != NULL) 
        llrb_imprimir_no(llrb->raiz);       
}

// Remoção em pré-ordem.
NO *llrb_remover_no(NO *raiz, int chave, ITEM **item)
{
    // Verifica raiz.
    if(raiz == NULL)
        return NULL;     

    // Se valor menor, percorre caminho esquerdo.
    if(chave < item_get_chave(raiz->item))
    {
        raiz = MoveRedLeft(raiz);
        raiz->esq = llrb_remover_no(raiz->esq, chave, item);
    }
    // Se valor maior, percorre caminho direito.
    else if(chave > item_get_chave(raiz->item))
    {
        raiz = MoveRedRight(raiz);
        raiz->dir = llrb_remover_no(raiz->dir, chave, item);
    }
    // Se for igual, remove-se o nó.
    else
    {  
        // Ao encontrar elemento buscado, guarda-se seu item.
        if(*item == NULL)
            *item = raiz->item;

        // Filho direito entra no lugar do pai se esquerdo for nulo.
        if(raiz->esq == NULL)
        {
            // Guarda filho direito para poder apagar a raiz.
            NO *nova_raiz = raiz->dir;
            // Se direito for nulo
            if(nova_raiz != NULL)
                // Como nó filho ocupa lugar do pai, recebe-se sua cor.
                nova_raiz->cor = raiz->cor;
            
            free(raiz);
            // Substitui filho direito pelo pai.
            raiz = nova_raiz;
        }
        // Filho esquerdo entra no lugar do pai se direito for nulo.
        else if(raiz->dir == NULL)
        {
            // Guarda filho direito para poder apagar a raiz.
            NO *nova_raiz = raiz->esq;
            // Como nó filho ocupa lugar do pai, recebe-se sua cor.
            nova_raiz->cor = raiz->cor;
            free(raiz);
            // Substitui filho direito pelo pai.
            raiz = nova_raiz;
        }
        // Caso existir os dois filhos, o sucessor arrume lugar do pai.
        // Que corresponde ao menor filho da sub-árvore da direita.
        else
        {
            // Guardar raiz original
            NO *aux = raiz;
            // Propagar aresta vermelha para direita.
            raiz = MoveRedRight(raiz);
            // Nesse processo a raiz pode ter sido alterada(não é a raiz buscada).
            // Ignoramos ela, e voltamos para a raiz original que está na direita.
            if(item_get_chave(raiz->item) == chave)
            {
                // Caso seja o nó buscado, trocamos pela folha que é sucessora a chave.
                aux = pegarSuccessor(raiz);
                // Copiamos o nó pela folha, e iremos apagar a folha.
                raiz->item = aux->item;
            } 
            // Percorrer caminho da direita
            raiz->dir = llrb_remover_no(raiz->dir, item_get_chave(aux->item), item);
        }
    }

    // Caso nó removido seja folha, raiz valerá NULL.
    if(raiz != NULL)
    {
        // Funções de balanceamento iguais as da inserção
        if (vermelho(raiz->dir) && !vermelho(raiz->esq))
            raiz = rot_esq(raiz);
    
        if (vermelho(raiz->esq) && vermelho(raiz->esq->esq))
            raiz = rot_dir(raiz);
        
        if (vermelho(raiz->esq) && vermelho(raiz->dir)) 
            inverte(raiz);
        
    }

    return raiz;
} 

// Retorna item do nó removido(nulo caso falhe).
ITEM *llrb_remover(LLRB *llrb, int chave) 
{
    ITEM *item = NULL; // Variavel armazena retorno.
    // Verifica a existência da árvore.
    if(llrb != NULL) 
    {
        llrb->raiz = llrb_remover_no(llrb->raiz, chave, &item);
        // Atualizar tamanho caso item carregue um item.
        if(item != NULL)
            llrb->tamanho--;
    }
    return item;
}

// Funções auxiliares que realizam a propagação de arestas vermelhas. 
// Propaga para a esquerda.
NO *MoveRedLeft (NO *raiz) 
{
    if (raiz != NULL) 
    {
        // Verifica se o filho esquerdo de raiz e seu filho esquerdo desse nó existem e têm arestas pretas, se sim invertem as cores em raiz.
        if (raiz->esq == NULL || (!vermelho(raiz->esq) && !vermelho(raiz->esq->esq)))
        {            
            inverte(raiz);

            // Verifica se o filho esquerdo do filho direito de raiz tem aresta vermelha, mas antes verifica a existencia dos nós
            // se sim, realiza-se uma rotação dupla direita-esquerda e inverte as cores em raiz.
            if (raiz->dir != NULL && vermelho(raiz->dir->esq)) 
            {
                raiz->dir = rot_dir(raiz->dir);
                raiz = rot_esq(raiz);
                inverte(raiz);
            }
        }
    }

    // Retorna a nova raiz.
    return raiz;
}

// Propaga para a direita.
NO *MoveRedRight(NO* raiz) 
{
    if (raiz != NULL)
    {
        // Verifica se raiz->l existe e sua cor, se vermelho realiza uma rotação direita.
        if (vermelho(raiz->esq)) 
            raiz = rot_dir(raiz);

        // Verifica se raiz->r e raiz->r->l existem e suas cores, 
        // se ambas pretas, invetem as cores em "raiz".
        if (raiz->dir == NULL || (!vermelho(raiz->dir) && !vermelho(raiz->dir->esq))) 
        {
            inverte(raiz);
            // Verifica se raiz->l e raiz->l->l existem e a cor do filho esquedo do filho esquerdo de raiz,
            //se vermelho realiza uma rotação direita em raiz e inverte as cores.
            if (raiz->esq != NULL && vermelho(raiz->esq->esq))
            {
                raiz = rot_dir(raiz);
                inverte(raiz);
            }
        }
    }

    // Retorna a nova raiz.
    return raiz;
}



