#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Sintese.h"

assembly* carregaMenmonicos(assembly *listaAssembly);
assembly* insere(assembly* listaAssembly, char *mnemonico, int codigo, int tamanho);
void imprime (assembly* l);

//typedef struct Assembly assembly;


assembly* insere(assembly* listaAssembly, char *mnemonico, int codigo, int tamanho)
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

void imprime (assembly* l)
{
	assembly* p;
	for (p = l; p != NULL; p = p->pa)
	{
		printf("mnemonico = %s\n", p->mnemonico);	
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

		listaAssembly = insere(listaAssembly, mnemonico, codigo, tamanho);

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

//void Sintese (infoLinha *linha, char *nomeArquivoSaida)
int main(int argc, char const *argv[])
{
	_Bool status;
	assembly *listaAssembly = NULL;

	// listaAssembly = (assembly *) malloc(1*sizeof(assembly));

	//status = carregaMenmonicos(listaAssembly);

	//while(status == 0)
	//{

	listaAssembly = carregaMenmonicos(listaAssembly);
	//}

	imprime(listaAssembly);
	// while(listaAssembly != NULL)
	// {
	// 	printf("mnemonico = %s\n", listaAssembly->mnemonico);
	// 	printf("codigo = %d\n", listaAssembly->codigo);
	// 	printf("tamanho = %d\n", listaAssembly->tamanho);
	// 	printf("###################################\n\n");

	// 	listaAssembly = listaAssembly->pa;
	// }


	return 0;
	
}




// void pegaLista(struct Teste *lista, int numero)
// {
// 	// lista = (struct Teste *) malloc(1*sizeof(struct Teste));

// 	lista->numero = numero;

// 	printf("lista = %d\n", lista->numero);

// }


