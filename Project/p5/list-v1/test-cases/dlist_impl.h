/*
 * @Author: Maize
 * @Date: 2021-11-28 10:56:29
 * @LastEditTime: 2021-12-08 00:25:50
 * @Description: VE280 2021 Fall Project 5
 * @FilePath: \p5\dlist_impl.h
 */
#ifndef __DLIST_IMPL_H__
#define __DLIST_IMPL_H__

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
        np->prev = np->next = np;
        last = np;
    }
    else {
        np->next = first;
        np->prev = last;
    }
    first = np;
}

template <class T>
void Dlist<T>::insertBack(T *op) {
    node *np = new node;
    np->op = op;
    if (isEmpty()) {
        np->prev = np->next = np;
        first = np;
    }
    else {
        np->next = first;
        np->prev = last;
    }
    last = np;
}

template <class T>
T *Dlist<T>::removeFront() {
    if (isEmpty()) throw emptyList();
    node *returnNode = first;
    T *returnVal = first->op;
    if (first->next == first)
        first = last = nullptr;
    else {
        returnNode->prev->next = returnNode->next;
        returnNode->next->prev = returnNode->prev;
        first = returnNode->next;
    }
    delete returnNode;
    return returnVal;
}

template <class T>
T *Dlist<T>::removeBack() {
    if (isEmpty()) throw emptyList();
    node *returnNode = last;
    T *returnVal = last->op;
    if (first->next == first)
        first = last = nullptr;
    else {
        returnNode->prev->next = returnNode->next;
        returnNode->next->prev = returnNode->prev;
        last = returnNode->prev;
    }
    delete returnNode;
    return returnVal;
}

template <class T>
Dlist<T>::Dlist() {
    first = last = nullptr;
}

template <class T>
Dlist<T>::Dlist(const Dlist &l) {
    removeAll();
    copyAll(l);
}

template <class T>
Dlist<T>::~Dlist() {
    removeAll();
}

template <class T>
void Dlist<T>::removeAll() {
    if (!isEmpty()) {
        node *temp = first;
        while (temp != temp->next) {
            temp = temp->next;
            delete temp->prev->op;
            delete temp->prev;
        }
        delete temp->op;
        delete temp;
    }
    first = last = nullptr;
}

template <class T>
void Dlist<T>::copyAll(const Dlist &l) {
    if (l.first != nullptr) {
        node *temp = l.first;
        while (temp != temp->next) {
            insertBack(new T(*temp->op));
            temp = temp->next;
        }
        this->insertBack(temp->op);
    }
}

#endif