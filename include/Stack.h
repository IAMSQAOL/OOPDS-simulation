#ifndef STACK_H
#define STACK_H
#include <fstream>
#include <iostream>
using namespace std;

#include "Node.h"

class Ship;
class Stack{
    protected:
        struct Node{
            Ship* shipPtr;
            Node * next;
        };
        Ship* pop();
    public:
        Node* top;
        int size=0;
        const int maxSize=5;
        Stack() : top(nullptr),size(0){}
        bool isEmpty() const;
        bool isFull() const;
        void push(Ship* shipPtr, ofstream& mof);
        Ship* pop(ofstream& mof);
        ~Stack();
};

#endif