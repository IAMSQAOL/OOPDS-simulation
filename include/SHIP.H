/**********|**********|**********|
Program: SHIP.H
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <string>

class Field;
class LinkedList;
class Queue;
class Stack;

class Ship {
public:
    bool CanMove;
    char Team_name;
    std::string Ship_name, Ship_type;
    int Ship_lives = 3;
    int Ship_kill_count = 0;
    int posX = -1, posY = -1, nextX = -1, nextY = -1;
    bool Ship_upgrade = false;
    bool ShootPosition = false;
    int record = 0;
    int targetX = -1;
    int targetY = -1;
    bool Ship_die = false;

    Ship();
    virtual ~Ship();

    virtual void actions(Field& field, LinkedList& ships, Queue& DESships, Stack& uS) = 0;
    static Ship* createShip(const char& Team_name, const std::string& Ship_Type, const std::string& Ship_name, Field& field, LinkedList& ships, Queue& DESships, Stack& uS);
    static Ship* updateShip(const char& Team_name, const std::string& Ship_Type, const std::string& Ship_name,const int& posX, const int& posY, Field& field, LinkedList& ships, Queue& DESships, Stack& uS);
};

#endif