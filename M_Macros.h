#ifndef _MACROS_H_
#define _MACROS_H_

#include <stdio.h>
#include <stdlib.h>


// extern struct infoLinha *linha;
// extern struct TS *TabelaSimbolos;

// void resolveMacro (char *nomeArquivo)

struct Macro
{
    char *nome;
    char *codigo;
    struct Macro *pm;
};

typedef struct Macro macro;



#endif