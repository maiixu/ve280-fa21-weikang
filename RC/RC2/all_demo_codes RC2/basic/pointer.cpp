#include <iostream>
using namespace std;

int main()
{
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {1, 2, 3, 4};
    int *ptr = b[0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0 ; j < 2; j++)
        {
            cout << i << "," << j << ":" << a[i][j] << "," << b[i][j] <<
                 "," << *(ptr + i * 2 + j) << endl;
        }
    }
}