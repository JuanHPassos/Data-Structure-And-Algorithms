#include "Conjunto.h"
#include "AVL.h"
#include "LLRB.h"

#include<stdio.h>
#include<stdlib.h>

struct conjunto_
{
    // 0 - AVL e 1 - Rubronegra
    unsigned char estrutura;
    // Ponteiro para implementação desejada.
    AVL *avl;
    LLRB *llrb;
};

// Cria estrutura com implementação escolhida pelo usuário.
CONJUNTO *conjunto_criar(unsigned char tipo)
{
    CONJUNTO *conjunto = (CONJUNTO*) malloc(sizeof(CONJUNTO));
    // Caso a estrutura de controle seja criada, inicia-se seus campos.
    if (conjunto != NULL)
    {
        // Inicializa-se os parâmetros do conjunto.
        conjunto->estrutura = tipo;

        // Adota-se a árvore(estrutura) escolhida pelo usuário.
        // Implementação com Árvore binária de busca auto-balanceada(AVL).
        if (tipo == AVL_)
        {
            conjunto->avl = avl_criar();
            conjunto->llrb = NULL;
        } 
        // Árvore Rubro negra caída para esquerda
        else if (tipo == LLRB_) 
        {
            conjunto->llrb = llrb_criar();
            conjunto->avl = NULL;
        }
    }

    return conjunto;
}

// Função que apaga o conjunto.
void conjunto_apagar(CONJUNTO **conjunto)
{
    if (*conjunto != NULL)
    {
        // Apagar AVL e Rubro negra
        avl_apagar(&((*conjunto)->avl));
        llrb_apagar(&((*conjunto)->llrb));
        // Apagar conjunto.
        free(*conjunto);
        *conjunto = NULL; // Evita ponteiro selvagem.
    }
}

// Função para inserir um elemento no conjunto(retorna verdadeiro caso insira)
bool conjunto_inserir(CONJUNTO *conjunto, int chave)
{
    if (conjunto != NULL)
    {   
        // Inserção AVL.
        if (conjunto->estrutura == AVL_)
            return avl_inserir(conjunto->avl, chave);
        // Inserção LLRB.
        else if (conjunto->estrutura == LLRB_)
            return llrb_inserir (conjunto->llrb, chave);
    }

    // Se conjunto não existe, não há inserção.
    return false;
}

// Remove elemento do conjunto caso exista.
bool conjunto_remover(CONJUNTO *conjunto, int chave)
{
    if (conjunto != NULL)
    {
        // Remoção AVL.
        if (conjunto->estrutura == AVL_)
            return avl_remover(conjunto->avl, chave);
        // Remoção LLRB.
        else if (conjunto->estrutura == LLRB_)
            return llrb_remover(conjunto->llrb, chave);
    }
    // Se conjunto não existe, não houve remoção.
    return false;
}

// Imprimi conjunto.
void conjunto_imprimir(CONJUNTO *conjunto)
{
    if (conjunto != NULL)
    {
        // Imprime a estrutura que está sendo utilizada.
        if (conjunto->estrutura == AVL_)
            avl_imprimir(conjunto->avl);
        else if (conjunto->estrutura == LLRB_)
            llrb_imprimir(conjunto->llrb);
    }
}

// Verifica se o elemento pertence ao conjunto (retorna verdadeiro se pertencer).
bool conjunto_pertence(CONJUNTO *conjunto, int chave)
{
    if (conjunto != NULL)
    {
        // Verifica existência de elemento na implementação utilizada.
        if (conjunto->estrutura == AVL_)
            return avl_buscar(conjunto->avl, chave);
        else if (conjunto->estrutura == LLRB_)
            return llrb_busca(conjunto->llrb, chave);

    }
    // Se não existe conjunto, elemento não pertence.
    return false;
}

// Cria um terceiro conjunto que é a união do conj1 e conj2.
CONJUNTO *conjunto_uniao(CONJUNTO *conjunto1, CONJUNTO *conjunto2)
{
    // Conjunto3 é a união do conjunto1 e o conjunto2.
    CONJUNTO *conjunto3 = conjunto_criar(conjunto1->estrutura);
    if (conjunto3 != NULL)
    {
        if (conjunto3->estrutura == AVL_)
        {
            // Copia elementos do conjunto 1 e 2 ao conjunto 3
            avl_copiar(conjunto3->avl, conjunto1->avl);
            avl_copiar(conjunto3->avl, conjunto2->avl);
        }
        else if (conjunto3->estrutura == LLRB_)
        {
            // Copia elementos do conjunto 1 e 2 ao conjunto 3
            llrb_copiar(conjunto3->llrb, conjunto1->llrb);
            llrb_copiar(conjunto3->llrb, conjunto2->llrb);
        }
    }

    return conjunto3;
}

// Cria um terceiro conjunto que é a intersecção do conj1 e conj2.
CONJUNTO *conjunto_interseccao(CONJUNTO *conjunto1, CONJUNTO *conjunto2)
{
    // Conjunto3 é a interccao do conjunto1 com o conjunto2.
    CONJUNTO *conjunto3 = conjunto_criar(conjunto1->estrutura);
    if (conjunto3 != NULL && conjunto1 != NULL && conjunto2 != NULL)
    {
        if (conjunto3->estrutura == AVL_)
        {
            // Função inseri elementos da interseccao ao conjunto3
            avl_interseccao(conjunto3->avl, conjunto1->avl, conjunto2->avl);
        }
        else if (conjunto3->estrutura == LLRB_)
        {
            // Função inseri elementos da interseccao ao conjunto3
            /*Implementar*/
        }
    }

    return conjunto3;
}



