/**********|**********|**********|
Program: STACK.H
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#ifndef STACK_H
#define STACK_H
#include "../include/NODE.H"
#include "../include/SHIP.H"

class Stack{
    protected:
        struct Node{
            Ship* shipPtr;
            Node * next;
        };
        Node* top;
    public:
        int size=0;
        const int maxSize=5;
        Stack();

        bool isEmpty() const;
        bool isFull() const;

        void push(Ship* shipPtr);

        Ship* pop();


        ~Stack();
};

#endif