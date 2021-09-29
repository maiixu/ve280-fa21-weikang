#include <iostream>
#include "touch_fish.h"
#include "study.h"
using namespace std;
int main()
{
    int i;
    cout << "please input the value of i from 0 to 1:\n";
    cin >> i;
    if(!i) touch_fish();
    else study();
    return 0;
}
