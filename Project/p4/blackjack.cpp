/*
 * @Author: Maize
 * @Date: 2021-11-13 11:42:12
 * @LastEditTime: 2021-11-17 19:02:34
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
    shuffle(myDeck, player);
    Deck save = myDeck;
    int thishand = 1;
    while (bankroll >= MINIMUM_BET && thishand < hands + 1) {
        Card temp1, temp2;
        cout << "Hand " << thishand << " bankroll " << bankroll << endl;
        if (myDeck.cardsLeft() < 20) {
            shuffle(save, player);
            myDeck = save;
        }
        int wager = player->bet(bankroll, MINIMUM_BET);
        cout << "Player bets " << wager << endl;
        temp1 = myDeck.deal();
        player->expose(temp1);
        playerHand.addCard(temp1);
        printCard(temp1, PLAYER);

        temp1 = myDeck.deal();
        player->expose(temp1);
        dealerHand.addCard(temp1);
        printCard(temp1, DEALER);

        temp2 = myDeck.deal();
        player->expose(temp2);
        playerHand.addCard(temp2);
        printCard(temp2, PLAYER);

        temp2 = myDeck.deal();
        dealerHand.addCard(temp2);
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
                    player->expose(dealt);
                    playerHand.addCard(dealt);
                    printCard(dealt, PLAYER);
                }
                else
                    break;
            }
            if (judgeHandValue(playerHand.handValue().count, bankroll, PLAYER, wager)) {
                player->expose(temp2);
                cout << "Dealer's hole card is " << SpotNames[temp2.spot] << " of " << SuitNames[temp2.suit] << endl;
                while (dealerHand.handValue().count < 17) {
                    Card dealt = myDeck.deal();
                    player->expose(dealt);
                    dealerHand.addCard(dealt);
                    printCard(dealt, DEALER);
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

        thishand++;
    }
    cout << "Player has " << bankroll << " after " << (thishand - 1) << " hands\n";
    delete player;
}

// TODO:
// 1. 拆函数
// 2. 写testcase
// 3. 对拍答案
// 4. 写注释, 修虚拟机 && 查coding style