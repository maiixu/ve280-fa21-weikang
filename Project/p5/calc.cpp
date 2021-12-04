/*
 * @Author: Maize
 * @Date: 2021-11-28 10:56:40
 * @LastEditTime: 2021-12-04 13:06:12
 * @Description: VE280 2021 Fall Project 5
 * @FilePath: \p5\calc.cpp
 */

#include "dlist.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// MODIFIES: stack
// EFFECTS: Apply operands involving two numbers.
void twoOperand(char c, Dlist<int> *stack) {
    int temp1, temp2;
    try {
        temp1 = *stack->removeFront();
    } catch (emptyList) {
        throw;
    }
    try {
        temp2 = *stack->removeFront();
    } catch (emptyList) {
        stack->insertFront(&temp1);
        throw;
    }
    switch (c) {
    case '+':
        int result = temp1 + temp2;
        stack->insertFront(&result);
    case '-':
        int result = temp2 - temp1;
        stack->insertFront(&result);
    case '*':
        int result = temp1 * temp2;
        stack->insertFront(&result);
    case '/':
        if (temp1 == 0) {
            stack->insertFront(&temp1);
            cout << "Divide by zero\n";
        }
        else {
            int result = temp2 / temp1;
            stack->insertFront(&result);
        }
    case 'r':
        stack->insertFront(&temp2);
        stack->insertFront(&temp1);
    default:
    }
}

// MODIFIES: stack
// EFFECTS: Apply operands involving one number.
void oneOperand(char c, Dlist<int> *stack) {
    int temp;
    try {
        temp = *stack->removeFront();
    } catch (emptyList) {
        throw;
    }
    switch (c) {
    case 'n':
        temp = temp * (-1);
        stack->insertFront(&temp);
    case 'd':
        stack->insertFront(&temp);
        stack->insertFront(&temp);
    case 'p':
        cout << temp << endl;
        stack->insertFront(&temp);
    default:
    }
}

// MODIFIES: stack
// EFFECTS: Clear the stack.
void clearStack(Dlist<int> *stack) {
    try {
        while (1) {
            stack->removeFront();
        }
    } catch (emptyList) {}
}

// MODIFIES: stack
// EFFECTS: Print all items of the stack.
void printStack(Dlist<int> *stack) {
    Dlist<int> *temp = new Dlist<int>(*stack);
    try {
        while (1) {
            cout << temp->removeFront() << " ";
        }
    } catch (emptyList) {
        cout << endl;
    }
    delete temp;
    //FIXME: delete or not?
}

// MODIFIES: stack
// EFFECTS: Insert an integer into the stack.
void insertInt(string input, Dlist<int> *stack) {
    int integer = stoi(input);
    stack->insertFront(new int(integer));
}

// EFFECTS: Check whether an input string is a valid integer.
bool checkInt(string input) {
    bool returnVal = true;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] > '9' || input[i] < '0') returnVal = false;
    }
    return returnVal;
}

// MODIFIES: stack
// EFFECTS: Check input and apply respective functions according to the input.
bool checkInput(string input, Dlist<int> *stack) {
    bool checkInteger = checkInt(input);
    if (checkInteger) {
        insertInt(input, stack);
        return true;
    }
    if (input.length() > 1) {
        cout << "Bad input\n";
        return true;
    }
    try {
        switch (input[0]) {
        case 'q': return false;
        case '+':
        case '-':
        case '*':
        case '/':
        case 'r':
            twoOperand(input[0], stack);
            return true;
        case 'n':
        case 'd':
        case 'p':
            oneOperand(input[0], stack);
            return true;
        case 'c':
            clearStack(stack);
            return true;
        case 'a':
            printStack(stack);
            return true;
        default:
            cout << "Bad input\n";
            return true;
        }
    } catch (emptyList) {
        cout << "Not enough operands\n";
        return true;
    }
}

int main() {
    string input;
    Dlist<int> *stack = new Dlist<int>;
    while (checkInput(input, stack))
        cin >> input;
    delete stack;
    return 0;
}