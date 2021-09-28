#include<iostream>
using namespace std;

enum color{r, g = 30, b} c;
int main()
{

    c = r;
    cout << c << endl;

    c = g;
    cout << c << endl;

    c = b;
    cout << c << endl;

    color d = c;
    cout <<d << endl;
}

