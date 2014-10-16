#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Macros.h"

void gravaLinha(char *, char *);
macro* insereMacro(macro* listaMacro, char *nome, char *codigo);
void lendoLinha(FILE *arquivoEntrada, char *NomeArquivoSaida);
char * separaTokens(char *PrimeiroToken, char *SegundoToken, char *linha);
macro* buscaMacro (macro* listaMacros, char *nome);
macro* guardandoMacro(macro *macro, FILE *arquivoEntrada, char *linha);


void gravaLinha(char *NomeArquivoSaida, char *linha)
{
	FILE *arquivoSaida;

	arquivoSaida = fopen(NomeArquivoSaida, "a");

	strcat(linha,"\n");
	fprintf(arquivoSaida, "%s", linha);
	printf("LINHA = %s\n", linha);
	// fprintf(arquivoSaida, "%s", SegundoToken);

	fclose(arquivoSaida);
}

void gravaMacro(char *NomeArquivoSaida, macro *resultadoBusca)
{
	FILE *arquivoSaida;

	arquivoSaida = fopen(NomeArquivoSaida, "a");

	fprintf(arquivoSaida, "%s\n", resultadoBusca->codigo);
	printf("LINHA MACRO = %s\n", resultadoBusca->codigo);
	// fprintf(arquivoSaida, "%s", SegundoToken);

	fclose(arquivoSaida);
}

macro* buscaMacro (macro* listaMacros, char *nome)
{
	macro *macro;

 	for (macro = listaMacros; macro != NULL; macro = macro->pm){
 		if (!strcmp(macro->nome, nome))
 		{
 			printf("ACHEI MACRO = %s\n", macro->nome);
 			return macro;			
 		}		
 	}

 	return NULL;
}

// char * separaTokens(char *PrimeiroToken, char *SegundoToken, char *linha)
// {
// 	char * token;
//   	printf ("Splitting string  - %s - into tokens:\n",linha);
//   	PrimeiroToken = (char*)strtok (linha," :");
//   	token = PrimeiroToken;
//   	// strcpy(PrimeiroToken, token);
//   	// &PrimeiroToken = token;

//   	while (token != NULL)
//   	{
//   		printf("entrei no while do separa\n");
//     	printf ("%s\n", token);
//     	// SegundoToken = token;
//     	// strcpy(SegundoToken, token);
//     	SegundoToken = token;
//     	token = (char*)strtok (NULL, " :");
//     	// token = SegundoToken;
    	
//     	// printf ("%s\n", token);
//   	}

//   	printf("PrimeiroToken = %s\n", PrimeiroToken);
//   	printf("SegundoToken = %s\n", SegundoToken);

//   	return token;
// }


void lendoLinha(FILE *arquivoEntrada, char *NomeArquivoSaida)
{
	char *PrimeiroToken, *SegundoToken, *linha, *ehMacro;
	macro *macro = NULL, *resultadoBusca;

	linha = (char*)malloc(sizeof(char*));
	// resultadoBusca = (macro*)malloc(sizeof(macro*));

	//lendo linha do arquivo
	fscanf(arquivoEntrada, "%[^\n]%*c", linha);


	while(!feof(arquivoEntrada))
	{
		//separando as duas palavras da linha (no minimo)
		// PrimeiroToken = (char*)malloc(sizeof(char*));
		// SegundoToken = (char *)malloc(sizeof(char*));	
		// PrimeiroToken = (char*)strtok (linha," ");
		// SegundoToken = (char*)strtok (NULL," ");

		// printf("li token = %s\n", PrimeiroToken);
		// printf("li token 2 =%s\n", SegundoToken);

		printf("LINHA = %s\n", linha);
		ehMacro = strstr(linha, "MACRO");

		// if (ehMacro != NULL)
		// {
		// 	printf("EH MACRO\n");
		// }

		

		if (ehMacro != NULL)
		{
			printf("achei macro\n\n\n");
			// printf("linhaaaaah = %s\n", linha);
			macro = guardandoMacro(macro, arquivoEntrada, linha);
		}
		else
		{
			resultadoBusca = buscaMacro (macro, linha);

			if (resultadoBusca != NULL)
			{
				printf("SUSBTITUI MACRO\n\n\n");
				gravaMacro(NomeArquivoSaida, resultadoBusca);
			}
			else
			{
				printf("nao é macro\n\n\n");
				gravaLinha(NomeArquivoSaida, linha);
			}
		}

		fscanf(arquivoEntrada, "%[^\n]%*c", linha);
	}
}

macro* guardandoMacro(macro *macro, FILE *arquivoEntrada, char *linha)
{
	char *nomeMacro, *NAME;
	char *linhaMacro;
	char *codigo;

	// codigo = (char*)malloc(sizeof(char*));
	linhaMacro = (char*)malloc(sizeof(char*));

	fscanf(arquivoEntrada, "%[^\n]%*c", linhaMacro);

	// getchar();
	while(strcmp(linhaMacro, "ENDMACRO"))
	{
		// getchar();
		strcat(codigo, linhaMacro);
		// getchar();
		strcat(codigo,"\n");
		// printf("LINHA MACRO = %s\n", codigo);
		// getchar();
		fscanf(arquivoEntrada, "%[^\n]%*c", linhaMacro);
		// getchar();
	}
	// getchar();

	nomeMacro =	(char *)malloc(sizeof(char*));
	nomeMacro = (char*)strtok (linha,": ");
	NAME =	(char *)malloc(sizeof(char*));	
	strcpy(NAME, nomeMacro);
	// *NAME = *nomeMacro;
	// printf("MACRO = %s\n", codigo);
	printf("NOME MACRO = %s\n", NAME);

	// getchar();
	macro = insereMacro(macro, NAME, codigo);
	// getchar();
	return macro;

}

//função que insere os mnemonicos de assembly em uma lista encadeada
macro* insereMacro(macro* listaMacro, char *nome, char *codigo)
{
	macro* listaAux = (macro*) calloc(1, sizeof(macro));

	listaAux->nome = nome;
	printf("NOME MACRO = %s\n", nome);
	strcpy(listaAux->codigo, codigo)
	// listaAux->codigo = codigo ;

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

	fclose(arquivoSaida);

	printf("nome saida = %s\n", nomeArquivoSaida);

	if (arquivoEntrada != NULL && arquivoSaida != NULL)
	{
		lendoLinha(arquivoEntrada, nomeArquivoSaida);

		// fclose(arquivoSaida);
		fclose(arquivoEntrada);

	}
	else
	{
		printf("nao consegui abrir o arquivo\n");
	}


	return 0;
}