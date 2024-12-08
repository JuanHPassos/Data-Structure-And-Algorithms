#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "LLRB.h"

#define VERMELHO 1
#define PRETO 0

typedef struct no_ NO;
struct no_ {
    int dado;
    NO *l, *r;
    int cor;
};

typedef struct llrb_ LLRB;
struct llrb_ {
    NO *raiz;
    int tamanho;
};

int no_get_dado (NO *no) {
    if(no)
        return no->dado;
    else 
        return -1;
}

void inverte (NO *raiz) {
    if(raiz != NULL)
        raiz->cor = !raiz->cor;
    if(raiz->l != NULL)
        raiz->l->cor = !raiz->l->cor;
    if(raiz->r != NULL)
        raiz->r->cor = !raiz->r->cor;
}

NO *rotDir (NO *raiz) {
    NO *no = raiz->l;
    raiz->l = no->r;
    no->r = raiz;
    
    no->cor = raiz->cor;
    raiz->cor = VERMELHO;

    
    return no;
}

NO *rotEsq (NO *raiz) {
    NO *no = raiz->r;
    raiz->r = no->l;
    no->l = raiz;

    no->cor = raiz->cor;
    raiz->cor = VERMELHO;

    
    return no;
}

int ehVermelho (NO *raiz) {
    if (raiz == NULL) 
        return 0;;
    return (raiz->cor == VERMELHO);
}

int ehPreto (NO *raiz) {
    if (raiz == NULL) 
        return 1;
    return (raiz->cor == PRETO);
}

int filhos (NO *raiz) {
    if(raiz) {
        if (raiz->l == NULL && raiz->r == NULL) {
            return 0;
        } else if (raiz->l != NULL && raiz->r != NULL) {
            return 2;
        } else {
            return 1;
        }
    }
    return 0;
}

NO *criar_no (int dado) {
    NO *novo = (NO*)malloc(sizeof(NO));
    if (novo) {
        novo->dado = dado;
        novo->l = novo->r = NULL;
        novo->cor = VERMELHO;
    }
    return novo;
}

NO* pegarSuccessor(NO* no) {
    if (no == NULL || no->r == NULL) {
        return NULL; // Não há sucessor
    }

    NO* atual = no->r; // Inicia na subárvore direita
    while (atual->l != NULL) { // Vai até o nó mais à esquerda
        atual = atual->l;
    }
    return atual;
}

LLRB *llrb_criar () {
    LLRB *arvore = (LLRB*)malloc(sizeof(LLRB));
    if (arvore) {
        arvore->tamanho = 0;
        arvore->raiz = NULL;
    }
    return arvore;
}

void no_apagar (NO **raiz) {
    if(*raiz != NULL) {
        no_apagar(&(*raiz)->r);
        no_apagar(&(*raiz)->l);
        free(*raiz); *raiz = NULL;
    }
}

void llrb_apagar (LLRB **arvore) {
    if (*arvore != NULL) {
        no_apagar(&(*arvore)->raiz);
        free(*arvore); *arvore = NULL;
    }
}

NO *inserir (NO *raiz, int dado) {
    if (raiz == NULL) {
        return criar_no(dado);
    }
    if (dado < raiz->dado) {
        raiz->l = inserir(raiz->l, dado);
    } else if (dado > raiz->dado) {
        raiz->r = inserir(raiz->r, dado);
    }

    if (ehVermelho(raiz->r) && ehPreto(raiz->l)) {
        raiz = rotEsq(raiz);
    }
    if (ehVermelho(raiz->l) && ehVermelho(raiz->l->l)) {
        raiz = rotDir(raiz);
    }
    if (ehVermelho(raiz->l) && ehVermelho(raiz->r)) {
        inverte(raiz);
    }

    return raiz;
}

bool llrb_inserir (LLRB *arvore, int dado) {
    if (arvore) {
        arvore->raiz = inserir(arvore->raiz, dado);
        arvore->tamanho++;
        return true;
    }
    return false;
}

NO *busca (NO *raiz, int chave) {
    if (raiz == NULL) {
        return NULL;
    }

    if (chave == raiz->dado) {
        return raiz;
    } else if (chave < raiz->dado) {
        return busca(raiz->l, chave);
    } else {
        return busca(raiz->r, chave);
    }
}

NO* llrb_busca (LLRB *arvore, int chave) {
    if (arvore) {
        return busca(arvore->raiz, chave);
    }
    return NULL;
}

NO *MoveRedLeft (NO *raiz) {
    if (raiz) {
        if (ehPreto(raiz->l) && ehPreto(raiz->l->l)) {
            inverte(raiz);
        }

        if (ehVermelho(raiz->r->l)) {
            raiz->r = rotDir(raiz->r);
            raiz = rotEsq(raiz);
            inverte(raiz);
        }
    }
    return raiz;
}

NO *MoveRedRight (NO *raiz) {
    if (raiz) {
        if (ehPreto(raiz->r) && ehPreto(raiz->r->l)) {
            inverte(raiz);
        }

        if (ehVermelho(raiz->l->l)) {
            raiz = rotDir(raiz);
            inverte(raiz);
        }
    }
    return raiz;
}

bool remover (NO **raiz, int chave) {
    if (*raiz == NULL) {
        return false;
    }

    if (chave == (*raiz)->dado) {
        if (filhos(*raiz) == 0) {
            free(*raiz);
            *raiz = NULL;
            return true;
        } else if (filhos(*raiz) == 1) {
            if ((*raiz)->l == NULL) {
                NO *p = *raiz;
                (*raiz)->r->cor = (*raiz)->cor;
                *raiz = (*raiz)->r;
                free(p); p = NULL;
                return true;
            }

            if ((*raiz)->r == NULL) {
                NO *p = *raiz;
                (*raiz)->l->cor = (*raiz)->cor;
                *raiz = (*raiz)->l;
                free(p); p = NULL;
                return true;
            }
        } else {
            NO *p = pegarSuccessor(*raiz);
            if(p==NULL)return false;
            (*raiz)->dado = p->dado;
            if (ehPreto((*raiz)->r) && ehPreto((*raiz)->r->l)) {
            *raiz = MoveRedRight(*raiz);
            }
            return remover(&(*raiz)->r, p->dado);
        }
    } else if (chave < (*raiz)->dado) {
        *raiz = MoveRedLeft(*raiz);
        return remover(&(*raiz)->l, chave);
    } else {
        *raiz = MoveRedRight(*raiz);
        return remover(&(*raiz)->r, chave);
    }

    if (ehVermelho((*raiz)->r) && !ehVermelho((*raiz)->l)) {
        *raiz = rotEsq(*raiz);
    }
    if (ehVermelho((*raiz)->l) && ehVermelho((*raiz)->l->l)) {
        *raiz = rotDir(*raiz);
    }
    if (ehVermelho((*raiz)->l) && ehVermelho((*raiz)->r)) {
        inverte(*raiz);
    }
     
    return true;
}

bool llrb_remover (LLRB *arvore, int chave) {
    if (arvore != NULL) {
        return remover(&(arvore)->raiz, chave);
    }
    return false;
}

void imprimir (NO *raiz) {
    if (raiz) {
        imprimir(raiz->l);
        printf("%d, ", raiz->dado);
        imprimir(raiz->r);
    }
}

void llrb_imprimir (LLRB *arvore) {
    if (arvore) {
        imprimir(arvore->raiz);
        printf("\n");
    }
}

bool pertence (LLRB *arvore, int chave) {
    NO *E = llrb_busca(arvore, chave);
    if (E) {
        return true;
    } 
    return false;
}

void unir (LLRB *arvore, NO *raiz) {
    if (raiz == NULL) return;
    llrb_inserir(arvore, raiz->dado);

    if (raiz->l != NULL) {
        unir(arvore, raiz->l);
    }
    if (raiz->r != NULL) {
        unir(arvore, raiz->r);
    }
}

LLRB *uniao (LLRB *arv1, LLRB *arv2) {
    LLRB *arv_uniao = llrb_criar();
    if (arv_uniao != NULL) {
        unir(arv_uniao, arv1->raiz);
        unir(arv_uniao, arv2->raiz);
    }
    return arv_uniao;
}

void intersec (LLRB *inter, LLRB *arv, NO *raiz) {
    if (raiz == NULL) return;

    if (pertence(arv, raiz->dado)) {
        llrb_inserir(inter, raiz->dado);
    }
    if (raiz->l != NULL) {
        intersec(inter, arv, raiz->l);
    }
    if (raiz->r != NULL) {
        intersec(inter, arv, raiz->r);
    }
}

LLRB *intersecao (LLRB *arv1, LLRB *arv2) {
    LLRB *arv_inter = llrb_criar();
    if (arv_inter) {
        if (arv1->tamanho > arv2->tamanho) {
            intersec(arv_inter, arv1, arv2->raiz);
        } else {
            intersec(arv_inter, arv2, arv1->raiz);
        }
    }
    return arv_inter;
}

// Adiciona os valores presentes no nó na LLRB.(Pré-ordem)
void llrb_copiar_no(LLRB *llrb, NO *raiz)
{
    llrb_inserir(llrb, raiz->dado);

    if(raiz->l != NULL)
        llrb_copiar_no(llrb, raiz->l);
    if(raiz->r != NULL)
        llrb_copiar_no(llrb, raiz->r);
}

// Adiciona os elementos da LLRB origem na LLRB destino. 
void llrb_copiar(LLRB *llrb_destino, LLRB *llrb_origem)
{
    if(llrb_destino != NULL && llrb_origem != NULL)
    {
        llrb_copiar_no(llrb_destino, llrb_origem->raiz);
    }
}


