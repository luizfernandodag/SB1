#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Sintese.h"
#include "M_Passagem_Unica.h"
#include "M_Analise.h"



int main(int argc, char const *argv[])
{
	infoLinha *linha;
	FILE *ptr_file;
	int i =0,j = 1, fim;

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
		fim = Analise (linha, ptr_file);

		if(fim)
		{
			break;
		}

		EscreveNumLinha(linha, j);
		j++;
		
		printf("numTokens = %d\n", linha->numTokens);
		printf("numChars  = %d\n", linha->numChars);
		printf("numLinha = %d\n", linha->numLinha);
		printf("linha = %s\n", linha->linha);

		for ( i = 0; i < linha->numTokens; ++i)
		{
		printf("Tokens %d = %s\n",i, linha->Tokens[i]);
		}
		printf("\n");
		//free(linha);
		
	}

	


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



