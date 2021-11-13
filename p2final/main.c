#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include<math.h>
#include "p2.h"
int main(int argc, char* argv[])
{
    int pnum=0;
    int cnum=0;
    int deck=0;
    int r=0;int au=0;int fi=0;FILE * fp=NULL;
    static struct option long_options[] = 
    {
        {"help", no_argument, NULL, 'h'},
        {"log", required_argument, NULL, 'f'},
        {"player-number", required_argument, NULL, 'n'},
        {"initial-cards", required_argument, NULL, 'c'},
        {"decks", required_argument, NULL, 'd'},
        {"rounds", required_argument, NULL, 'r'},
        {"auto", optional_argument, NULL, 'a'},
        {0, 0, 0, 0}
    };
    static char* const short_options=(char *)"hf:n:c:d:r:a";
    int option_index = 0;
    int ret=0;
    while((ret=getopt_long(argc,argv,short_options,long_options,&option_index))!=-1)
    {
        switch(ret)
        {
            case 'h':
                printf("-h|--help print this help message\n--log filename write the logs in filename (default: onecard.log)\n-n n|--player-number=n n players, n must be larger than 2 (default: 4)\n-c c|--initial-cards=c deal c cards per player, c must be at least 2 (default: 5)\n-d d|--decks=d use d decks 52 cards each, d must be at least 2 (default: 2)\n-r r|--rounds=r play r rounds, r must be at least 1 (default: 1)\n-a|--auto run in demo mode\n\n");
                return 0;
                break;
            case 'f':
                fi=1;
                
                fp = fopen(optarg, "w+");
                if(fp == NULL) 
                {perror("Error");}
                else{
                printf("load in %s\n\n",optarg);
                fprintf(fp,"Welcome to Onecard!\n");}
                break;
            case 'n':
                pnum = atoi(optarg);
                printf("The number of players is %d\n\n",pnum);
                break;
            case 'c':
                cnum= atoi(optarg);
                printf("The number of initial cards is %d\n\n",cnum);
                break;
            case 'd':
                deck = atoi(optarg);
                printf("The number of deck is %d\n\n",deck);
                break;
            case 'r':
                r = atoi(optarg);
                printf("The number of rounds is %d\n\n",r);
                break;  
            case 'a':
                printf("AUTO mode\n");
                au=1;   
                break;  
            case '?':
                return 0;
                break;
        }
    }
    onecard(deck,pnum,cnum,r,au,fi,fp);
    if (fi==1)
    {fclose(fp);}
    return 0;
}  
