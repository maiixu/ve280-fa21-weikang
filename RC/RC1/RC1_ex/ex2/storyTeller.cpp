#include "node.h"
#include "constant.h"
#include <iostream>

using namespace std;
int main(){
    Node story(0, 2);
    story.addChild(1);
    story.addChild(3);
    story[0].addChild(2);
    story[1].addChild(4);
    story[1][0].addChild(5);
    story[1][0].addChild(7);
    story[1][0][0].addChild(6);
    story[1][0][1].addChild(8);
    story[1][0][1].addChild(9);
    story[1][0][1][1].addChild(10);

    vector<int> my_story;
    story.traverse(my_story);
    for(unsigned long long i=0; i<my_story.size();i++){
        cout << storyProcess[i];
    }
    cout <<endl;

    return 0;
}


