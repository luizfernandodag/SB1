#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// #include "M_Sintese.h"
#include "testeLuiz.h"
#include "M_Analise.h"



int main(int argc, char const *argv[])
{
	infoLinha *linha;
	/*char * teste1 = "NEW_DATA", *teste2 = "OLD_DATA";

    if(!strcmp(teste1,teste2))
    	printf("IGAULLLLL\n");*/

	FILE *ptr_file;
	int i =0,j = 0, k, fim,m;
	int posicao;
	//posicao = (int*)malloc(1*sizeof(int));
	posicao = 0;
	TS * tabelaSims = NULL;
    opLinha * linhas = NULL;
		

	//tabelaSims = NULL;
	int * numSim;
	numSim = (int *)malloc(1*sizeof(int));
	numSim[0] = 0;

	ptr_file =fopen(argv[1],"r");

    if (!ptr_file)
    { 
        return 1;
	}

	linha = (infoLinha *) malloc(1*sizeof(infoLinha));
    //ini(linha);
	//while (!feof(ptr_file))
	//for (j = 0; j < 22; j++)
    while(1)
	{
		//Comeco Analise Lexica
		fim = Analise (linha, ptr_file, tabelaSims, numSim);

		if(fim)
		{
			break;
		}

		EscreveNumLinha(linha, j);
		j++;// NAO APAGAR  ISSO !!!!
		tabelaSims = retornaTabelaSimbolos(linha, tabelaSims,  posicao);


		if(!verificaSections(linha))
		posicao+= linha->numTokens;
       //fim Analise Lexica

		linhas = AnaliseSintatica( linha, tabelaSims,linhas);


		//printfTS(tabelaSims);
        
//retornaTabelaSimbolos(infoLinha * linha, TS * tabelaSims,int  posicao) //int * numSim)
		//printf("POS  entrei = %d\n",posicao);
        //printf("POS sai = %d\n",posicao);
       

		//printf("numTokens = %d\n", linha->numTokens);
		//printf("numChars  = %d\n", linha->numChars);
		//printf("numLinha = %d\n", linha->numLinha);
		//printf("linha = %s\n", linha->linha);

		// for ( i = 0; i < linha->numTokens; ++i)
		// {
		// printf("Tokens %d = %s\n",i, linha->Tokens[i]);
		// }
		// printf("\n");
		//free(linha);
		
	}

	printfTS(tabelaSims);


	// listaNo = (struct Teste *) malloc(1*sizeof(struct Teste));

	// pegaLista(lista, 10);

	// pegaLista (listaNo, 20);

	// printf("vou ligar a lista\n");

	// lista->pt = listaNo;

	// printf("liguei a lista com lista\n");

	// getchar();

	// for (int i = 0; i < 2; ++i)
	// {
	// 	printf("Lista = %d\n", lista->numero);
	// 	lista = lista->pt;
	// }
	

	fclose(ptr_file);

	return 0;
}



