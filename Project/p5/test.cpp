/*
 * @Author: your name
 * @Date: 2019-11-05 17:14:38
 * @LastEditTime: 2021-12-02 22:09:47
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \p5\test.cpp
 */
#include <iostream>
#include "dlist.h"
#include "dlist_impl.h"
using namespace std;

int main(int argc, char *argv[]) {
    int result = 0;

    Dlist<int> ilist;
    int *ip = new int(1);
    cout << "C" << endl;
    ilist.insertFront(ip);
    cout << "B" << endl;
    ip = ilist.removeFront();
    cout << "A" << endl;
    if (*ip != 1)
        result = -1;
    delete ip;

    if (!ilist.isEmpty())
        result = -1;

    return result;
}
