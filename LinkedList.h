#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Ship.h"

struct Node {
    Ship* data;
    Node* next;
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    void append(Ship* data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            temp->data->display();
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    void deleteNode(Ship* data) {
        Node* temp = head;
        Node* prev = nullptr;

        if (temp != nullptr && temp->data == data) {
            head = temp->next;
            delete temp;
            return;
        }

        while (temp != nullptr && temp->data != data) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) return;

        prev->next = temp->next;
        delete temp;
    }

    ~LinkedList() {
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

#endif // LINKEDLIST_H