#ifndef SIMULATION_H
#define SIMULATION_H
#include "QUEUE.H"
#include "LINKEDLIST.H"
#include "FIELD.H"
#include "STACK.H"
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