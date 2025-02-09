/**********|**********|**********|
Program: LINKEDLIST.CPP
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#include "../include/LINKEDLIST.H"
#include <iostream>

LinkedList::LinkedList() : head(nullptr){} 


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

LinkedList::LinkedList(LinkedList&& other) noexcept : head(other.head) {
    other.head = nullptr;
}

LinkedList& LinkedList::operator=(LinkedList&& other) noexcept {
    if (this == &other) return *this;
    clear();
    head = other.head;
    other.head = nullptr;
    return *this;
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

//return Ship's name when correspond position is found
std::string LinkedList::findShipname(int x, int y) {
    Node* findptr = head;
    while (findptr != nullptr) {
        if (findptr->shipPtr->posX == x && findptr->shipPtr->posY == y) {
            return findptr->shipPtr->Ship_name;
        }
        findptr = findptr->next;
    }
    return "nothing"; 
}

//return Ship's Team Name when correspond position is found
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

//return Ship's pointer when correspond position is found
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

//return false when no Team with 'A' or 'B' remain inside LinkedList
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
