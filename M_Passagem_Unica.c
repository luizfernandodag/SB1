#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Sintese.h"
#include "M_Passagem_Unica.h"
#include "M_Analise.h"



int main(int argc, char const *argv[])
{
	char arqSaida[] = "SAIDA.txt";

	infoLinha *linha;
	FILE *ptr_file;
	int i =0,j = 0, k, fim,m, posicao = 1, primeiraVez = 1;
	TS * tabelaSims = NULL;
	int * numSim;
	opLinha * linhas = NULL;
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
		fim = Analise (linha, ptr_file, tabelaSims, numSim);

		if(fim)
		{
			break;
		}

		EscreveNumLinha(linha, j);

		 j++;

		tabelaSims = retornaTabelaSimbolos(linha, tabelaSims,  posicao);
		if(!verificaSections(linha))
		posicao+= linha->numTokens;
       //fim Analise Lexica

		//AnaliseSintatica( linha, tabelaSims);

		linhas = AnaliseSintatica( linha, tabelaSims,linhas);
		//chamando a funcao de sintese para gerar o codigo objeto
		Sintese (linha, arqSaida, tabelaSims, primeiraVez);
		// Sintese (linha, arqSaida, primeiraVez);
		
	}
	printfTS(tabelaSims);


	//resolvePendencia(arqSaida, 3);
	//resolvePendencia(arqSaida, 6);

	fclose(ptr_file);

	return 0;
}



