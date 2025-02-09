/**********|**********|**********|
Program: LINKEDLIST.H
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include "../include/SHIP.H"
#include "../include/NODE.H"
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