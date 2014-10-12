#ifndef _PASSAGEM_H_
#define _PASSAGEM_H_

#include <stdio.h>
#include <stdlib.h>

// typedef struct Teste
// {
// 	int numero;
// 	struct Teste *pt;
// }Teste;


typedef struct infoLinha
{
    int numTokens;
    int numChars;
    int numLinha;
    char * linha;
    char **Tokens;
}infoLinha;

#endif


