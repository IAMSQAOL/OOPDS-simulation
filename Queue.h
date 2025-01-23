#ifndef QUEUE_H
#define QUEUE_H

#include "Ship.h"

struct Node {
    Ship* data;
    Node* next;
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue();
    ~Queue();
    void enqueue(Ship* ship);
    Ship* dequeue();
    bool isEmpty() const;
    void display() const;
};

#endif // QUEUE_H