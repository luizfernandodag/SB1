#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Interface_Usuario.h"
#include "M_Macros.h"
#include "M_Passagem_Unica.h"


int main(int argc, char const *argv[])
{
	char *nomeEntrada;
	char *nomeSaida;

	nomeEntrada = (char*)malloc((strlen(argv[2])+4)*sizeof(char*));
	nomeSaida = (char*)malloc((strlen(argv[3])+4)*sizeof(char*));


	strcpy(nomeEntrada, argv[2]);
	strcpy(nomeSaida, argv[3]);

	strcat(nomeEntrada, ".asm");
	// printf("NOME DE ENTRADA = %s\n", nomeEntrada);

	if (!strcmp(argv[1], "-m"))
	{
		strcat(nomeSaida, ".mcr");
		// printf("NOME SAIDA = %s\n", nomeSaida);
		resolveMacro(nomeEntrada, nomeSaida);
	}

	return 0;
}