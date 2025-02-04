#include "LinkedList.h"
#include <iostream>
#include "Ship.h"  // Ensure Ship is included
using namespace std;

LinkedList::LinkedList() : head(nullptr){};

LinkedList::~LinkedList(){
    clear();
}

LinkedList::LinkedList(const LinkedList& other) : head(nullptr) {
    Node* temp = other.head;
    while (temp != nullptr) {
        append(temp->shipPtr);
        temp = temp->next;
    }
}


LinkedList& LinkedList::operator=(const LinkedList& other) {
    if (this == &other) return *this;
    clear();
    Node* temp = other.head;
    while (temp != nullptr) {
        append(temp->shipPtr);
        temp = temp->next;
    }
    return *this;
}


LinkedList& LinkedList::operator=(LinkedList&& other) noexcept {
    if (this == &other) return *this;
    clear();
    head = other.head;
    other.head = nullptr;
    return *this;
}

LinkedList::LinkedList(LinkedList&& other) noexcept : head(other.head) {
            other.head = nullptr;
        }

void LinkedList::append(Ship* shipPtr){
    Node * newNode = new Node();
    newNode -> shipPtr = shipPtr; 
    newNode -> next = nullptr;

    if(head == nullptr){
        head = newNode;
    }else{
        Node* temp = head;
        while(temp -> next != nullptr){
            temp = temp -> next;
        }
        temp -> next = newNode;
    }
}

void LinkedList::deleteNode(Ship* shipPtr){
    Node* temp = head;
    Node* prev = nullptr;

    while(temp != nullptr && temp -> shipPtr != shipPtr){
        prev = temp;
        temp = temp -> next;
    }

    if(temp == nullptr){
        return;
    }

    if(prev == nullptr){
        head = temp -> next;
    }else{
        prev -> next = temp -> next;
    }

    delete temp;
}


void LinkedList::clear() {
    Node* temp;
    while(head!=nullptr){
        temp = head;
        head = head -> next;
        delete temp;
    }
}

string LinkedList::findShipname(int x, int y) {
    Node* findptr = head;
    while (findptr != nullptr) {
        if (findptr->shipPtr->posX == x && findptr->shipPtr->posY == y) {
            return findptr->shipPtr->Ship_name;
        }
        findptr = findptr->next;
    }
    return "nothing"; 
}

char LinkedList::findShipTeam(int x, int y) {
    Node* findteam = head;
    while (findteam != nullptr) {
        if (findteam->shipPtr->posX == x && findteam->shipPtr->posY == y) {
            return findteam->shipPtr->Team_name;
        }
        findteam = findteam->next;
    }
    return '-';
}

Ship* LinkedList::findShipPtr(int x,int y){
        Node* findShipptr = head;
    while (findShipptr != nullptr) {
        if (findShipptr->shipPtr->posX == x && findShipptr->shipPtr->posY == y) {
            return findShipptr->shipPtr;
        }
        findShipptr = findShipptr->next;
        }
    return nullptr;
}

bool LinkedList::remainTeam(char TeamName){
    Node* ptr = head;
    while (ptr != nullptr) {
        if (ptr->shipPtr->Team_name == TeamName) {
            return true;
        }
        ptr = ptr->next;
        }
    return false;
}