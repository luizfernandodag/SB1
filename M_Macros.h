#ifndef _MACROS_H_
#define _MACROS_H_

#include <stdio.h>
#include <stdlib.h>


// extern struct infoLinha *linha;
// extern struct TS *TabelaSimbolos;

// void resolveMacro (char *nomeArquivo)

struct LinhaMacro
{
    char *linha;
    struct LinhaMacro *pl;
    struct LinhaMacro *pla;
};

typedef struct LinhaMacro linha_Macro;


struct Macro
{
    char *nome;
    linha_Macro *codigo;
    struct Macro *pm;
};

typedef struct Macro macro;



#endif