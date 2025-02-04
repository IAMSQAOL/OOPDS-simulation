
#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <cstdlib>
#include<ctime>
#include <fstream>
using namespace std;

#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "Field.h"


class Simulation{
    private:
        string ignore_line, Ship_Type, Ship_symbol, Ship_Name;
        char Team_Name;
        int ships_count_in_Team, ship_num;
    public:
        int iterations;
        Queue DESships;
        Field field;
        LinkedList ships;
        Stack uS,uS2;
        ofstream mof;

        Simulation();
        void StartGame();
        ~Simulation();
};
#endif