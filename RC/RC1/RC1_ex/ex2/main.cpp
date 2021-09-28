#include <iostream>
#include "node.h"
using namespace std;

int main() {
    Node mpc(1,2);
    Node sjj(2,2);

    sjj.addChild(3);
    sjj.addChild(4);

    mpc.addChild(2);
    mpc.addChild(6);
    mpc[0].addChild(3);
    mpc[0].addChild(4);
    mpc[1].addChild(5);

    vector<int> mm;
    mpc.traverse(mm);
    for(int i : mm)cout << i <<endl;
    cout << mpc.contain(&sjj);


    return 0;
}