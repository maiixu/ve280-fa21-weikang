/*
 * @Author: Maize
 * @Date: 2021-11-13 11:41:28
 * @LastEditTime: 2021-11-17 18:52:46
 * @Description: VE280 2021 Fall Project 4
 * @FilePath: \p4\player.cpp
 */
#include "player.h"
#include <iostream>

bool Player::draw(Card dealer, const Hand &player) {
    // If the player’s hand totals 11 or less, he always hits.
    // If the player’s hand totals 12, he stands if the dealer shows 4, 5, or 6; otherwise he hits.
    // If the player’s hand totals between 13 and 16 inclusive, he stands if the dealer shows a 2 through a 6 inclusive; otherwise he hits.
    // If the player's hand totals 17 or greater, he always stands.
    if (!player.handValue().soft) {
        if (player.handValue().count <= 11)
            return true;
        else if (player.handValue().count == 12) {
            if (dealer.spot >= 2 && dealer.spot <= 4)
                return false;
            else
                return true;
        }
        else if (player.handValue().count >= 13 && player.handValue().count <= 16) {
            if (dealer.spot <= 4 && dealer.spot >= 0)
                return false;
            else
                return true;
        }
        else
            return false;
    }
    // If the player’s hand totals 17 or less, he always hits.
    // If the player’s hand totals 18, he stands if the dealer shows a 2, 7, or 8, otherwise he hits.
    // If the player’s hand totals 19 or greater, he always stands.
    else {
        if (player.handValue().count <= 17)
            return true;
        else if (player.handValue().count == 18) {
            if (dealer.spot == 0 || dealer.spot == 5 || dealer.spot == 6)
                return false;
            else
                return true;
        }
        else
            return false;
    }
}

class simplePlayer : public Player {
public:
    int bet(unsigned int bankroll, unsigned int minimum) override {
        return (int)minimum;
    }
    bool draw(Card dealer, const Hand &player) override {
        return Player::draw(dealer, player);
    }
    void expose(Card c) override {
    }
    void shuffled() override {
    }
};

extern Player *get_Simple() {
    return (Player *)new simplePlayer();
}

class countingPlayer : public Player {
    int count;

public:
    int bet(unsigned int bankroll, unsigned int minimum) override {
        if (count >= 2 && bankroll >= 2 * minimum) {
            return 2 * minimum;
        }
        return (int)minimum;
    }
    bool draw(Card dealer, const Hand &player) override {
        return Player::draw(dealer, player);
    }
    void expose(Card c) override {
        if (c.spot >= 0 && c.spot <= 4)
            count++;
        else if (c.spot >= 8)
            count--;
    }
    void shuffled() override {
        count = 0;
    }
};

extern Player *get_Counting() {
    return (Player *)new countingPlayer();
}