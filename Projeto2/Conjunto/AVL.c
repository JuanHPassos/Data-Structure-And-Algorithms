#include "AVL.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct no_ NO;

struct no_
{
    int valor;
    NO *dir;
    NO *esq;
    int altura;
};

struct avl_
{
    NO *raiz;
    int tamanho;
};

// Modularização
// Similiares ABB.
NO *avl_cria_no(int valor);
void avl_apagar_no(NO *raiz);
NO *avl_inserir_no(NO *raiz, int valor, bool *inserido);
NO *avl_remover_no(NO *raiz, int valor, bool *removido);
bool avl_buscar_no(NO *raiz, int valor);
// Balanceamento.
NO *rot_dir(NO *A);
NO *rot_esq(NO *A);
// Auxiliares implementação.
NO *pegar_sucessor(NO *raiz);
int avl_altura_no(NO* raiz);
void avl_imprimi_no(NO *raiz);
// Auxiliares TAD conjunto.
void avl_copiar_no(AVL *avl, NO *raiz);
void avl_interseccao_no(AVL *avl_intersec, AVL *avl_maior, NO *raiz);

// Cria estrutura nó e armazena seu valor.
NO *avl_cria_no(int valor)
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
        
        // Valor do nó.
        no->valor = valor;
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
        avl_apagar_no((*avl)->raiz);
        free(*avl);
        *avl = NULL;
    }
}

// Apaga a árvore em pós-ordem.
void avl_apagar_no(NO *raiz)
{
    if(raiz != NULL)
    {
        // Percorre em pós-ordem.
        avl_apagar_no(raiz->esq);
        avl_apagar_no(raiz->dir);
        
        // Desalocação memória.
        free(raiz);
        raiz = NULL;
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

// Percorre o caminho da valor, inserindo recursivamente(pré-ordem).
NO *avl_inserir_no(NO *raiz, int valor, bool *inserido)
{
    if(raiz == NULL)
    {
        raiz = avl_cria_no(valor);
        *inserido = true; // Garante incremento de tamanho da árvore.
    }
    // Se valor for menor, percorre caminho da esquerda do nó.
    else if (valor < raiz->valor)
        raiz->esq = avl_inserir_no(raiz->esq, valor, inserido);
    // Se valor for maior, percorre caminho da direita do nó.
    else if (valor > raiz->valor)
        raiz->dir = avl_inserir_no(raiz->dir, valor, inserido);

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

// Chama função que insere recursivamente.
bool avl_inserir(AVL *avl, int valor)
{
    // Variável de retorno.
    bool inserido =  false;
    if (avl != NULL)
    {
        avl->raiz = avl_inserir_no(avl->raiz, valor, &inserido);
        // Caso nó tenha sido inserido(não tinha nó com mesmo valor na árvore)
        if(inserido == true)
            avl->tamanho++;
    }
    
    return inserido;
}

// Remove nó e retorna verdadeiro caso consiga e falso caso contrário.
bool avl_remover(AVL *avl, int valor)
{
    bool removido = false;
    // Se árvore existir.
    if(avl != NULL)
    {
        // Remover nó com valor passado no parametro.
        avl->raiz = avl_remover_no(avl->raiz, valor, &removido);
        // Caso valor tenha sido removido(valor existia na árvore)
        if(removido == true)
            avl->tamanho--;
    }
    // Retorna nulo caso não tenha removido.
    return removido;
}


// Remoção em pré-ordem.
NO *avl_remover_no(NO *raiz, int valor, bool *removido)
{
    // Verifica raiz.
    if(raiz == NULL)
        return NULL;     

    // Se valor menor, percorre caminho esquerdo.
    if(valor < raiz->valor)
        raiz->esq = avl_remover_no(raiz->esq, valor, removido);
    // Se valor maior, percorre caminho direito.
    else if(valor > raiz->valor)
        raiz->dir = avl_remover_no(raiz->dir, valor, removido);
    // Se for igual, remove-se o nó.
    else
    {  
        // Garante decremento do tamanho da árvore.
        *removido = true;

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
        // Caso existir os dois filhos, a próxima valor maior assume.
        // Que corresponde ao menor filho da sub-árvore da direita.
        else
        {
            NO *sucessor = pegar_sucessor(raiz);
            // Troca raiz pela folha.                
            raiz->valor = sucessor->valor;
            // Remove a folha.
            raiz->dir = avl_remover_no(raiz->dir, sucessor->valor, removido);
        }
    }

    return raiz;
} 

// Obtém o próximo número do filho da direita.
// Pega o menor filho da esquerda do filho da direita da raiz.
NO *pegar_sucessor(NO *raiz)
{
    // Avança para sub-arvore com valores maiores que a raiz.
    NO *sucessor = raiz->dir; 
    // Busca-se valor sucessor da raiz.
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

// Retorna true se valor estiver na árvore, false caso contrário.
bool avl_buscar(AVL *avl, int valor)
{
    if(avl != NULL)
    {
        // Retorna true se achou elemento, e falso caso contrário.
        return avl_buscar_no(avl->raiz, valor);
    }
    // Se não estiver árvore, o elemento não está nela.
    return false;
}

// Busca elemento da valor, retorna falso caso ache nulo.
bool avl_buscar_no(NO *raiz, int valor)
{
    // Percorreu árvore e não encontrou elemento buscado.
    if (raiz == NULL) 
        return false;
    
    // Elemento existe na árvore.
    if(raiz->valor == valor)
        return true;

    // Se o valor do nó atual for menor, deve-se pegar o caminho da esquerda.
    if(raiz->valor < valor)
        return avl_buscar_no(raiz->esq, valor); // Propaga resultado 
    else
        // Pegar caminho da direita caso seja maior.
        return avl_buscar_no(raiz->dir, valor); // Propaga resultado
}

// Função para imprimir árvore.
void avl_imprimir(AVL *avl)
{
    if(avl != NULL)
    {
        // Imprimir árvore de forma recursiva
        avl_imprimi_no(avl->raiz);
        printf("\n");
    }
}

// Numeros são impressos usando travessia em ordem.
void avl_imprimi_no(NO *raiz)
{
    if (raiz == NULL) 
        return;

    avl_imprimi_no(raiz->esq);
    printf("%d, ", raiz->valor);
    avl_imprimi_no(raiz->dir);
}

// Adiciona os elementos da avl origem na avl destino. 
void avl_copiar(AVL *avl_destino, AVL *avl_origem)
{
    if(avl_destino != NULL && avl_origem != NULL)
    {
        avl_copiar_no(avl_destino, avl_origem->raiz);
    }
}

// Adiciona os valores presentes no nó na avl.(Pré-ordem)
void avl_copiar_no(AVL *avl, NO *raiz)
{
    avl_inserir(avl, raiz->valor);
    // Percorrem nós da esquerda e direita.
    if(raiz->esq != NULL)
        avl_copiar_no(avl, raiz->esq);
    if(raiz->dir != NULL)
        avl_copiar_no(avl, raiz->dir);
}

// Função que preenche uma avl com a interseccao de outras duas.
void avl_interseccao(AVL *avl_intersec, AVL *avl_1, AVL *avl_2)
// avl_intersec = avl a ser preenchida com os elementos da inserseccao
{
    // Seleciona o menor conjunto para percorrer verificando
    // se existe o mesmo elemento em ambos.
    if(avl_1->tamanho > avl_2->tamanho)
        avl_interseccao_no(avl_intersec, avl_1, avl_2->raiz);
    else
        avl_interseccao_no(avl_intersec, avl_2, avl_1->raiz);
}

// Função que executa a interseccao recursivamente, percorrendo menor avl em ordem.
void avl_interseccao_no(AVL *avl_intersec, AVL *avl_maior, NO *raiz)
{
    // Se estiver nos dois conjunto = elemento de interseccao
    if(avl_buscar(avl_maior, raiz->valor))
        avl_inserir(avl_intersec, raiz->valor);
    // Visitar filhos da esquerda e direita
    if(raiz->esq != NULL)
        avl_interseccao_no(avl_intersec, avl_maior, raiz->esq);
    if(raiz->dir != NULL)
        avl_interseccao_no(avl_intersec, avl_maior, raiz->dir);
}







