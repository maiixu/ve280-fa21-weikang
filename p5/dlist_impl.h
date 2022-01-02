#ifndef __DLIST_IMPL_H__
#define __DLIST_IMPL_H__
#include <iostream>
#include "dlist.h"

template <class T>
bool Dlist<T>::isEmpty() const {
    return first == nullptr;
}

template <class T>
void Dlist<T>::insertFront(T *op) {
    node *np = new node;
    np->op = op;
    if (isEmpty()) {
        np->prev = np->next = nullptr;
        last = np;
    }
    else {
        np->next = first;
        np->prev = nullptr;
        first->prev = np;
    }
    first = np;
}

template <class T>
void Dlist<T>::insertBack(T *op) {
    node *np = new node;
    np->op = op;
    if (isEmpty()) {
        np->prev = np->next = nullptr;
        first = np;
    }
    else {
        np->next = nullptr;
        np->prev = last;
        last->next = np;
    }
    last = np;
}

template <class T>
T *Dlist<T>::removeFront() {
    if (isEmpty()) throw emptyList();
    node *returnNode = first;
    T *returnVal = first->op;
    first = first->next;
    if (!first)
        last = nullptr;
    else
        first->prev = nullptr;
    delete returnNode;
    return returnVal;
}

template <class T>
T *Dlist<T>::removeBack() {
    if (isEmpty()) throw emptyList();
    node *returnNode = last;
    T *returnVal = last->op;
    last = last->prev;
    if (!last)
        first = nullptr;
    else
        last->next = nullptr;
    delete returnNode;
    return returnVal;
}

template <class T>
Dlist<T>::Dlist() {
    first = last = nullptr;
}

template <class T>
Dlist<T>::Dlist(const Dlist<T> &l) {
    first = last = nullptr;
    copyAll(l);
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist<T> &l) {
    removeAll();
    copyAll(l);
    return *this;
}

template <class T>
Dlist<T>::~Dlist() {
    removeAll();
}

template <class T>
void Dlist<T>::removeAll() {
    node *temp = first;
    while (temp) {
        delete temp->op;
        node *victim = temp;
        temp = temp->next;
        delete victim;
    }
    first = last = nullptr;
}

template <class T>
void Dlist<T>::copyAll(const Dlist<T> &l) {
    removeAll();
    if (!l.isEmpty()) {
        node *temp = l.first;
        while (temp) {
            T *val = new T(*temp->op);
            insertBack(val);
            temp = temp->next;
        }
    }
}

#endif