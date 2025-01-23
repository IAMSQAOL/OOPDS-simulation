#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <iostream>

class Ship {
public:
    virtual ~Ship() = 0; // Pure virtual destructor to make Ship an abstract class
    virtual void display() = 0; // Pure virtual function to display ship details
    static Ship* createShip(const std::string& type); // Factory method to create ships
};

inline Ship::~Ship() {}

class MovingShip : virtual public Ship {
public:
    virtual void move() = 0; // Pure virtual function
};

class ShootingShip : virtual public Ship {
public:
    virtual void shoot() = 0; // Pure virtual function
};

class SeeingRobot : virtual public Ship {
public:
    virtual void see() = 0; // Pure virtual function
};

class RamShip : virtual public Ship {
public:
    virtual void step() = 0; // Pure virtual function
};

class Cruiser : public MovingShip {
public:
    void move() override {
        std::cout << "Cruiser is moving" << std::endl;
    }
    void display() override {
        std::cout << "This is a Cruiser" << std::endl;
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
    void display() override {
        std::cout << "This is a Destroyer" << std::endl;
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
    void display() override {
        std::cout << "This is a Frigate" << std::endl;
    }
};

class Battleship : public MovingShip, public ShootingShip {
public:
    void move() override {
        std::cout << "Battleship is moving" << std::endl;
    }
    void shoot() override {
        std::cout << "Battleship is shooting" << std::endl;
    }
    void display() override {
        std::cout << "This is a Battleship" << std::endl;
    }
};

class Amphibious : public MovingShip {
public:
    void move() override {
        std::cout << "Amphibious is moving" << std::endl;
    }
    void display() override {
        std::cout << "This is an Amphibious Ship" << std::endl;
    }
};

class SuperShip : public MovingShip, public ShootingShip, public SeeingRobot, public RamShip {
public:
    void move() override {
        std::cout << "SuperShip is moving" << std::endl;
    }
    void shoot() override {
        std::cout << "SuperShip is shooting" << std::endl;
    }
    void see() override {
        std::cout << "SuperShip is seeing" << std::endl;
    }
    void step() override {
        std::cout << "SuperShip is stepping" << std::endl;
    }
    void display() override {
        std::cout << "This is a SuperShip" << std::endl;
    }
};

#endif // SHIP_H