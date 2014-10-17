#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Pre_Processamento.h"


codigo* insereLinha(codigo* listaCodigo, char *linha);
void lendoLinha(FILE *arquivoEntrada, char *NomeArquivoSaida);
char* preparaLinha(char *linha);

//função cujo motivo principal é o debug, pois imprimi na tela a lista encadeada
void imprime (codigo* l)
{
	codigo* p;
	int i = 0;
	for (p = l; p != NULL; p = p->pl)
	{
		printf("linha = %s\n", p->linha);

		i++;
	}
	
}



//função que insere os as linhas do codigo
codigo* insereLinha(codigo* listaCodigo, char *linha)
{
	codigo* listaAux = (codigo*)malloc(sizeof(codigo));
	listaAux->linha = (char*)malloc(sizeof(char*));

	strcpy(listaAux->linha, linha);

	listaAux->pl = listaCodigo;
	
	if (listaCodigo != NULL)
	{
		listaCodigo->pla = listaAux;
	}

	return listaAux;
}


//funccao que le o arquivo e avalia se é uma macro ou nao
void lendoLinha(FILE *arquivoEntrada, char *NomeArquivoSaida)
{
	char *linha, *linha_preparada, new_line, primeiro_token, *linha_completa;
	codigo *implementacao = NULL;
	fpos_t position;

	linha = (char*)malloc(sizeof(char*));
	linha_preparada = (char*)malloc(sizeof(char*));
	linha_completa = (char*)malloc(sizeof(char*));

	//lendo linha do arquivo
	fgetpos(arquivoEntrada, &position);
	fscanf(arquivoEntrada, "%c", &primeiro_token);

	while(!feof(arquivoEntrada))
	{
		if (primeiro_token != '\n')
		{
			fsetpos(arquivoEntrada, &position);
			fscanf(arquivoEntrada, "%[^\n]", linha);
			fscanf(arquivoEntrada, "%c", &new_line);

			linha_preparada = preparaLinha(linha);
			implementacao = insereLinha(implementacao, linha_preparada);
		}
		
		fgetpos(arquivoEntrada, &position);
		fscanf(arquivoEntrada, "%c", &primeiro_token);
	}

	imprime(implementacao);

}

char* preparaLinha(char *linha)
{
	char *token;
	char *instrucao;
  	
  	instrucao = (char*)malloc(sizeof(char*));
  	token = strtok (linha," \t");

  	strcpy(instrucao, token);

  	while (token != NULL)
  	{
    	token = strtok (NULL, " \t");

    	if (token != NULL)
    	{
    		strcat(instrucao, " ");
    		strcat(instrucao, token);
    	}
    	
  	}

  	return instrucao;
}


int main(int argc, char const *argv[])
{
	FILE *entrada;

	entrada = fopen("triangulo.asm", "r");

	lendoLinha(entrada, "preSAIDA");
	return 0;
}