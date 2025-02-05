#ifndef STACK_H
#define STACK_H
#include "NODE.H"
#include "SHIP.H"

class Stack{
    protected:
        struct Node{
            Ship* shipPtr;
            Node * next;
        };
        Node* top;
    public:
        int size=0;
        const int maxSize=5;
        Stack();

        bool isEmpty() const;
        bool isFull() const;

        void push(Ship* shipPtr);

        Ship* pop();


        ~Stack();
};

#endif