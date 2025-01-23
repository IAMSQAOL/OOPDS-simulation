#include "Queue.h"
#include <iostream>

using namespace std;

Queue::Queue() : front(nullptr), rear(nullptr) {}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Queue::enqueue(Ship* ship) {
    Node* newNode = new Node();
    newNode->data = ship;
    newNode->next = nullptr;

    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

Ship* Queue::dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty" << endl;
        return nullptr;
    }

    Node* temp = front;
    Ship* ship = front->data;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    return ship;
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

void Queue::display() const {
    Node* temp = front;
    while (temp != nullptr) {
        temp->data->display();
        temp = temp->next;
    }
    cout << "nullptr" << endl;
}