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
	int i =0,j = 1, k, fim,m, posicao = 1;
	TS * tabelaSims = NULL;
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
		fim = Analise (linha, ptr_file, tabelaSims, numSim);

		if(fim)
		{
			break;
		}

		EscreveNumLinha(linha, j);

        for(k = 0; k < linha->numTokens; k++)
        {
        	printf("ABCD\n");
			
			if(!verificaSeInstrucao(linha->Tokens[k]) && !verificaSeDiretiva(linha->Tokens[k]) )
            {
            	printf("ABCD2\n");

            	

                //printf("AAA111\n");
                //numSim[0]++;
                tabelaSims =  insereSimbolo( tabelaSims, linha->Tokens[k],posicao, 1,numSim );
                printf("ABCD3\n");
                //printTabelaSims( tabelaSims,numSimbolos);
                posicao++;

                for(m = 0; m< numSim[0]; m++ )
                { 
                    printf(" AAAA FORA2 m = %d,  %s\n",m,  tabelaSims[m].simbolo.nome);
                }
            
            }
	    }



		j++;

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



