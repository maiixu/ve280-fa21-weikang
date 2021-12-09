/*
 * @Author: Maize
 * @Date: 2021-11-28 10:56:52
 * @LastEditTime: 2021-12-09 08:55:54
 * @Description: VE280 2021 Fall Project 5
 * @FilePath: \p5\call.cpp
 */

#include "dlist.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

const string STATUS[] = {"regular", "silver", "gold", "platinum"};

const int NUM_STATUS = 4;
class Customer {
    string name;
    int status;
    int tick;
    int duration;

public:
    Customer(int duration, string name, int status, int tick) {
        this->duration = duration;
        this->name = name;
        this->status = status;
        this->tick = tick;
    };

    Customer() {
        this->duration = -1;
        this->name = "";
        this->status = -1;
        this->tick = -1;
    }

    void setVal(int duration, string name, int status, int tick) {
        this->duration = duration;
        this->name = name;
        this->status = status;
        this->tick = tick;
    };

    int getStatus() {
        return status;
    }
    void setStatus(int status) {
        this->status = status;
    }

    int getDuration() {
        return duration;
    }
    void setDuration(int d) {
        duration = d;
    }

    string getName() {
        return name;
    }
    void setName(string name) {
        this->name = name;
    }

    int getTick() {
        return tick;
    }
    void setTick(int tick) {
        this->tick = tick;
    }
};

int trans_str(string str) {
    switch (str[0]) {
    case 'r': {
        return 0;
    }
    case 's': {
        return 1;
    }
    case 'g': {
        return 2;
    }
    case 'p': {
        return 3;
    }
    default: return -1;
    }
}

int main() {
    Dlist<Customer> *queue = new Dlist<Customer>[4]; // Storaging customer number
    int customerNum;
    cin >> customerNum;
    int tick = 0, dur = 0, next = 0, end = 0;
    if (customerNum > 0) {
        customerNum--;
        cin >> next;
    }
    else {
        next = -1;
    }

    bool isOccupied = false;
    while (1) {
        cout << "Starting tick #" << tick << endl;
        while (customerNum >= 0 && tick == next) {
            string nameStr, statusStr;
            cin >> nameStr >> statusStr >> dur;
            int status = trans_str(statusStr);
            Customer *temp = new Customer(dur, nameStr, status, tick);
            queue[status].insertBack(temp);
            cout << "Call from " << temp->getName() << " a " << STATUS[status] << " member" << endl;
            customerNum--;
            if (customerNum >= 0) {
                cin >> next;
            }
        }
        if (end > tick) {
            tick++;
            continue;
        }
        else
            isOccupied = false;
        bool judge = true;
        for (int i = NUM_STATUS - 1; i >= 0; i--) {
            if (!queue[i].isEmpty()) {
                auto temp = queue[i].removeFront();
                judge = false;
                if (temp->getTick() <= tick) {
                    cout << "Answering call from " << temp->getName() << endl;
                    end += temp->getDuration();
                    delete temp;
                    isOccupied = true;
                    break;
                }
                else {
                    queue[i].insertFront(temp);
                }
            }
        }
        if (judge == true && tick == end && customerNum <= 0 && tick >= next) break;
        tick++;
        if (isOccupied == false) end++;
    }

    delete[] queue;
    return 0;
}