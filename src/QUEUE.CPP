/**********|**********|**********|
Program: QUEUE.CPP
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#include <iostream>
#include "../include/QUEUE.H"
#include "../include/FIELD.H"
#include "../include/OUTPUT.H"
#include "../include/LINKEDLIST.H"

Queue::Queue() : front(nullptr), rear(nullptr){} 
        Queue::~Queue(){
            clear();
        }

        Queue::Queue(const Queue& other) : front(nullptr), rear(nullptr) {
            Node* temp = other.front;
            while (temp != nullptr) {
                enqueue(temp->shipPtr);
                temp = temp->next;
            }
        }
        
        Queue& Queue::operator=(const Queue& other) {
            if (this == &other) return *this;
            clear();
            Node* temp = other.front;
            while (temp != nullptr) {
                enqueue(temp->shipPtr);
                temp = temp->next;
            }
            return *this;
        }

        Queue::Queue(Queue&& other) noexcept : front(other.front), rear(other.rear) {
            other.front = nullptr;
            other.rear = nullptr;
        }

        Queue& Queue::operator=(Queue&& other) noexcept {
            if (this == &other) return *this;
            clear();
            front = other.front;
            rear = other.rear;
            other.front = nullptr;
            other.rear = nullptr;
            return *this;
        }

        void Queue::enqueue(Ship* shipPtr){
            Node * newNode = new Node();
            newNode -> shipPtr = shipPtr; 
            newNode -> next = nullptr;

            if(front == nullptr){
                front = newNode;
                rear = newNode;
            }else{
                rear -> next = newNode;
                rear = newNode;
            }
        }

        void Queue::dequeue(Field& field,LinkedList& ships){
            if(front == nullptr){
                return;
            }
            Node* temp = front;
            int newX, newY;
            do {
                newX = rand() % 10;
                newY = rand() % 10;
            } while (field.checkCell(newY, newX) != "0");
            temp->shipPtr->posX = newX;
            temp->shipPtr->posY = newY;
            mof << temp->shipPtr->Ship_name <<" return to battlefield at ("<<newX <<","<<newY<<") !"<<std::endl;
            std::cout << temp->shipPtr->Ship_name <<" return to battlefield at ("<<newX <<","<<newY<<") !"<<std::endl;
            field.updateField(temp->shipPtr, newY, newX);
            ships.append(temp->shipPtr);
            front = front -> next;
            delete temp;
        }

        bool Queue::WaitTeam(char teamName){
            Node* temp = front;
            while (temp != nullptr) {
                if (temp->shipPtr->Team_name == teamName) {
                    return true; 
                }
                temp = temp->next;
            }
            return false;
        }

        void Queue::clear() {
            Node* temp;
            while(front!=nullptr){
                temp = front;
                front = front -> next;
                delete temp;
            }
            rear = nullptr;
        }