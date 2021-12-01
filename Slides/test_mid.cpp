/*
 * @Author: your name
 * @Date: 2021-10-05 18:03:54
 * @LastEditTime: 2021-11-04 13:43:47
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \p1\test.cpp
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void func(int x)
{
    if (x < 4)
    {
        cout << "x before is " << x << ",";
        func(++x);
    }
    cout << "x after is " << x << endl;
}

int plus_one(int x)
{
    return (x + 1);
}
int plus_two(int x)
{
    return (1 + plus_one(x));
}

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

    // int x = 0;
    // int *p = &x; // *取值符 &取址符
    // int y = 1;
    // p = &y;
    // *p = 2;
    // cout << "p = " << p << endl;
    // cout << "x = " << x << endl;
    // cout << "y = " << y << endl;

    func(1);
    int a;
    int const *c = &a;
    // *c = 10;
    // int result = 0;
    // result = plus_two(0);
    // cout << result;
    // return 0;

    //  string foo = "Hello, world!";
    // int bar = 0;
    //  cout << foo << setw(20) << bar << endl;
    // return 0;
}