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
        if(Token[i] != ' ' && (isdigit(Token[i]) || isalpha(Token[i]) || Token[i] == '_' || Token[i] == ':'|| Token[i] == '+' || Token[i] == '-'))
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
    //string = retiraEspaco(string);
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



int verificaErroToken(char * Token, int posicao, int op )
{
   int i, size, ehInstrucao, ehDiretiva;
   char c;
   size = strlen(Token);

//printf("AQUII 777777\n");

   //printf("\nNumErros = %d, \nString = %s size = %d \n", NumErros[0], Token, size);
   
// printf("ENTREI = %s\n",Token );

 if(size == 1 && op == 1 )
 {
    if(Token[0] == '+' || Token[0] == '-' )
        return 1;
 }

   if(!verificaSeNumero( Token))  
   for (i = 0; i < size; i++)
   {    
        c = Token[i]; 
       
        if(size > 1)
            if(c =='+' ||c == '-')
                return 0;

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
    linha = maiuscula(linha);
    Linhas->linha = linha;//retiraEspaco(linha);
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

        token = maiuscula(token);
        

        Linhas->Tokens[i] = retiraEspaco(token);
        

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

        //    printf("nome = %s, nomeobtido = %s\n", nome, p->nome );
            return p;           
        }       
    }
    //printf("nao achei %s\n",nome );
    return NULL;
}



void printfPilhaPos(pilhaPos * lista)
{

  pilhaPos* p;
  int i =  0, j;

    for (p = lista; p!= NULL; p = p->pilhaPosProx){
         printf(" %d", p->pos );
        }
}

void printfTS(TS * lista)
{

  TS* p;
  int i =  1, j;

    for (p = lista; p!= NULL; p = p->prox){
         printf("nome = %s, val = %d, def = %d, valido = %d, apari = %d, ", p->nome, p->valor, p->def, p->valido, p->numAparicoes);
         printfPilhaPos(p->pilhaDePosicoes);
         i++;
         printf("\n");
// for (j = 0; i < p->numAparicoes; ++i)
// {
//     /* code */
// }


        }
    

}


  
  
//diretivas[0] = "SECTION";
int verificaSeSection( char * Token)
{
  if(!strcmp(Token, "SECTION") )
        return 1;
    return 0;
 
}



    //diretivas[7] = "DATA";
    //diretivas[8] = "TEXT";


int verificaSeOpTipoSection(char * Token)
{

 if(!strcmp(Token, "DATA") || !strcmp(Token, "TEXT") )
        return 1;
    return 0;
   
}   

    //instrucoes[11] = "INPUT";// = 12,
    //instrucoes[12] = "OUTPUT";// = 13,

int verificaSeOpEntradaSaida(char * Token)
{
    if(!strcmp(Token, "INPUT") || !strcmp(Token, "OUTPUT") )
        return 1;
    return 0;

}




    //instrucoes[9] = "LOAD";// = 10,
    //instrucoes[10] = "STORE";// = 11,
int verificaSeOpMemoria(char * Token)
{

    if(!strcmp(Token, "LOAD") || !strcmp(Token, "STORE") )
        return 1;
    return 0;
}

int verificaSeMaisOuMenos(char * Token)
{

 if(!strcmp(Token, "+") || !strcmp(Token, "-") )
        return 1;
    return 0;   
}



    //instrucoes[0] = "ADD"; //1
    //instrucoes[1] = "SUB";// = 2,
    //instrucoes[2] = "MULT";// = 3,
    //instrucoes[3] = "DIV";// = 4,


int verificaSeOpAritmetica(char * Token)
{

  if(!strcmp(Token, "ADD") || !strcmp(Token, "SUB") ||!strcmp(Token, "MULT") || !strcmp(Token, "DIV"))
    return 1;

    return 0;
}



int verificaSeVariavel(char * Token)
{

    if(verificaSeNumero(Token) || verificaSeInstrucao(Token) || verificaSeDiretiva(Token) )
        return 0;
    if(strlen(Token) == 0 && (Token[0] == '+' || Token[0] == '-' ))
       return 0;

        return 1;
}



   // instrucoes[4] = "JMP";// = 5,
   // instrucoes[5] = "JMPN";// = 6,
   // instrucoes[6] = "JMPP";// = 7,
   // instrucoes[7] = "JMPZ";// = 8,
    

int verificaSeOpPulo(char * Token)
{
    
    if(!( !strcmp(Token, "JMPZ") ||!strcmp(Token, "JMPN") || !strcmp(Token, "JMP") || !strcmp(Token, "JMPP")  ))
        return 0;
    else
        return 1;


}



//instrucoes[8] = "COPY";// = 9,
  
int verificaSeOpCopy(char * Token)
{

   if(!strcmp(Token, "COPY"))
    return 1;

    return 0;
}

    
    //diretivas[1] = "SPACE";
    //diretivas[2] = "CONST";
    //diretivas[3] = "EQU";
    
int verificaSeOpAlocacaoMemoria(char * Token)
{
   if(!( !strcmp(Token, "SPACE") || !strcmp(Token, "CONST") || !strcmp(Token, "EQU") ))
        return 0;
    else
        return 1;
}

int verificaAritmeticaExtendida(infoLinha * linha)
{
    int numTokens = linha->numTokens;
    int i;
    int caso;
  


       if(numTokens >= 2)
       if(verificaSeDefiniToken(linha->Tokens[0]))
        {     
              if(!verificaSeOpAritmetica(linha->Tokens[1]))
              return 1; 
          caso = 0;
        }
        else
        {  

            if(!verificaSeOpAritmetica(linha->Tokens[0]))
                return 1;
            caso = 1;
        }

    //    printf("linha = %d caso %d,  numTokens = %d\n",linha->numLinha,caso, numTokens);

   if(caso)
   {
      if(numTokens > 4)
        return 1;
   }
   else
   {
      if(numTokens > 5)
        return 1;

   }

    for ( i = 0; i < numTokens; i++)
    {
    // printf(" i = %d %s\n", i, linha->Tokens[i]  );
     if(caso)// exemplo: ADD N + 1 + N2
     {
        if(i > 0)
        {

            if(i%2 == 0 && !verificaSeMaisOuMenos(linha->Tokens[i]))//CONTINUAR AAQQQQUIIII
            {//printf("A = %s \n", linha->Tokens[i]);
                return 1;
            }

            if(i%2 == 1 && !(verificaSeVariavel(linha->Tokens[i])  || verificaSeNumero(linha->Tokens[i])  ))
            {//printf("B = %s  \n", linha->Tokens[i]);
                return 1;
            }
        }

     }  
     else if(!caso)// exemplo: L1: ADD N +1 +N2
     {
        if(i > 1)
        {
           if(i%2 == 1 && !verificaSeMaisOuMenos(linha->Tokens[i]))//CONTINUAR AAQQQQUIIII
            {//printf("C = %s \n", linha->Tokens[i]);
                return 1;
            }

            if(i%2 == 0 && !(verificaSeVariavel(linha->Tokens[i]) || verificaSeNumero(linha->Tokens[i]) ))
            {//printf("D = %s \n", linha->Tokens[i]);
                return 1;
            }
        }

     } 

    }

return 0;

}





pilhaPos * inserePilhaPos(pilhaPos* p, int posicao)
{
    pilhaPos* pilhaAUX = (pilhaPos*) malloc(sizeof(pilhaPos));

    
    pilhaAUX->pos = posicao;
    pilhaAUX->pilhaPosProx = p;

    return pilhaAUX;
}

void EscreveArgErro(int linha, int TipoErro)
{

    FILE *argErros = fopen("erros.txt", "a");
    if (TipoErro == 1)
    {
        printf("Erro Lexico linha = %d \n", linha);
    }
    if (TipoErro == 2)
    {
        printf("Erro Sintatico linha = %d \n", linha);
    }
    if (TipoErro == 3)
    {
        printf("Erro Semantico linha = %d \n", linha);
    }
    

    fprintf(argErros, "%d %d |", TipoErro, linha);
    fclose(argErros);
}

int verificaSeOpAritmeticaLabel(infoLinha * linha)
{
  if(linha->numTokens >= 2)
  {
       if(verificaSeDefiniToken(linha->Tokens[0]))
        {     
              if(!verificaSeOpAritmetica(linha->Tokens[1]))
              return 1; 
          
        }
        else
        {  

            if(!verificaSeOpAritmetica(linha->Tokens[0]))
                return 1;
           
        }
  }
        return 0;
}

void atualizaTS(infoLinha *linha, TS * lista,char * nome, int pos, int Numlinha)
{

   TS * listaAUX = (TS*)malloc(sizeof(TS));

   int definido = verificaSeDefiniToken(nome);
   int op = 0;
   char *nomeLabel;
   nomeLabel = (char *)malloc(strlen(nome)*sizeof(char));
   nomeLabel = obtemNomeLabel(nome);
  // printf("nome = %s, nomeLabel = %s\n", nome, nomeLabel );
//   int ap = contaNumAparicoes(lista);
        
//printf("ap1 = %d\n",ap );
   if(verificaSeOpAritmeticaLabel(linha))
    op = 1;

   if(!verificaErroToken(nomeLabel,pos, op))
        EscreveArgErro(Numlinha, 1);

//printf("\nATUALIZA %s\n", nomeLabel ); 
   listaAUX = buscaTS(lista, nomeLabel);

   if(verificaSeMaisOuMenos(nome))
   {
    return;
   }
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
    //printf("INSERE %s pos = %d \n", nomeLabel, pos);
    //printf("nome = %s, val = %d, def = %d, valido = %d, apari = %d, ", listaAUX->nome, listaAUX->valor, listaAUX->def, listaAUX->valido, listaAUX->numAparicoes);
    //printfPilhaPos(listaAUX->pilhaDePosicoes);
    
    //printfTS(listaAUX); 
  //  printf("%s insere %d \n", nomeLabel,pos );
    listaAUX->pilhaDePosicoes = inserePilhaPos(listaAUX->pilhaDePosicoes, pos);
  //printf("\n");
  //   printfPilhaPos(listaAUX->pilhaDePosicoes);
    
    //listaAUX->valor = -1;
    //listaAUX->def = 0;
    //listaAUX->valido = 1;//MODIFICAR AQUI DEPOIS

    }
  //     ap = contaNumAparicoes(lista);
  //     int ap2= contaNumAparicoes(listaAUX);
  //printf("ap2 = %d,ap3 = %d\n",ap, ap2 ); 


}




TS* insereTS(infoLinha *linha, TS* listaTS,  char *nome, int pos, int Numlinha)   
{
    TS* listaAUX = (TS*) malloc(sizeof(TS));
//    printf("\nINSERE %s\n", nome ); 
    TS* listaAUXJaExiste = buscaTS(listaTS, nome);
    char *nomeLabel;
    pilhaPos *pilha = NULL;
    int op = 0;
    nomeLabel = (char *)malloc(strlen(nome)*sizeof(char));
    nomeLabel = obtemNomeLabel(nome);
     
    //nomeLabel = obtemNomeLabel(nome);
    //printf("Aqui\n");

    int defini = verificaSeDefiniToken(nome);
    //printf("definido = %d string = %s",definido, nome);
    //printf("defini = %d, nome = %s, nomeLabel = %s\n",defini, nome, nomeLabel);
    //if(!(!strcmp(nomeLabel,"+") && !strcmp(nomeLabel,"-")))
if(verificaSeOpAritmeticaLabel(linha))
    op = 1;

    if(!verificaErroToken(nomeLabel,pos,op))
        EscreveArgErro(Numlinha,1);


if(verificaSeMaisOuMenos(nome))
    return listaTS;

    if(defini)
    {
     
    //printf("DEFINI INSERE \n"); 
     listaAUX->pilhaDePosicoes = pilha;
     listaAUX->nome = nomeLabel;
     listaAUX->valor = pos;
     listaAUX->def = 1;
     listaAUX->valido = verificaErroToken(nomeLabel,pos,op);//MODIFICAR AQUI DEPOIS

     

     listaAUX->numAparicoes = 1;

     listaAUX->prox = listaTS;

    }
    else
    {

        //printf("NAO DEFINI INSERE \n");
        //printf("INSERE %s pos = %d \n", nomeLabel, pos); 
        //printf("nome = %s, val = %d, def = %d, valido = %d, apari = %d, ", listaAUX->nome, listaAUX->valor, listaAUX->def, listaAUX->valido, listaAUX->numAparicoes);
        //printfPilhaPos(listaAUX->pilhaDePosicoes);
    //printf("%s insere %d \n", nomeLabel,pos );
        listaAUX->pilhaDePosicoes = inserePilhaPos(pilha, pos);
//        printfPilhaPos(listaAUX->pilhaDePosicoes);
    //printf("\n");    
        //printfTS(listaAUX);
        listaAUX->nome = nome;
        listaAUX->valor = -1;
        listaAUX->def = 0;
        listaAUX->valido = verificaErroToken(nome,pos,op);//MODIFICAR AQUI DEPOIS
        listaAUX->numAparicoes = 2;
        listaAUX->prox = listaTS;

   }

   //int ap = contaNumAparicoes(listaAUX);
   // printf("ap = %d\n",ap ); 
        
        return listaAUX;
    //}

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
            
            if(!verificaSeInstrucao(linha->Tokens[k]) && !verificaSeDiretiva(linha->Tokens[k]) && !verificaSeNumero(linha->Tokens[k]) && !verificaSeMaisOuMenos(linha->Tokens[k]) &&  strcmp(linha->Tokens[k], ","))
            {
                //printf("ABCD2\n");

                //listaAUX = buscaTS(tabelaSims, linha->Tokens[k]);
                listaAUX = buscaTS(tabelaSims, nomeLabel);
                //printf("AQUI1");
                if(listaAUX == NULL)
                {   
                    //printf(" insere TOKEN[k] = %s\n", nomeLabel );
                    tabelaSims = insereTS( linha, tabelaSims,  linha->Tokens[k], pos, linha->numLinha);
                }
                else
                {
                    //printf(" atualiza TOKEN[k] = %s\n", linha->Tokens[k] );
                    atualizaTS(linha, tabelaSims,  linha->Tokens[k], pos, linha->numLinha);
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

int verificaoInicial( infoLinha * linha)
{
    //printf("A\n");
    if(linha->numTokens >= 2)
    { 
        if(verificaSections(linha))
        {
            return 0;
        }
        else if (verificaSeDefiniToken(linha->Tokens[0]) )
        {
         //  if(verificaSeInstrucao(linha->Tokens[1]) || verificaSeOpAlocacaoMemoria()) //||  verificaSeDiretiva(linha->Tokens[1]))
           //{

            //printf("A\n");
            return 1;
           //}
           //else
           //return -1;
        }
        else if(verificaSeInstrucao(linha->Tokens[0]))
        {
           return 0;

        }
    }


    return -1;


}

  
  



    // instrucoes[0] = "ADD"; //1
    // instrucoes[1] = "SUB";// = 2,
    // instrucoes[2] = "MULT";// = 3,
    // instrucoes[3] = "DIV";// = 4,
void AnaliseSintaticaOpAritmetica(infoLinha * linha, int posInicial)
{
   int i;
   int numTokens = linha->numTokens;

   if( verificaSeOpAritmetica(  linha->Tokens[posInicial]))
   {
        if(verificaAritmeticaExtendida( linha))
            EscreveArgErro(linha->numLinha,2);
   }

}



//instrucoes[9] = "LOAD";// = 10,
//instrucoes[10] = "STORE";// = 11,
    
void AnaliseSintaticaOpMemoria(infoLinha * linha, int posInicial)
{

    int i = posInicial;
   int numTokens = linha->numTokens;

   if(verificaSeOpMemoria(linha->Tokens[i]))
   {

        if( numTokens - i < 2)
        {
            printf("AnaliseSintaticaOpMemoria A\n");
            EscreveArgErro(linha->numLinha,2);        
        }
        if(!verificaSeVariavel(linha->Tokens[i+1]))
        {   printf("AnaliseSintaticaOpMemoria B\n");
            EscreveArgErro(linha->numLinha,2);        
        }

   }

}

    // instrucoes[4] = "JMP";// = 5,
    // instrucoes[5] = "JMPN";// = 6,
    // instrucoes[6] = "JMPP";// = 7,
    // instrucoes[7] = "JMPZ";// = 8,

void AnaliseSintaticaOpPulo(infoLinha * linha, int posInicial)
{

    int i = posInicial;
   int numTokens = linha->numTokens;

   if( verificaSeOpPulo(linha->Tokens[i]))
   {
         if( numTokens - i < 2)
        {
            printf("AnaliseSintaticaOpPulo A\n");
            EscreveArgErro(linha->numLinha,2);        
        }
        if(!verificaSeVariavel(linha->Tokens[i+1]))
        {   printf("AnaliseSintaticaOpPulo B\n");
            EscreveArgErro(linha->numLinha,2);        
        }

   }

}


    // instrucoes[11] = "INPUT";// = 12,
    // instrucoes[12] = "OUTPUT";// = 13,


void AnaliseSintaticaOpEntradaSaida(infoLinha * linha, int posInicial)
{
 
    int i = posInicial;
   int numTokens = linha->numTokens;

   if( verificaSeOpEntradaSaida (linha->Tokens[i]))
   {
        if( numTokens - i < 2)
        {
            printf("AnaliseSintaticaOpEntradaSaida A\n");
            EscreveArgErro(linha->numLinha,2);        
        }
        if(!verificaSeVariavel(linha->Tokens[i+1]))
        {   printf("AnaliseSintaticaOpEntradaSaida B\n");
            EscreveArgErro(linha->numLinha,2);        
        }

   }

}


    //     diretivas[1] = "SPACE";
    // diretivas[2] = "CONST";
    // diretivas[3] = "EQU";
void AnaliseSintaticaOpAlocacaoMemoria(infoLinha * linha, int posInicial)
{
 
    int i = posInicial;
   int numTokens = linha->numTokens;
   int flagSpaceSemNumero = 0;

 //  printf("pos ini = %d str = %s\n", i, linha->Tokens[i] );
   // if(i+1 >= numTokens)
   // {
   //   flagSpaceSemNumero = 1;

   // }



   //printf(" flagSPACESemNumero = %d AAAAA22222\n", flagSpaceSemNumero );
   //printf("%s Token[posinicial] = %s\n", linha->linha, linha->Tokens[posInicial] );
   if( verificaSeOpAlocacaoMemoria  (linha->Tokens[i]))
   {
        

        if(!strcmp(linha->Tokens[i], "SPACE"))
        {

            if(i +1 < numTokens)
            {

                if(!(verificaSeNumero(linha->Tokens[i+1])))
                {
                    printf("AnaliseSintaticaOpAlocacaoMemoria A \n");
                    EscreveArgErro(linha->numLinha,2);                
                }
            }  
        }
        else
        {

            if(i +1 >= numTokens)
            {

                    printf("AnaliseSintaticaOpAlocacaoMemoria B \n");
                    EscreveArgErro(linha->numLinha,2);                
            }
            else
            {
                if(!(verificaSeNumero(linha->Tokens[i+1])))
                {
                    printf("AnaliseSintaticaOpAlocacaoMemoria C \n");
                    EscreveArgErro(linha->numLinha,2);                
                }



            }

        }
            
   }
   //printf("AAAAA333333\n" );
        

}

/*  instrucoes[8] = "COPY";// = 9,
*/
void AnaliseSintaticaOpCopy(infoLinha * linha, int posInicial)
{
 
    int i = posInicial;
   int numTokens = linha->numTokens;

   if(  verificaSeOpCopy(linha->Tokens[i]))
   {
        if( numTokens - i < 4)
        {
            printf("AnaliseSintaticaOpCopy A\n");
            EscreveArgErro(linha->numLinha,2);        
        }
        else if(!verificaSeVariavel(linha->Tokens[i+1]) || !verificaSeVariavel(linha->Tokens[i+3]))
        {   printf("AnaliseSintaticaOpCopy B\n");
            EscreveArgErro(linha->numLinha,2);        
        }

   }

}


/*    diretivas[0] = "SECTION";
    diretivas[7] = "DATA";
    diretivas[8] = "TEXT";
*/

void AnaliseSintaticaOpSection(infoLinha * linha, int posInicial)
{
 
    int i = posInicial;
   int numTokens = linha->numTokens;

   if(  verificaSeSection (linha->Tokens[i]))
   {
        if( numTokens != 2)
        {
            printf("AnaliseSintaticaOpSection A\n");
            EscreveArgErro(linha->numLinha,2);        
        }
        if(!verificaSeOpTipoSection( linha->Tokens[i+1]))
        {   printf("AnaliseSintaticaOpSection B\n");
            EscreveArgErro(linha->numLinha,2);        
        }

   }

}


void AnaliseSintatica(infoLinha * linha, TS * tabelaSims)
{
    int numTokens = linha->numTokens;
    int erro = 1;
    char * string1 = (char *)malloc(sizeof(char *));
    char * string2 = (char *)malloc(sizeof(char *));

    string1 = NULL;
    string2 = NULL;
    if(numTokens >= 2)
    {

        string1 = linha->Tokens[0];
        string2 = linha->Tokens[1];
    }
    else
    {
        string1 = linha->Tokens[0];
    }

//printf("str1 = %s, str2 = %s\n", string1, string2 );

    
//printf("teste em %s, numTokens = %d\n", linha->linha, linha->numTokens);
        // if(!(verificaSeInstrucao(linha->Tokens[1]) || !strcmp(linha->Tokens[1], "CONST") || !strcmp(linha->Tokens[1], "EQU"))  )
        // {
        //     EscreveArgErro(linha->numLinha,2);
   if(numTokens == 1)
   {
   if(strcmp(linha->Tokens[0], "STOP") != 0)
   {
    printf("Erro linha apenas com um Token diferente de STOP\n");
    EscreveArgErro(linha->numLinha,2);
   }
  }
   else 
   { 
      int posInicial = verificaoInicial( linha);

      if(posInicial == -1)
      {
        printf("Erro sintatico linha %d : %s\n",linha->numLinha, linha->Tokens[0]);
         EscreveArgErro(linha->numLinha,2);
      }
      else
      {    
        AnaliseSintaticaOpMemoria( linha, posInicial);
        AnaliseSintaticaOpSection(linha, posInicial);
        AnaliseSintaticaOpAritmetica(linha,posInicial);
        AnaliseSintaticaOpAlocacaoMemoria(linha, posInicial);
        AnaliseSintaticaOpCopy(linha, posInicial);
        AnaliseSintaticaOpPulo(linha, posInicial);
        AnaliseSintaticaOpEntradaSaida(linha, posInicial);

        }
    }
            


    
}





