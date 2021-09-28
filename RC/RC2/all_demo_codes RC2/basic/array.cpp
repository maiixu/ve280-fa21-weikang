#include <iostream>
using namespace std;

#include<iomanip>
using std::setw;

int main()
{
    int a[10] = {1, 2, 3}; // the left will be initiallized with 0.

    for (int i = 0 ; i < 10; i++)
    {
        cout << setw(4) << i << ":" <<setw(8)<< a[i] << endl;
    }

    int b[] = {1, 2, 3};

}