//Codigo fonte
#include "ponto.h"
//Encapsulamento dos dados
struct ponto_{
    float X;
    float Y;
};
/*Função para criar um ponto = ponto_criar()*/
PONTO *ponto_criar (float x, float y){
    //Declaração de um ponteiro para uma variavel do tipo PONTO, que está definido no ponto.h, porem é armazenado 8 bytes, pois é um ponteiro, o que permite o encapsulamento dos dados e o funcionamento do código.(por isso a necessidade de um ponteiro)
    PONTO *pon = NULL;
    //Alocação dinamica da variavel do tipo PONTO
    pon = (PONTO*)malloc(1*sizeof(PONTO));
    //Se a alocação der errado, o codigo encerra com erro.
    if(pon == NULL){
        exit(1);
    }
    //Elemento X da struct do ponteiro pon, recebe x.(Mesma lógica para o y)
    pon -> X = x;
    pon -> Y = y;
    //Retorna um ponteiro que aponta para uma variavel do tipo PONTO.
    return pon; 
} 
/*Função para apagar um ponto - ponto_apagar()*/
void ponto_apagar (PONTO **p){
    //Cuidado para nao tentar desalocar algo que nao existe.(double free() ou segmentation_fault())
    if(*p != NULL){
        //Liberar memoria.
        free(*p);
    }
    //Ponteiro não aponta para nada.
    *p = NULL;
    return;
}
/*Função para mudar os valores da variavel ponto - ponto_set()*/
bool ponto_set(PONTO *p, float x, float y){
    //Se o ponto nao existir, nao é possivel atualizar o valor, retornado-se falso.
    if(p == NULL) return false;
    //Caso exista, os valores são atualizados e retorna-se verdadeiro, como operação bem sucedida.
    p -> X = x;
    p -> Y = y;
    return true;
}
/*Função para acessar o valor da coordenada x do ponto - ponto_get_x()*/
float ponto_get_x (PONTO *p){
    //Retorna-se o valor da coordenada x do ponto.(operação seta derreferencia o ponteiro e acessa um campo da struct)
    return p->X;
}
/*Função para acessar o valor da coordenada y do ponto - ponto_get_Y()*/
float ponto_get_y (PONTO *p){
    //Mesma lógica da coordenada x, esta sendo aplicada na coordenada y.
    return p->Y;
}
/*Função para printar a coordenda x e y do ponto - ponto_print()*/
void ponto_print (PONTO *p){
    //Imprimi dois numeros floats com uma casa decimal apos a virgula, sendo eles respectivamente, a coordenada X e Y do ponto.
    printf("(%.1f, %.1f)", p->X, p->Y);
    return;
} 
//Cabe destacar que essa função foi implementada no codigo do ponto.c, pois a diferença entre dois pontos pode ser utilizada em diversas situações que envolvam pontos, e nao se restringem ao uso de circulos.
/*Função para calcular a distancia entre dois pontos - distancia()*/
float distancia(PONTO *pa, PONTO *pb){
    //Retorno a distancia entre dois pontos de acordo com a formula d = raiz quadrada((x1-x2)^2+(y1-y2)^2)
    //Diferença dos valores das abcissas ao quadrado.
    float x = ((pa->X)-(pb->X))*((pa->X)-(pb->X));
    //Diferença dos valores das ordenadas ao quadrado.
    float y = ((pa->Y)-(pb->Y))*((pa->Y)-(pb->Y));
    //Raiz quadrada da soma desses resultados(distancia entre dois pontos).
    return sqrt(x+y);
}
