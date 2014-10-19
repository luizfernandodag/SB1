#ifndef _SINTESE_H_
#define _SINTESE_H_

#include <stdio.h>
#include <stdlib.h>

#include "M_Passagem_Unica.h"

extern struct infoLinha *linha;
extern struct TS *TabelaSimbolos;

// void Sintese (infoLinha *linha, char *nomeArquivoSaida, TS *TabelaSimbolos, _Bool primeiraVez);
void Sintese (infoLinha *linha, char *nomeArquivoSaida, _Bool primeiraVez);
void resolvePendencia(char *nomeArquivoSaida, int posicao);

struct Assembly
{
    char * mnemonico;
    int codigo;
    int tamanho;
    struct Assembly *pa;
};

typedef struct Assembly assembly;

//void pegaLista(struct Teste *, int);


#endif