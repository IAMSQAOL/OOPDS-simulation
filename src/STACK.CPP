/**********|**********|**********|
Program: STACK.CPP
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#include "../include/STACK.H"
#include <iostream>
#include "../include/OUTPUT.H"

Ship* Stack::pop(){
    if(isEmpty()){
        mof<<"Stack empty" << std::endl;
        std::cout<<"Stack empty" << std::endl;
        return nullptr;
    }
    Node*temp = top;
    Ship* shipPtr = top ->shipPtr;
    top = top->next;
    delete temp;
    size--;
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
        mof<<"Stack Full" << std::endl;
        std::cout<<"Stack Full" << std::endl;
        return;
    }
    //use Dynamic Memory to store pointer of ships
    Node* newNode = new Node();
    newNode->shipPtr =shipPtr;
    newNode->next = top;
    top = newNode;
    size++;
    }

Stack::~Stack(){
    while(!isEmpty()){
        pop();
    }
}