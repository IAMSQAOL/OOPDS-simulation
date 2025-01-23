#ifndef SPECIFICSHIPS_H
#define SPECIFICSHIPS_H

#include "Ship.h"
#include <iostream>

class Battleship : public MovingShip, public ShootingShip {
public:
    void move() override {
        std::cout << "Battleship is moving" << std::endl;
    }

    void shoot() override {
        std::cout << "Battleship is shooting" << std::endl;
    }
};

class Cruiser : public MovingShip, public SeeingRobot {
public:
    void move() override {
        std::cout << "Cruiser is moving" << std::endl;
    }

    void see() override {
        std::cout << "Cruiser is seeing" << std::endl;
    }
};

class Destroyer : public MovingShip, public RamShip {
public:
    void move() override {
        std::cout << "Destroyer is moving" << std::endl;
    }

    void step() override {
        std::cout << "Destroyer is stepping" << std::endl;
    }
};

class Frigate : public MovingShip, public ShootingShip, public SeeingRobot {
public:
    void move() override {
        std::cout << "Frigate is moving" << std::endl;
    }

    void shoot() override {
        std::cout << "Frigate is shooting" << std::endl;
    }

    void see() override {
        std::cout << "Frigate is seeing" << std::endl;
    }
};

// Define other specific ship types similarly...

#endif // SPECIFICSHIPS_H