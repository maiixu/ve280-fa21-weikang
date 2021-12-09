/*
 * @Author: your name
 * @Date: 2021-11-28 09:11:17
 * @LastEditTime: 2021-12-08 00:35:53
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \p5\list-v1\test-cases\test-exception.cpp
 */
#include <iostream>
#include "dlist.h"
#include "dlist_impl.h"

using namespace std;

int main(int argc, char *argv[]) {
    Dlist<int> ilist;
    try {
        int *ip = ilist.removeFront();
    } catch (...) {
        cout << "Exception" << endl;
    }
    return 0;
}