//Inclusão do TAD do ponto.
#include "ponto.h"
#include "circulo.h"

//Struct que permite o encapsulamento dos dados.
struct circulo_{
    PONTO *P;
    float RAIO;
};
/*Função para criar um circulo - circulo_criar()*/
CIRCULO *circulo_criar (PONTO *p, float raio){
    //Não existe medida negativa, logo, o codigo encerra com erro.
    if(raio < 0){
        return NULL;
    }
    //Declaração de um ponteiro para a varivel CIRCULO definida no arquivo.h(inicialize os ponteiros!!)
    CIRCULO *c = NULL;
    //Alocação dinamica de memoria para armazenar os dados. 
    c = (CIRCULO*)malloc(1*sizeof(CIRCULO));
    //Se ocorrer erro na alocação, o programa encerra com erro.
    if(c == NULL){
        exit(1);
    }
    //Caso a memoria seja alocada, os dados são guardados.
    c -> P = p;
    c -> RAIO = raio;
    //Retorna-se o circulo com as suas informações guardadas
    return c;
}
/*Função para mudar o ponto do circulo - circulo_set_ponto()*/
bool circulo_set_ponto (CIRCULO *c, PONTO *p){
    //Se o Circulo nao existir ou se o ponto nao existir, retorna-se falso.(Operação mal-sucedida)
    if(c == NULL || p == NULL){
        return false;
    }
    //Caso contrario, muda-se o ponto.
    c -> P = p;
    //Retorna-se true para operação bem sucedida.
    return true;
}
/*Função para mudar o raio do circulo - circulo_set_raio()*/
bool circulo_set_raio (CIRCULO *c, float raio){
    //Se o Circulo nao existir, retorna-se falso.(Operação mal-sucedida)
    if(c == NULL){
        return false;
    }
    //Caso contrario, muda-se o raio.
    c -> RAIO = raio;
    //Retorna-se true para operação bem sucedida
    return true;
}
/*Função para recuperar o dado do campo PONTO da struct CIRCULO - circulo_get_ponto()*/
PONTO *circulo_get_ponto (CIRCULO *c){
    //Retorna-se o ponto.
    return c->P;
} 
/*Função para recuperar o dado do campo RAIO da struct CIRCULO - circulo_get_raio()*/
float circulo_get_raio (CIRCULO *c){
    //Retorna-se o RAIO.
    return c->RAIO;
}
/*Função para apagar um circulo - circulo_apagar()*/
void circulo_apagar (CIRCULO **circulo){
    //Apagar o ponto contido no circulo(se existir o ponto).
    if((*circulo)->P != NULL){
        ponto_apagar(&((*circulo)->P));
    }
    //Apagar o circulo, se ele existir.
    if(*circulo != NULL){
        free(*circulo);
    }
    //Ponteiro para a variavel circulo aponta para nulo.
    *circulo = NULL;
    
}