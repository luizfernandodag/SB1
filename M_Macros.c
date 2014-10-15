#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Macros.h"

macro* guardandoMacro(macro *macro, FILE *arquivoEntrada, char *PrimeiroToken, char *SegundoToken);
void gravaLinha(FILE *, char *);
macro* insereMacro(macro* listaMacro, char *nome, char *codigo);
void lendoLinha(FILE *arquivoEntrada, FILE *arquivoSaida);
void separaTokens(char *PrimeiroToken, char *SegundoToken, char *linha);


void gravaLinha(FILE *arquivoSaida, char *linha)
{
	fprintf(arquivoSaida, "%s", linha);
	// fprintf(arquivoSaida, "%s", SegundoToken);
}

void separaTokens(char *PrimeiroToken, char *SegundoToken, char *linha)
{
	char * token;
  	printf ("Splitting string \"%s\" into tokens:\n",linha);
  	token = strtok (linha," ");
  	PrimeiroToken = token;

  	while (token != NULL)
  	{
  		printf("entrei no while do separa\n");
    	printf ("%s\n", token);
    	SegundoToken = token;
    	token = strtok (NULL, " ");
    	
    	// printf ("%s\n", token);
  	}

  	printf("PrimeiroToken = %s\n", PrimeiroToken);
  	printf("SegundoToken = %s\n", SegundoToken);
}


void lendoLinha(FILE *arquivoEntrada, FILE *arquivoSaida)
{
	char *PrimeiroToken, *SegundoToken, *linha;
	macro *macro = NULL;

	linha = (char*)malloc(sizeof(char*));
	PrimeiroToken = (char*)malloc(sizeof(char*));
	SegundoToken = (char *)malloc(sizeof(char*));

	// printf("entrei na lendo arquivo\n");

	// if (arquivoEntrada != NULL)
	// {
	// 	printf("arquivo existe e esta aberto\n");
	// }
	// else{
	// 	printf("arquivo nao esta aberto\n");
	// }

	fscanf(arquivoEntrada, "%[^\n]%*c", linha);

	printf("Linha = %s\n", linha);

	while(!feof(arquivoEntrada))
	{
		printf("entrei no while do lendo arquivo\n");
		
		//fscanf(arquivoEntrada, "%s", SegundoToken);
		separaTokens(PrimeiroToken, SegundoToken, linha);

		printf("li token = %s\n", PrimeiroToken);
		printf("li token = %s\n", SegundoToken);

		if (!strcmp(SegundoToken, "MACRO"))
		{
			printf("achei macro\n");
			macro = guardandoMacro(macro, arquivoEntrada, PrimeiroToken, SegundoToken);
		}
		else{
			printf("nao é macro\n");
			gravaLinha(arquivoSaida, linha);
		}

		fscanf(arquivoEntrada, "%s", PrimeiroToken);
	}
}

macro* guardandoMacro(macro *macro, FILE *arquivoEntrada, char *PrimeiroToken, char *SegundoToken)
{
	char *nomeMacro = PrimeiroToken;
	char *token;
	char codigo[] = "";

	fscanf(arquivoEntrada, "%s", token);

	while(strcmp(token, "ENDMACRO"))
	{
		strcat(codigo, token);
		fscanf(arquivoEntrada, "%s", token);
	}

	macro = insereMacro(macro, nomeMacro, codigo);

	return macro;

}

//função que insere os mnemonicos de assembly em uma lista encadeada
macro* insereMacro(macro* listaMacro, char *nome, char *codigo)
{
	macro* listaAux = (macro*) calloc(1, sizeof(macro));

	listaAux->nome = nome;
	listaAux->codigo = codigo ;

	listaAux->pm = listaMacro;

	return listaAux;
}


// void resolveMacro (char *nomeArquivo)
int main(int argc, char *argv[])
{
	
	FILE *arquivoEntrada, *arquivoSaida;
	char *nomeArquivoSaida;

	arquivoEntrada = fopen(argv[1], "r");

	printf("nome entrada = %s\n", argv[1]);
	// nomeArquivoSaida = (char *)malloc(sizeof(char))
	nomeArquivoSaida = (char*)argv[2];
	strcat(nomeArquivoSaida, ".mcr");
	arquivoSaida = fopen(nomeArquivoSaida, "w");

	printf("nome saida = %s\n", nomeArquivoSaida);

	if (arquivoEntrada != NULL && arquivoSaida != NULL)
	{
		lendoLinha(arquivoEntrada, arquivoSaida);

		fclose(arquivoSaida);
		fclose(arquivoEntrada);

	}
	else
	{
		printf("nao consegui abrir o arquivo\n");
	}


	return 0;
}