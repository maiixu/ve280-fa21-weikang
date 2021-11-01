/*
 * @Author: your name
 * @Date: 2021-10-05 18:03:54
 * @LastEditTime: 2021-11-01 22:28:52
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \p1\test.cpp
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    // TODO: Slide4 Test Code
    /*
    int foo = 1;
    int *bar;   // Define a pointer
    bar = &foo; // addressing operation
    cout << "bar's value is " << *bar << endl;
    cout << "bar's value is " << bar << endl;
    *bar = 2; // dereference operation
    cout << "bar's value is " << bar << endl;
    return 0;
    */
    /*
    int iVal = 1024;
    int &refVal = iVal;
    cout << "refVal's address is " << &refVal << endl;
    cout << "iVal's value is " << iVal << endl;
    int iVal2 = 10;
    int &refVal2 = iVal2;
    cout << "iVal2's address is " << &refVal2 << endl;
    refVal = iVal2;
    cout << "iVal2's address is " << &refVal2 << endl;
    cout << "refVal's address is " << &refVal << endl;
    cout << "iVal's value is " << iVal << endl;
    return 0;
    */
    /*
    int x = 0;
    int *p = &x; // *取值符 &取址符
    int y = 1;
    p = &y;
    *p = 2;
    cout << "p = " << p << endl;
    cout << "x = " << x << endl;
    cout << "y = " << &y << endl;
    return 0;
    */
    string foo = "Hello, world!";
    int bar = 0;
    cout << foo << setw(20) << bar << endl;
    return 0;
}