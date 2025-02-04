#include "../include/Stack.h"

Ship* Stack::pop(){
            if(isEmpty()){
                cout<<"Stack empty dumbass your code suck" << endl;
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
        int size=0;
        const int maxSize=5;

        bool Stack::isEmpty() const{
            return top == nullptr;
        }
        bool Stack::isFull() const{
            return size>= maxSize;
        }

        void Stack::push(Ship* shipPtr, ofstream& mof){
            if(isFull()){
                mof<<"No gonna happen" << endl;
                return;
            }
            Node* newNode = new Node();
            newNode->shipPtr =shipPtr;
            newNode->next = top;
            top = newNode;
            size++;
            //cout << "checking " << size  << endl;
            }

        Ship* Stack::pop(ofstream& mof){
            if(isEmpty()){
                mof<<"Stack empty dumbass your code suck" << endl;
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


        Stack::~Stack(){
            while(!isEmpty()){
                pop();
            }
        }