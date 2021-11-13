#include "p2.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include <stddef.h>
void gmbg(int au,int rn,FILE *fp,int fi){
    printf("round:%d\n",rn+1);
    printf("Game starts!\n");
    printf("\nDealing cards..\n\n");
    if(fi==1)
    {fprintf(fp,"round:%d\n",rn+1);}
    if (au==0){sleep(1);}
    return;
}
void nctop(int au)
{
    if (au==0)
    {
        printf("So you give up to play a second card.\n(Press Enter.)");
        getchar();
    }                 
}
int fwin(int* c,int pnum,int*imin)
{
    int minc=c[0];
    int cnt=0;imin[0]=0;
        for (int k=1;k<pnum;k++)
        {
            if (c[k]<minc)
            {   cnt=0;
                minc=c[k];imin[0]=k;
                
            }else if (c[k]==minc)
                {
                    cnt++;
                    imin[cnt]=k;
                }
        }
        return cnt;
}
void cardpn(card c,FILE* fp,int fi){
    char a='0';char b='0';char d=' ';
    scanc(c,&a,&b);
    printf("\n_____ \n");
    if (fi==1)
    {
        fprintf(fp,"\n____ \n");
    }
    cardpsuit(c,b,d,fp,fi);
    printf("\n| %c | \n",a);
    if(fi==1)
        {
            fprintf(fp,"\n| %c | \n",a);
        }
    cardpnumber(c,b,d,fp,fi);
    carden(fp,fi);
    return;
}
void scanc(card c,char* a,char* b)
{
    switch (c.suit) 
    {
        case SPADE: *a='S'; break;
        case HEART: *a='H'; break;
        case CLUB: *a='C';break;
        case DIAMONDS: *a='D';break;
        default:*a='0'; break;
    }
    switch (c.number) 
    {
        case ACE: *b='A';break;
        case KING: *b='K'; break;
        case QUEEN: *b='Q'; break;
        case JACK: *b='J'; break;
        case 10:*b='1';break;
        default: *b='0';
    }
}
void cardp2(card* c,int num,FILE* fp,int fi){
    char a[600];char b[600];char d[600];
    carden(fp,fi);
    int t=(int)floor(num/10);
	for (int i=0;i<(int)num;i++)
    {
        d[i]=' ';
        scanc(c[i],&a[i],&b[i]);}
    for (int k=0;k<t;k++)
    {
    for (int i=0;i<10;i++)
    { int cardn=k*t+i+1;
        printf("%d     ",cardn);
        if (fi==1)
        {
        fprintf(fp,"%d     ",cardn);
        }
    }
    carden(fp,fi);
    for (int i=0;i<10;i++)
    {printf("_____ ");
    if (fi==1)
        {fprintf(fp,"_____ ");}
    }
    carden(fp,fi);
    for (int i=0;i<10;i++)
    {cardpsuit(c[k*10+i],b[k*10+i],d[k*10+i],fp,fi);}
    carden(fp,fi);
    for (int i=0;i<10;i++)
    {printf("| %c | ",a[k*10+i]);
    if (fi==1)
        {
        fprintf(fp,"| %c  | ",a[k*10+i]);
        }}
    carden(fp,fi);
    for (int i=0;i<10;i++)
    {
        cardpnumber(c[k*10+i],b[k*10+i],d[k*10+i],fp,fi);
    }
    printf("\n");
    carden(fp,fi);
    for (int i=0;i<10;i++)
    {
        if (c[k*10+i].ok>=2){printf("  *  ");}
        else{printf("     ");}
        printf(" ");
    }
    printf("\n");
    }
    for(int i=(t*10);i<num;i++)
    {
        printf("%d     ",i+1);
        if (fi==1)
        {
            fprintf(fp,"%d     ",(i+1));
        }
    }
    carden(fp,fi);
    for(int i=t*10;i<num;i++)
    {printf("_____ ");
    if (fi==1)
    {fprintf(fp,"_____ ");}
    }
    carden(fp,fi);
    for(int i=t*10;i<num;i++)
    {cardpsuit(c[i],b[i],d[i],fp,fi);}
    carden(fp,fi);
    for(int i=t*10;i<num;i++)
    {printf("| %c | ",a[i]);
    if (fi==1)
    {
        fprintf(fp,"| %c  | ",a[i]);
        }}
    carden(fp,fi);
    for(int i=t*10;i<num;i++)
    {
        cardpnumber(c[i],b[i],d[i],fp,fi);
    }
    printf("\n");
    carden(fp,fi);
    for(int i=t*10;i<num;i++)
    {
        if (c[i].ok>=2){printf("  *  ");}
        else{printf("   ");}
        printf(" ");
    }
    printf("\n");
    return;
}
void cardpnumber(card c,char b,char d,FILE* fp,int fi)
{
if (c.number==10)
        {
            printf("|_%c%c| ",b,d);
            if (fi==1)
        {
        fprintf(fp,"|_%c%c| ",b,d);
        }
        }
        else if(c.number>10)
        {
            printf("|__%c| ",b);
            if (fi==1)
        {
        fprintf(fp,"|__%c| ",b);
        }
        }
        else 
        {
            printf("|__%d| ",c.number);
            if (fi==1)
        {
        fprintf(fp,"|__%d| ",c.number);
        }
        }
}
void cardpsuit(card c,char b,char d,FILE* fp,int fi)
{
if (c.number>=10)
        {
            printf("|%c%c | ",b,d);
            if (fi==1)
            {fprintf(fp,"|%c%c  | ",b,d);}
        }
    else if(c.number>10)
        {
            printf("|%c  | ",b);
            if (fi==1)
        {
        fprintf(fp,"|%c   | ",b);
        }
        }
    else 
        {
            printf("|%d  | ",c.number);
            if (fi==1)
        {
        fprintf(fp,"|%d   | ",c.number);
        }
        }
}
card* chang(card* cards,int n)
{
    card t;int i,j;
    for(i=0;i<n-1;++i)
    {                 
        for( j=0;j<n-1-i;++j)
        {
            if(cards[j].cardnum>cards[j+1].cardnum)
            {
                t=cards[j];
                cards[j]=cards[j+1];
                cards[j+1]=t;
            }
        }
    }
    for (size_t i = 0; (int)i < n; i++)
    {
        cards[i]=suitnnum(cards[i]);
    }
    
    return cards;
}
int cmin(card* c,int pnum)
{
    int imin=0;int minc=c[0].cardnum;
        for (int k=0;k<pnum;k++)
        {
            if (c[k].cardnum<minc)
            {
                minc=c[k].cardnum;imin=k;
            }
        }
    return imin;
}
card suitnnum(card c)
{
	c.suit=c.cardnum/13+1;c.number=(c.cardnum)%13+2;
	return c;
}
card draw(card* newcards,int deck,int* ni,card*d,int* m,FILE* fp,int fi)
{
    card c;
    if (*ni>0)
    {   *ni=*ni-1;
        c=newcards[*ni];
    }
    else
    {
        printf("\n\nOops, the stock pile is used up.\nGathering the discarded piles..\n");
        if (fi==1)
        {
            fprintf(fp,"\n\nOops, the stock pile is used up.\nGathering the discarded piles..\n");
        }
        card x=d[*m-1];
        *m=*m-1;
        shuffle(d,*m,fp,fi);
        for(int i=0;i<52*deck;i++)
        {
            newcards[i].cardnum=0;newcards[i]=suitnnum(newcards[i]);newcards[i].ok=0;
        }
        for(int i=0;i<*m;i++)
        {
            newcards[i].cardnum=d[i].cardnum;newcards[i]=suitnnum(newcards[i]);newcards[i].ok=1;
        }
        *ni=*m;
        *m=0;*ni=*ni-1;
        c=newcards[*ni];
        d[0]=x;*m=*m+1;
    }
    return c;
}
card* shuffle(card* c,int num,FILE* fp,int fi){
    card temc;
    printf("Shuffling cards..\n");
    if (fi==1)
    {
        fprintf(fp,"Shuffling cards..\n");
    }
    for (int i=0;i<num;i++)
    {   
        int q=rand()%(num); 
        temc=c[i];
        c[i]=c[q];
        c[q]=temc;
        c[i].ok=1;
    }
return c;
}
int mstar(int a,int b){
    if(a>=0)
    {
        return(a%b);
    }
    else
    {
        if(a%b==0)
        {
            return 0;
        }
        else 
        {
            return(a%b+b);
        }
    }
}
void in(card c,int*fcard,card*discarded,int* di)
{
    switch (c.number)
    {
    case 2:
        *fcard=2;
        break;
    case 3:
        *fcard=3;
        break;
    default:
        *fcard=0;
        break;
    }
    discarded[*di]=c;*di=*di+1;
    printf("\n");
}
card* incard(int deck,card*c)
{   
    for (int i=0;i<deck*52;i++)
    {
        c[i].cardnum=i%52;
        c[i]=suitnnum(c[i]);
    }
    return c;
}
void carden(FILE* fp,int fi)
{
    if (fi==1)
    {
        fprintf(fp,"\n");
    }
    printf("\n");
}
