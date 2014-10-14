#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Sintese.h"

assembly* carregaMenmonicos(assembly *listaAssembly);
assembly* insereAssembly(assembly* listaAssembly, char *mnemonico, int codigo, int tamanho);
void imprime (assembly* l);
TS* buscaSimbolo (TS* lista, char *nome);
assembly* buscaAssembly (assembly* lista, char *mnemonico);


//typedef struct Assembly assembly;


assembly* insereAssembly(assembly* listaAssembly, char *mnemonico, int codigo, int tamanho)
{
	assembly* listaAux = (assembly*) malloc(sizeof(assembly));

	// printf("#####################\n");
	// printf("imprimindo dentro de insere\n");
	// printf("Mnemonico = %s\n", mnemonico);
	// imprime(listaAssembly);
	// printf("###################\n\n");

	listaAux->mnemonico = mnemonico;
	listaAux->codigo = codigo;
	listaAux->tamanho = tamanho;

	listaAux->pa = listaAssembly;

	return listaAux;
}

assembly* buscaAssembly (assembly* lista, char *mnemonico)
{
	assembly* p;
 	for (p = lista; p!= NULL; p = p->pa){
 		if (!strcmp(p->mnemonico, mnemonico)){
 			return p;			
 		}		
 	}
 	return NULL;
}

TS* buscaSimbolo (TS* lista, char *nome)
{
	TS* p;
 	for (p = lista; p!= NULL; p = p->prox){
 		if (!strcmp(p->nome, nome)){
 			return p;			
 		}		
 	}
 	return NULL;
}

void imprime (assembly* l)
{
	assembly* p;
	int i = 0;
	for (p = l; p != NULL; p = p->pa)
	{
		printf("i = %d\n", i);
		printf("mnemonico = %s\n", p->mnemonico);
		//printf("codigo = %d\n", p->codigo);
		//printf("tamanho = %d\n", p->tamanho);	

		i++;
	}
	
}

assembly* carregaMenmonicos(assembly *listaAssembly)
{
	FILE *assembler;
	assembly *listaAux = NULL;
	int vez = 0;
	char *mnemonico;
	char separador;
	int codigo;
	int tamanho;

	

	assembler = fopen("assembly.txt", "r");

	printf("abri aqrquivo\n");
	while(!feof(assembler))
	{
		mnemonico = (char*) malloc(1*sizeof(char));
		fscanf(assembler, "%s %d %d %c", mnemonico, &codigo, &tamanho, &separador);

		listaAssembly = insereAssembly(listaAssembly, mnemonico, codigo, tamanho);

		// printf("#####################\n");
		// printf("imprimindo depois do insere\n");
		// printf("Mnemonico = %s\n", mnemonico);
		// imprime(listaAssembly);
		// printf("#####################\n\n");

		//free(mnemonico);



		// fscanf(assembler, "%d", &codigo);
		// fscanf(assembler, "%d", &tamanho);

		//printf("%s\n", mnemonico);
		//if (vez == 1)
		//{
			//listaAux = (assembly *) malloc(1*sizeof(assembly));
		//}

		// listaAux->mnemonico = mnemonico;
		// listaAux->codigo = codigo;
		// listaAux->tamanho = tamanho;

		// listaAux->pa = listaAssembly;

		// listaAssembly = listaAux;


		//return 0
	}
	// else{
	// 	return 1;
	// }

	free(mnemonico);

	return listaAssembly;
}

// void Sintese (infoLinha *linha, char *nomeArquivoSaida, TS *TabelaSimbolos, _Bool primeiraVez)
void Sintese (infoLinha *linha, char *nomeArquivoSaida, _Bool primeiraVez)
{
	_Bool status;
	assembly *listaAssembly = NULL, *resultadoBuscaAssembly;
	TS *resultadoBuscaSimbolo;
	FILE *saida;

	listaAssembly = carregaMenmonicos(listaAssembly);

	imprime (listaAssembly);

	if (primeiraVez)
	{
		saida = fopen(nomeArquivoSaida, "a");
		primeiraVez = 0;
	}
	else
	{
		saida = fopen (nomeArquivoSaida, "w");
	}
	

	for (int i = 0; i < linha->numTokens; ++i)
	{	
		//verifica se o simbolo é uma instrucao de assembly
		resultadoBuscaAssembly = buscaAssembly(listaAssembly, linha->Tokens[i]);

		//se o simbolo for uma instrucao ele grava
		if (resultadoBuscaAssembly != NULL)
		{
			fprintf(saida, "%d ", resultadoBuscaAssembly->codigo);
		}
		// else{
		// 	//se nao for instrucao ele procura na tabela de simbolo
		// 	resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha->Tokens[i]);

		// 	//se for um simbolo ele grava
		// 	if (resultadoBuscaSimbolo != NULL)
		// 	{
		// 		fprintf(saida, "%d ", resultadoBuscaSimbolo->valor);
		// 	}
		// }
	}




	fclose(saida);
	
}


// void resolvePendencia(char *nomeArquivoSaida, TS *TabelaSimbolos)
void resolvePendencia(char *nomeArquivoSaida, int posicao)
{
	FILE *saida;
	int numero, contPosicao = -1;

	saida = fopen (nomeArquivoSaida, "w");

	while(contPosicao < posicao)
	{
		fscanf(saida, "%d", &numero);
		contPosicao++;
	}

	fseek(saida, 2, SEEK_CUR);

	fprintf(saida, "77");


}



// void pegaLista(struct Teste *lista, int numero)
// {
// 	// lista = (struct Teste *) malloc(1*sizeof(struct Teste));

// 	lista->numero = numero;

// 	printf("lista = %d\n", lista->numero);

// }


