#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NumInstr 14
#define NumDire 7

#include "M_Analise.h"


// typedef struct 
// {
//     int numTokens;
//     int numChars;
//     int numLinha;
//     char * linha;
//     char **Tokens;
   

// }infoLinha;

// typedef struct
// {
//     int numAparicoes;
//     int * Val;
//     char * nome;

// }ListaSim;

// typedef struct 
// {
//     ListaSim simbolo;
//     int valor;
//     int def;
//     int valido;

// }TS;



typedef struct 
{
    int NumLinha;
    int TipoErro;

}erros;


char ** instrucoes ;
char ** diretivas ;
// infoLinha * Linhas;
//TS * tabelaSims = NULL;
int * LinhaAtual, * NumErros, * posAtual;

int verificaSeDefiniToken(char * Token)
{

    int i = strlen(Token);

    if(Token[i-1]==':')
        return 1;
    else
        return 0;
}

char * obtemNomeLabel(char * Token)
{
   int i;

    if(verificaSeDefiniToken)
    { 
        int size = strlen(Token) - 1;
        char * stringOut = (char *)malloc(size*sizeof(char));

        for ( i = 0; i < size; i++)
        {
            stringOut[i] = Token[i];
        }

        stringOut[size] = '\0';

        return stringOut;
    }
    else
    {
        return Token;
    }
}









void ini(infoLinha * Linhas)
{
    instrucoes = (char **)malloc(NumInstr*sizeof(char *));
    diretivas = (char **) malloc(NumDire*sizeof(char *));
    //LinhaAtual = (int *)malloc(1*sizeof(int));
    //LinhaAtual[0] = 0;
    //Linhas = NULL;
    NumErros = (int *)malloc(1*sizeof(int));
    NumErros[0] = 0;

    //numSimbolos = (int *)malloc(1*sizeof(int));
    //numSimbolos[0] = 0;
    
    

    int i = 0;

    for(i = 0 ;i < NumInstr;i++)
    instrucoes[i] = (char *)malloc(10*sizeof(char ));

    for(i = 0 ;i < NumDire;i++)
    diretivas[i] = (char *)malloc(10*sizeof(char ));


    instrucoes[0] = "ADD"; //1
    instrucoes[1] = "SUB";// = 2,
    instrucoes[2] = "MULT";// = 3,
    instrucoes[3] = "DIV";// = 4,
    instrucoes[4] = "JMP";// = 5,
    instrucoes[5] = "JMPN";// = 6,
    instrucoes[6] = "JMPP";// = 7,
    instrucoes[7] = "JMPZ";// = 8,
    instrucoes[8] = "COPY";// = 9,
    instrucoes[9] = "LOAD";// = 10,
    instrucoes[10] = "STORE";// = 11,
    instrucoes[11] = "INPUT";// = 12,
    instrucoes[12] = "OUTPUT";// = 13,
    instrucoes[13] = "STOP";// = 14

    diretivas[0] = "SECTION";
    diretivas[1] = "SPACE";
    diretivas[2] = "CONST";
    diretivas[3] = "EQU";
    diretivas[4] = "IF";
    diretivas[5] = "MACRO";
    diretivas[6] = "END";
    
    //simbolos = (ListaSim *)realloc(simbolos, 1*sizeof(ListaSim);
    
        


}

char * retiraEspaco(char * Token)
{
    char * stringOut;
//printf("AQUII 44444AAAA = %s\n",Token);
    int i, j = 0, tamanhoReal = 0;

    for(i = 0; i< strlen(Token);i++)
    {
        if(Token[i] != ' ')
            tamanhoReal++;
    }
//printf("AQUI 4444BBBBBBB\n");
    stringOut = (char *)malloc(tamanhoReal*sizeof(char));

    for(i = 0; i< strlen(Token);i++)
    {
        if(Token[i] != ' ' && (isdigit(Token[i]) || isalpha(Token[i]) || Token[i] == '_' || Token[i] == ':'))
            {
                stringOut[j] = Token[i];
                j++;
                //printf("out = %c", stringOut[j]);
            }

    }

    //printf("AQUII 44444CCCCC\n");

    stringOut[j] = '\0';
    //printf("%s\n",stringOut );


    return stringOut;


}

char * maiuscula(char *string)
{
    int i;
    char *stringOut;
//printf("AQUII 3333AAAA\n");
    string = retiraEspaco(string);
    stringOut = ( char *)malloc(strlen(string)*sizeof(char));
    
    for(i=0;i<strlen(string);i++)
    {
        stringOut[i]=toupper(string[i]);
    }
//printf("AQUII 3333\n");

    return stringOut;
}

int verificaSeInstrucao(char * Token)
{
 int i, j = 0;
 char * UPtoken = maiuscula(Token);
 //printf("AQUII 22222 AAAAA\n");
 //UPtoken = retiraEspaco(UPtoken);

    for( i = 0;i < NumInstr ; i++)
    {
        if(!strcmp(UPtoken,instrucoes[i]))
        {    
            j = i+1;
        }

    }

//printf("AQUII 22222\n");
 return j ;

}

int verificaSeDiretiva(char * Token)
{
 int i, j = 0;
 //printf("AQUII 55555AAAA\n");
 char * UPtoken = maiuscula(UPtoken);
   // UPtoken = retiraEspaco(Token);
    for( i = 0;i < NumDire ; i++)
    {
        if(!strcmp(UPtoken,diretivas[i]))
        {    
            j = i+1;
        }

    }

   // printf("AQUII 5555\n");


 return j ;

}

int verificaSeNumero( char *token)
{
   int i;

   //printf("AQUII 66666 AAAA\n");
   token = retiraEspaco(token);


//printf("%s\n", token);


   for ( i = 0; i < strlen(token); i++)
   {   //printf("%c", token[i]);
            
       //if(!(isdigit(token[i])||  (  (i == 0 && token[i] =='0') && ( i + 1 == 1) && token[i+1] == 'x'  ) || (token[i] == '.' && i < strlen(token) -1 ) ))
        if(!(isdigit(token[i])||(i == 0 && token[i] =='0') || ( i == 1) && token[i] == 'x'||(token[i] == '.' && i < strlen(token) -1 )))
            return 0;
   }
//printf("AQUII 66666\n");
   return 1;

}

void printErros(erros *errosInfo, int * NumErros)
{
   int i;

   int NumLinha;
    int TipoErro;


   for (i = 0; i < NumErros[0]; i++)
   {
     //printf("\n  Erro %d, Linha = %d, Tipo = %d", i, errosInfo[i].NumLinha, errosInfo[i].TipoErro);
   }



}



erros * verificaToken(char * Token, int linha,erros *errosInfo, int * NumErros, int posLinha  )
{
   int i, size, ehInstrucao, ehDiretiva;
   char c;
   size = strlen(Token);

//printf("AQUII 777777\n");

   //printf("\nNumErros = %d, \nString = %s size = %d \n", NumErros[0], Token, size);
   


   if(!verificaSeNumero( Token))  
   for (i = 0; i < size; i++)
   {    
        c = Token[i]; 
       
       if(i == 0)
        {   
            
            if(!(isalpha(c) || c == '_') || isdigit(c) )
            {
               //printf("\nAqui 1 ERROOOOOOOOOOOOOO \n");
               errosInfo = (erros *)realloc(errosInfo, (NumErros[0]+1)*sizeof(erros));
               errosInfo[NumErros[0]+1].NumLinha = linha;
               errosInfo[NumErros[0]+1].TipoErro = 1; // 1 =Erro Lexico
               NumErros[0]++;

            }
            

        }
        else
        {
            if( i == size -1)
            {
                if(!( isalpha(c) || isdigit(c) || c == '_' || c == ':'))
                {
                  //  printf("\nAqui 2 ERROOOOOOOOOOOOOO \n");
                    errosInfo = (erros *)realloc(errosInfo, (NumErros[0]+1)*sizeof(erros));   
                    errosInfo[NumErros[0]+1].NumLinha = linha;
                    errosInfo[NumErros[0]+1].TipoErro = 1; // 1 =Erro Lexico
                    NumErros[0]++;
                }   

        
            }
            else if(!( isalpha(c) || isdigit(c) || c == '_') )
            {
                if((c != '_') || (c != ':') ) 
                {
                    //printf("\nAqui 3 ERROOOOOOOOOOOOOO \n");

                    errosInfo = (erros *)realloc(errosInfo, (NumErros[0]+1)*sizeof(erros));   
                    errosInfo[NumErros[0]+1].NumLinha = linha;
                    errosInfo[NumErros[0]+1].TipoErro = 1; // 1 =Erro Lexico
                    NumErros[0]++;
                }
            }
       }


   }

  // printf("77777AAA\n");
return errosInfo;
   
}



TS * insereLinhaTab (TS * tabSim,infoLinha Linha, int NumSim)
{
    int i = 0;



    for (i = 0; i < Linha.numTokens; i++)
    {
        
     tabSim = (TS *) realloc(tabSim, (NumSim+i+1)*sizeof(TS));

     tabSim[ NumSim+i+1].simbolo.nome = Linha.Tokens[i];


    }

    return tabSim;
}
/*
char * lerToken(FILE *ptr_file, int j)

Funcao para ler um token na linha atual

ARGUMENTOS: 
FILE *ptr_file: Ponteiro para um arquivo


SAIDA:
LINHA atual (String) 



*/
char * lerToken(FILE *ptr_file)
{   

    char * token = (char*)malloc(1*sizeof(char));
    char c;
    int i = 0;
    while((c = fgetc(ptr_file))!=' ')
    {    if ( c == '\n' || c ==-1)
        {
            break;
        }
         token[i] = c;
         token = realloc(token, (i+2)*sizeof(char));
         //printf("A%c", token[i]);
         i++;    
    }

    token[i] = '\0';
   
    return token;
}

//int verifica

/*
char * lerLinha(FILE *ptr_file, fpos_t  pos)

Função para ler a linha atual 

ARGUMENTOS: 
FILE *ptr_file: Ponteiro para um arquivo
fpos_t  pos: Posicao atual de leitura ou escrita no arquivo

SAIDA:
LINHA atual (String) 

*/


int lerLinha(FILE *ptr_file, fpos_t  pos,int * LinhaAtual ,infoLinha * Linhas)
{
	char c, cAntigo, *linha, *token;
    char ** tokensAUX;
    int i = 0, j = 0, numTokens = 0, tamanhoToken = 0;
    long int size;
    //printf("pos = %ld\n", ftell(ptr_file) );
    fpos_t  posAux;
    // Alocacao de espaco das strings
	linha = (char *)malloc(1*sizeof(char));// aloca espaço para a linha
    token = (char *)malloc(100*sizeof(char));// aloca espaço para o token
    fgetpos(ptr_file, &pos);
    // loop para ler a linha e guarda na variavel linha
    
    // alocar mais uma linha no ponteiro da struct
    //Linhas = (infoLinha *)realloc(Linhas, (LinhaAtual[0]+1)*sizeof(infoLinha));
    //Linhas[LinhaAtual[0]].numLinha = LinhaAtual[0]+1;



    
    //printf("\nLinha atual = %d\n", LinhaAtual[0]);
    LinhaAtual[0]++;

// Lendo a linha
    //printf("AAAAA\n");
    while((c = fgetc(ptr_file))!= '\n')
	{
        if(feof(ptr_file))
            return 1;

    if(c == -1)
    break;   
    //Se o caracter nao era espaco e agora eh, entao um token estava sendo lido
        if(i != 0)
        {
            if(cAntigo != ' ')
            {


                if( c == ' ')
                {

                    //Numero de tokens na linha
                    numTokens++;
                }
            }

        }
        cAntigo = c; 
        size = ftell(ptr_file);
     	linha[i] = c;
      //  printf("%c",c);
		i++;
        linha = (char *)realloc(linha,(i+1)*sizeof(char));
     
	}



    numTokens++;
    //marcacao do fim da string
    linha = (char *)realloc(linha,(i+1)*sizeof(char));	
    linha[i] = '\0';
  //  printf("BBBBBBB\n");
    Linhas->linha = (char *)malloc(strlen(linha)*sizeof(char));
    //printf("CCCCC\n" );
    Linhas->linha = linha;
    Linhas->numChars = i+1;
    //printf("%s\n", linha );
    //printf("\n Num Tokens = %d\n", numTokens);

	
	
     Linhas->Tokens = (char **)malloc(numTokens*sizeof(char *));
    
     j = 0;i = 0;
    // seguencia de instrucoes para ler token a token na linha
    c = fgetc(ptr_file);
    if(c != ' ' )
    fsetpos (ptr_file, &pos);
    //printf("\n");

    //Lendo todos os tokens da linha e guardando na estrutura
    for(i = 0;i<numTokens;i++)
    {
        token = lerToken(ptr_file);    
        Linhas->Tokens[i] = (char *)malloc(sizeof(token)*sizeof(char ));
        Linhas->Tokens[i] = token;
      //  printf("\nTOKEN = %s tamanho = %d",token, strlen(token));
    }

    
    Linhas->numTokens = numTokens;

    fgetpos(ptr_file,&pos);
    //fazer a posicao voltar ao final da linha
    fsetpos (ptr_file, &pos);
   
    return 0;

}

int procuraSimboloTS(char * Token, TS * tabelaSims, int * numSimbolos)
{
    int pos = -1;
    int i;

    printf("procuraSimboloTS 1\n");
    if(tabelaSims != NULL)
    for (i = 0; i < numSimbolos[0] ; i++)
    {printf("procuraSimboloTS 2\n");
        if(!strcmp(Token, tabelaSims[i].simbolo.nome))
         {
            printf("verifica TOKEN = %s, Tabela = %s, pos = %d\n", Token,tabelaSims[i].simbolo.nome, i );
            pos = i;
         }
    }
    printf("procuraSimboloTS 3 pos = %d\n", pos);

    return pos;


}

void printTabelaSims(TS * tabelaSims, int * numSimbolos)
{
    int i, j;
   printf("\n\n");
    for(i = 0; i< numSimbolos[0]; i++ )
    {
        printf(" i = %d,  %s, numAparicoes = %d , pilhaDePosicoes = ",i,  tabelaSims[i].simbolo.nome, tabelaSims[i].simbolo.numAparicoes );
        for(j = 0; j < tabelaSims[i].simbolo.numAparicoes; j++)
        {
        printf(" %d ",tabelaSims[i].simbolo.pilhaDePosicoes[j] );
        }

        //printf("\n");
        printf("DEF = %d VALIDO = %d\n", tabelaSims[i].def, tabelaSims[i].valido );


    }
}


TS * insereSimbolo(TS * tabelaSims, char * Token,int Val, int valido, int * numSimbolos )
{   

    int i, j, pos;
    //if(procuraSimboloTS(Token) != -1 )
    printf("AQUI1\n");
    pos = procuraSimboloTS(Token, tabelaSims, numSimbolos); 
    printf("AQUI2\n");
    //if(numSimbolos)
   // printf("i = %d, numSimbolos = %d \n", i, numSimbolos[0]);
    printf("AAAA2222\n");
    if( pos == -1)
    {
        numSimbolos[0]++;
        i =numSimbolos[0] - 1;
        printf("AAAA88888\n");
        tabelaSims = (TS *)realloc(tabelaSims, numSimbolos[0]*sizeof(TS));
        printf("AAAA3333\n");
      

        tabelaSims[i].simbolo.nome = (char *)malloc(strlen(Token)*sizeof(char));
        tabelaSims[i].simbolo.nome = Token;
        tabelaSims[i].simbolo.nome[strlen(Token)] = '\0';
        printf("\n");
          for(j = 0; j< numSimbolos[0]; j++ )
         { 
          printf(" DENTRO j = %d,  %s\n",j,  tabelaSims[j].simbolo.nome);
         }

        //printf("\n");
        


    

        printf("AAAA44444\n");
        
        tabelaSims[i].simbolo.numAparicoes = 1;
        if(!verificaSeDefiniToken(Token))
        {
            tabelaSims[i].simbolo.pilhaDePosicoes = NULL;//SERA????
            tabelaSims[i].simbolo.pilhaDePosicoes = (int *)realloc(tabelaSims[i].simbolo.pilhaDePosicoes, ( tabelaSims[i].simbolo.numAparicoes +1 )*sizeof(int));
            tabelaSims[i].simbolo.pilhaDePosicoes[0] = -1;
            tabelaSims[i].simbolo.pilhaDePosicoes[1] = Val;
            tabelaSims[i].def = 0;
          //  printf("AAAA55555\n");
          //  printf("nome = %s, numSimbolos = %d, val = %d, def = %d\n",tabelaSims[i].simbolo.nome, numSimbolos[0], tabelaSims[i].simbolo.pilhaDePosicoes[1], tabelaSims[i].def   );
        }
        else
        {
            tabelaSims[i].simbolo.pilhaDePosicoes = NULL;//SERA????
            tabelaSims[i].simbolo.pilhaDePosicoes = (int *)realloc(tabelaSims[i].simbolo.pilhaDePosicoes, (tabelaSims[i].simbolo.numAparicoes )*sizeof(int));
            tabelaSims[i].simbolo.pilhaDePosicoes[0] = -1;
            tabelaSims[i].valor = Val;
            tabelaSims[i].def= 1;
            //printf("nome = %s, numSimbolos = %d, val = %d, def = %d\n",tabelaSims[i].simbolo.nome, numSimbolos[0], tabelaSims[i].simbolo.pilhaDePosicoes[1], tabelaSims[i].def   );
            //printf("AAAA6666\n");    


        }

        //tabelaSims[i].valor = Val;

       // printf("AAAA77777\n");
        tabelaSims[i].valido = valido;

        printTabelaSims( tabelaSims,  numSimbolos);

    }
    else
    {

     printf("ELSE 11111\n");
        int topoPilhaPosicoes;
        tabelaSims[pos].simbolo.numAparicoes++;
        topoPilhaPosicoes = tabelaSims[pos].simbolo.numAparicoes;
//        printf("AAAA88888\n");
        printf("ELSE 22222\n");

        if(!verificaSeDefiniToken(Token))
        {
            //tabelaSims[i].simbolo.pilhaDePosicoes = NULL;//SERA????
            tabelaSims[pos].simbolo.pilhaDePosicoes = (int *)realloc(tabelaSims[i].simbolo.pilhaDePosicoes, ( tabelaSims[i].simbolo.numAparicoes +1 )*sizeof(int));
            tabelaSims[pos].simbolo.pilhaDePosicoes[topoPilhaPosicoes + 1] = Val;
            printf("ELSE 33333\n");
        }
        else
        {
            tabelaSims[pos].def= 1;    
            tabelaSims[pos].valor = Val;
            printf("ELSE 4444\n");

        }


  //      printf("AAAA99999\n");
    }
//printf("AAAA3333\n");

    //printTabelaSims( tabelaSims,  numSimbolos);
    return tabelaSims;
}




int LerArquivo( FILE *ptr_file, fpos_t  pos,int * LinhaAtual, infoLinha * Linhas, erros *errosInfo, int * NumErros, TS * tabelaSims, int * numSimbolos )
{
    int NumLinhas = 0, i = LinhaAtual[0], j, k,numErrosAux, fim;
    int posicao = 1, m;
    // char c;
    // while((c = fgetc(ptr_file))!= -1)
    // {
    //     if(c == '\n')
    //         NumLinhas++; 

    // }
    // NumLinhas++;
    //printf("NumLinhas = %d\n",NumLinhas );
    //rewind(ptr_file);

    numErrosAux = NumErros[0];

    //for(i = 0;i <= NumLinhas;i++)
    //{
        fim = lerLinha(ptr_file, pos,LinhaAtual, Linhas);
        //Linhas[LinhaAtual[0]].tokens.
       // LinhaAtual[0]++;
        
      
      for(j = 0;j< Linhas[i].numTokens; j++)
        {


            if(!verificaSeInstrucao(Linhas->Tokens[j]) && !verificaSeDiretiva(Linhas->Tokens[j]) )
            {
                //printf("\n %s nao eh instrucao nem diretiva", Linhas[i].Tokens[j]);
                //printf("EEEEEEERRRRRRRRRRRRRRROOOOOOOOOOOOOOOOOOO\n");
                //numSimbolos[0]++;
                errosInfo =  verificaToken(Linhas->Tokens[j], i  , errosInfo, NumErros,j  );
                printErros(errosInfo, NumErros);


                //printf("AAA111\n");
                //tabelaSims =  insereSimbolo( tabelaSims, Linhas->Tokens[j],posicao, 1,numSimbolos );
                
                //printTabelaSims( tabelaSims,numSimbolos);
                

                
            
            }



            
            
        }


    //}


    
    return fim;
}

FILE * argSemEspacos(FILE * ptr_file)
{

    FILE *semEspacos = fopen("semEspacos.txt", "w+");

    char c, cAntigo;
    int sai = 0; 
    c = ' ';
    cAntigo = c;

    while((c = fgetc(ptr_file)  ) != -1)
    {
        sai = 0;
        //if((cAntigo != ' ' || cAntigo != '\n')
          //  fputc(cAntigo, semEspacos);
        if(c != ' ' ||(cAntigo != ' ' && cAntigo != '\n' && c == ' ' ))
        fputc(c, semEspacos);
        
        while(c == ' ' || c == 9)
        {
            c = fgetc(ptr_file);
            sai = 1;
        }

        if(sai)
        fputc(c, semEspacos);


     cAntigo = c;
       
    }

    rewind(semEspacos);
    
    return semEspacos;
}

infoLinha * EscreveNumLinha(infoLinha * Linhas, int num)
{

    Linhas->numLinha = num;

    return Linhas;
}


int Analise (infoLinha *Linhas, FILE *ptr_file, TS * tabelaSims, int *numSimbolos)
{
    

    //verificacao quem irá fazer será a interface com o usuário
	// if(argc == 1)
	// {
	// 	printf("Digite o nome do arquivo no formato arg.txt ");
 //        return 0;
	// }
int fim;
    LinhaAtual = (int *)malloc(1*sizeof(int));
LinhaAtual[0] = 0;


   ini(Linhas);//INICIALIZAR AS VARIAVEIS GLOBAIS	

    




    

    // FILE *ptr_file;
    char buf[1000];
    char *linha;
	fpos_t  pos;
    long int size;
    //infoLinha * Linhas = NULL;
   // Linhas = NULL;
    erros *errosInfo = NULL;

    //Linhas.Tokens = NULL;
 
    int i, j;

    
    //verificacao que vai fazer á a interface com o usuário
 //    printf("\nNome do arquivo digitado: %s\n", argv[1]);

  //   ptr_file =fopen(argv[1],"r");

  //   if (!ptr_file)
  //   {
  //       return 1;
	 // }


    fgetpos (ptr_file, &pos);

    //colcoar essa funcao no modulo -p
    // FILE *semEspacos;
    //  semEspacos = argSemEspacos(ptr_file);




    fim = LerArquivo(ptr_file, pos, LinhaAtual, Linhas,errosInfo, NumErros, tabelaSims, numSimbolos);
    //printf("FFFFFFF\n");
        

   // fclose(ptr_file);
    //fclose(semEspacos);
    
    return fim;
    
}







