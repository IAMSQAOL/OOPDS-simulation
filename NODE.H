#ifndef NODE_H
#define NODE_H
#include "SHIP.H"

struct Node{ 
    Ship* shipPtr;
    Node* next;
};

#endif