/*
 * @Author: your name
 * @Date: 2021-11-28 09:11:17
 * @LastEditTime: 2021-12-05 13:03:57
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \p5\list-v1\answer\call.cpp
 */
//
// Created by liu on 2016/7/19.
//

#include "dlist.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

enum STATUS {
    PLATINUM,
    GOLD,
    SILVER,
    REGULAR,
};

const char *STATUS_STR[] = {"platinum", "gold", "silver", "regular"};

struct Customer {
    int timestamp;
    string name;
    int duration;
};

STATUS getStatus(string str) {
    for (int i = 0; i < 4; i++) {
        if (str == STATUS_STR[i]) {
            return STATUS(i);
        }
    }
    return PLATINUM;
}

int main() {
    int num, time_next = 0;
    auto customer = new Dlist<Customer>[4];
    cin >> num;
    if (num > 0) {
        num--;
        cin >> time_next;
    }
    else {
        time_next = -1;
    }
    int time = 0, end = 0;
    while (true) {
        cout << "Starting tick #" << time << endl;
        while (time == time_next && num >= 0) {
            auto temp = new Customer;
            temp->timestamp = time_next;
            cin >> temp->name;
            string str;
            cin >> str;
            auto status = getStatus(str);
            cin >> temp->duration;
            customer[status].insertBack(temp);
            cout << "Call from " << temp->name << " a " << STATUS_STR[status] << " member" << endl;
            num--;
            if (num >= 0) {
                cin >> time_next;
            }
        }
        if (end > time) {
            time++;
            continue;
        }
        bool count = 0;
        for (int i = 0; i < 4; i++) {
            try {
                auto temp = customer[i].removeFront();
                count = 1;
                if (temp->timestamp <= time) {
                    cout << "Answering call from " << temp->name << endl;
                    end += temp->duration;
                    delete temp;
                    break;
                }
                else {
                    customer[i].insertFront(temp);
                }
            } catch (emptyList) {
                continue;
            }
        }
        if (count == 0 && time == end) {
            break;
        }
        time++;
    }
    delete[] customer;
    return 0;
}