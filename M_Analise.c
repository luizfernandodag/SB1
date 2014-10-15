#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NumInstr 14
#define NumDire 9

#include "M_Analise.h"
#include "testeLuiz.h"


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
/*int j;
printf("strlen = %d \n",i);
for(j = 0; j<=i; j++)
{
    printf("j = %d c = %c\n", j,Token[j]);
}*/

    if(Token[i-1]==':')
    {
        
        return 1;
    }
    else
    {
        return 0;
    }
}

char * obtemNomeLabel(char * Token)
{
   int i;

    if(verificaSeDefiniToken(Token))
    { 
        int size = strlen(Token);
        char * stringOut = (char *)malloc(size*sizeof(char));

        for ( i = 0; i < size-1; i++)
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
    diretivas[7] = "DATA";
    diretivas[8] = "TEXT";

    
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



int verificaErroToken(char * Token, int posicao )
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
                return 0;            
   
            }
            

        }
        else
        {
            if( i == size -1)
            {
                if(!( isalpha(c) || isdigit(c) || c == '_' || c == ':'))
                {
                    return 0;
                }   

        
            }
            else if(!( isalpha(c) || isdigit(c) || c == '_') )
            {
                if((c != '_') || (c != ':') ) 
                {
                    return 0;
                }
            }
       }


   }

  // printf("77777AAA\n");
return 1;
   
}



/*TS * insereLinhaTab (TS * tabSim,infoLinha Linha, int NumSim)
{
    int i = 0;



    for (i = 0; i < Linha.numTokens; i++)
    {
        
     tabSim = (TS *) realloc(tabSim, (NumSim+i+1)*sizeof(TS));

     tabSim[ NumSim+i+1].simbolo.nome = Linha.Tokens[i];


    }

    return tabSim;
}*/
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

TS* buscaTS (TS* lista, char *nome)
{
    TS* p;
    for (p = lista; p!= NULL; p = p->prox){
        if (!strcmp(p->nome, nome)){
            return p;           
        }       
    }
    return NULL;
}



void printfPilhaPos(pilhaPos * lista)
{

  pilhaPos* p;
  int i =  0, j;

    for (p = lista; p!= NULL; p = p->pilhaPosProx){
         i++;
        }
}



pilhaPos * inserePilhaPos(pilhaPos* p, int posicao)
{
    pilhaPos* pilhaAUX = (pilhaPos*) malloc(sizeof(pilhaPos));

    
    pilhaAUX->pos = posicao;
    pilhaAUX->pilhaPosProx = p;

    return pilhaAUX;
}

void atualizaTS(TS * lista,char * nome, int pos)
{

   TS * listaAUX = (TS*)malloc(sizeof(TS));

   int definido = verificaSeDefiniToken(nome);
   char *nomeLabel;
   nomeLabel = (char *)malloc(strlen(nome)*sizeof(char));
   nomeLabel = obtemNomeLabel(nome);
  // printf("nome = %s, nomeLabel = %s\n", nome, nomeLabel );
//   int ap = contaNumAparicoes(lista);
        
//printf("ap1 = %d\n",ap ); 
   listaAUX = buscaTS(lista, nomeLabel);
   if(definido)
   {
//printf("DEFINI ATUALIZA \n");
//printf("nome = %s\n", nome );

    //printf("BBBBBBB\n ");
    //listaAUX->numAparicoes++;
    //listaAUX->pilhaDePosicoes = (int *)realloc(listaAUX->pilhaDePosicoes, (listaAUX->numAparicoes)*sizeof(int));
    //listaAUX->pilhaDePosicoes[listaAUX->numAparicoes] = pos;
    //printf("CCCCC\n");
    listaAUX->valor = pos;
    //printf("AAAAA\n");
    listaAUX->def = 1;
    //printf("AAAAABBBBB\n");
    //listaAUX->valido = 1;//MODIFICAR AQUI DEPOIS
    //printf("AAAAACCCCC\n");
    }
    else
    {
     //   printf("NAO DEFINI ATUALIZA \n"); 
    listaAUX->numAparicoes++;

    listaAUX->pilhaDePosicoes = inserePilhaPos(lista->pilhaDePosicoes, pos);
    //listaAUX->valor = -1;
    //listaAUX->def = 0;
    //listaAUX->valido = 1;//MODIFICAR AQUI DEPOIS

    }
  //     ap = contaNumAparicoes(lista);
  //     int ap2= contaNumAparicoes(listaAUX);
  //printf("ap2 = %d,ap3 = %d\n",ap, ap2 ); 


}




TS* insereTS(TS* listaTS,  char *nome, int pos)   
{
    TS* listaAUX = (TS*) malloc(sizeof(TS));
    TS* listaAUXJaExiste = buscaTS(listaTS, nome);
    char *nomeLabel;
    pilhaPos *pilha = NULL;

    nomeLabel = (char *)malloc(strlen(nome)*sizeof(char));
    nomeLabel = obtemNomeLabel(nome);
     
    //nomeLabel = obtemNomeLabel(nome);
    //printf("Aqui\n");

    int defini = verificaSeDefiniToken(nome);
    //printf("definido = %d string = %s",definido, nome);
    //printf("defini = %d, nome = %s, nomeLabel = %s\n",defini, nome, nomeLabel);

    if(defini)
    {
     
    //printf("DEFINI INSERE \n"); 
     listaAUX->pilhaDePosicoes = pilha;
     listaAUX->nome = nomeLabel;
     listaAUX->valor = pos;
     listaAUX->def = 1;
     listaAUX->valido = verificaErroToken(nomeLabel,pos);//MODIFICAR AQUI DEPOIS
     listaAUX->numAparicoes = 1;

     listaAUX->prox = listaTS;

    }
    else
    {

        //printf("NAO DEFINI INSERE \n"); 
        listaAUX->pilhaDePosicoes = inserePilhaPos(pilha, pos);
        listaAUX->nome = nome;
        listaAUX->valor = -1;
        listaAUX->def = 0;
        listaAUX->valido = verificaErroToken(nome,pos);;//MODIFICAR AQUI DEPOIS
        listaAUX->numAparicoes = 2;
        listaAUX->prox = listaTS;

   }

   //int ap = contaNumAparicoes(listaAUX);
   // printf("ap = %d\n",ap ); 
        
        return listaAUX;
    //}

}

void printfTS(TS * lista)
{

  TS* p;
  int i =  1, j;

    for (p = lista; p!= NULL; p = p->prox){
         printf("i = %d, nome = %s, valor = %d, def = %d, valido = %d, apari = %d, \n",i, p->nome, p->valor, p->def, p->valido, p->numAparicoes);
         i++;
// for (j = 0; i < p->numAparicoes; ++i)
// {
//     /* code */
// }


        }
    

}



int contaSimbolosTS(TS *lista)
{
    TS * p;
    int i = 0;

    for (p = lista; p!= NULL; p = p->prox){
        
            i++;           
        
    }
    return i;
}

int verificaSections(infoLinha *linha)
{

    //printf("TOKEN[0] = %s, TOKEN[1] = %s\n",linha->Tokens[0], linha->Tokens[1] );
    //if(linha->numTokens == 2)
    //{
      //  printf("AQUI 1");
        if(!strcmp( maiuscula(linha->Tokens[0]), "SECTION")){
        //    printf("AQUI 2");
            if(!strcmp( maiuscula(linha->Tokens[1]), "DATA") ||!strcmp( maiuscula(linha->Tokens[1]), "TEXT")){
          //      printf("AQUI 3 retorno 1 nao soma\n");
              return 1;
            }
        }
    //}


   return 0;
}



TS * retornaTabelaSimbolos(infoLinha * linha, TS * tabelaSims,int  posicao) //int * numSim)
{   

    int k, m, numSimbolosDefinidos;
    numSimbolosDefinidos = contaSimbolosTS(tabelaSims);
    TS *listaAUX;
    int pos = posicao;
    

    for(k = 0; k < linha->numTokens; k++)
        {
         //   printf("token = %s\n", linha->Tokens[k] );
            char *nomeLabel;
            nomeLabel = (char *)malloc(strlen(linha->Tokens[k])*sizeof(char));

            nomeLabel = obtemNomeLabel(linha->Tokens[k]);
    
            //printf("ABCD\n");
            
            if(!verificaSeInstrucao(linha->Tokens[k]) && !verificaSeDiretiva(linha->Tokens[k]) && !verificaSeNumero(linha->Tokens[k]) )
            {
                //printf("ABCD2\n");

                //listaAUX = buscaTS(tabelaSims, linha->Tokens[k]);
                listaAUX = buscaTS(tabelaSims, nomeLabel);
                //printf("AQUI1");
                if(listaAUX == NULL)
                {   
                    //printf(" insere TOKEN[k] = %s\n", nomeLabel );
                    tabelaSims = insereTS( tabelaSims,  linha->Tokens[k], pos);
                }
                else
                {
                    //printf(" atualiza TOKEN[k] = %s\n", linha->Tokens[k] );
                    atualizaTS( tabelaSims,  linha->Tokens[k], pos);
                }

                //printf("AAA111\n");
                //numSim[0]++;
                //insere(TS* listaTS, int numAparicoes, int *pilhaDePosicoes, char *nome, int valor, int def, int valido)   
                //tabelaSims =  insere( tabelaSims, linha->Tokens[k],posicao, 1,numSim );
                //printf("ABCD3\n");
                //printTabelaSims( tabelaSims,numSimbolos);
                //posicao[0]++;
                
            }
           if( !verificaSections(linha))
            pos++;   
        }


    return  tabelaSims; 

}





