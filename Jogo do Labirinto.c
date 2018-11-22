#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define NLIN 8
#define NCOL 19

int playerI, playerJ;
char mapa[NLIN][NCOL];

int verificaMovimento(int i, int j);
void atualizaPosicao(int i, int j);

void clrscr()
{
    system("@cls||clear");
}

void inicializaMapa()
{
    int i, j;
    char ch;
    char url[]="mapa.txt";
    FILE *arq;
    arq = fopen(url,"r");
    if ((arq = fopen(url,"r") )==NULL)
    {
        printf("null\n");
    }
    for (i=0; i<NLIN; i++)
    {
        for (j=0; j<NCOL; j++)
        {
            ch = fgetc(arq);
            //if(ch == '\n')
            //    ch = fgetc(arq);
            mapa[i][j] = ch;
        }
        ch=fgetc(arq);
    }
    fclose(arq);
}

void inicializaPlayer()
{
    int i, j;
    i = playerI = 1;
    j = playerJ = 1;
    if (mapa[i][j] == ' ')
        mapa[i][j] = 'O';
}

void imprimeTela()
{
    clrscr();
    int i, j;
    int imin, imax, jmin, jmax;
    int linha = NLIN, coluna = NCOL;
    imin = playerI-3;
    imax = playerI+3;
    jmin = playerJ-3;
    jmax = playerJ+3;
    if(imin<0)
        imin=0;
    if(imax>=linha)
        imax=linha;
    if (jmin<0)
        jmin=0;
    if(jmax>=coluna)
        jmax=coluna;
    for (i=imin; i<imax; i++)
    {
        for (j=jmin; j<jmax; j++)
        {
                printf("%c", mapa[i][j]);
        }
        printf("\n");
    }
}

void movimenta(char p)
{
    int tempI = playerI;
    int tempJ = playerJ;

    switch(p)
    {
        case ('w'):
            tempI-=1;
            break;
        case ('s'):
            tempI+=1;
            break;
        case ('a'):
            tempJ-=1;
            break;
        case ('d'):
            tempJ+=1;
            break;
        default:
        break;
    }
    if (verificaMovimento(tempI, tempJ) == 1)
        {
            mapa[playerI][playerJ] = ' ';
            mapa[tempI][tempJ] = 'O';
            atualizaPosicao(tempI, tempJ);
        }
    else if (verificaMovimento(tempI, tempJ) == -1)
    {
            mapa[playerI][playerJ] = ' ';
            mapa[tempI][tempJ] = '$';
            atualizaPosicao(tempI, tempJ);
    }
}

int verificaMovimento(int i, int j)
{
    int verifica = 0;
    if (mapa[i][j] == ' ')
        verifica=1;
    else if (mapa[i][j] == '$')
        verifica = -1;
    return verifica;
}

void atualizaPosicao(int i, int j)
{
    playerI = i;
    playerJ = j;
}

int verificaFim()
{
    if (mapa[playerI][playerJ]== '$')
        return 1;
    else
        return 0;
}

int main()
{
    char p =' ';
    //Inicializa mapa
    inicializaMapa();
    //Inicializa posição inicial do jogador
    inicializaPlayer();
    while(1)
    {
        imprimeTela();
        p=getch();
        movimenta(p);
        if (verificaFim() == 1)
        {
            clrscr();
            printf("FIMMMM!\n");
            break;
        }
    }
}
