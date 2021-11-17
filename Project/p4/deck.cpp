/*
 * @Author: Maize
 * @Date: 2021-11-13 11:42:04
 * @LastEditTime: 2021-11-17 12:53:51
 * @Description: VE280 2021 Fall Project 4
 * @FilePath: \p4\deck.cpp
 */
#include "deck.h"
#include <iostream>

extern const Suit SuitValue[DIAMONDS + 1] = {SPADES, HEARTS, CLUBS, DIAMONDS};

extern const Spot SpotValue[ACE + 1] = {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                                        JACK, QUEEN, KING, ACE};

int getMin(int a, int b) {
    return a >= b ? b : a;
}

Deck::Deck() {
    reset();
}

void Deck::reset() {
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            deck[j * 13 + i].suit = SuitValue[j];
            deck[j * 13 + i].spot = SpotValue[i];
        }
    }
    next = 0;
}

void Deck::shuffle(int n) {
    Card left[n], right[DeckSize - n];
    for (int i = 0; i < n; i++) {
        left[i] = this->deck[i];
    }
    for (int i = 0; i < DeckSize - n; i++) {
        right[i] = this->deck[n + i];
    }
    for (int i = 0; i < getMin(n, DeckSize - n); i++) {
        deck[2 * i] = right[i];
        deck[2 * i + 1] = left[i];
    }
    if (n != getMin(n, DeckSize - n)) {
        for (int i = 0; i < (n - (DeckSize - n)); i++)
            deck[2 * (DeckSize - n) + i] = left[(DeckSize - n) + i]; //left: 2n - DeckSize -> 2n - DeckSize + i
    }
    else {
        for (int i = 0; i < ((DeckSize - n) - n); i++)
            deck[2 * n + i] = right[n + i];
    }
    next = 0;
}

Card Deck::deal() {
    if (next < DeckSize) {
        return deck[next++];
    }
    throw DeckEmpty();
}

int Deck::cardsLeft() {
    return DeckSize - next;
}