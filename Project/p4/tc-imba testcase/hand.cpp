/*
 * @Author: Maize
 * @Date: 2021-11-13 11:41:28
 * @LastEditTime: 2021-11-17 14:48:26
 * @Description: VE280 2021 Fall Project 4
 * @FilePath: \p4\player.cpp
 */
#include "hand.h"

Hand::Hand() {
    discardAll();
}

void Hand::discardAll() {
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::addCard(Card c) {
    switch (c.spot) {
    case ACE:
        curValue.soft = true;
        curValue.count++;
        break;
    case JACK:
    case QUEEN:
    case KING:
        curValue.count += 10;
        break;
    default:
        curValue.count += (c.spot + 2);
        break;
    }
    /*
    if (curValue.count > 21 && curValue.soft == true) {
        curValue.soft == false;
        curValue.count -= 10;
    }
    */
}

HandValue Hand::handValue() const {
    HandValue result = curValue;
    if (curValue.soft) {
        result.count += 10;
        if (result.count > 21) {
            result.soft = false;
            result.count -= 10;
        }
    }
    return result;
}