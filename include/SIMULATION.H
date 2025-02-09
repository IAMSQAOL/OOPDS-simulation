/**********|**********|**********|
Program: SIMULATION.H
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#ifndef SIMULATION_H
#define SIMULATION_H
#include "../include/QUEUE.H"
#include "../include/LINKEDLIST.H"
#include "../include/FIELD.H"
#include "../include/STACK.H"
#include <iostream>

class Simulation{
    private:
        std::string ignore_line, Ship_Type, Ship_symbol, Ship_Name;
        char Team_Name;
        int ships_count_in_Team, ship_num;

    public:
        int iterations;
        Queue DESships;
        Field field;
        LinkedList ships;
        Stack uS,uS2;
        
        Simulation();


        void StartGame();

        ~Simulation();
};

#endif