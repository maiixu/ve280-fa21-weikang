/*
 * @Author: Maize
 * @Date: 2021-11-28 10:56:52
 * @LastEditTime: 2021-12-04 21:47:13
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
    int duration;
    string name;
    int status;
    int tick;

public:
    Customer(int duration, string name, int status, int tick) {
        this->duration = duration;
        this->name = name;
        this->status = status;
        this->tick = tick;
    };

    int getStatus() {
        return status;
    }

    int getDuration() {
        return duration;
    }

    string getName() {
        return name;
    }

    int getTick() {
        return tick;
    }
};

int main() {
    cout << "B" << endl;
    Dlist<Customer> *queue = new Dlist<Customer>[4]; // Storaging customer number
    Dlist<Customer> *wlist = new Dlist<Customer>[4]; // Storaging waiting list
    int customerNum;
    cin >> customerNum;
    int tick, dur = 0;
    cout << "A" << endl;
    for (int i = 0; i < customerNum; i++) {
        int duration, status;
        string name, statusName;
        cin >> tick;
        cin >> name;
        cin >> statusName;
        cin >> duration;
        switch (statusName[0]) {
        case 'r':
            status = 0;
            queue[status].insertFront(new Customer(duration, name, status, tick)); // FIXME: why 不是 pointer
            break;
        case 's':
            status = 1;
            queue[status].insertFront(new Customer(duration, name, status, tick)); // FIXME: why 不是 pointer
            break;
        case 'g':
            status = 2;
            queue[status].insertFront(new Customer(duration, name, status, tick)); // FIXME: why 不是 pointer
            break;
        case 'p':
            status = 3;
            queue[status].insertFront(new Customer(duration, name, status, tick)); // FIXME: why 不是 pointer
            break;
        default: status = -1; break;
        }
    }
    for (int i = 0; i < tick; i++) {
        cout << "Starting tick #" << i << endl;
        for (int status = 0; status < NUM_STATUS; status++) {
            Customer tempCustomer = *queue[status].removeBack();
            wlist[status].insertFront(&tempCustomer);
            while (tempCustomer.getTick() != i) {
                cout << "Call from " << tempCustomer.getName() << " a " << STATUS[status] << " member" << endl;
                Customer tempCustomer = *queue[status].removeBack();
                wlist[status].insertFront(&tempCustomer);
            }
            cout << "Call from " << tempCustomer.getName() << " a " << STATUS[status] << " member" << endl;
        }
        if (dur == 0) {
            for (int status = NUM_STATUS; status > 0; status--) {
                if (!wlist[status].isEmpty()) {
                    Customer tempCustomer = *queue[status].removeBack();
                    cout << "Answering call from " << tempCustomer.getName() << endl;
                    dur = tempCustomer.getDuration();
                }
            }
        }
        else
            dur--;
    }
    for (int i = 0; i < dur; i++) {
        cout << "Starting tick #" << tick << endl;
    }
    return 0;
}