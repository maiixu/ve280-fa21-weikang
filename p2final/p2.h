#include <stddef.h>
#include <stdio.h>
#define ACE 14
#define KING 13
#define QUEEN 12
#define JACK 11
#define SPADE 1
#define HEART 2
#define CLUB 3
#define DIAMONDS 4
#ifdef linux
#define SY 1
#endif
#ifdef _WINDOWS_
#define SY 0
#endif
#ifndef _CAR
typedef struct _card
{
    int suit;
    int number;
    int cardnum;
    int ok;
}card;
typedef struct _player
{   
    char name[20];
    card cards[200];
    int cardsize;
    card played;
    struct _player* next;
    struct _player* prev;
    int score;
}player;
void scanc(card c,char* a,char* b);
void carden(FILE* fp,int fi);
void cardpsuit(card c,char b,char d,FILE* fp,int fi);
void cardpnumber(card c,char b,char d,FILE* fp,int fi);
player* fwho(int n,player* head);
void name(int pnum,int au,player **a);
void FreeList(player **head);
void InsertList(player **head,char na[20]);
player *Initialize(char na[20]);
void gmbg(int au,int rn,FILE *fp,int fi);
void PrintList(player *head);
void nctop(int au);
 void cardpn(card c,FILE *fp,int fi);
void cardp2(card* c,int num,FILE *fp,int fi);
card* chang(card* cards,int n);
int cmin(card* c,int pnum);
card suitnnum(card c);
card draw(card* newcards,int deck,int* ni,card*d,int* m,FILE* fp,int fi);
card* shuffle(card* c,int num,FILE* fp,int fi);
player* playacard(player* p,int* dir,int*fcard,int* skip,int au,FILE* fp,int fi);
player* scan(player* p,card* dis,int m,FILE* fp,int au);
player* ret(player* p,int au,FILE* fp,int fi);
int mstar(int a,int b);
int fwin(int* c,int pnum,int*imin);
void in(card c,int*fcard,card*discarded,int* di);
card* incard(int deck,card*c);
void onecard(int deck,int pnum,int cnum,int r,int au,int fi,FILE* fp);
#endif