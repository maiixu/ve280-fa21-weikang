/*
 * @Author: Maize
 * @Date: 2021-11-13 11:42:12
 * @LastEditTime: 2021-11-19 22:15:58
 * @Description: VE280 2021 Fall Project 4
 * @FilePath: \p4\blackjack.cpp
 */
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"
#include <iostream>
#include <string>

using namespace std;

const int MINIMUM_BET = 5;

const int PLAYER = 1;

const int DEALER = 0;

void shuffle(Deck &thisDeck, Player *thisPlayer) {
    cout << "Shuffling the deck\n";
    for (int i = 0; i < 7; i++) {
        int cut = get_cut();
        thisDeck.shuffle(cut);
        cout << "cut at " << cut << endl;
    }
    thisPlayer->shuffled();
}

void printCard(Card c, int pType) {
    if (pType == 1)
        cout << "Player dealt " << SpotNames[c.spot] << " of " << SuitNames[c.suit] << endl;
    else
        cout << "Dealer dealt " << SpotNames[c.spot] << " of " << SuitNames[c.suit] << endl;
}

bool judgeHandValue(int handValue, int &bankroll, int pType, int wager) {
    if (pType == 1) {
        if (handValue > 21) {
            cout << "Player's total is " << handValue << endl;
            cout << "Player busts\n";
            bankroll -= wager;
            return false;
        }
        else {
            cout << "Player's total is " << handValue << endl;
            return true;
        }
    }
    else {
        if (handValue > 21) {
            cout << "Dealer's total is " << handValue << endl;
            cout << "Dealer busts\n";
            bankroll += wager;
            return false;
        }
        else {
            cout << "Dealer's total is " << handValue << endl;
            return true;
        }
    }
}

void initDeal(Player *player, Hand &hand, Card temp, int pType) {
    if (pType == 1) {
        player->expose(temp);
        hand.addCard(temp);
        printCard(temp, PLAYER);
    }
    else {
        player->expose(temp);
        hand.addCard(temp);
        printCard(temp, DEALER);
    }
}

void oneHand(Deck &myDeck, Deck &save, int &thishand, int &bankroll, Player *player, Hand &playerHand, Hand &dealerHand) {
    Card temp1, temp2;
    cout << "Hand " << thishand << " bankroll " << bankroll << endl;
    if (myDeck.cardsLeft() < 20) {
        shuffle(save, player);
        myDeck = save;
    }
    int wager = player->bet(bankroll, MINIMUM_BET);
    cout << "Player bets " << wager << endl;
    temp1 = myDeck.deal();
    initDeal(player, playerHand, temp1, PLAYER); // Deal the first card
    temp1 = myDeck.deal();
    initDeal(player, dealerHand, temp1, DEALER); // Deal the second card
    temp2 = myDeck.deal();
    initDeal(player, playerHand, temp2, PLAYER); // Deal the third card
    temp2 = myDeck.deal();
    dealerHand.addCard(temp2); // Deal the fourth card
    if (playerHand.handValue().count == 21) {
        cout << "Player dealt natural 21\n";
        bankroll += wager * 3 / 2;
        dealerHand.discardAll();
        playerHand.discardAll();
    }
    else {
        while (1) {
            if (player->draw(temp1, playerHand)) {
                Card dealt = myDeck.deal();
                initDeal(player, playerHand, dealt, PLAYER);
            }
            else
                break;
        }
        if (judgeHandValue(playerHand.handValue().count, bankroll, PLAYER, wager)) {
            player->expose(temp2);
            cout << "Dealer's hole card is " << SpotNames[temp2.spot] << " of " << SuitNames[temp2.suit] << endl;
            while (dealerHand.handValue().count < 17) {
                Card dealt = myDeck.deal();
                initDeal(player, dealerHand, dealt, DEALER);
            }
            if (judgeHandValue(dealerHand.handValue().count, bankroll, DEALER, wager)) {
                if (playerHand.handValue().count == dealerHand.handValue().count)
                    cout << "Push\n";
                else if (playerHand.handValue().count > dealerHand.handValue().count) {
                    cout << "Player wins\n";
                    bankroll += wager;
                }
                else {
                    cout << "Dealer wins\n";
                    bankroll -= wager;
                }
                dealerHand.discardAll();
                playerHand.discardAll();
            }
            else {
                dealerHand.discardAll();
                playerHand.discardAll();
            }
        }
        else {
            dealerHand.discardAll();
            playerHand.discardAll();
        }
    }
}

int main(int argc, char *argv[]) {
    int bankroll = stoi(argv[1]);
    int hands = stoi(argv[2]);
    Deck myDeck;
    string pType = (string)argv[3];
    Player *player;
    Hand playerHand, dealerHand;
    if (pType == "simple")
        player = get_Simple();
    else
        player = get_Counting();
    shuffle(myDeck, player); // Shuffle my deck
    Deck save = myDeck;
    int thishand = 1; // Initialize all parameters
    while (bankroll >= MINIMUM_BET && thishand < hands + 1) {
        oneHand(myDeck, save, thishand, bankroll, player, playerHand, dealerHand);
        thishand++;
    }                                                                               // Play one hand for each loop
    cout << "Player has " << bankroll << " after " << (thishand - 1) << " hands\n"; // Print results
    delete player;
}

// TODO:
// 1. 写testcase
// 2. 对拍答案
// 3. 写注释, 修虚拟机 && 查coding style