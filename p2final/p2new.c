#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include<math.h>
#include "p2.h"
#ifndef linux
#include<windows.h>
#endif
#ifdef linux
#define SY 1
#endif
#ifdef _WINDOWS_
#define SY 0
#endif

void onecard(int deck,int pnum,int cnum,int r,int au,int fi,FILE* fp)
{
    srand((unsigned int)time(NULL));
    
    if (au==0){printf("Welcome to ONECARD GAME!\n(Press Enter)");getchar();}
    int fcard=0;int dir=0;int cnt1;int rn=0;int cntn;int cnt;char yon;
    if(au==1)
    {
        if (deck==0){deck=2;}
        if (pnum==0){pnum=5;}
        if (r==0){r=2;}
        if (cnum==0){cnum=6;}
    }
    if(deck==0){printf("Please input the number of the deck\n");if(scanf("%d",&deck)==0){printf("-1");}}int ni=52*deck;
    if(pnum==0){printf("Please input the number of the players\n");if(scanf("%d",&pnum)==0){printf("-1");}}
    if(r==0){printf("Please input the number of the round\n");if(scanf("%d",&r)==0){printf("-1");}}
    card* fc=(card*)malloc(sizeof(card)*(unsigned int)r);
    card* newcards=(card*)malloc(sizeof(card)*(unsigned int)deck*52);
    player* p = NULL;
    card* firstc=(card*)malloc(sizeof(card)*(unsigned int)pnum);
    card* discarded=(card*)malloc(sizeof(card)*(unsigned int)deck*52);int di=0;
    incard(deck,newcards);
    newcards=shuffle(newcards,52*deck,fp,fi);
    if(au==1)
    {cardp2(newcards,ni,fp,fi);}
    name(pnum,au,&p);
    if (cnum==0){printf("Please input the number of the cards at first\n");if(scanf("\n%d",&cnum)==0){printf("-1");}}
    if(fi==1)
    {
        fprintf(fp,"player number:%d\ninitial card number:%d\ndeck number:%d\ntotal round number:%d\n",pnum,cnum,deck,r);
    }
    player* temp=p;
    for (size_t k=0;(int)k<pnum;++k)
    {   
	    firstc[k]=draw(newcards,deck,&ni,discarded,&di,fp,fi);
        discarded[di]=firstc[k];di=di+1;
        printf("%s:",temp->name);
        if(fi==1)
        {fprintf(fp,"%s:",temp->name);}
        cardpn(firstc[k],fp,fi);printf("\n");
        if(fi==1)
        {fprintf(fp,"\n");}
        temp=temp->next;
    }
    printf("\n");
    if(fi==1)
    {fprintf(fp,"\n");}
    int who=cmin(firstc,pnum);
    printf("%s first\n\n",fwho(who,p)->name);
    if(fi==1)
    {fprintf(fp,"%s first\n\n",fwho(who,p)->name);}
    
    for(rn=0;rn<r;rn++)
    {   gmbg(au,rn,fp,fi);
        for (size_t k=0;(int)k<pnum;++k)
        {   
            temp->cardsize=0;
            for(int i=0;i<cnum;++i)
            {temp->cards[i]=draw(newcards,deck,&ni,discarded,&di,fp,fi);temp->cardsize++;}
            chang(temp->cards,temp->cardsize);
            printf("%s:\n",temp->name);
            if(fi==1)
            {fprintf(fp,"%s:\n",temp->name);}
	        cardp2(temp->cards,temp->cardsize,fp,fi);
            printf("\n");
            temp=temp->next;
        }
        fc[rn]=draw(newcards,deck,&ni,discarded,&di,fp,fi);
        printf("first card:");
        if(fi==1)
        {fprintf(fp,"first card:");}
        cardpn(fc[rn],fp,fi);
        in(fc[rn],&fcard,discarded,&di);
        if (rn==0){temp=fwho(who,p);}int ftr=0;
        if (au==0){
                if (SY){if(system("clear")==2){printf("-1");}}
                else{if(system("CLS")==2){printf("-1");}}}  
        int skip=1;
        do
        {  int nop=mstar(dir,2);
        if (ftr!=0)
        {
            for(int kk=0;kk<skip;kk++)
            {
        switch (nop)
        {
        case 0:
            temp=temp->next;
            break;
        default:
            temp=temp->prev;
            break;
        }
            }
        }
        skip=1;
            //printf("%d",fcard);printf("dir:%d",dir);
            cntn=0;
            do
            {
            cnt=0;cnt1=0;
            temp=scan(temp,discarded,di-1,fp,au);
            for (int k=0;k<temp->cardsize;k++)
            {
                if(temp->cards[k].ok>1)
                {cnt++;}
                if (temp->cards[k].ok==3)
                {cnt1++;}
            }
            if(fcard==0)
            {
                if (cnt>0)
                {
                    temp=playacard(temp,&dir,&fcard,&skip,au,fp,fi);
                    discarded[di]=temp->played;di++;
                }
                else 
                {
                    if (au==0){printf("You don't have the proper card to play.\n");}
                    if (cntn==1)
                    {
                        nctop(au);
                        break;
                    }
                    if (au==0){printf("(Press Enter.)");getchar();printf("You get ");}
                    else{printf("%s get",temp->name);}
                    temp->cardsize++;
                    temp->cards[temp->cardsize-1]=draw(newcards,deck,&ni,discarded,&di,fp,fi);
                    
                    if (fi==1)
                    {fprintf(fp,"%s get",temp->name);}
                    cardpn(temp->cards[temp->cardsize-1],fp,fi);
                    printf("\n");
                }
            }
            else 
            {
                if(cnt1>0)
                {
                    for (int k=0;k<temp->cardsize;k++)
                    {
                        temp->cards[k].ok--;
                    }
                    temp=playacard(temp,&dir,&fcard,&skip,au,fp,fi);
                    discarded[di]=temp->played;di++;
                }
                else 
                {
                    if (au==0){printf("You don't have the proper card to play.\nSo you have to draw %d cards.\n",fcard);}
                    if (cntn==1)
                    {
                        nctop(au);
                        break;
                    }
                    if (au==0){printf("(Press Enter.)");getchar();printf("You get ");}
                    else{printf("%s get",temp->name);}
                    if (fi==1)
                    {fprintf(fp,"%s get",temp->name);}
                    for (int i=0;i<fcard;i++)
                    {
                        temp->cardsize++;
                        temp->cards[temp->cardsize-1]=draw(newcards,deck,&ni,discarded,&di,fp,fi);
                        cardpn(temp->cards[temp->cardsize-1],fp,fi);
                        printf("\n");
                    }
                    fcard=0;
                }
            }
            chang(temp->cards,temp->cardsize);
            temp=ret(temp,au,fp,fi);
            if(temp->cardsize==0)
            {break;}
            if(cntn==0)
            {
                if(au==0)
                    {printf("Do you want to play one more card?\n'y'for yes\n'n'for no\n");if(scanf("%c",&yon)==0){printf("-1");}getchar();}
                else
                    {yon='y';}
            }
            switch (yon)
            {
            case 'y':break;
            case 'n':cntn++;break;
            default:break;
            }
            cntn++;
            }
            while(cntn<2);
            if (au==0)
            {
                if (SY){if(system("clear")==2){printf("a");}}
                else{if(system("CLS")==2){printf("a");}}
            }
        ftr=1;
        }while(temp->cardsize>0);
        printf("%s wins!!\n\n",temp->name);
        if(fi==1)
        {fprintf(fp,"\n%s wins!!\n\n",temp->name);}
        for(int i=0;i<pnum;i++)
        {
            temp->score+=temp->cardsize;
            printf("%s has %d cards\n",temp->name,temp->cardsize);
            if(fi==1)
            {fprintf(fp,"%s has %d cards\n",temp->name,temp->cardsize);}
            temp=temp->next;
        }
        printf("\nCurrent Scoreboard:\n\n");
        if(fi==1)
        {fprintf(fp,"\nCurrent Scoreboard:\n\n");}
        printf("\n");
        for (int i=0;i<pnum;i++)
        {
            printf("%s: %d\n",temp->name,-temp->score);
            if(fi==1)
        {fprintf(fp,"%s: %d\n",temp->name,-temp->score);}
            for(int k=0;k<temp->cardsize;k++)
            {
                discarded[di]=temp->cards[k];
                di++;
            }
            temp=temp->next;
        }
        if (au==0)
        {printf("(Press Enter.)");getchar();}
    }
    printf("\nResult:\n");
    if(fi==1)
    {fprintf(fp,"\nResult:\n");}
    for(int i=0;i<pnum;i++)
    {
        printf("%s: %d\n",temp->name,-temp->score);
        if(fi==1)
        {fprintf(fp,"%s: %d\n",temp->name,-temp->score);}
        temp=temp->next;
    }
    printf("\nSo..\n");
    if (au==0) {sleep(1);}
    int*win=malloc((unsigned int)pnum*sizeof(int));
    int*sc=malloc((unsigned int)pnum*sizeof(int));
    temp=p;
    for(int i=0;i<pnum;i++)
    {
        sc[i]=temp->score;
        temp=temp->next;
    }
    int cntww=fwin(sc,pnum,win);
    for (int i=0;i<cntww+1;i++)
    {
        printf("%s is the WINNER!\n",fwho(win[i],p)->name);
        if(fi==1)
        {fprintf(fp,"%s is the WINNER!\n",fwho(win[i],p)->name);}
    }
    free(win);free(firstc);free(discarded);free(newcards);free(fc);FreeList(&p);free(sc);
}
