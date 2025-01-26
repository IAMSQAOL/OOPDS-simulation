#ifndef SIMULATION_H
#define SIMULATION_H

#include "Team.h"
#include "Field.h"
#include <string>
#include <fstream>
#include <iostream>

class Simulation {
public:
    Simulation();
    void readGameFile(const std::string& filename);
    Field field;
    Team team1;
    Team team2;
};

#endif // SIMULATION_H