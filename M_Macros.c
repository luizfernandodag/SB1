#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Macros.h"

void gravaLinha(char *, char *);
macro* insereMacro(macro* listaMacro, char *nome, linha_Macro *listaLinhaMacro);
void lendoLinha(FILE *arquivoEntrada, char *NomeArquivoSaida);
char * separaTokens(char *PrimeiroToken, char *SegundoToken, char *linha);
macro* buscaMacro (macro* listaMacros, char *nome);
macro* guardandoMacro(macro *macro, FILE *arquivoEntrada, char *linha);
void gravaMacro(char *NomeArquivoSaida, macro *resultadoBusca);
linha_Macro* insereLinhaMacro(linha_Macro* listaLinhaMacro, char *linha);
linha_Macro* tamanhoCodigo (linha_Macro *);


void gravaLinha(char *NomeArquivoSaida, char *linha)
{
	FILE *arquivoSaida;

	arquivoSaida = fopen(NomeArquivoSaida, "a");

	strcat(linha,"\n");
	fprintf(arquivoSaida, "%s", linha);

	fclose(arquivoSaida);
}

macro* buscaMacro (macro* listaMacros, char *nome)
{
	macro *macro;

 	for (macro = listaMacros; macro != NULL; macro = macro->pm){
 		if (!strcmp(macro->nome, nome))
 		{
 			return macro;			
 		}		
 	}

 	return NULL;
}


void gravaMacro(char *NomeArquivoSaida, macro *resultadoBusca)
{
	FILE *arquivoSaida;
	linha_Macro *codigo, *ultimo_elemento;
	int tamanho, contador = 0;

	arquivoSaida = fopen(NomeArquivoSaida, "a");

	ultimo_elemento = tamanhoCodigo(resultadoBusca->codigo);

	while(ultimo_elemento != resultadoBusca->codigo)
	{
		fprintf(arquivoSaida, "%s\n", ultimo_elemento->linha);
		
		ultimo_elemento = ultimo_elemento->pla;
	}

	fprintf(arquivoSaida, "%s\n", ultimo_elemento->linha);

	fclose(arquivoSaida);
}

//função que insere os as linhas do codigo de uma macro
linha_Macro* insereLinhaMacro(linha_Macro* listaLinhaMacro, char *linha)
{
	linha_Macro* listaAux = (linha_Macro*)malloc(sizeof(linha_Macro));
	listaAux->linha = (char*)malloc(sizeof(char*));

	strcpy(listaAux->linha, linha);

	listaAux->pl = listaLinhaMacro;
	
	if (listaLinhaMacro != NULL)
	{
		listaLinhaMacro->pla = listaAux;
	}

	return listaAux;
}


linha_Macro* tamanhoCodigo (linha_Macro *lista)
{
	linha_Macro *p, *ultimo_elemento;
	int tamanho = 0;

	for (p = lista; p != NULL; p = p->pl)
	{	
		ultimo_elemento = p;
		tamanho++;
	}
	
	return ultimo_elemento;
}


void lendoLinha(FILE *arquivoEntrada, char *NomeArquivoSaida)
{
	char *linha, *ehMacro;
	macro *macro = NULL, *resultadoBusca;

	linha = (char*)malloc(sizeof(char*));

	//lendo linha do arquivo
	fscanf(arquivoEntrada, "%[^\n]%*c", linha);


	while(!feof(arquivoEntrada))
	{
		ehMacro = strstr(linha, "MACRO");

		if (ehMacro != NULL)
		{
			macro = guardandoMacro(macro, arquivoEntrada, linha);
		}
		else
		{
			resultadoBusca = buscaMacro (macro, linha);

			if (resultadoBusca != NULL)
			{
				gravaMacro(NomeArquivoSaida, resultadoBusca);
			}
			else
			{
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
	
	linha_Macro *linhaCodigo = NULL;

	linhaMacro = (char*)malloc(sizeof(char*));

	fscanf(arquivoEntrada, "%[^\n]%*c", linhaMacro);

	while(strcmp(linhaMacro, "ENDMACRO"))
	{
		linhaCodigo = insereLinhaMacro(linhaCodigo, linhaMacro);
		fscanf(arquivoEntrada, "%[^\n]%*c", linhaMacro);
	}

	nomeMacro =	(char *)malloc(sizeof(char*));
	nomeMacro = (char*)strtok (linha,": ");
	NAME =	(char *)malloc(sizeof(char*));	
	strcpy(NAME, nomeMacro);

	macro = insereMacro(macro, NAME, linhaCodigo);

	// free(nomeMacro);
	// free(NAME);
	// free(linhaMacro);
	
	return macro;

}


//função que insere os mnemonicos de assembly em uma lista encadeada
macro* insereMacro(macro* listaMacro, char *nome, linha_Macro *listaLinhaMacro)
{
	macro* listaAux = (macro*) calloc(1, sizeof(macro));

	listaAux->nome = nome;
	listaAux->codigo = listaLinhaMacro ;

	listaAux->pm = listaMacro;

	return listaAux;
}


// void resolveMacro (char *nomeArquivo)
int main(int argc, char *argv[])
{
	
	FILE *arquivoEntrada, *arquivoSaida;
	char *nomeArquivoSaida;

	arquivoEntrada = fopen(argv[1], "r");

	nomeArquivoSaida = (char*)argv[2];
	strcat(nomeArquivoSaida, ".mcr");
	arquivoSaida = fopen(nomeArquivoSaida, "w");

	fclose(arquivoSaida);

	if (arquivoEntrada != NULL && arquivoSaida != NULL)
	{
		lendoLinha(arquivoEntrada, nomeArquivoSaida);

		fclose(arquivoEntrada);

	}
	else
	{
		printf("nao consegui abrir o arquivo\n");
	}


	return 0;
}