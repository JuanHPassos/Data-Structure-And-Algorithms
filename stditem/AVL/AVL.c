#include "AVL.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct no_ NO;

struct no_
{
    ITEM *item;
    // Filhos direito(dir) e esquerdo(esq)
    NO *dir;
    NO *esq;
    // Distância do nó a folha mais longe.
    int altura;
};

struct avl_
{
    NO *raiz;
    int tamanho;
};

// Modularização
// Similiares ABB.
NO *avl_cria_no(ITEM *item);
void avl_apagar_no(NO **raiz);
NO *avl_inserir_no(NO *raiz, ITEM *item, bool *inserido);
NO *avl_remover_no(NO *raiz, int chave, ITEM **item);
ITEM *avl_buscar_no(NO *raiz, int chave);
// Balanceamento.
NO *rot_dir(NO *A);
NO *rot_esq(NO *A);
// Auxiliares implementação.
NO *pegar_sucessor(NO *raiz);
int avl_altura_no(NO* raiz);
void avl_imprimi_no(NO *raiz);

// Cria estrutura nó e armazena seu item.
NO *avl_cria_no(ITEM *item)
{
    // Alocação dinâmica do nó.
    NO *no = (NO*) malloc(sizeof(NO));
    // Caso haja memória, cria-se nó folha
    if(no != NULL)
    {
        // Altura = comprimento do nó a uma folha.
        no->altura = 0; 
        
        // Nó a ser inserido é nó folha(0 filhos).
        no->dir = NULL; 
        no->esq = NULL;
        
        // item do nó.
        no->item = item;
    }
    return no;
}

// Cria árvore AVL
AVL *avl_criar(void)
{
    // Armazenar espaço para estrutura de controle da AVL.
    AVL *avl = (AVL*) malloc(sizeof(AVL));
    // Caso haja memória, inicia-se seus campos.
    if(avl != NULL)
    {
        avl->raiz = NULL;
        avl->tamanho = 0;
    }
    return avl;
}

// Apagar árvore.
void avl_apagar(AVL **avl)
{
    if(*avl != NULL)
    {
        // Apagar todos os nós.
        avl_apagar_no(&((*avl)->raiz));
        free(*avl);
        *avl = NULL;
    }
}

// Apaga a árvore em pós-ordem.
void avl_apagar_no(NO **raiz)
{
    if(*raiz != NULL)
    {
        // Percorre em pós-ordem.
        avl_apagar_no(&((*raiz)->esq));
        avl_apagar_no(&((*raiz)->dir));
        
        // Apaga dado, item e raiz.
        int *dado = item_get_dados((*raiz)->item);
        if(dado != NULL)
        {
            free(dado);
            dado = NULL;
        }
        item_apagar(&((*raiz)->item));
        free(*raiz);
        *raiz = NULL;
    }
}

// Árvore está desbalanceada para esquerda.
NO *rot_dir(NO *A)
{
    NO *B = A->esq;
    // Filho direito de B vira filho esquerdo de A.
    A->esq = B->dir;
    // A vira filho direito de B.
    B->dir = A;

    // Árvore está balanceada, calcula altura atual.
    A->altura = max(avl_altura_no(A->esq), avl_altura_no(A->dir)) + 1;
    B->altura = max(avl_altura_no(B->esq), avl_altura_no(B->dir)) + 1;

    // Retorna B como nova raiz.
    return B;
}

// Árvore está desbalanceada para direita.
NO *rot_esq(NO *A)
{
    NO *B = A->dir;
    // Filho esquerdo de B vira filho direito de A.
    A->dir = B->esq;
    // A vira filho esquerdo de B
    B->esq = A;

    // Árvore está balanceada, calcula altura atual.
    A->altura = max(avl_altura_no(A->esq), avl_altura_no(A->dir)) + 1;
    B->altura = max(avl_altura_no(B->esq), avl_altura_no(B->dir)) + 1;

    // Retorna B como nova raiz.
    return B;
}

// Rotação dupla para esquerda-direita.
NO *rot_esq_dir(NO *A)
{
    // Ajusta sub-árvore com sinal negativo.
    A->esq = rot_esq(A->esq);
    // Ajusta árvore desbalanceada para direita.
    // Retorna nova raiz.
    return(rot_dir(A));
}

// Rotação dupla para direita-esquerda.
NO *rot_dir_esq(NO *A)
{
    // Ajusta sub-árvore com sinal negativo.
    A->dir = rot_dir(A->dir);

    // Ajusta árvore desbalanceada para a direita.
    // Retorna nova raiz.
    return(rot_esq(A));
}

// Retorna altura de um nó.
int avl_altura_no(NO* raiz)
{
    // Se não existe árvore, altura é -1(convenção).
    if(raiz == NULL)
        return -1;
    // Retorna altura caso exista.
    return raiz->altura;
}

// Chama função que insere recursivamente.
bool avl_inserir(AVL *avl, ITEM *item)
{
    // Variável de retorno.
    bool inserido =  false;
    if (avl != NULL)
    {
        avl->raiz = avl_inserir_no(avl->raiz, item, &inserido);
        // Caso nó tenha sido inserido(não tinha nó com mesmo item na árvore)
        if(inserido == true)
            avl->tamanho++;
    }
    
    return inserido;
}

// Percorre o caminho da item, inserindo recursivamente(pré-ordem).
NO *avl_inserir_no(NO *raiz, ITEM *item, bool *inserido)
{
    if(raiz == NULL)
    {
        raiz = avl_cria_no(item);
        // Caso haja memória e o nó seja criado
        if(raiz != NULL)
            *inserido = true; // Garante incremento de tamanho da árvore.
    }
    // Se item for menor, percorre caminho da esquerda do nó.
    else if (item_get_chave(item) < item_get_chave(raiz->item))
        raiz->esq = avl_inserir_no(raiz->esq, item, inserido);
    // Se item for maior, percorre caminho da direita do nó.
    else if (item_get_chave(item) > item_get_chave(raiz->item))
        raiz->dir = avl_inserir_no(raiz->dir, item, inserido);

    // Altura de um nó é a máximo entre seus filhos + 1.
    raiz->altura = max(avl_altura_no(raiz->esq), avl_altura_no(raiz->dir)) + 1;

    // Verifica se houve desbalanceamento( FB = -2 || FB = 2 )
    // FB = altura_esquerda - altura_direita
    int A_FB = avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir);
    // Desbalanceamento para direita.(rotação esquerda)
    if (A_FB == -2)
    {
        // Se B_FB for negativo, deve-se aplicar rotação esquerda.
        // Caso contrário, aplicar rotação dupla esquerda_direita.
        int B_FB = avl_altura_no(raiz->dir->esq) - avl_altura_no(raiz->dir->dir);
        if( B_FB < 0 )
            raiz = rot_esq(raiz);
        else 
            raiz = rot_dir_esq(raiz);
            
    } else if ( A_FB == 2 ){
        // Pode ser rotação direita ou esquerda_direita(A == 2).
        // Se B_FB for positivo, deve-se aplicar rotação direita.
        int B_FB = avl_altura_no(raiz->esq->esq) - avl_altura_no(raiz->esq->dir);
        if( B_FB >= 0 )
            raiz = rot_dir(raiz);
        else 
            raiz = rot_esq_dir(raiz);
    }

    return raiz;
}

// Remove nó, retornando item, caso nó não esteja na árvore, retorna nulo.
ITEM *avl_remover(AVL *avl, int chave)
{
    ITEM *item = NULL;
    // Se árvore existir.
    if(avl != NULL)
    {
        // Remover nó com item passado no parametro.
        avl->raiz = avl_remover_no(avl->raiz, chave, &item);
        // Caso item tenha sido removido(item existia na árvore)
        if(item != NULL)
            avl->tamanho--;
    }
    // Retorna nulo caso não tenha removido.
    return item;
}

// Remoção em pré-ordem.
NO *avl_remover_no(NO *raiz, int chave, ITEM **item)
{
    // Verifica raiz.
    if(raiz == NULL)
        return NULL;     

    // Se item menor, percorre caminho esquerdo.
    if(chave < item_get_chave(raiz->item))
        raiz->esq = avl_remover_no(raiz->esq, chave, item);
    // Se item maior, percorre caminho direito.
    else if(chave > item_get_chave(raiz->item))
        raiz->dir = avl_remover_no(raiz->dir, chave, item);
    // Se for igual, remove-se o nó.
    else
    {  
        // Caso o item já tenha sido guardado, não há necessidade de guardar outro.
        // If necessário devido ao caso em que queremos remover nó intermediário.
        if(*item == NULL)
        {
            // Guardar o valor do item de retorno, para poder apagar o nó.
            *item = raiz->item;
        }

        // Filho direito entra no lugar do pai se esquerdo for nulo.
        if(raiz->esq == NULL)
        {
            // Guarda filho direito para poder apagar a raiz.
            NO *temp = raiz->dir; 
            free(raiz);
            // Substitui filho direito pelo pai.
            raiz = temp;
        }
        // Filho esquerdo entra no lugar do pai se direito for nulo.
        else if(raiz->dir == NULL)
        {
            // Guarda filho direito para poder apagar a raiz.
            NO *temp = raiz->esq;
            free(raiz);
            // Substitui filho direito pelo pai.
            raiz = temp;
        }
        // Caso existir os dois filhos, o sucessor arrume lugar do pai.
        // Que corresponde ao menor filho da sub-árvore da direita.
        else
        {
            NO *sucessor = pegar_sucessor(raiz);
            // Troca raiz pela folha(antigo item foi guardado acima).                
            raiz->item = sucessor->item;
            // Remove a folha.
            raiz->dir = avl_remover_no(raiz->dir, item_get_chave(sucessor->item), item);
        }
    }

    // Caso nó removido seja folha, raiz valerá NULL.
    if(raiz != NULL)
    {
        // Altura de um nó é a máximo entre seus filhos + 1.
        raiz->altura = max(avl_altura_no(raiz->esq), avl_altura_no(raiz->dir)) + 1;

        // Verifica se houve desbalanceamento( FB = -2 || FB = 2 )
        // FB = altura_esquerda - altura_direita
        int A_FB = avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir);
        // Desbalanceamento para direita.(rotação esquerda)
        if (A_FB == -2)
        {
            // Se B_FB for negativo, deve-se aplicar rotação esquerda.
            // Caso contrário, aplicar rotação dupla esquerda_direita.
            int B_FB = avl_altura_no(raiz->dir->esq) - avl_altura_no(raiz->dir->dir);
            if( B_FB <= 0 )
                raiz = rot_esq(raiz);
            else 
                raiz = rot_dir_esq(raiz);
                
        } else if (A_FB == 2){
            // Pode ser rotação direita ou esquerda_direita(A == 2).
            // Se B_FB for positivo, deve-se aplicar rotação direita.
            int B_FB = avl_altura_no(raiz->esq->esq) - avl_altura_no(raiz->esq->dir);
            if( B_FB >= 0 )
                raiz = rot_dir(raiz);
            else 
                raiz = rot_esq_dir(raiz);
        }
    }

    return raiz;
} 

// Obtém o próximo número do filho da direita.
// Pega o menor filho da esquerda do filho da direita da raiz.
NO *pegar_sucessor(NO *raiz)
{
    // Avança para sub-arvore com itemes maiores que a raiz.
    NO *sucessor = raiz->dir; 
    // Busca-se item sucessor da raiz.
    if(sucessor != NULL)
    {
        // Sucessor é o nó na sub-árvore mais a esquerda possível.
        while(sucessor->esq != NULL)
        {
            sucessor = sucessor->esq;
        }
    }

    return sucessor;
} 

// Retorna o item se estiver na árvore, nulo caso contrário.
ITEM *avl_buscar(AVL *avl, int chave)
{
    if(avl != NULL)
    {
        // Retorna true se achou elemento, e falso caso contrário.
        return avl_buscar_no(avl->raiz, chave);
    }
    // Se não estiver árvore, o elemento não está nela.
    return NULL;
}

// Busca elemento da item, retorna falso caso ache nulo.
ITEM *avl_buscar_no(NO *raiz, int chave)
{
    // Percorreu árvore e não encontrou elemento buscado.
    if (raiz == NULL) 
        return NULL;
    
    // Elemento existe na árvore.
    if(chave == item_get_chave(raiz->item))
        return raiz->item;

    // Se a chave do nó atual for menor, deve-se pegar o caminho da esquerda.
    if(chave < item_get_chave(raiz->item))
        return avl_buscar_no(raiz->esq, chave); // Propaga resultado 
    else
        // Pegar caminho da direita caso seja maior.
        return avl_buscar_no(raiz->dir, chave); // Propaga resultado
}

// Imprimi árvore em ordem(crescente) com espaços.
void avl_imprimir(AVL *avl)
{
    if(avl != NULL)
    {
        // Imprimir árvore de forma recursiva
        avl_imprimi_no(avl->raiz);
    }
}

// Numeros são impressos usando travessia em ordem.
void avl_imprimi_no(NO *raiz)
{
    if (raiz == NULL) 
        return;

    avl_imprimi_no(raiz->esq);
    printf("%d ", item_get_chave(raiz->item));
    avl_imprimi_no(raiz->dir);
}







