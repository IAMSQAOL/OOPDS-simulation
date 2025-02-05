#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include "SHIP.H"
#include "NODE.H"
class LinkedList{
    public:
        Node* head;
        LinkedList();
        ~LinkedList();

        LinkedList(const LinkedList& other);


        LinkedList& operator=(const LinkedList& other);

        LinkedList(LinkedList&& other) noexcept;

        LinkedList& operator=(LinkedList&& other) noexcept;

        void append(Ship* shipPtr);

        void deleteNode(Ship* shipPtr);
        void clear() ;

        std::string findShipname(int x, int y);

        char findShipTeam(int x, int y) ;

        Ship* findShipPtr(int x,int y);

        bool remainTeam(char TeamName);
};

#endif