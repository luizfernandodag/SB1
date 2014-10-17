#ifndef _PRE_PROCESSAMENTO_H_
#define _PRE_PROCESSAMENTO_H_

#include <stdio.h>
#include <stdlib.h>

//struct para guardar as linhas do codigo da macro
struct Codigo
{
    char *linha;
    struct Codigo *pl;
    struct Codigo *pla;
};

typedef struct Codigo codigo;



#endif