#include "node.h"

void Node::addChild(Node *child){
    if(child_num == n){
        delete child;
        throw tooManyChildren();
    }
    else{
        children[child_num] = child;
        child_num ++;
        height = (height > child->getHeight() + 1) ? height : child->getHeight() + 1;
        child->parent = this;

        Node* curr = parent;
        int i = 1;
        while(curr){
            if(curr->height < height+i) curr->height = height + i;
            i++;
            curr = curr->parent;
        }
    }
}

bool Node::equal(Node* sub){
    bool final_judge = true;
    if(child_num == sub->child_num && height == sub->getHeight()) {
        final_judge = final_judge && (value == sub->value);
        for (int i = 0; i < child_num; i++) {
            final_judge = final_judge && children[i]->equal(sub->children[i]);
        }
        return final_judge;
    }
    else return false;
}


Node::Node(int _value, int _n):value(_value), child_num(0), n(_n), parent(nullptr), children(new Node*[_n]), height(0){}

Node::~Node(){
    for(int i=0;i<child_num;i++) delete children[i];
    delete []children;
}

void Node::addChild(int _value){
    Node* np = new Node(_value, n);
    addChild(np);
}

Node & Node::operator[](int i){
    if(i>=0 && i<child_num){
        Node & my_ref = *children[i];
        return my_ref;
    }
    else throw invalidIndex();
}

void Node::traverse(vector<int>& traverseValue){
    traverseValue.push_back(value);
     if(child_num!=0){
         for(int i=0;i<child_num;i++){
             children[i]->traverse(traverseValue);
         }
     }
}

int Node::getHeight(){
    return height;
}

bool Node::contain(Node *sub){
    bool final_judge = equal(sub);
    if(child_num != 0){
        for (int i = 0; i < child_num; i++) {
            final_judge = final_judge || children[i]->contain(sub);
        }
    }
    return final_judge;
}


