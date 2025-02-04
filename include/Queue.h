#ifndef QUEUE_H
#define QUEUE_H

#include <fstream>
#include <iostream>
#include "Node.h"
#include "LinkedList.h"
#include "Ship.h"
#include "Field.h"

class Queue {
public:
    Node* front;
    Node* rear;

    Queue();
    ~Queue();
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);
    Queue(Queue&& other) noexcept; // Added `noexcept`
    Queue& operator=(Queue&& other) noexcept; // Added `noexcept`

    void clear();
    void enqueue(Ship* shipPtr);
    void dequeue(Field& field, LinkedList& ships, std::ofstream& mof);
    bool WaitTeam(char teamName);
};

#endif // QUEUE_H