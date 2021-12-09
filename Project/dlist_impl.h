#ifndef __DLIST_IMPL_H__
#define __DLIST_IMPL_H__
#include "dlist.h"
#include <iostream>
#include <cstdlib>
template <class T>
Dlist<T>::Dlist(): first(0),last(0)
{
    
}

template <class T>
void Dlist<T>::copyAll(const Dlist &l){
    if (l.isEmpty()) return;
   // first=l.first;
    node* lfirst=l.first;
    T * op=new T(*lfirst->op);
    insertBack(op);
    while(lfirst->next!=NULL){
        lfirst=lfirst->next;
        T * op=new T(*lfirst->op);
        insertBack(op);
    }
}

template <class T>
void Dlist<T>::removeAll(){
    while (!isEmpty()){
        T *op=removeBack();
        delete op;
    }
}

template <class T>
Dlist<T>::Dlist (const Dlist &l){
    if (l.isEmpty()) return;
    removeAll();
    copyAll(l);
}

template <class T>
Dlist<T>::~Dlist(){
    removeAll();
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l){
    if (l.isEmpty()) return *this;
    removeAll();
    copyAll(l);
    return *this;
}

template <class T>
bool Dlist<T>::isEmpty() const{
    if (!first)
        return 1;
    else
        return 0;
}

template <class T>
void Dlist<T>::insertFront(T *op){
    node * newNode=new node;
    newNode->op=op;
    newNode->prev=NULL;
    newNode->next=first;
    //restore invariant
    if (!isEmpty()){
        first->prev=newNode;
        first=newNode;
    }
    else{
        first=last=newNode;
    }
}

template <class T>
void Dlist<T>::insertBack(T* op){
    node * newNode=new node;
    newNode->op=op;
    newNode->next=NULL;
    newNode->prev=last;
    //restore invariant
    if (!isEmpty()){
        last->next=newNode;
        last=newNode;
    }
    else{
        first=last=newNode;
    }
}

template <class T>
T* Dlist<T>::removeFront(){
    T* firstValue=first->op;
    node* victim=first;
    //restore invariant
    if (first==last){
        delete first;
        first=NULL;
        last=NULL;
        return firstValue;
    }
    else{
        (first->next)->prev=NULL;
        first=victim->next;
        delete victim;
        return firstValue;
    }
}

template <class T>
T* Dlist<T>::removeBack(){
    T* lastValue=last->op;
    node* secondButLast=last->prev;
    delete last;
    //restore invariant
    if (first==last){
        first=NULL;
        last=NULL;
        return lastValue;
    }
    else{
        secondButLast->next=NULL;
        last=secondButLast;
        return lastValue;
    }
}
#endif
