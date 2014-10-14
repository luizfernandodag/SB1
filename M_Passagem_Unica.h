#ifndef _PASSAGEM_H_
#define _PASSAGEM_H_

#include <stdio.h>
#include <stdlib.h>

// typedef struct Teste
// {
// 	int numero;
// 	struct Teste *pt;
// }Teste;


typedef struct
{
    int numTokens;
    int numChars;
    int numLinha;
    char * linha;
    char **Tokens;
}infoLinha;

// typedef struct
// {
//     int numAparicoes;
//     int * pilhaDePosicoes;
//     char * nome;

// }ListaSim;

struct ts 
{
    //ListaSim simbolo;
    int numAparicoes;
    int *pilhaDePosicoes;
    char *nome;
    int valor;
    int def;
    int valido;
    struct ts * prox;

};

typedef struct ts TS;



#endif


