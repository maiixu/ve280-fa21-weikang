/*
 * @Author: Maize
 * @Date: 2021-11-13 11:41:28
 * @LastEditTime: 2021-11-17 13:31:18
 * @Description: VE280 2021 Fall Project 4
 * @FilePath: \p4\player.cpp
 */
#include "player.h"

bool Player::draw(Card dealer, const Hand &player) {
    if (player.handValue().count <= 11)
        return true;
    else if (player.handValue().count == 12) {
        if (dealer.spot >= 4 && dealer.spot <= 6)
            return false;
        else
            return true;
    }
    else if (player.handValue().count >= 13 && player.handValue().count <= 16) {
        if (dealer.spot <= 6 && dealer.spot >= 2)
            return false;
        else
            return true;
    }
    else
        return false;
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
private:
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
        if (c.spot >= 8)
            count++;
        else
            count--;
    }
    void shuffled() override {
        count = 0;
    }
};

extern Player *get_Counting() {
    return (Player *)new countingPlayer();
}