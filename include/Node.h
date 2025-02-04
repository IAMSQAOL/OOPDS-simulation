#ifndef NODE_H
#define NODE_H

class Ship;  // Forward declaration

struct Node {
    Ship* shipPtr;
    Node* next;
};

#endif // NODE_H