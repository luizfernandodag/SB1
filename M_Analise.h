#ifndef _ANALISE_H_
#define _ANALISE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "M_Passagem_Unica.h"
#include "testeLuiz.h"

extern infoLinha * Linhas;

extern TS * tabelaSims;

int Analise (infoLinha *, FILE *, TS*, int *);

infoLinha * EscreveNumLinha(infoLinha *, int);
TS * insereSimbolo(TS * , char *,int , int , int *  );
TS * retornaTabelaSimbolos(infoLinha * , TS * ,int ); //int * numSim)
int verificaSections(infoLinha *linha);
void AnaliseSintatica(infoLinha * linha, TS * tabelaSims);

void ini(infoLinha *);

#endif
