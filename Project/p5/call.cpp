/*
 * @Author: Maize
 * @Date: 2021-11-28 10:56:52
 * @LastEditTime: 2021-12-09 15:24:08
 * @Description: VE280 2021 Fall Project 5 Call Center Simulation
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
    //OVERVIEW: A class that contains information about a customer.
    string name;
    int status;
    int tick;
    int duration;

public:
    // MODIFIES: this.
    // EFFECTS: Default constructor.
    Customer(int duration_, string name_, int status_, int tick_) {
        this->duration = duration_;
        this->name = name_;
        this->status = status_;
        this->tick = tick_;
    };

    // MODIFIES: this.
    // EFFECTS: Default constructor.
    Customer() {
        this->duration = -1;
        this->name = "";
        this->status = -1;
        this->tick = -1;
    }

    // EFFECTS: Return Status.
    int getStatus() const {
        return status;
    }

    // EFFECTS: Return Duration.
    int getDuration() const {
        return duration;
    }

    // EFFECTS: Return Name.
    string getName() const {
        return name;
    }

    // EFFECTS: Return Tick.
    int getTick() const {
        return tick;
    }
};

// EFFECTS: Return int that is translated from a string.
int trans_str(string str) {
    switch (str[0]) {
    case 'r': return 0;
    case 's': return 1;
    case 'g': return 2;
    case 'p': return 3;
    default: return -1;
    }
}

int main() {
    Dlist<Customer> *queue = new Dlist<Customer>[4]; // Storaging customer number
    int customerNum;
    cin >> customerNum;
    int tick = 0, dur = 0, next = -1, end = 0;
    if (customerNum > 0) {
        customerNum--;
        cin >> next;
    }
    bool isOccupied = false; // Represent whether the operator is occupied.
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
            if (customerNum >= 0)
                cin >> next;
        }
        if (end > tick) {
            tick++;
            continue;
        } // The operator is occupied.
        else
            isOccupied = false;
        for (int i = NUM_STATUS - 1; i >= 0; i--) {
            if (!queue[i].isEmpty()) {
                Customer *temp = queue[i].removeFront();
                if (temp->getTick() <= tick) {
                    cout << "Answering call from " << temp->getName() << endl;
                    end += temp->getDuration();
                    delete temp;
                    isOccupied = true;
                    break;
                }
                else
                    queue[i].insertFront(temp);
            }
        }
        if (tick == end && customerNum <= 0 && tick >= next) break;
        if (isOccupied == false) end++; //If not occupied, the current end iterates along with tick.
        tick++;
    }
    delete[] queue;
    return 0;
}

//输入空文件会咋样？需要检测么？