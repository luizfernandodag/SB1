#ifndef _ANALISE_H_
#define _ANALISE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "M_Passagem_Unica.h"

extern infoLinha * Linhas;

int Analise (infoLinha *, FILE *);

infoLinha * EscreveNumLinha(infoLinha *, int);

void ini(infoLinha *);

#endif
