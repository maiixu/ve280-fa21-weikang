#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    cout << time(NULL) << endl;
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        int j = rand();
        cout << j << endl;
    }
}