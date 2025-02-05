#include "STACK.H"
#include <iostream>
#include "OUTPUT.H"

Ship* Stack::pop(){
            if(isEmpty()){
                std::cout<<"Stack empty dumbass your code suck" << std::endl;
                return nullptr;
            }
            Node*temp = top;
            Ship* shipPtr = top ->shipPtr;
            top = top->next;
            delete temp;
            size--;
            //cout << "check2 " << size  << endl;
            return shipPtr;
        }

        Stack::Stack() : top(nullptr),size(0){}

        bool Stack::isEmpty() const{
            return top == nullptr;
        }
        bool Stack::isFull() const{
            return size>= maxSize;
        }

        void Stack::push(Ship* shipPtr){
            if(isFull()){
                mof<<"No gonna happen" << std::endl;
                return;
            }
            Node* newNode = new Node();
            newNode->shipPtr =shipPtr;
            newNode->next = top;
            top = newNode;
            size++;
            //cout << "checking " << size  << endl;
            }

        Stack::~Stack(){
            while(!isEmpty()){
                pop();
            }
        }