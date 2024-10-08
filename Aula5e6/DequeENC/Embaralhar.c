#include "Deque.h"

#include<stdio.h>
#include<stdlib.h>

void criar_baralho(DEQUE **baralho);
char *junta_strings(char *numero, char *naipe);
int tam_string(char *string);
bool compara_strings(char *str1, char *str2);
void imprimir_baralho(DEQUE **baralho);
void embaralhar(DEQUE **baralho1, DEQUE **baralho2);

int main(void){
    DEQUE *baralho1, *baralho2;
    baralho1 = deque_criar();
    baralho2 = deque_criar();
    criar_baralho(&baralho1);

    embaralhar(&baralho1, &baralho2);

    printf("\n-------------------\n");
    printf("\nO BARALHO\n");
    printf("\n-------------------\n\n");
    
    imprimir_baralho(&baralho1);
    imprimir_baralho(&baralho2);

    deque_apagar(&baralho1);
    deque_apagar(&baralho2);
}

void criar_baralho(DEQUE **baralho){
    char *numero[13]; char *naipe[4];
    numero[0] = "Ás ";
    numero[1] = "Dois ";
    numero[2] = "Três ";
    numero[3] = "Quatro ";
    numero[4] = "Cinco ";
    numero[5] = "Seis ";
    numero[6] = "Sete ";
    numero[7] = "Oito ";
    numero[8] = "Nove ";
    numero[9] = "Dez ";
    numero[10] = "Valete ";
    numero[11] = "Rainha ";
    numero[12] = "Rei ";
    
    naipe[0] = "de Paus";
    naipe[1] = "de Copas";
    naipe[2] = "de Espadas";
    naipe[3] = "de Ouros";

    printf("\n-------------------\n");
    printf("\nO BARALHO\n");
    printf("\n-------------------\n\n");

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            printf("%s%s\n", numero[j], naipe[i]);
            char *carta = junta_strings(numero[j], naipe[i]);
            deque_inserir_fim(*baralho, item_criar(0, carta));
        }
    }

    return;
}

char *junta_strings(char *numero, char *naipe){
    int tam1 = tam_string(numero);
    int tam2 = tam_string(naipe);
    char *carta = (char*) malloc(sizeof(char) * (tam1+tam2+1));
    for(int i = 0; i < tam1; i++){
        carta[i] = numero[i];
    }
    for(int i = tam1; i < tam1+tam2; i++){
        carta[i] = naipe[i-tam1];
    }
    carta[tam1+tam2] = '\0';

    return(carta);
}

int tam_string(char *string){
    int tamanho = 0;
    while(*string != '\0'){
        tamanho++;
        string++;
    }
    return(tamanho);
}

bool compara_strings(char *str1, char *str2){
    if(tam_string(str1) != tam_string(str2)) return false;
    while(*str1 != '\0' && *str2 != '\0'){
        if(*str1 != *str2) return false;
        str1++; str2++;       
    }
    return true;
}

void imprimir_baralho(DEQUE **baralho){
    while(deque_contar(*baralho) != 0){
        ITEM *carta = deque_remover_inicio(*baralho);
            
        printf("%s\n", (char*)item_get_dados(carta));
        
        free(item_get_dados(carta));

        item_apagar(&carta);
    }
}

void embaralhar(DEQUE **baralho1, DEQUE **baralho2){
    printf("\n-------------------\n");
    printf("\nTROCAS\n");
    printf("\n-------------------\n\n");

    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        int baralho, orig, dest;
        char origem[7], destino[7];
        
        scanf("%d %s %s", &baralho, origem, destino);
        //orig == 1 representa fim, se for 0 é inicio.
        //dest == 1 representa fim, se for 0 é inicio.
        if(compara_strings(origem, "fim")) orig = 1;
        else orig = 0;  

        if(compara_strings(destino, "fim")) dest = 1;
        else dest = 0;

        ITEM *carta = NULL;
        if(baralho == 1){
            //A carta é obtida do fim ou do começo do baralho 1.
            if(orig) carta = deque_remover_fim(*baralho1);
            else carta = deque_remover_inicio(*baralho1);
            //E ira para o fim ou comeco do baralho 2.
            if(dest) deque_inserir_fim(*baralho2, carta);
            else deque_inserir_inicio(*baralho2, carta);
        }
        else{
            //Pega a carta do baralho1(fim ou inicio).  
            if(orig) carta = deque_remover_fim(*baralho2);
            else carta = deque_remover_inicio(*baralho2);
            //Coloca no baralho2(fim ou inicio).
            if(dest) deque_inserir_fim(*baralho1, carta);
            else deque_inserir_inicio(*baralho1, carta);
        }

        printf("A carta %s foi removida do deque %d na posição %s e inserida no deque %d na posição %s\n",
        (char*)(item_get_dados(carta)), baralho, origem, ((baralho%2)+1), destino);
    }
}
