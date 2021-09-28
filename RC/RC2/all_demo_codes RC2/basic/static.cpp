#include<iostream>
using namespace std;

void fn(void);
int main()
{
    for (int i = 0; i < 3; i++)
    {
        fn();
    }
}

void fn()
{
    static int count = 0;
    cout << count++ << endl;
}