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
void resolvePendencia(char *nomeArquivoSaida, int posicao, int valor);


//função que insere os mnemonicos de assembly em uma lista encadeada
assembly* insereAssembly(assembly* listaAssembly, char *mnemonico, int codigo, int tamanho)
{
	assembly* listaAux = (assembly*) malloc(sizeof(assembly));

	listaAux->mnemonico = mnemonico;
	listaAux->codigo = codigo;
	listaAux->tamanho = tamanho;

	listaAux->pa = listaAssembly;

	return listaAux;
}

//funcao que busca na lista de mnemonicos assembly o mnemonico que eu quero
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

//funcao busca na tabela de simbolos o simbolo que eu quero
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

//função cujo motivo principal é o debug, pois imprimi na tela a lista encadeada
void imprime (assembly* l)
{
	assembly* p;
	int i = 0;
	for (p = l; p != NULL; p = p->pa)
	{
		printf("i = %d\n", i);
		printf("mnemonico = %s\n", p->mnemonico);
		printf("codigo = %d\n", p->codigo);
		printf("tamanho = %d\n", p->tamanho);	

		i++;
	}
	
}

//funcao principal que constroi a lista encadeada de mnemonicos
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

//funcao principal do modulo que gera o cógigo objeto, porem ainda não resolve as pendencias
void Sintese (infoLinha *linha, char *nomeArquivoSaida, TS *TabelaSimbolos, int *primeiraVez)
// void Sintese (infoLinha *linha, char *nomeArquivoSaida, _Bool primeiraVez)
{
	_Bool status;
	assembly *listaAssembly = NULL, *resultadoBuscaAssembly;
	TS *resultadoBuscaSimbolo;
	FILE *saida;
	char *EhValido;
	int valor;

	listaAssembly = carregaMenmonicos(listaAssembly);


	saida = fopen(nomeArquivoSaida, "a");
	

	for (int i = 0; i < linha->numTokens; ++i)
	{	
		//verifica se o simbolo é uma instrucao de assembly
		resultadoBuscaAssembly = buscaAssembly(listaAssembly, linha->Tokens[i]);

		//se o simbolo for uma instrucao ele grava
		if (resultadoBuscaAssembly != NULL)
		{
			if (resultadoBuscaAssembly->codigo > 9)
			{
				fprintf(saida, " %d", resultadoBuscaAssembly->codigo);
			}
			else
			{
				fprintf(saida, " 0%d", resultadoBuscaAssembly->codigo);	
			}

			
		}
		else{

			EhValido = strstr(linha->Tokens[i], ":");


			if (EhValido == NULL)
			{
				//se nao for instrucao ele procura na tabela de simbolo
				resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha->Tokens[i]);

				//se for um simbolo ele grava
				if (resultadoBuscaSimbolo != NULL)
				{
					printf("SIMBOLO EhValido = %s\n", linha->Tokens[i]);
					printf("Valor = %d\n", resultadoBuscaSimbolo->valor);
					printf("OFFSET = %d\n", resultadoBuscaSimbolo->offset);

					valor = resultadoBuscaSimbolo->valor;

					if (resultadoBuscaSimbolo->offset != 0)
					{
						valor = resultadoBuscaSimbolo->valor + resultadoBuscaSimbolo->offset +1;
					}

					if (valor < 0 || valor > 9)
					{
						fprintf(saida, " %d", valor);
					}
					else
					{
						fprintf(saida, " 0%d", valor);	
					}
					
					
				}
			}
		}
	}




	fclose(saida);
	
}


void resolveIndefinicoes(char *nomeArquivoSaida, TS *TabelaSimbolos)
{
	TS* simbolo;
	pilhaPos *pilha;

 	for (simbolo = TabelaSimbolos; simbolo!= NULL; simbolo = simbolo->prox)
 	{
 		printf("SIMBOLO = %s\n", simbolo->nome);
 		printf("VALOR = %d\n", simbolo->valor);
 
 		for (pilha = simbolo->pilhaDePosicoes; pilha != NULL; pilha = pilha->pilhaPosProx)
 		{
 			resolvePendencia(nomeArquivoSaida, pilha->pos, simbolo->valor);

 		}		
 	}

}


//funcao que resolve as pensadencias da tabela de simbolos
// void resolvePendencia(char *nomeArquivoSaida, TS *TabelaSimbolos)
void resolvePendencia(char *nomeArquivoSaida, int posicao, int valor)
{
	FILE *saida;
	int numero, contPosicao = 0, seek;
	char *subs, *token;
	fpos_t position;
	
	subs = (char*)malloc(sizeof(char*));
	token = (char*)malloc(sizeof(char*));

	sprintf(subs, "%d", valor);
	
	saida = fopen (nomeArquivoSaida, "r+");

	printf("POSICAO = %d\n", posicao);

	// while(contPosicao < posicao)
	// {
	// 	// fgetpos(saida, &position);
	// 	fscanf(saida, "%s", token);
	// 	contPosicao++;
	// }

	seek = (posicao-1) * 3;

	fseek(saida, seek, SEEK_SET);

	// fsetpos(saida, &position);

	fprintf(saida, " %s" , subs);

	// fprintf(saida, "77");

	rewind(saida);
	
	fclose(saida);

}




