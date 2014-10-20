#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Erros.h"



//funcao principal que mostra os erros na tela
void MostraErros(void)
{
	FILE *erros;
	int erro, linha;
	char separador;
	_Bool temErro = 0;

	erros = fopen("erros.txt", "r");

	while(!feof(erros))
	{
		fscanf(erros, "%d %d %c", &erro, &linha, &separador);

		switch(erro)
		{
			case 1:
				printf("Erro Léxico: linha %d\n", linha);
				temErro = 1;
				break;
			case 2:
				printf("Erro Sintático: linha %d\n", linha);
				temErro = 1;
				break;
			case 3:
				printf("Erro Semântico: linha %d\n", linha);
				temErro = 1;
				break;
			case 4:
				printf("Erro Macro sem limitador de END: linha %d\n", linha);
				temErro = 1;
				break;
			default:
				break;
		}
	}

	if (!temErro)
	{
		printf("Código sem erro de implementação!\nParabéns!!\n\n");
	}

	fclose(erros);
}