#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "Node.h"

class LinkedList {
public:
    Node* head;

    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);
    LinkedList(LinkedList&& other) noexcept;  // Added `noexcept`
    LinkedList& operator=(LinkedList&& other) noexcept; // Added `noexcept`

    void append(Ship* shipPtr);
    void deleteNode(Ship* shipPtr);
    void clear();
    std::string findShipname(int x, int y);
    char findShipTeam(int x, int y);
    Ship* findShipPtr(int x, int y);
    bool remainTeam(char TeamName);
};

#endif 
