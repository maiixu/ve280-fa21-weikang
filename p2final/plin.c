#include "p2.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include <stddef.h>
player* playacard(player *p,int*dir,int* fcard,int*skip,int au,FILE* fp,int fi){
    int d;
    if (au==0){
        printf("Which card?\n");
        cardp2(p->cards,p->cardsize,fp,0);
        printf("\n\n");
        }
    if(fi==1)
    {
        fprintf(fp,"\n\n");
    }
    if (au==0)
    {
        if(scanf("%d",&d)==0){printf("-1");}
        getchar();
        while (d>p->cardsize||d-1<0||p->cards[d-1].ok<=1)
        {
            printf("Invalid\n");
            printf("%s:\nWhich card?\n",p->name);
            cardp2(p->cards,p->cardsize,fp,0);
            printf("\n");
            if(scanf("%d",&d)==0){printf("-1");}
            getchar();
            printf("You played:");
        }
    }
    else
    {
        d=1;
        while (d>p->cardsize||d-1<0||p->cards[d-1].ok<=1)
        {
            d++;
        }
        printf("%s played:",p->name);
    }
    
    if(fi==1)
    {
        fprintf(fp,"%s played:",p->name);
    }
    cardpn(p->cards[d-1],fp,fi);
    p->played=p->cards[d-1];
    switch (p->played.number)
    {
    case 2:
        *fcard=*fcard+2;
        break;
    case 3:
        *fcard=*fcard+3;
        break;
    case JACK:
        *skip=*skip+1;
        break;
    case 7:
        *fcard=0;
        break;
    case QUEEN:
        *dir=*dir+1;
        break;
    default:
        *fcard=0;
        break;
    }

    printf("\n");
    for (int k=0;k<p->cardsize;k++)
    {
        if (k>=d-1)
        {
            p->cards[k]=p->cards[k+1];
        }
    }
    p->cardsize--;
    return p; 
}
player* scan(player* p,card* dis,int m,FILE*fp,int au){
    if (au==0)
    {
        printf("Previous card:");
        cardpn(dis[m],fp,0);
        printf("\n");
        printf("\n%s:\n",p->name);
    }
    
    for (int k=0;k<p->cardsize;k++)
    {
        p->cards[k].ok=1;
    }
    for (int k=0;k<p->cardsize;k++)
    {
        if (dis[m].suit==p->cards[k].suit)
        {
            p->cards[k].ok=2;
            if(p->cards[k].number==7||p->cards[k].number==2||p->cards[k].number==3||p->cards[k].number==JACK||p->cards[k].number==QUEEN)
            {p->cards[k].ok=3;}
        } 
        if (dis[m].number==p->cards[k].number)
        {p->cards[k].ok=3;}  
    }
    return p;
}
player* ret(player* p,int au,FILE* fp,int fi)
{   if (p->cardsize>0)
    {
        if(au==0){printf("\nYou have:\n");}
        else
        {
            printf("%s have",p->name);
        }
        
        if (fi==1)
        {
            fprintf(fp,"\n%s have:\n",p->name);
        }
        
        for (int k=0;k<p->cardsize;k++)
        {p->cards[k].ok=1;}
        cardp2(p->cards,p->cardsize,fp,fi);
        if (p->cardsize==1)
        {
            printf("UNO!\n");
        }
        if (au==0)
        {
            printf("(Press enter)\n");
            getchar();
        }
    }
    return p;
}
player *Initialize(char na[20]) {
player *head;
head=(player*)calloc(1,sizeof(player));
if(head==NULL){ fprintf(stderr,"Failed to assign memory!\n"); exit(-1); }
head->next=head;head->prev=head;strcpy(head->name,na);head->score=0;head->cardsize=0;
return head;
}
void InsertList(player **head,char na[20])//,newcards,*ni,displayed,*di,)
{   if(*head==NULL){
    *head=Initialize(na);
}else{
    player *in=(player*)calloc(1,sizeof(player));
    if(in==NULL){ fprintf(stderr,"Failed to assign memory!\n"); exit(-1); }
    player *tmp=NULL;tmp=(*head)->prev;
    in->next=*head;(*head)->prev=in;
    in->prev=tmp;tmp->next=in;strcpy(in->name,na);in->score=0;in->cardsize=0;(*head)=in;
    }
    return;
}
void FreeList(player **head)
{
player *tmp=NULL; player *pHead=(*head)->next;
while(pHead!=*head)
{ tmp=pHead; pHead=pHead->next; free(tmp);}
free(pHead);
}
void PrintList(player *head) {
player *temp=head;
printf("***Print Linked List***\n");
do{ printf("%s ",temp->name); temp=temp->next;}while(temp!=head);
printf("\n****Print Finished****\n\n");
}
void name(int pnum,int au,player **a)
{char na[20];
for(int i=0;i<pnum;i++)
    {int pn=pnum-i;
        if (au==0)
        {
            printf("Your name?\n");
            if(scanf("\n%s",na)==0){printf("-1");}
        }
        else
        {sprintf(na,"Player %d",(short)pn);}
        InsertList(a,na);
    }
}
player* fwho(int n,player* head)
{
    player* temp=head;
    for(int i=0;i<n;i++)
    {temp=temp->next;}
    return temp;
}