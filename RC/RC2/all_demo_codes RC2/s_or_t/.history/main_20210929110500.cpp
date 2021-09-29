/*
 * @Author: your name
 * @Date: 2021-09-28 16:40:05
 * @LastEditTime: 2021-09-29 11:03:18
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \s_or_t\main.cpp
 */

#include <iostream>
#include "touch_fish.h"
#include "study.h"
using namespace std;
int main()
{
    int i;
    cout << "please input the value of i from 0 to 1:\n";
    cin >> i;
    if (!i)
        touch_fish();
    else
        study();
    return 0;
}
